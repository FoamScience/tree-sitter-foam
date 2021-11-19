/**
    This was shamelessly stolen from tree-sitter-haskell by @tek
    See https://github.com/tree-sitter/tree-sitter-haskell for more information
**/
#include "tree_sitter/parser.h"
#include <cstdint>
#include <vector>
#include <cstdio>
#include <iostream>
#include <functional>
#include <algorithm>
#include <string>
#include <iterator>

using namespace std;

/**
 * The scanner is abstracted for compositionality as functions of the type:
 *
 * typedef function<Result(State&)> Parser;
 *
 * A simple parser can look like this:
 *
 * Result layout_start_brace(State & state) {
 *   if (next_char(state) == '{') return result::finish(Sym::start);
 *   else return result::cont;
 * }
 *
 * With the provided combinators in `namespace `parser`, this can be rewritten as:
 *
 * Parser layout_start_brace = peek('{')(finish(Sym::start));
 *
 * In the API function `scan`, this parser can be executed:
 *
 * parser::eval(layout_start_brace, state);
 *
 * This will set the `lexer-result_symbol` accordingly and return a bool indicating success.
 *
 * Multiple parsers can be executed in succession with the plus operator:
 *
 * peek('w')(handle_w) + peek('i')(handle_i)
 *
 * If `handle_w` terminates with `result::finish` or `result::fail` instead of `result::cont`, `handle_i` is not
 * executed.
 */

// --------------------------------------------------------------------------------------------------------
// Utilities
// --------------------------------------------------------------------------------------------------------

/**
 * Print input and result information.
 */
bool debug = false;

/**
 * Print the upcoming token after parsing finished.
 * Note: May change parser behaviour.
 */
bool debug_next_token = false;

/**
 * Print to stderr if the `debug` flag is `true`.
 */
struct Log {
  template<class A> void operator()(A msg) { if (debug) cerr << msg << endl; }
} logger;

struct Endl {} nl;

template<class A> Log & operator<<(Log & l, const A & a) {
  if (debug) cerr << a;
  return l;
}

Log & operator<<(Log & l, Endl) {
  if (debug) cerr << endl;
  return l;
}

template<class A, class B> A fst(pair<A, B> p) { return p.first; }

template<class A, class B, class C> function<C(A)> operator*(function<C(B)> f, function<B(A)> g) {
  return [=](A a) { return f(g(a)); };
}

template<class A, class B, class C> function<C(A)> operator*(function<C(B)> f, B (&g)(A)) {
  return [=](A a) { return f(g(a)); };
}

template<class A, class B, class C> function<C(A)> operator*(C (&f)(B), function<B(A)> g) {
  return [=](A a) { return f(g(a)); };
}

template<class A, class B> function<B(A)> const_(B b) { return [=](auto _) { return b; }; }

// --------------------------------------------------------------------------------------------------------
// Symbols
// --------------------------------------------------------------------------------------------------------

namespace syms {

/**
 * This enum is mapped to the `externals` list in the grammar according to how they are ordered (the names are
 * abitrary).
 *
 * When the `scan` function is called, the parameter `syms` contains a bool for each enum attribute indicating whether
 * the parse tree at the current position can accept the corresponding symbol.
 *
 * The attribute `fail` is not part of the parse tree, it is used to indicate that no matching symbol was found.
 *
 * The meanings are:
 *   - identifier: OpenFOAM identifiers (keyword names)
 *   - empty: The empty file
 *   - fail: special indicator of failure
 */
enum Sym: uint16_t {
  identifier,
  empty,
  fail,
};

vector<string> names = {
  "identifier",
  "empty",
};

string name(Sym t) { return t < names.size() ? names[t] : "unknown"; }

/**
 * The parser appears to call `scan` with all symbols declared as valid directly after it encountered an error, so
 * this function is used to detect them.
 */
bool all(const bool *syms) { return std::all_of(syms, syms + empty, [](bool a) { return a; }); }

/**
 * Append a symbol's string representation to the string `s` if it is valid.
 */
void add(string & s, const bool *syms, Sym t) {
  if (syms[t]) {
    if (!s.empty()) s += ",";
    s += name(t);
  }
}

/**
 * Produce a comma-separated string of valid symbols.
 */
string valid(const bool *syms) {
  if (syms::all(syms)) return "all";
  string result = "";
  for (Sym i = identifier; i <= identifier + empty; i = Sym(i + 1)) add(result, syms, i);
  return '"' + result + '"';
}

}

using syms::Sym;

// --------------------------------------------------------------------------------------------------------
// State
// --------------------------------------------------------------------------------------------------------

/**
 * This structure contains the external and internal state.
 *
 * The parser provides the lexer interface and the list of valid symbols.
 *
 * The internal state consists of a stack of indentation widths that is manipulated whenever a layout is started or
 * terminated.
 */
struct State {
  TSLexer *lexer;
  const bool *symbols;
  vector<uint16_t> & indents;
  int marked;
  string marked_by;

  State(TSLexer *l, const bool *vs, vector<uint16_t> & is):
    lexer(l),
    symbols(vs),
    indents(is),
    marked(-1),
    marked_by("")
  {}
};

const string format_indents(State & state) {
  if (state.indents.empty()) return "empty";
  string s;
  for (auto i : state.indents) {
    if (!s.empty()) s += "-";
    s += std::to_string(i);
  }
  return s;
}

ostream & operator<<(ostream & out, State & state) {
  return out << "State { syms = " << syms::valid(state.symbols) <<
    ", indents = " << format_indents(state) <<
    " }";
}

/**
 * These functions provide the basic interface to the lexer.
 * They are not defined as members for easier composition.
 */
namespace state {

bool eof(State & state) { return state.lexer->eof(state.lexer); }

/**
 * The parser's position in the current line.
 */
uint32_t column(State & state) {
  return eof(state) ? 0 : state.lexer->get_column(state.lexer);
}

/**
 * The next character that would be parsed.
 * Does not advance the parser position (consume the character).
 */
uint32_t next_char(State & state) { return state.lexer->lookahead; }

/**
 * Move the parser position one character to the right, treating the consumed character as part of the parsed token.
 */
void advance(State & state) { state.lexer->advance(state.lexer, false); }

/**
 * Move the parser position one character to the right, treating the consumed character as whitespace.
 */
void skip(State & state) { state.lexer->advance(state.lexer, true); }

function<void(State&)> mark(string marked_by) {
  return [=](State & state) {
    if (debug) {
      state.marked = column(state);
      state.marked_by = marked_by;
    }
    state.lexer->mark_end(state.lexer);
  };
}

}

// --------------------------------------------------------------------------------------------------------
// Condition
// --------------------------------------------------------------------------------------------------------

/**
 * A predicate for the next character.
 *
 * With the provided operator overloads, conditions can be logically combined without having to write lambdas for
 * passing along the character.
 */
typedef function<bool(uint32_t)> Peek;

Peek operator&(const Peek & l, const Peek & r) { return [=](uint32_t c) { return l(c) && r(c); }; }
Peek operator|(const Peek & l, const Peek & r) { return [=](uint32_t c) { return l(c) || r(c); }; }
Peek not_(Peek con) { return [=](uint32_t c) { return !con(c); }; }

/**
 * This type abstracts over a boolean predicate of the current state.
 * It is used whenever a condition should guard a nested parser.
 *
 * With the provided operator overloads, conditions can be logically combined without having to write lambdas for
 * passing along the `State`.
 */
typedef function<bool(State&)> Condition;

Condition operator&(const Condition & l, const Condition & r) { return [=](auto s) { return l(s) && r(s); }; }
Condition operator|(const Condition & l, const Condition & r) { return [=](auto s) { return l(s) || r(s); }; }
Condition not_(const Condition & c) { return [=](State & state) { return !c(state); }; }

/**
 * Peeking the next character uses the `State` to access the lexer and returns the predicate success as well as the
 * character itself.
 */
typedef function<pair<bool, uint32_t>(State &)> PeekResult;

/**
 * The set of conditions used in the parser implementation.
 */
namespace cond {

Condition pure(bool c) { return const_<State&>(c); }

Peek eq(uint32_t target) { return [=](uint32_t c) { return target == static_cast<uint32_t>(c); }; }

Peek identifier_char = not_
(
        eq('"') | eq(';') | eq('$')
    |   eq(' ') | eq('{') | eq('}')
    |   eq('\t') | eq('\n') | eq('\0')
    |   eq('\r') | eq('\f') | eq('#')
    |   eq('[') | eq(']')
);

/**
 * Require that the next character matches a predicate, without advancing the parser.
 * Returns the next char as well.
 */
function<std::pair<bool, uint32_t>(State &)> peeks(Peek pred) {
  return [=](State & state) {
    auto c = state::next_char(state);
    auto res = pred(c);
    return std::make_pair(res, c);
  };
}

Condition peek_with(Peek pred) { return fst<bool, uint32_t> * peeks(pred); }

//Condition varid = cond::peek_with(cond::varid_start_char);

/**
 * Require that the next character equals a concrete `c`, without advancing the parser.
 */
Condition peek(uint32_t c) { return fst<bool, uint32_t> * peeks(eq(c)); }

/**
 * Require that the next character matches a predicate, advancing the parser on success, treating the character as
 * whitespace.
 */
PeekResult skip_if(Peek pred) {
  return [=](State & state) {
    auto res = peeks(pred)(state);
    if (res.first) { state::skip(state); }
    return res;
  };
}

/**
 * Like `skip_if`, but only return the bool result.
 */
Condition skips(Peek pred) { return fst<bool, uint32_t> * skip_if(pred); }

/**
 * Require that the next character equals a concrete `c`, advancing the parser on success, treating the character as
 * whitespace.
 */
Condition skip(uint32_t c) { return skips(eq(c)); }

/**
 * Require that the next character matches a predicate, advancing the parser on success.
 */
PeekResult consume_if(Peek pred) {
  return [=](State & state) {
    auto res = peeks(pred)(state);
    if (res.first) { state::advance(state); }
    return res;
  };
}

/**
 * Like `consume_if`, but only return the bool result.
 */
Condition consumes(Peek pred) { return fst<bool, uint32_t> * consume_if(pred); }

/**
 * Require that the next character equals a concrete `c`, advancing the parser on success.
 */
Condition consume(uint32_t c) { return consumes(eq(c)); }

/**
 * Require that the argument string follows the current position, consuming all characters.
 * Note: This leaves characters from a partial match consumed, there is no way to backtrack the parser.
 */
Condition seq(const string & s) {
  return [=](State & state) { return all_of(s.begin(), s.end(), [&](auto a) { return consume(a)(state); }); };
}

function<void(State &)> read_while(Peek pred) {
  return [=](State & state) {
    while (true) {
      if (state::eof(state)) break;
      uint32_t c = state::next_char(state);
      if (!pred(c)) break;
      state::advance(state);
    }
  };
}

function<void(State &)> consume_while(Peek pred) { return read_while(pred); }

// TODO this breaks if the target sequence has a repetition of its prefix
function<void(State &)> consume_until(string target) {
  if (target.empty()) return [=](auto) {};
  uint32_t first = target[0];
  return [=](State & state) {
    Peek check = [&](uint32_t c) {
      if (eq(first)(c)) {
        state::mark("consume_until " + target)(state);
        return !seq(target)(state);
      }
      else return true;
    };
    return read_while(check)(state);
  };
}

function<u32string(State &)> read_string(Peek pred) {
  return [=](State & state) {
    u32string s;
    read_while([&](uint32_t c) {
        auto res = pred(c);
        if (res) s += static_cast<uint32_t>(c);
        return res;
    })(state);
    return s;
  };
}

/**
 * Require that the argument symbol is valid for the current parse tree state.
 */
Condition sym(Sym t) { return [=](State & state) { return state.symbols[t]; }; }

/**
 * Require that the next character is whitespace (space or newline) without advancing the parser.
 */
Condition peekws = [](State & state) { return iswspace(state::next_char(state)); };

/**
 * Require that the next character is end-of-file.
 */
Condition peekeof = peek(0);

/**
 * A token like a varsym can be terminated by whitespace of brackets.
 */
Condition token_end =
  peekeof | peekws | peek(')') | peek(']') | peek('[') | peek('(');

/**
 * Require that the argument string follows the current position and is followed by whitespace.
 * See `seq`
 */
Condition token(const string & s) { return seq(s) & token_end; }

Condition column(uint32_t col) {
  return [=](State & state) { return state::column(state) == col; };
}

/**
 * Require that the parser determined an error in the previous step (see `syms::all`).
 */
bool after_error(State & state) { return syms::all(state.symbols); }

}

// --------------------------------------------------------------------------------------------------------
// Result
// --------------------------------------------------------------------------------------------------------

/**
 * Returned by a parser, indicating whether to continue with the next parser (`finished`) which symbol to select when
 * successful (`sym`).
 *
 * Whether parsing was successful is indicated by which symbol is selected – `Sym::fail` signals failure.
 */
struct Result {
  Sym sym;
  bool finished;
  Result(Sym s, bool f): sym(s), finished(f) {}
};

template<class A> ostream & operator<<(ostream & out, const Result & res) {
  out << "Result { finished = " << res.finished;
  if (res.finished) out << ", " << "result = " << syms::name(res.sym);
  return out << " }";
}

/**
 * Constructors for the continue, failure and success results.
 */
namespace result {

Result cont = Result(Sym::fail, false);
Result finish(Sym t) { return Result(t, true); }
Result fail = finish(Sym::fail);

}

// --------------------------------------------------------------------------------------------------------
// Parser
// --------------------------------------------------------------------------------------------------------

namespace parser {

/**
 * The main function shape for all parser combinators.
 */
typedef function<Result(State&)> Parser;

/**
 * Parsers that depend on the next character.
 */
typedef function<Parser(uint32_t)> CharParser;

/**
 * Convenience alias for a function that attaches conditions to a parser.
 */
typedef function<Parser(Parser)> Modifier;

/**
 * Combinators that manipulate the state without producing a value or parse result.
 */
typedef function<void(State&)> Effect;

/**
 * Monadic bind for `Parser`. (>>=)
 */
template<class A> function<Parser(function<Parser(A)>)> with(A (&fa)(State &)) {
  return [&](function<Parser(A)> f) {
    return [=](State & state) {
      return f(fa(state))(state);
    };
  };
}

template<class A> function<Parser(function<Parser(A)>)> with(function<A(State &)> fa) {
  return [&](function<Parser(A)> f) {
    return [=](State & state) {
      return f(fa(state))(state);
    };
  };
}

/**
 * Variant of `with` that discards the left operand's result. (>>)
 *
 * Semantics are "execute the right parser if the left parser doesn't fail".
 */
Parser operator+(Parser fa, Parser fb) {
  return [=](State & state) {
    auto res = fa(state);
    return res.finished ? res : fb(state);
  };
}

/**
 * Depending on the result of a condition, execute one of the supplied parsers.
 */
Parser either(Condition c, Parser match, Parser nomatch) {
  return [=](State & state) { return c(state) ? match(state) : nomatch(state); };
}

/**
 * Depending on the result of a condition, execute one of the supplied parsers.
 */
Parser either(bool c, Parser match, Parser nomatch) { return either(const_<State &>(c), match, nomatch); }

/**
 * Lazy evaluation for recursion.
 */
Parser lazy(function<Parser()> p) {
  return [=](State & state) { return p()(state); };
}

/**
 * Execute an `Effect`, then continue.
 */
Parser effect(Effect eff) {
  return [=](State & state) {
    eff(state);
    return result::cont;
  };
}

/**
 * Parser that terminates the execution with the successful detection of the given symbol.
 */
Parser finish(const Sym s, string desc) {
  return [=](auto _) {
    logger << "finish: " << desc << nl;
    return result::finish(s);
  };
}

/**
 * Parser that terminates the execution unsuccessfully;
 */
Parser fail = ::const_<State>(result::fail);

CharParser as_char_parser(CharParser p) { return p; }
CharParser as_char_parser(Parser p) { return ::const_<uint32_t>(p); }
CharParser as_char_parser(Result r) { return ::const_<uint32_t>(::const_<State>(r)); }

/**
 * Require a condition to be true for the next parser to be executed.
 *
 * If the condition is false, parsing continues after the skipped parser.
 *
 * This function returns a function, so it is applied with two parameter lists:
 *
 * iff(cond::after_error)(fail)
 */
Modifier iff(Condition c) { return [=](Parser next) { return either(c, next, const_<State>(result::cont)); }; }

/**
 * Require a plain `bool` to be true for the next parser to be executed.
 */
Modifier when(const bool c) { return iff(::const_<State>(c)); }

/**
 * Require the given symbol to be valid for the next parser to be executed.
 */
Modifier sym(const Sym s) { return iff(cond::sym(s)); }

/**
 * Parser that terminates the execution with the successful detection of the given symbol, but only if it is expected.
 */
Parser finish_if_valid(const Sym s, string desc) { return sym(s)(finish(s, desc)); }

/**
 * :: (State -> (bool, uint32_t)) -> (uint32_t -> Parser) -> (uint32_t -> Parser) -> Parser
 *
 * If the predicate is true, pass the character to the `match` parser, otherwise the `nomatch`
 * parser.
 *
 * The template allows passing in `Parser` or `Result` for the `(uint32_t -> Parser)` parameters.
 */
template<class A, class B> Parser either(function<pair<bool, uint32_t>(State &)> con, A match, B nomatch) {
  return [=](State & state) {
    auto res = con(state);
    return res.first ? as_char_parser(match)(res.second)(state) : as_char_parser(nomatch)(res.second)(state);
  };
}

/**
 * :: (uint32_t -> bool) -> (uint32_t -> Parser) -> (uint32_t -> Parser) -> Parser
 *
 * If the predicate for the next character is true, pass the character to the `match` parser, otherwise the `nomatch`
 * parser.
 *
 * The template allows passing in `Parser` or `Result` for the `(uint32_t -> Parser)` parameters.
 */
template<class A, class B> Parser peeks(Peek pred, A match, B nomatch) {
  return either(cond::peeks(pred), match, nomatch);
}

/**
 * :: (uint32_t -> bool) -> Parser -> Parser
 *
 * Specialization for a conditional parser that's executed in the success case.
 */
Modifier peeks(Peek pred) { return [=](Parser next) { return peeks(pred, next, result::cont); }; }

/**
 * Requires the next character to be `c` for the next parser to be executed.
 */
Modifier peek(uint32_t c) { return peeks(cond::eq(c)); }

/**
 * :: (uint32_t -> bool) -> (uint32_t -> Parser) -> Parser
 *
 * If the predicate for the next character is true, advance the lexer and pass the consumed character to the next
 * parser.
 */
function<Parser(CharParser)> consume_if(Peek pred) {
  return [=](const CharParser & next) { return either(cond::consume_if(pred), next, result::cont); };
}

/**
 * Require the next character to be `c` for the next parser to be executed, advancing the lexer in the success case.
 */
Modifier consume(uint32_t c) { return [=](Parser next) { return consume_if(cond::eq(c))(as_char_parser(next)); }; }

/**
 * Consume all characters while the predicate holds.
 */
Parser consume_while(Peek pred) { return effect(cond::consume_while(pred)); }

/**
 * Consume all characters until the given sequence is encountered.
 */
Parser consume_until(string s) { return effect(cond::consume_until(s)); }

/**
 * Advance the lexer.
 */
Parser advance = effect(state::advance);

/**
 * Skip whitespace.
 */
Parser skip_ws = effect([](State & state) { while (cond::peekws(state)) state::skip(state); });

Modifier seq(string s) { return iff(cond::seq(s)); }

/**
 * Require the next characters to be equal to `s` for the next parser to be executed, advancing the lexer as far as the
 * characters match, even if not all of them match.
 */
Modifier token(string s) { return iff(cond::token(s)); }

/**
 * Instruct the lexer that the current position is the end of the potentially detected symbol, causing the next run to
 * be started after this character in the success case.
 *
 * This is useful if the validity of the detected symbol depends on what follows, e.g. in the case of a layout end
 * before a `where` token.
 */
Parser mark(string target) { return effect(state::mark(target)); }

/**
 * If the parser returns `cont`, fail.
 */
Parser or_fail(Parser chk) { return chk + fail; }

/**
 * Require the next character to be whitespace for the next parser to be executed, not advancing the lexer.
 */
Modifier peekws = iff(cond::peekws);

}

// --------------------------------------------------------------------------------------------------------
// Logic
// --------------------------------------------------------------------------------------------------------

/**
 * These parsers constitute the higher-level logic, loosely.
 */
namespace logic {

using namespace parser;

/**
 * End-of-file check.
 *
 * If EOF has been reached, two scenarios are valid:
 *  - The file is empty, in which case the parser is still at the root rule, where `Sym::empty` is valid.
 *  - The file has been parsed successfully (all symbols returned true)
 *
 * If those cases do not apply, parsing fails.
 */
Parser eof = peek(0)(sym(Sym::empty)(finish(Sym::empty, "eof")) + fail);


/**
 * Continuing check for identifier characters; parses identifier tokens
 */
function<Result(State &)> read_while_identifier(Peek pred) {

  return [=](State & state) {
    string s = "";
    int32_t nesting_level = 0;
    uint32_t c = state::next_char(state);

    // skip white space at the beginning if any
    //while (iswspace(c)) {
    //    if (state::eof(state)) break;
    //    state::skip(state);
    //    c = state::next_char(state);
    //}

    while (true) {
      if (state::eof(state)) break;
      c = state::next_char(state);

      // Stop if:
      //   Not an identifier char and nesting level is 0,
      //   or if nesting level falls under 0 (There is an extra ")")
      if (!pred(c) && nesting_level == 0) {
            state::mark("identifier");
            break;
      } else if (c == '(') {
            ++nesting_level;
      } else if (c == ')') {
            --nesting_level;
            if (nesting_level == -1) {
                state::mark("identifier");
                break;
            }
      }
      s += char(c);
      state::advance(state);
    }

    // Protect against empty identifiers and return
    if (s.empty()) {
        return result::fail;
    }
    return Result(Sym::identifier, true);
  };
}


/**
 * The identifier parser; can distingwish ) in identifier name from list symbols
 * so: (one line(12,13)) will parse as list (identifier identifier)
 * the last identifier being "line(12,13)"
 */
Parser identifier = sym(Sym::identifier)(
  read_while_identifier(cond::identifier_char) + 
  parser::finish(Sym::identifier, "Identifier")
);

// Do nothing but check for identifiers
Parser all = identifier;

}

// --------------------------------------------------------------------------------------------------------
// Evaluation
// --------------------------------------------------------------------------------------------------------

namespace eval {

/**
  * Helper that consume_if all characters up to the next whitespace, for debugging after a run.
  *
  * Note: This may break the parser, since not all paths use `mark`.
  */
void debug_lookahead(State & state) {
  string s = "";
  for (;;) {
    if (cond::peekws(state) || cond::peekeof(state)) break;
    else {
      s += state::next_char(state);
      state::advance(state);
    }
  }
  if (!s.empty()) logger("next: " + s);
}

/**
  * The main function of the parsing machinery, executing the parser by passing in the initial state and analyzing the
  * result.
  *
  * If the parser concluded with success, the `result_symbol` attribute of the lexer is set, by which the parsed symbol
  * is communicated to tree-sitter, and `true` is returned, indicating to tree-sitter to use the result.
  *
  * If the parser concluded with failure, no `result_symbol` is set and `false` is returned.
  *
  * If the parser did _not_ conclude, i.e. all steps finished with `cont`, a failure is reported as well.
  *
  * If the `debug_next_token` flag is set, the next token will be printed.
  */
bool eval(logic::Parser chk, State & state) {
  auto result = chk(state);
  if (debug_next_token) debug_lookahead(state);
  if (result.finished && result.sym != Sym::fail) {
    if (debug) {
      auto col =
        state.marked == -1 ?
        to_string(state::column(state)) :
        state.marked_by + "@" + to_string(state.marked);
      logger("result: " + syms::name(result.sym) + ", " + col);
    }
    state.lexer->result_symbol = result.sym;
    return true;
  } else return false;
}

}

// --------------------------------------------------------------------------------------------------------
// API
// --------------------------------------------------------------------------------------------------------

extern "C" {

/**
 * This function allocates the persistent state of the parser that is passed into the other API functions.
 */
void *tree_sitter_foam_external_scanner_create() { return new vector<uint16_t>(); }

/**
 * Main logic entry point.
 * Since the state is a singular vector, it can just be cast and used directly.
 */
bool tree_sitter_foam_external_scanner_scan(void *payload, TSLexer *lexer, const bool *syms) {
  auto *indents = static_cast<vector<uint16_t> *>(payload);
  auto state = State(lexer, syms, *indents);
  logger(state);
  return eval::eval(logic::all, state);
}

/**
 * Copy the current state to another location for later reuse.
 * This is normally more complex, but since this parser's state constists solely of a vector of integers, it can just be
 * copied.
 */
unsigned tree_sitter_foam_external_scanner_serialize(void *payload, char *buffer) {
  auto *state = static_cast<vector<uint16_t> *>(payload);
    copy(state->begin(), state->end(), buffer);
  return state->size();
}

/**
 * Load another parser state into the currently active state.
 * `payload` is the state of the previous parser execution, while `buffer` is the saved state of a different position
 * (e.g. when doing incremental parsing).
 */
void tree_sitter_foam_external_scanner_deserialize(void *payload, char *buffer, unsigned length) {
  auto *state = static_cast<vector<uint16_t> *>(payload);
  state->clear();
  copy(buffer, buffer + length, back_inserter(*state));
}

/**
 * Destroy the state.
 */
void tree_sitter_foam_external_scanner_destroy(void *payload) { delete static_cast<vector<uint16_t> *>(payload); }

}
