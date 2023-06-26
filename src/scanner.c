/**
    This was shamelessly stolen from tree-sitter-foam by @tek
    See https://github.com/tree-sitter/tree-sitter-foam for more information
**/
#include "tree_sitter/parser.h"
#include <assert.h>
//#ifdef DEBUG
//#include <stdint.h>
//#include <stdio.h>
//#endif
#include <string.h>
#include <stdbool.h>
#include <wctype.h>

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

// short circuit
#define SHORT_SCANNER if (res.finished) return res;
#define PEEK state->lexer->lookahead
// Move the parser position one character to the right.
#define S_ADVANCE state->lexer->advance(state->lexer, false)
// Move the parser position one character to the right, treating the consumed character as whitespace.
#define S_SKIP state->lexer->advance(state->lexer, true)
#define SYM(s) (state->symbols[s])

#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define VEC_RESIZE(vec, _cap) \
  (vec)->data = realloc((vec)->data, (_cap) * sizeof((vec)->data[0])); \
  assert((vec)->data != NULL); \
  (vec)->cap = (_cap);

#define VEC_GROW(vec, _cap) if ((vec)->cap < (_cap)) { VEC_RESIZE((vec), (_cap)); }

#define VEC_PUSH(vec, el) \
  if ((vec)->cap == (vec)->len) { VEC_RESIZE((vec), MAX(20, (vec)->len * 2)); } \
  (vec)->data[(vec)->len++] = (el);

#define VEC_POP(vec) (vec)->len--;
  
#define VEC_NEW { .len = 0, .cap = 0, .data = NULL }

#define VEC_BACK(vec) ((vec)->data[(vec)->len - 1])

#define VEC_FREE(vec) { if ((vec)->data != NULL) free((vec)->data); }

// --------------------------------------------------------------------------------------------------------
// Symbols
// --------------------------------------------------------------------------------------------------------

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
typedef enum {
  IDENTIFIER,
  EMPTY,
  FAIL,
} Sym;

/**
 * The parser appears to call `scan` with all symbols declared as valid directly after it encountered an error, so
 * this function is used to detect them.
 */
static bool all_syms(const bool *syms) {
  for (int i = 0; i <= EMPTY; i++) {
    if (!syms[i]) return false;
  }
  return true;
}

/**
 * Append a symbol's string representation to the string `s` if it is valid.
 */
//void add(string & s, const bool *syms, Sym t) {
//  if (syms[t]) {
//    if (!s.empty()) s += ",";
//    s += name(t);
//  }
//}

typedef struct {
  uint32_t len;
  uint32_t cap;
  uint16_t *data;
} indent_vec;

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
typedef struct {
  TSLexer *lexer;
  const bool *symbols;
  indent_vec *indents;
} State;

//State state_new(TSLexer *l, const bool * restrict vs, indent_vec *is) {
//  return (State) {
//    .lexer = l,
//    .symbols = vs,
//    .indents = is,
//  };
//}

/**
 * These functions provide the basic interface to the lexer.
 * They are not defined as members for easier composition.
 */
static bool is_eof(State *state) { return state->lexer->eof(state->lexer); }

/**
 * The parser's position in the current line.
 */
static uint32_t column(State *state) {
  return is_eof(state) ? 0 : state->lexer->get_column(state->lexer);
}

///**
// * The next character that would be parsed.
// * Does not advance the parser position (consume the character).
// */
//uint32_t next_char(State & state) { return state.lexer->lookahead; }
//
///**
// * Move the parser position one character to the right, treating the consumed character as part of the parsed token.
// */
//void advance(State & state) { state.lexer->advance(state.lexer, false); }
//
///**
// * Move the parser position one character to the right, treating the consumed character as whitespace.
// */
//void skip(State & state) { state.lexer->advance(state.lexer, true); }

/**
 * Instruct the lexer that the current position is the end of the potentially detected symbol, causing the next run to
 * be started after this character in the success case.
 *
 * This is useful if the validity of the detected symbol depends on what follows, e.g. in the case of a layout end
 * before a `where` token.
 */

// Only use string literals we actually need
#define MARK(s, nf, state) state->lexer->mark_end(state->lexer);

// --------------------------------------------------------------------------------------------------------
// Condition
// --------------------------------------------------------------------------------------------------------

/**
 * The set of conditions used in the parser implementation.
 */

//static bool varid_start_char(const uint32_t c) { return c == '_' || iswlower(c); }
//static bool varid_char(const uint32_t c) { 
//  switch (c) {
//    case '_':
//    case '\'':
//      return true;
//    default:
//      return iswalnum(c);
//  }
//}
//static bool quoter_char(const uint32_t c) { return varid_char(c) || c == '.'; };

static bool non_identifier_char(const uint32_t c)
{
    switch (c) {
        case '"':
        case '\'':
        case ';':
        case '$':
        case '#':
        case ' ':
        case '{':
        case '}':
        case '[':
        case ']':
        case '\t':
        case '\n':
        case '\0':
        case '\r':
        case '\f':
        case '\v':
            return true;
        default:
            return false;
  }
}

/**
 * Require that the argument string follows the current position, consuming all characters.
 * Note: This leaves characters from a partial match consumed, there is no way to backtrack the parser.
 */
static bool seq(const char * restrict s, State *state) {
  size_t len = strlen(s);
  for (size_t i = 0; i < len; i++) {
    int32_t c = s[i];
    int32_t c2 = PEEK;
    if (c != c2) return false;
    S_ADVANCE;
  }
  return true;
}

// TODO this breaks if the target sequence has a repetition of its prefix
static void consume_until(char *target, State *state) {
  int32_t first = target[0];
  assert(first != 0);
  while (PEEK != 0 && !seq(target, state)) {
    while (PEEK != 0 && PEEK != first) S_ADVANCE;
    // Why mark where the first char matched? Let's just not do this check.
    if (first == PEEK) {
      state->lexer->mark_end(state->lexer);
    }
  }
}

typedef struct {
  uint32_t len;
  uint32_t cap;
  int32_t *data;
} wchar_vec;

static wchar_vec read_string(bool (*cond)(uint32_t), State *state) {
  wchar_vec res = VEC_NEW;
  int32_t c = PEEK;
  while (cond(c)) {
    VEC_PUSH(&res, c);
    S_ADVANCE;
    c = PEEK;
  }
  return res;
}

#define WS_CASES \
  case ' ': \
  case '\f': \
  case '\n': \
  case '\r': \
  case '\t': \
  case '\v'

/**
 * Require that the next character is whitespace (space or newline) without advancing the parser.
 */
static bool isws(uint32_t c) {
  switch (c) {
    WS_CASES: return true;
    default: return false;
  }
}

/**
 * A token like a varsym can be terminated by whitespace of brackets.
 */
static bool token_end(uint32_t c) {
  switch (c) {
    WS_CASES:
    case 0:
    case '(':
    case ')':
    case '[':
    case ']':
      return true;
    default:
      return false;
  }
}

/**
 * Require that the argument string follows the current position and is followed by whitespace.
 * See `seq`
 */
static bool token(const char *restrict s, State *state) { 
  return seq(s, state) && token_end(PEEK);
}

/**
 * Require that the stack of layout indentations is not empty.
 * This is mostly used for safety.
 */
static bool indent_exists(State *state) { return state->indents->len != 0; };

/**
 * Require that the current line's indent is greater or equal than the containing layout's, so the current layout is
 * continued.
 */
static bool keep_layout(uint16_t indent, State *state) {
  return indent_exists(state) && indent >= VEC_BACK(state->indents);
}

/**
 * Require that the current line's indent is equal to the containing layout's, so the line may start a new `decl`.
 */
static bool same_indent(uint32_t indent, State *state) { return indent_exists(state) && indent == VEC_BACK(state->indents); }

/**
 * Require that the current line's indent is smaller than the containing layout's, so the layout may be ended.
 */
static bool smaller_indent(uint32_t indent, State *state) {
  return indent_exists(state) && indent < VEC_BACK(state->indents);
}

static bool indent_lesseq(uint32_t indent, State *state) { return indent_exists(state) && indent <= VEC_BACK(state->indents); }

/**
 * Composite condition examining whether the current layout can be terminated if the line after the position where the
 * scan started begins with a `where`.
 *
 * This is needed because `where` can appear on the same indent as, for example, a `do` statement in a `decl`, while
 * being part of the latter and therefore having to end the `do`'s layout before parsing the `where`.
 *
 * This does only check whether the line begins with a `w`, the entire `where` is consumed by the calling parser below.
 */
//static bool is_newline_where(uint32_t indent, State *state) {
//  return keep_layout(indent, state)
//    && (SYM(SEMICOLON) || SYM(END))
//    && !SYM(WHERE)
//    && PEEK == 'w';
//}

#define NEWLINE_CASES \
  case '\n': \
  case '\r': \
  case '\f'

static bool is_newline(uint32_t c) {
  switch (c) {
    NEWLINE_CASES:
      return true;
    default:
      return false;
  }
}

/**
 * Require that the state has not been initialized after parsing has started.
 *
 * This is necessary to handle a nonexistent `module` declaration.
 */
static bool uninitialized(State *state) { return !indent_exists(state); }

/**
 * Require that the parser determined an error in the previous step (see `all_syms`).
 */
static bool after_error(State *state) { return all_syms(state->symbols); }

// --------------------------------------------------------------------------------------------------------
// Result
// --------------------------------------------------------------------------------------------------------

/**
 * Returned by a parser, indicating whether to continue with the next parser (`finished`) which symbol to select when
 * successful (`sym`).
 *
 * Whether parsing was successful is indicated by which symbol is selected – `FAIL` signals failure.
 */
typedef struct {
  Sym sym;
  bool finished;
} Result;

/**
 * Constructors for the continue, failure and success results.
 */
static Result res_cont = {.sym = FAIL, .finished = false};
static Result res_finish(Sym t) { return (Result) {.sym = t, .finished = true}; }
static Result res_fail = {.sym = FAIL, .finished = true};
static Result res_empty = {.sym = EMPTY, .finished = true};

// --------------------------------------------------------------------------------------------------------
// Parser
// --------------------------------------------------------------------------------------------------------


/**
 * Parser that terminates the execution with the successful detection of the given symbol.
 */
static Result finish(const Sym s, char *restrict desc) {
  //DEBUG_PRINTF("finish: %s\n", desc);
  return res_finish(s);
}

/**
 * Parser that terminates the execution with the successful detection of the given symbol, but only if it is expected.
 */
static Result finish_if_valid(const Sym s, char *restrict desc, State *state) {
  return SYM(s) ? finish(s, desc) : res_cont;
}

/**
 * Add one level of indentation to the stack, caused by starting a layout.
 */
static void push(uint16_t ind, State *state) {
  //DEBUG_PRINTF("push: %d\n", ind);
  VEC_PUSH(state->indents, ind);
}
/**
 * Remove one level of indentation from the stack, caused by the end of a layout.
 */
static void pop(State *state) {
  if (indent_exists(state)) {
    //DEBUG_PRINTF("pop");
    VEC_POP(state->indents);
  }
}

/**
 * Advance the lexer until the following character is neither space nor tab.
 */
static void skipspace(State *state) {
  for (;;) {
    switch (PEEK) {
      case ' ':
      case '\t':
        S_SKIP;
        break;
      default:
        return;
    }
  }
}

// --------------------------------------------------------------------------------------------------------
// Logic
// --------------------------------------------------------------------------------------------------------

/**
 * These parsers constitute the higher-level logic, loosely.
 */

/**
 * End-of-file check.
 *
 * If EOF has been reached, two scenarios are valid:
 *  - The file is empty, in which case the parser is still at the root rule, where `Sym::empty` is valid.
 *  - The file has been parsed successfully (all symbols returned true)
 *
 * If those cases do not apply, parsing fails.
 */
static Result eof(State *state) {
  if (is_eof(state)) {
    if (SYM(EMPTY)) {
      return finish(EMPTY, "eof");
    }
    //Result res = end_or_semicolon("eof", state);
    //SHORT_SCANNER;
    return res_fail;
  }
  return res_cont;
}


/**
 * The identifier parser; can distingwish ) in identifier name from list symbols
 * so: (one line(12,13)) will parse as list (identifier identifier)
 * the last identifier being "line(12,13)"
 */
static Result read_while_identifier(State *state) {
    char s[1024];
    bool finished = false;
    int32_t nesting_level = 0;
    uint32_t c = PEEK;

    // Require that the first char is an identifier char
    //if (state->lexer->eof(state->lexer)) return res_fail;
    if (
        non_identifier_char(c)
        || c == '('
        || c == ')'
        || c == '<'
        || c == '>'
        || c == '-'
    ) {
        return res_fail;
    }
    s[strlen(s)] = (char) c;
    if (strlen(s) == 0) {
        return res_empty;
    }
    //if (state->lexer->eof(state->lexer)) return ;
    //uint32_t c = PEEK;
    //if (non_identifier_char(c)) {
    //    return res_cont;
    //}

    // skip white space at the beginning if any
    //while (iswspace(c)) {
    //    if (state::eof(state)) break;
    //    state::skip(state);
    //    c = state::next_char(state);
    //}

    while (true) {
        if (state->lexer->eof(state->lexer)) break;
        c = PEEK;

        // Stop if:
        //   Not an identifier char and nesting level is 0,
        //   or if nesting level falls under 0 (There is an extra ")")
        if (non_identifier_char(c) && nesting_level == 0) {
            state->lexer->mark_end(state->lexer);
            break;
        } else if (c == '(') {
            ++nesting_level;
        } else if (c == ')') {
            --nesting_level;
            if (nesting_level == -1) {
                state->lexer->mark_end(state->lexer);
                break;
            }
        }
        s[strlen(s)] = (char) c;
        state->lexer->advance(state->lexer, false);
    }

    // Protect against empty identifiers and return
    if (strlen(s) == 0) {
        return res_empty;
    }
    if (SYM(IDENTIFIER)) {
        return res_finish(IDENTIFIER);
    }
    return res_cont;
}


//Parser identifier = sym(Sym::identifier)(
//  read_while_identifier(cond::identifier_char) + 
//  parser::finish(Sym::identifier, "Identifier")
//);

// Do nothing but check for identifiers
static Result scan_all(State *state) {
  return read_while_identifier(state);
}


// --------------------------------------------------------------------------------------------------------
// Evaluation
// --------------------------------------------------------------------------------------------------------

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
static bool eval(Result (*chk)(State *state), State *state) {
  Result result = chk(state);
#ifdef DEBUG_NEXT_TOKEN
  debug_lookahead(state);
#endif
  if (result.finished && result.sym != FAIL) {
    state->lexer->result_symbol = result.sym;
    return true;
  } else return false;
}

// --------------------------------------------------------------------------------------------------------
// API
// --------------------------------------------------------------------------------------------------------

/**
 * This function allocates the persistent state of the parser that is passed into the other API functions.
 */
void *tree_sitter_foam_external_scanner_create() {
  void *res = calloc(sizeof(indent_vec), 1);
  return res;
}

/**
 * Main logic entry point.
 * Since the state is a singular vector, it can just be cast and used directly.
 */
bool tree_sitter_foam_external_scanner_scan(void *payload, TSLexer *lexer, const bool *syms) {
    indent_vec *indents = (indent_vec*) payload;
    State state = { 
        .lexer = lexer, 
        .symbols = syms, 
        .indents = indents
    };
  return eval(scan_all, &state);
}

/**
 * Copy the current state to another location for later reuse.
 * This is normally more complex, but since this parser's state constists solely of a vector of integers, it can just be
 * copied.
 */
unsigned tree_sitter_foam_external_scanner_serialize(void *payload, char *buffer) {
  indent_vec *indents = (indent_vec*) payload;
  unsigned to_copy = sizeof(indents->data[0]) * indents->len;
  assert(to_copy <= TREE_SITTER_SERIALIZATION_BUFFER_SIZE);
  memcpy(buffer, indents->data, to_copy);
  return to_copy;
}

/**
 * Load another parser state into the currently active state.
 * `payload` is the state of the previous parser execution, while `buffer` is the saved state of a different position
 * (e.g. when doing incremental parsing).
 */
void tree_sitter_foam_external_scanner_deserialize(void *payload, char *buffer, unsigned length) {
    indent_vec *indents = (indent_vec*) payload;
    unsigned els = length / sizeof(indents->data[0]);
    if (els > 0) {
      VEC_GROW(indents, els);
      indents->len = els;
      memcpy(indents->data, buffer, length);
    }
}

/**
 * Destroy the state.
 */
void tree_sitter_foam_external_scanner_destroy(void *payload) {
    indent_vec *indents = (indent_vec*) payload;
    VEC_FREE(indents);
}
