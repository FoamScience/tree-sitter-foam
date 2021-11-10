#include <tree_sitter/parser.h>

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 13
#define STATE_COUNT 45
#define LARGE_STATE_COUNT 8
#define SYMBOL_COUNT 39
#define ALIAS_COUNT 0
#define TOKEN_COUNT 22
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 3
#define MAX_ALIAS_SEQUENCE_LENGTH 4
#define PRODUCTION_ID_COUNT 4

enum {
  sym_comment = 1,
  anon_sym_SEMI = 2,
  aux_sym_word_token1 = 3,
  sym_identifier = 4,
  sym_number_literal = 5,
  anon_sym_L_DQUOTE = 6,
  anon_sym_u_DQUOTE = 7,
  anon_sym_U_DQUOTE = 8,
  anon_sym_u8_DQUOTE = 9,
  anon_sym_DQUOTE = 10,
  aux_sym_string_literal_token1 = 11,
  sym_escape_sequence = 12,
  sym_list_head = 13,
  anon_sym_LPAREN = 14,
  anon_sym_RPAREN = 15,
  anon_sym_LBRACK = 16,
  anon_sym_RBRACK = 17,
  sym_prev_scope = 18,
  anon_sym_DOLLAR = 19,
  anon_sym_LBRACE = 20,
  anon_sym_RBRACE = 21,
  sym_source_file = 22,
  sym__statement = 23,
  sym_keyvalue = 24,
  sym_word = 25,
  sym_value = 26,
  sym_basic_value = 27,
  sym_string_literal = 28,
  sym_list_items = 29,
  sym_list = 30,
  sym_dimensions = 31,
  sym_macro = 32,
  sym_dict = 33,
  aux_sym_source_file_repeat1 = 34,
  aux_sym_value_repeat1 = 35,
  aux_sym_string_literal_repeat1 = 36,
  aux_sym_list_items_repeat1 = 37,
  aux_sym_dimensions_repeat1 = 38,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [sym_comment] = "comment",
  [anon_sym_SEMI] = ";",
  [aux_sym_word_token1] = "word_token1",
  [sym_identifier] = "identifier",
  [sym_number_literal] = "number_literal",
  [anon_sym_L_DQUOTE] = "L\"",
  [anon_sym_u_DQUOTE] = "u\"",
  [anon_sym_U_DQUOTE] = "U\"",
  [anon_sym_u8_DQUOTE] = "u8\"",
  [anon_sym_DQUOTE] = "\"",
  [aux_sym_string_literal_token1] = "string_literal_token1",
  [sym_escape_sequence] = "escape_sequence",
  [sym_list_head] = "list_head",
  [anon_sym_LPAREN] = "(",
  [anon_sym_RPAREN] = ")",
  [anon_sym_LBRACK] = "[",
  [anon_sym_RBRACK] = "]",
  [sym_prev_scope] = "prev_scope",
  [anon_sym_DOLLAR] = "$",
  [anon_sym_LBRACE] = "{",
  [anon_sym_RBRACE] = "}",
  [sym_source_file] = "source_file",
  [sym__statement] = "_statement",
  [sym_keyvalue] = "keyvalue",
  [sym_word] = "word",
  [sym_value] = "value",
  [sym_basic_value] = "basic_value",
  [sym_string_literal] = "string_literal",
  [sym_list_items] = "list_items",
  [sym_list] = "list",
  [sym_dimensions] = "dimensions",
  [sym_macro] = "macro",
  [sym_dict] = "dict",
  [aux_sym_source_file_repeat1] = "source_file_repeat1",
  [aux_sym_value_repeat1] = "value_repeat1",
  [aux_sym_string_literal_repeat1] = "string_literal_repeat1",
  [aux_sym_list_items_repeat1] = "list_items_repeat1",
  [aux_sym_dimensions_repeat1] = "dimensions_repeat1",
};

static const TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [sym_comment] = sym_comment,
  [anon_sym_SEMI] = anon_sym_SEMI,
  [aux_sym_word_token1] = aux_sym_word_token1,
  [sym_identifier] = sym_identifier,
  [sym_number_literal] = sym_number_literal,
  [anon_sym_L_DQUOTE] = anon_sym_L_DQUOTE,
  [anon_sym_u_DQUOTE] = anon_sym_u_DQUOTE,
  [anon_sym_U_DQUOTE] = anon_sym_U_DQUOTE,
  [anon_sym_u8_DQUOTE] = anon_sym_u8_DQUOTE,
  [anon_sym_DQUOTE] = anon_sym_DQUOTE,
  [aux_sym_string_literal_token1] = aux_sym_string_literal_token1,
  [sym_escape_sequence] = sym_escape_sequence,
  [sym_list_head] = sym_list_head,
  [anon_sym_LPAREN] = anon_sym_LPAREN,
  [anon_sym_RPAREN] = anon_sym_RPAREN,
  [anon_sym_LBRACK] = anon_sym_LBRACK,
  [anon_sym_RBRACK] = anon_sym_RBRACK,
  [sym_prev_scope] = sym_prev_scope,
  [anon_sym_DOLLAR] = anon_sym_DOLLAR,
  [anon_sym_LBRACE] = anon_sym_LBRACE,
  [anon_sym_RBRACE] = anon_sym_RBRACE,
  [sym_source_file] = sym_source_file,
  [sym__statement] = sym__statement,
  [sym_keyvalue] = sym_keyvalue,
  [sym_word] = sym_word,
  [sym_value] = sym_value,
  [sym_basic_value] = sym_basic_value,
  [sym_string_literal] = sym_string_literal,
  [sym_list_items] = sym_list_items,
  [sym_list] = sym_list,
  [sym_dimensions] = sym_dimensions,
  [sym_macro] = sym_macro,
  [sym_dict] = sym_dict,
  [aux_sym_source_file_repeat1] = aux_sym_source_file_repeat1,
  [aux_sym_value_repeat1] = aux_sym_value_repeat1,
  [aux_sym_string_literal_repeat1] = aux_sym_string_literal_repeat1,
  [aux_sym_list_items_repeat1] = aux_sym_list_items_repeat1,
  [aux_sym_dimensions_repeat1] = aux_sym_dimensions_repeat1,
};

static const TSSymbolMetadata ts_symbol_metadata[] = {
  [ts_builtin_sym_end] = {
    .visible = false,
    .named = true,
  },
  [sym_comment] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_SEMI] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_word_token1] = {
    .visible = false,
    .named = false,
  },
  [sym_identifier] = {
    .visible = true,
    .named = true,
  },
  [sym_number_literal] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_L_DQUOTE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_u_DQUOTE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_U_DQUOTE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_u8_DQUOTE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DQUOTE] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_string_literal_token1] = {
    .visible = false,
    .named = false,
  },
  [sym_escape_sequence] = {
    .visible = true,
    .named = true,
  },
  [sym_list_head] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_LPAREN] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RPAREN] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LBRACK] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RBRACK] = {
    .visible = true,
    .named = false,
  },
  [sym_prev_scope] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_DOLLAR] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LBRACE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RBRACE] = {
    .visible = true,
    .named = false,
  },
  [sym_source_file] = {
    .visible = true,
    .named = true,
  },
  [sym__statement] = {
    .visible = false,
    .named = true,
  },
  [sym_keyvalue] = {
    .visible = true,
    .named = true,
  },
  [sym_word] = {
    .visible = true,
    .named = true,
  },
  [sym_value] = {
    .visible = true,
    .named = true,
  },
  [sym_basic_value] = {
    .visible = true,
    .named = true,
  },
  [sym_string_literal] = {
    .visible = true,
    .named = true,
  },
  [sym_list_items] = {
    .visible = true,
    .named = true,
  },
  [sym_list] = {
    .visible = true,
    .named = true,
  },
  [sym_dimensions] = {
    .visible = true,
    .named = true,
  },
  [sym_macro] = {
    .visible = true,
    .named = true,
  },
  [sym_dict] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_source_file_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_value_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_string_literal_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_list_items_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_dimensions_repeat1] = {
    .visible = false,
    .named = false,
  },
};

enum {
  field_body = 1,
  field_key = 2,
  field_value = 3,
};

static const char * const ts_field_names[] = {
  [0] = NULL,
  [field_body] = "body",
  [field_key] = "key",
  [field_value] = "value",
};

static const TSFieldMapSlice ts_field_map_slices[PRODUCTION_ID_COUNT] = {
  [1] = {.index = 0, .length = 1},
  [2] = {.index = 1, .length = 2},
  [3] = {.index = 3, .length = 2},
};

static const TSFieldMapEntry ts_field_map_entries[] = {
  [0] =
    {field_key, 0},
  [1] =
    {field_key, 0},
    {field_value, 1},
  [3] =
    {field_body, 2},
    {field_key, 0},
};

static const TSSymbol ts_alias_sequences[PRODUCTION_ID_COUNT][MAX_ALIAS_SEQUENCE_LENGTH] = {
  [0] = {0},
};

static const uint16_t ts_non_terminal_alias_map[] = {
  0,
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(36);
      if (lookahead == '"') ADVANCE(66);
      if (lookahead == '$') ADVANCE(79);
      if (lookahead == '(') ADVANCE(73);
      if (lookahead == ')') ADVANCE(74);
      if (lookahead == '.') ADVANCE(78);
      if (lookahead == '/') ADVANCE(6);
      if (lookahead == ';') ADVANCE(40);
      if (lookahead == 'L') ADVANCE(41);
      if (lookahead == 'U') ADVANCE(42);
      if (lookahead == '[') ADVANCE(75);
      if (lookahead == '\\') ADVANCE(20);
      if (lookahead == ']') ADVANCE(76);
      if (lookahead == 'u') ADVANCE(43);
      if (lookahead == '{') ADVANCE(80);
      if (lookahead == '}') ADVANCE(81);
      if (lookahead == '+' ||
          lookahead == '-') ADVANCE(17);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(0)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(49);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(47);
      END_STATE();
    case 1:
      if (lookahead == '\n') SKIP(3)
      if (lookahead == '"') ADVANCE(66);
      if (lookahead == '\\') ADVANCE(20);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(67);
      if (lookahead != 0) ADVANCE(68);
      END_STATE();
    case 2:
      if (lookahead == '"') ADVANCE(66);
      if (lookahead == '$') ADVANCE(79);
      if (lookahead == '(') ADVANCE(73);
      if (lookahead == ')') ADVANCE(74);
      if (lookahead == '.') ADVANCE(22);
      if (lookahead == ';') ADVANCE(40);
      if (lookahead == 'L') ADVANCE(41);
      if (lookahead == 'U') ADVANCE(42);
      if (lookahead == '[') ADVANCE(75);
      if (lookahead == 'u') ADVANCE(43);
      if (lookahead == '{') ADVANCE(80);
      if (lookahead == '+' ||
          lookahead == '-') ADVANCE(17);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(2)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(49);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(47);
      END_STATE();
    case 3:
      if (lookahead == '"') ADVANCE(66);
      if (lookahead == '\\') ADVANCE(20);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(3)
      END_STATE();
    case 4:
      if (lookahead == ')') ADVANCE(53);
      if (lookahead == ',') ADVANCE(32);
      if (lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(4);
      END_STATE();
    case 5:
      if (lookahead == ')') ADVANCE(53);
      if (lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(4);
      END_STATE();
    case 6:
      if (lookahead == '*') ADVANCE(8);
      if (lookahead == '/') ADVANCE(38);
      END_STATE();
    case 7:
      if (lookahead == '*') ADVANCE(7);
      if (lookahead == '/') ADVANCE(37);
      if (lookahead != 0) ADVANCE(8);
      END_STATE();
    case 8:
      if (lookahead == '*') ADVANCE(7);
      if (lookahead != 0) ADVANCE(8);
      END_STATE();
    case 9:
      if (lookahead == ',') ADVANCE(33);
      if (lookahead == '>') ADVANCE(53);
      if (lookahead == 'a') ADVANCE(12);
      if (lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(14);
      END_STATE();
    case 10:
      if (lookahead == ',') ADVANCE(33);
      if (lookahead == '>') ADVANCE(53);
      if (lookahead == 'a') ADVANCE(13);
      if (lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(14);
      END_STATE();
    case 11:
      if (lookahead == ',') ADVANCE(33);
      if (lookahead == '>') ADVANCE(53);
      if (lookahead == 'c') ADVANCE(9);
      if (lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(14);
      END_STATE();
    case 12:
      if (lookahead == ',') ADVANCE(33);
      if (lookahead == '>') ADVANCE(53);
      if (lookahead == 'l') ADVANCE(10);
      if (lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(14);
      END_STATE();
    case 13:
      if (lookahead == ',') ADVANCE(33);
      if (lookahead == '>') ADVANCE(53);
      if (lookahead == 'r') ADVANCE(15);
      if (lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(14);
      END_STATE();
    case 14:
      if (lookahead == ',') ADVANCE(33);
      if (lookahead == '>') ADVANCE(53);
      if (lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(14);
      END_STATE();
    case 15:
      if (lookahead == ',') ADVANCE(33);
      if (lookahead == '>') ADVANCE(72);
      if (lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(14);
      END_STATE();
    case 16:
      if (lookahead == '.') ADVANCE(77);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(16)
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(58);
      END_STATE();
    case 17:
      if (lookahead == '.') ADVANCE(22);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(59);
      END_STATE();
    case 18:
      if (lookahead == '>') ADVANCE(53);
      if (lookahead == 's') ADVANCE(11);
      if (lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(14);
      END_STATE();
    case 19:
      if (lookahead == '>') ADVANCE(53);
      if (lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(14);
      END_STATE();
    case 20:
      if (lookahead == 'U') ADVANCE(31);
      if (lookahead == 'u') ADVANCE(27);
      if (lookahead == 'x') ADVANCE(25);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(71);
      if (lookahead != 0) ADVANCE(69);
      END_STATE();
    case 21:
      if (lookahead == '+' ||
          lookahead == '-') ADVANCE(23);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(61);
      END_STATE();
    case 22:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(60);
      END_STATE();
    case 23:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(61);
      END_STATE();
    case 24:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(69);
      END_STATE();
    case 25:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(24);
      END_STATE();
    case 26:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(25);
      END_STATE();
    case 27:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(26);
      END_STATE();
    case 28:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(27);
      END_STATE();
    case 29:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(28);
      END_STATE();
    case 30:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(29);
      END_STATE();
    case 31:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(30);
      END_STATE();
    case 32:
      if (lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(4);
      END_STATE();
    case 33:
      if (lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(14);
      END_STATE();
    case 34:
      if (lookahead != 0 &&
          lookahead != '\r') ADVANCE(38);
      if (lookahead == '\r') ADVANCE(39);
      END_STATE();
    case 35:
      if (eof) ADVANCE(36);
      if (lookahead == '"') ADVANCE(66);
      if (lookahead == '(') ADVANCE(73);
      if (lookahead == '.') ADVANCE(22);
      if (lookahead == '/') ADVANCE(6);
      if (lookahead == 'L') ADVANCE(54);
      if (lookahead == 'U') ADVANCE(55);
      if (lookahead == ']') ADVANCE(76);
      if (lookahead == 'u') ADVANCE(56);
      if (lookahead == '}') ADVANCE(81);
      if (lookahead == '+' ||
          lookahead == '-') ADVANCE(17);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(35)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(59);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(58);
      END_STATE();
    case 36:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 37:
      ACCEPT_TOKEN(sym_comment);
      END_STATE();
    case 38:
      ACCEPT_TOKEN(sym_comment);
      if (lookahead == '\\') ADVANCE(34);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(38);
      END_STATE();
    case 39:
      ACCEPT_TOKEN(sym_comment);
      if (lookahead != 0 &&
          lookahead != '\\') ADVANCE(38);
      if (lookahead == '\\') ADVANCE(34);
      END_STATE();
    case 40:
      ACCEPT_TOKEN(anon_sym_SEMI);
      END_STATE();
    case 41:
      ACCEPT_TOKEN(aux_sym_word_token1);
      if (lookahead == '"') ADVANCE(62);
      if (lookahead == '(') ADVANCE(5);
      if (lookahead == '<') ADVANCE(19);
      if (lookahead == 'i') ADVANCE(45);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(47);
      END_STATE();
    case 42:
      ACCEPT_TOKEN(aux_sym_word_token1);
      if (lookahead == '"') ADVANCE(64);
      if (lookahead == '(') ADVANCE(5);
      if (lookahead == '<') ADVANCE(19);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(47);
      END_STATE();
    case 43:
      ACCEPT_TOKEN(aux_sym_word_token1);
      if (lookahead == '"') ADVANCE(63);
      if (lookahead == '(') ADVANCE(5);
      if (lookahead == '8') ADVANCE(44);
      if (lookahead == '<') ADVANCE(19);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(47);
      END_STATE();
    case 44:
      ACCEPT_TOKEN(aux_sym_word_token1);
      if (lookahead == '"') ADVANCE(65);
      if (lookahead == '(') ADVANCE(5);
      if (lookahead == '<') ADVANCE(19);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(47);
      END_STATE();
    case 45:
      ACCEPT_TOKEN(aux_sym_word_token1);
      if (lookahead == '(') ADVANCE(5);
      if (lookahead == '<') ADVANCE(19);
      if (lookahead == 's') ADVANCE(46);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(47);
      END_STATE();
    case 46:
      ACCEPT_TOKEN(aux_sym_word_token1);
      if (lookahead == '(') ADVANCE(5);
      if (lookahead == '<') ADVANCE(19);
      if (lookahead == 't') ADVANCE(48);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(47);
      END_STATE();
    case 47:
      ACCEPT_TOKEN(aux_sym_word_token1);
      if (lookahead == '(') ADVANCE(5);
      if (lookahead == '<') ADVANCE(19);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(47);
      END_STATE();
    case 48:
      ACCEPT_TOKEN(aux_sym_word_token1);
      if (lookahead == '(') ADVANCE(5);
      if (lookahead == '<') ADVANCE(18);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(47);
      END_STATE();
    case 49:
      ACCEPT_TOKEN(aux_sym_word_token1);
      if (lookahead == '.') ADVANCE(22);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(50);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(49);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(52);
      END_STATE();
    case 50:
      ACCEPT_TOKEN(aux_sym_word_token1);
      if (lookahead == '+' ||
          lookahead == '-') ADVANCE(23);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(51);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(52);
      END_STATE();
    case 51:
      ACCEPT_TOKEN(aux_sym_word_token1);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(51);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(52);
      END_STATE();
    case 52:
      ACCEPT_TOKEN(aux_sym_word_token1);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(52);
      END_STATE();
    case 53:
      ACCEPT_TOKEN(sym_identifier);
      END_STATE();
    case 54:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '"') ADVANCE(62);
      if (lookahead == '(') ADVANCE(5);
      if (lookahead == '<') ADVANCE(19);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(58);
      END_STATE();
    case 55:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '"') ADVANCE(64);
      if (lookahead == '(') ADVANCE(5);
      if (lookahead == '<') ADVANCE(19);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(58);
      END_STATE();
    case 56:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '"') ADVANCE(63);
      if (lookahead == '(') ADVANCE(5);
      if (lookahead == '8') ADVANCE(57);
      if (lookahead == '<') ADVANCE(19);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(58);
      END_STATE();
    case 57:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '"') ADVANCE(65);
      if (lookahead == '(') ADVANCE(5);
      if (lookahead == '<') ADVANCE(19);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(58);
      END_STATE();
    case 58:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == '(') ADVANCE(5);
      if (lookahead == '<') ADVANCE(19);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(58);
      END_STATE();
    case 59:
      ACCEPT_TOKEN(sym_number_literal);
      if (lookahead == '.') ADVANCE(22);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(21);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(59);
      END_STATE();
    case 60:
      ACCEPT_TOKEN(sym_number_literal);
      if (lookahead == 'E' ||
          lookahead == 'e') ADVANCE(21);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(60);
      END_STATE();
    case 61:
      ACCEPT_TOKEN(sym_number_literal);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(61);
      END_STATE();
    case 62:
      ACCEPT_TOKEN(anon_sym_L_DQUOTE);
      END_STATE();
    case 63:
      ACCEPT_TOKEN(anon_sym_u_DQUOTE);
      END_STATE();
    case 64:
      ACCEPT_TOKEN(anon_sym_U_DQUOTE);
      END_STATE();
    case 65:
      ACCEPT_TOKEN(anon_sym_u8_DQUOTE);
      END_STATE();
    case 66:
      ACCEPT_TOKEN(anon_sym_DQUOTE);
      END_STATE();
    case 67:
      ACCEPT_TOKEN(aux_sym_string_literal_token1);
      if (lookahead == '\t' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(67);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(68);
      END_STATE();
    case 68:
      ACCEPT_TOKEN(aux_sym_string_literal_token1);
      if (lookahead != 0 &&
          lookahead != '\n' &&
          lookahead != '"' &&
          lookahead != '\\') ADVANCE(68);
      END_STATE();
    case 69:
      ACCEPT_TOKEN(sym_escape_sequence);
      END_STATE();
    case 70:
      ACCEPT_TOKEN(sym_escape_sequence);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(69);
      END_STATE();
    case 71:
      ACCEPT_TOKEN(sym_escape_sequence);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(70);
      END_STATE();
    case 72:
      ACCEPT_TOKEN(sym_list_head);
      END_STATE();
    case 73:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      END_STATE();
    case 74:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      END_STATE();
    case 75:
      ACCEPT_TOKEN(anon_sym_LBRACK);
      END_STATE();
    case 76:
      ACCEPT_TOKEN(anon_sym_RBRACK);
      END_STATE();
    case 77:
      ACCEPT_TOKEN(sym_prev_scope);
      if (lookahead == '.') ADVANCE(77);
      END_STATE();
    case 78:
      ACCEPT_TOKEN(sym_prev_scope);
      if (lookahead == '.') ADVANCE(77);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(60);
      END_STATE();
    case 79:
      ACCEPT_TOKEN(anon_sym_DOLLAR);
      END_STATE();
    case 80:
      ACCEPT_TOKEN(anon_sym_LBRACE);
      END_STATE();
    case 81:
      ACCEPT_TOKEN(anon_sym_RBRACE);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 35},
  [2] = {.lex_state = 2},
  [3] = {.lex_state = 2},
  [4] = {.lex_state = 2},
  [5] = {.lex_state = 2},
  [6] = {.lex_state = 2},
  [7] = {.lex_state = 2},
  [8] = {.lex_state = 2},
  [9] = {.lex_state = 2},
  [10] = {.lex_state = 2},
  [11] = {.lex_state = 2},
  [12] = {.lex_state = 2},
  [13] = {.lex_state = 2},
  [14] = {.lex_state = 2},
  [15] = {.lex_state = 2},
  [16] = {.lex_state = 2},
  [17] = {.lex_state = 2},
  [18] = {.lex_state = 2},
  [19] = {.lex_state = 2},
  [20] = {.lex_state = 2},
  [21] = {.lex_state = 2},
  [22] = {.lex_state = 2},
  [23] = {.lex_state = 35},
  [24] = {.lex_state = 2},
  [25] = {.lex_state = 2},
  [26] = {.lex_state = 35},
  [27] = {.lex_state = 2},
  [28] = {.lex_state = 35},
  [29] = {.lex_state = 35},
  [30] = {.lex_state = 35},
  [31] = {.lex_state = 35},
  [32] = {.lex_state = 35},
  [33] = {.lex_state = 1},
  [34] = {.lex_state = 1},
  [35] = {.lex_state = 1},
  [36] = {.lex_state = 35},
  [37] = {.lex_state = 35},
  [38] = {.lex_state = 35},
  [39] = {.lex_state = 35},
  [40] = {.lex_state = 0},
  [41] = {.lex_state = 16},
  [42] = {.lex_state = 16},
  [43] = {.lex_state = 0},
  [44] = {.lex_state = 0},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [sym_comment] = ACTIONS(1),
    [anon_sym_SEMI] = ACTIONS(1),
    [aux_sym_word_token1] = ACTIONS(1),
    [sym_identifier] = ACTIONS(1),
    [sym_number_literal] = ACTIONS(1),
    [anon_sym_L_DQUOTE] = ACTIONS(1),
    [anon_sym_u_DQUOTE] = ACTIONS(1),
    [anon_sym_U_DQUOTE] = ACTIONS(1),
    [anon_sym_u8_DQUOTE] = ACTIONS(1),
    [anon_sym_DQUOTE] = ACTIONS(1),
    [sym_escape_sequence] = ACTIONS(1),
    [sym_list_head] = ACTIONS(1),
    [anon_sym_LPAREN] = ACTIONS(1),
    [anon_sym_RPAREN] = ACTIONS(1),
    [anon_sym_LBRACK] = ACTIONS(1),
    [anon_sym_RBRACK] = ACTIONS(1),
    [sym_prev_scope] = ACTIONS(1),
    [anon_sym_DOLLAR] = ACTIONS(1),
    [anon_sym_LBRACE] = ACTIONS(1),
    [anon_sym_RBRACE] = ACTIONS(1),
  },
  [1] = {
    [sym_source_file] = STATE(44),
    [sym__statement] = STATE(29),
    [sym_keyvalue] = STATE(29),
    [sym_string_literal] = STATE(2),
    [sym_dict] = STATE(29),
    [aux_sym_source_file_repeat1] = STATE(29),
    [ts_builtin_sym_end] = ACTIONS(3),
    [sym_comment] = ACTIONS(5),
    [sym_identifier] = ACTIONS(7),
    [anon_sym_L_DQUOTE] = ACTIONS(9),
    [anon_sym_u_DQUOTE] = ACTIONS(9),
    [anon_sym_U_DQUOTE] = ACTIONS(9),
    [anon_sym_u8_DQUOTE] = ACTIONS(9),
    [anon_sym_DQUOTE] = ACTIONS(9),
  },
  [2] = {
    [sym_word] = STATE(14),
    [sym_value] = STATE(43),
    [sym_basic_value] = STATE(27),
    [sym_string_literal] = STATE(17),
    [sym_list_items] = STATE(18),
    [sym_list] = STATE(14),
    [sym_dimensions] = STATE(19),
    [sym_macro] = STATE(20),
    [aux_sym_value_repeat1] = STATE(6),
    [aux_sym_word_token1] = ACTIONS(11),
    [sym_identifier] = ACTIONS(13),
    [sym_number_literal] = ACTIONS(15),
    [anon_sym_L_DQUOTE] = ACTIONS(9),
    [anon_sym_u_DQUOTE] = ACTIONS(9),
    [anon_sym_U_DQUOTE] = ACTIONS(9),
    [anon_sym_u8_DQUOTE] = ACTIONS(9),
    [anon_sym_DQUOTE] = ACTIONS(9),
    [sym_list_head] = ACTIONS(17),
    [anon_sym_LPAREN] = ACTIONS(19),
    [anon_sym_LBRACK] = ACTIONS(21),
    [anon_sym_DOLLAR] = ACTIONS(23),
    [anon_sym_LBRACE] = ACTIONS(25),
  },
  [3] = {
    [sym_word] = STATE(14),
    [sym_basic_value] = STATE(3),
    [sym_string_literal] = STATE(17),
    [sym_list_items] = STATE(18),
    [sym_list] = STATE(14),
    [sym_dimensions] = STATE(19),
    [sym_macro] = STATE(20),
    [aux_sym_value_repeat1] = STATE(3),
    [anon_sym_SEMI] = ACTIONS(27),
    [aux_sym_word_token1] = ACTIONS(29),
    [sym_identifier] = ACTIONS(32),
    [sym_number_literal] = ACTIONS(35),
    [anon_sym_L_DQUOTE] = ACTIONS(38),
    [anon_sym_u_DQUOTE] = ACTIONS(38),
    [anon_sym_U_DQUOTE] = ACTIONS(38),
    [anon_sym_u8_DQUOTE] = ACTIONS(38),
    [anon_sym_DQUOTE] = ACTIONS(38),
    [sym_list_head] = ACTIONS(41),
    [anon_sym_LPAREN] = ACTIONS(44),
    [anon_sym_LBRACK] = ACTIONS(47),
    [anon_sym_DOLLAR] = ACTIONS(50),
  },
  [4] = {
    [sym_word] = STATE(14),
    [sym_basic_value] = STATE(5),
    [sym_string_literal] = STATE(17),
    [sym_list_items] = STATE(18),
    [sym_list] = STATE(14),
    [sym_dimensions] = STATE(19),
    [sym_macro] = STATE(20),
    [aux_sym_list_items_repeat1] = STATE(5),
    [aux_sym_word_token1] = ACTIONS(11),
    [sym_identifier] = ACTIONS(13),
    [sym_number_literal] = ACTIONS(15),
    [anon_sym_L_DQUOTE] = ACTIONS(9),
    [anon_sym_u_DQUOTE] = ACTIONS(9),
    [anon_sym_U_DQUOTE] = ACTIONS(9),
    [anon_sym_u8_DQUOTE] = ACTIONS(9),
    [anon_sym_DQUOTE] = ACTIONS(9),
    [sym_list_head] = ACTIONS(17),
    [anon_sym_LPAREN] = ACTIONS(19),
    [anon_sym_RPAREN] = ACTIONS(53),
    [anon_sym_LBRACK] = ACTIONS(21),
    [anon_sym_DOLLAR] = ACTIONS(23),
  },
  [5] = {
    [sym_word] = STATE(14),
    [sym_basic_value] = STATE(5),
    [sym_string_literal] = STATE(17),
    [sym_list_items] = STATE(18),
    [sym_list] = STATE(14),
    [sym_dimensions] = STATE(19),
    [sym_macro] = STATE(20),
    [aux_sym_list_items_repeat1] = STATE(5),
    [aux_sym_word_token1] = ACTIONS(55),
    [sym_identifier] = ACTIONS(58),
    [sym_number_literal] = ACTIONS(61),
    [anon_sym_L_DQUOTE] = ACTIONS(64),
    [anon_sym_u_DQUOTE] = ACTIONS(64),
    [anon_sym_U_DQUOTE] = ACTIONS(64),
    [anon_sym_u8_DQUOTE] = ACTIONS(64),
    [anon_sym_DQUOTE] = ACTIONS(64),
    [sym_list_head] = ACTIONS(67),
    [anon_sym_LPAREN] = ACTIONS(70),
    [anon_sym_RPAREN] = ACTIONS(73),
    [anon_sym_LBRACK] = ACTIONS(75),
    [anon_sym_DOLLAR] = ACTIONS(78),
  },
  [6] = {
    [sym_word] = STATE(14),
    [sym_basic_value] = STATE(3),
    [sym_string_literal] = STATE(17),
    [sym_list_items] = STATE(18),
    [sym_list] = STATE(14),
    [sym_dimensions] = STATE(19),
    [sym_macro] = STATE(20),
    [aux_sym_value_repeat1] = STATE(3),
    [anon_sym_SEMI] = ACTIONS(81),
    [aux_sym_word_token1] = ACTIONS(11),
    [sym_identifier] = ACTIONS(13),
    [sym_number_literal] = ACTIONS(15),
    [anon_sym_L_DQUOTE] = ACTIONS(9),
    [anon_sym_u_DQUOTE] = ACTIONS(9),
    [anon_sym_U_DQUOTE] = ACTIONS(9),
    [anon_sym_u8_DQUOTE] = ACTIONS(9),
    [anon_sym_DQUOTE] = ACTIONS(9),
    [sym_list_head] = ACTIONS(17),
    [anon_sym_LPAREN] = ACTIONS(19),
    [anon_sym_LBRACK] = ACTIONS(21),
    [anon_sym_DOLLAR] = ACTIONS(23),
  },
  [7] = {
    [sym_word] = STATE(14),
    [sym_basic_value] = STATE(4),
    [sym_string_literal] = STATE(17),
    [sym_list_items] = STATE(18),
    [sym_list] = STATE(14),
    [sym_dimensions] = STATE(19),
    [sym_macro] = STATE(20),
    [aux_sym_list_items_repeat1] = STATE(4),
    [aux_sym_word_token1] = ACTIONS(11),
    [sym_identifier] = ACTIONS(13),
    [sym_number_literal] = ACTIONS(15),
    [anon_sym_L_DQUOTE] = ACTIONS(9),
    [anon_sym_u_DQUOTE] = ACTIONS(9),
    [anon_sym_U_DQUOTE] = ACTIONS(9),
    [anon_sym_u8_DQUOTE] = ACTIONS(9),
    [anon_sym_DQUOTE] = ACTIONS(9),
    [sym_list_head] = ACTIONS(17),
    [anon_sym_LPAREN] = ACTIONS(19),
    [anon_sym_LBRACK] = ACTIONS(21),
    [anon_sym_DOLLAR] = ACTIONS(23),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 2,
    ACTIONS(85), 3,
      aux_sym_word_token1,
      sym_identifier,
      sym_number_literal,
    ACTIONS(83), 12,
      anon_sym_SEMI,
      anon_sym_L_DQUOTE,
      anon_sym_u_DQUOTE,
      anon_sym_U_DQUOTE,
      anon_sym_u8_DQUOTE,
      anon_sym_DQUOTE,
      sym_list_head,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
      anon_sym_LBRACK,
      anon_sym_DOLLAR,
      anon_sym_LBRACE,
  [20] = 3,
    STATE(24), 1,
      sym_list_items,
    ACTIONS(89), 3,
      aux_sym_word_token1,
      sym_identifier,
      sym_number_literal,
    ACTIONS(87), 11,
      anon_sym_SEMI,
      anon_sym_L_DQUOTE,
      anon_sym_u_DQUOTE,
      anon_sym_U_DQUOTE,
      anon_sym_u8_DQUOTE,
      anon_sym_DQUOTE,
      sym_list_head,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
      anon_sym_LBRACK,
      anon_sym_DOLLAR,
  [42] = 2,
    ACTIONS(93), 3,
      aux_sym_word_token1,
      sym_identifier,
      sym_number_literal,
    ACTIONS(91), 12,
      anon_sym_SEMI,
      anon_sym_L_DQUOTE,
      anon_sym_u_DQUOTE,
      anon_sym_U_DQUOTE,
      anon_sym_u8_DQUOTE,
      anon_sym_DQUOTE,
      sym_list_head,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
      anon_sym_LBRACK,
      anon_sym_DOLLAR,
      anon_sym_LBRACE,
  [62] = 2,
    ACTIONS(97), 3,
      aux_sym_word_token1,
      sym_identifier,
      sym_number_literal,
    ACTIONS(95), 11,
      anon_sym_SEMI,
      anon_sym_L_DQUOTE,
      anon_sym_u_DQUOTE,
      anon_sym_U_DQUOTE,
      anon_sym_u8_DQUOTE,
      anon_sym_DQUOTE,
      sym_list_head,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
      anon_sym_LBRACK,
      anon_sym_DOLLAR,
  [81] = 2,
    ACTIONS(101), 3,
      aux_sym_word_token1,
      sym_identifier,
      sym_number_literal,
    ACTIONS(99), 11,
      anon_sym_SEMI,
      anon_sym_L_DQUOTE,
      anon_sym_u_DQUOTE,
      anon_sym_U_DQUOTE,
      anon_sym_u8_DQUOTE,
      anon_sym_DQUOTE,
      sym_list_head,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
      anon_sym_LBRACK,
      anon_sym_DOLLAR,
  [100] = 2,
    ACTIONS(105), 3,
      aux_sym_word_token1,
      sym_identifier,
      sym_number_literal,
    ACTIONS(103), 11,
      anon_sym_SEMI,
      anon_sym_L_DQUOTE,
      anon_sym_u_DQUOTE,
      anon_sym_U_DQUOTE,
      anon_sym_u8_DQUOTE,
      anon_sym_DQUOTE,
      sym_list_head,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
      anon_sym_LBRACK,
      anon_sym_DOLLAR,
  [119] = 2,
    ACTIONS(109), 3,
      aux_sym_word_token1,
      sym_identifier,
      sym_number_literal,
    ACTIONS(107), 11,
      anon_sym_SEMI,
      anon_sym_L_DQUOTE,
      anon_sym_u_DQUOTE,
      anon_sym_U_DQUOTE,
      anon_sym_u8_DQUOTE,
      anon_sym_DQUOTE,
      sym_list_head,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
      anon_sym_LBRACK,
      anon_sym_DOLLAR,
  [138] = 2,
    ACTIONS(113), 3,
      aux_sym_word_token1,
      sym_identifier,
      sym_number_literal,
    ACTIONS(111), 11,
      anon_sym_SEMI,
      anon_sym_L_DQUOTE,
      anon_sym_u_DQUOTE,
      anon_sym_U_DQUOTE,
      anon_sym_u8_DQUOTE,
      anon_sym_DQUOTE,
      sym_list_head,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
      anon_sym_LBRACK,
      anon_sym_DOLLAR,
  [157] = 2,
    ACTIONS(117), 3,
      aux_sym_word_token1,
      sym_identifier,
      sym_number_literal,
    ACTIONS(115), 11,
      anon_sym_SEMI,
      anon_sym_L_DQUOTE,
      anon_sym_u_DQUOTE,
      anon_sym_U_DQUOTE,
      anon_sym_u8_DQUOTE,
      anon_sym_DQUOTE,
      sym_list_head,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
      anon_sym_LBRACK,
      anon_sym_DOLLAR,
  [176] = 2,
    ACTIONS(121), 3,
      aux_sym_word_token1,
      sym_identifier,
      sym_number_literal,
    ACTIONS(119), 11,
      anon_sym_SEMI,
      anon_sym_L_DQUOTE,
      anon_sym_u_DQUOTE,
      anon_sym_U_DQUOTE,
      anon_sym_u8_DQUOTE,
      anon_sym_DQUOTE,
      sym_list_head,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
      anon_sym_LBRACK,
      anon_sym_DOLLAR,
  [195] = 2,
    ACTIONS(125), 3,
      aux_sym_word_token1,
      sym_identifier,
      sym_number_literal,
    ACTIONS(123), 11,
      anon_sym_SEMI,
      anon_sym_L_DQUOTE,
      anon_sym_u_DQUOTE,
      anon_sym_U_DQUOTE,
      anon_sym_u8_DQUOTE,
      anon_sym_DQUOTE,
      sym_list_head,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
      anon_sym_LBRACK,
      anon_sym_DOLLAR,
  [214] = 2,
    ACTIONS(89), 3,
      aux_sym_word_token1,
      sym_identifier,
      sym_number_literal,
    ACTIONS(87), 11,
      anon_sym_SEMI,
      anon_sym_L_DQUOTE,
      anon_sym_u_DQUOTE,
      anon_sym_U_DQUOTE,
      anon_sym_u8_DQUOTE,
      anon_sym_DQUOTE,
      sym_list_head,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
      anon_sym_LBRACK,
      anon_sym_DOLLAR,
  [233] = 2,
    ACTIONS(129), 3,
      aux_sym_word_token1,
      sym_identifier,
      sym_number_literal,
    ACTIONS(127), 11,
      anon_sym_SEMI,
      anon_sym_L_DQUOTE,
      anon_sym_u_DQUOTE,
      anon_sym_U_DQUOTE,
      anon_sym_u8_DQUOTE,
      anon_sym_DQUOTE,
      sym_list_head,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
      anon_sym_LBRACK,
      anon_sym_DOLLAR,
  [252] = 2,
    ACTIONS(133), 3,
      aux_sym_word_token1,
      sym_identifier,
      sym_number_literal,
    ACTIONS(131), 11,
      anon_sym_SEMI,
      anon_sym_L_DQUOTE,
      anon_sym_u_DQUOTE,
      anon_sym_U_DQUOTE,
      anon_sym_u8_DQUOTE,
      anon_sym_DQUOTE,
      sym_list_head,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
      anon_sym_LBRACK,
      anon_sym_DOLLAR,
  [271] = 2,
    ACTIONS(137), 3,
      aux_sym_word_token1,
      sym_identifier,
      sym_number_literal,
    ACTIONS(135), 11,
      anon_sym_SEMI,
      anon_sym_L_DQUOTE,
      anon_sym_u_DQUOTE,
      anon_sym_U_DQUOTE,
      anon_sym_u8_DQUOTE,
      anon_sym_DQUOTE,
      sym_list_head,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
      anon_sym_LBRACK,
      anon_sym_DOLLAR,
  [290] = 6,
    ACTIONS(141), 1,
      sym_comment,
    ACTIONS(144), 1,
      sym_identifier,
    STATE(2), 1,
      sym_string_literal,
    ACTIONS(139), 2,
      ts_builtin_sym_end,
      anon_sym_RBRACE,
    STATE(23), 4,
      sym__statement,
      sym_keyvalue,
      sym_dict,
      aux_sym_source_file_repeat1,
    ACTIONS(147), 5,
      anon_sym_L_DQUOTE,
      anon_sym_u_DQUOTE,
      anon_sym_U_DQUOTE,
      anon_sym_u8_DQUOTE,
      anon_sym_DQUOTE,
  [317] = 2,
    ACTIONS(152), 3,
      aux_sym_word_token1,
      sym_identifier,
      sym_number_literal,
    ACTIONS(150), 11,
      anon_sym_SEMI,
      anon_sym_L_DQUOTE,
      anon_sym_u_DQUOTE,
      anon_sym_U_DQUOTE,
      anon_sym_u8_DQUOTE,
      anon_sym_DQUOTE,
      sym_list_head,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
      anon_sym_LBRACK,
      anon_sym_DOLLAR,
  [336] = 2,
    ACTIONS(156), 3,
      aux_sym_word_token1,
      sym_identifier,
      sym_number_literal,
    ACTIONS(154), 11,
      anon_sym_SEMI,
      anon_sym_L_DQUOTE,
      anon_sym_u_DQUOTE,
      anon_sym_U_DQUOTE,
      anon_sym_u8_DQUOTE,
      anon_sym_DQUOTE,
      sym_list_head,
      anon_sym_LPAREN,
      anon_sym_RPAREN,
      anon_sym_LBRACK,
      anon_sym_DOLLAR,
  [355] = 6,
    ACTIONS(7), 1,
      sym_identifier,
    ACTIONS(158), 1,
      sym_comment,
    ACTIONS(160), 1,
      anon_sym_RBRACE,
    STATE(2), 1,
      sym_string_literal,
    STATE(23), 4,
      sym__statement,
      sym_keyvalue,
      sym_dict,
      aux_sym_source_file_repeat1,
    ACTIONS(9), 5,
      anon_sym_L_DQUOTE,
      anon_sym_u_DQUOTE,
      anon_sym_U_DQUOTE,
      anon_sym_u8_DQUOTE,
      anon_sym_DQUOTE,
  [381] = 3,
    ACTIONS(162), 1,
      anon_sym_SEMI,
    ACTIONS(164), 3,
      aux_sym_word_token1,
      sym_identifier,
      sym_number_literal,
    ACTIONS(166), 9,
      anon_sym_L_DQUOTE,
      anon_sym_u_DQUOTE,
      anon_sym_U_DQUOTE,
      anon_sym_u8_DQUOTE,
      anon_sym_DQUOTE,
      sym_list_head,
      anon_sym_LPAREN,
      anon_sym_LBRACK,
      anon_sym_DOLLAR,
  [401] = 6,
    ACTIONS(7), 1,
      sym_identifier,
    ACTIONS(168), 1,
      sym_comment,
    ACTIONS(170), 1,
      anon_sym_RBRACE,
    STATE(2), 1,
      sym_string_literal,
    STATE(26), 4,
      sym__statement,
      sym_keyvalue,
      sym_dict,
      aux_sym_source_file_repeat1,
    ACTIONS(9), 5,
      anon_sym_L_DQUOTE,
      anon_sym_u_DQUOTE,
      anon_sym_U_DQUOTE,
      anon_sym_u8_DQUOTE,
      anon_sym_DQUOTE,
  [427] = 6,
    ACTIONS(7), 1,
      sym_identifier,
    ACTIONS(158), 1,
      sym_comment,
    ACTIONS(172), 1,
      ts_builtin_sym_end,
    STATE(2), 1,
      sym_string_literal,
    STATE(23), 4,
      sym__statement,
      sym_keyvalue,
      sym_dict,
      aux_sym_source_file_repeat1,
    ACTIONS(9), 5,
      anon_sym_L_DQUOTE,
      anon_sym_u_DQUOTE,
      anon_sym_U_DQUOTE,
      anon_sym_u8_DQUOTE,
      anon_sym_DQUOTE,
  [453] = 2,
    ACTIONS(176), 1,
      sym_identifier,
    ACTIONS(174), 8,
      ts_builtin_sym_end,
      sym_comment,
      anon_sym_L_DQUOTE,
      anon_sym_u_DQUOTE,
      anon_sym_U_DQUOTE,
      anon_sym_u8_DQUOTE,
      anon_sym_DQUOTE,
      anon_sym_RBRACE,
  [467] = 2,
    ACTIONS(180), 1,
      sym_identifier,
    ACTIONS(178), 8,
      ts_builtin_sym_end,
      sym_comment,
      anon_sym_L_DQUOTE,
      anon_sym_u_DQUOTE,
      anon_sym_U_DQUOTE,
      anon_sym_u8_DQUOTE,
      anon_sym_DQUOTE,
      anon_sym_RBRACE,
  [481] = 2,
    ACTIONS(184), 1,
      sym_identifier,
    ACTIONS(182), 8,
      ts_builtin_sym_end,
      sym_comment,
      anon_sym_L_DQUOTE,
      anon_sym_u_DQUOTE,
      anon_sym_U_DQUOTE,
      anon_sym_u8_DQUOTE,
      anon_sym_DQUOTE,
      anon_sym_RBRACE,
  [495] = 4,
    ACTIONS(186), 1,
      anon_sym_DQUOTE,
    ACTIONS(188), 1,
      aux_sym_string_literal_token1,
    ACTIONS(190), 1,
      sym_escape_sequence,
    STATE(35), 1,
      aux_sym_string_literal_repeat1,
  [508] = 4,
    ACTIONS(192), 1,
      anon_sym_DQUOTE,
    ACTIONS(194), 1,
      aux_sym_string_literal_token1,
    ACTIONS(196), 1,
      sym_escape_sequence,
    STATE(33), 1,
      aux_sym_string_literal_repeat1,
  [521] = 4,
    ACTIONS(198), 1,
      anon_sym_DQUOTE,
    ACTIONS(200), 1,
      aux_sym_string_literal_token1,
    ACTIONS(203), 1,
      sym_escape_sequence,
    STATE(35), 1,
      aux_sym_string_literal_repeat1,
  [534] = 3,
    ACTIONS(206), 1,
      sym_number_literal,
    ACTIONS(208), 1,
      anon_sym_RBRACK,
    STATE(39), 1,
      aux_sym_dimensions_repeat1,
  [544] = 3,
    ACTIONS(210), 1,
      sym_number_literal,
    ACTIONS(212), 1,
      anon_sym_RBRACK,
    STATE(36), 1,
      aux_sym_dimensions_repeat1,
  [554] = 3,
    ACTIONS(19), 1,
      anon_sym_LPAREN,
    ACTIONS(214), 1,
      sym_number_literal,
    STATE(24), 1,
      sym_list_items,
  [564] = 3,
    ACTIONS(216), 1,
      sym_number_literal,
    ACTIONS(219), 1,
      anon_sym_RBRACK,
    STATE(39), 1,
      aux_sym_dimensions_repeat1,
  [574] = 2,
    ACTIONS(19), 1,
      anon_sym_LPAREN,
    STATE(13), 1,
      sym_list_items,
  [581] = 2,
    ACTIONS(221), 1,
      sym_identifier,
    ACTIONS(223), 1,
      sym_prev_scope,
  [588] = 1,
    ACTIONS(225), 1,
      sym_identifier,
  [592] = 1,
    ACTIONS(227), 1,
      anon_sym_SEMI,
  [596] = 1,
    ACTIONS(229), 1,
      ts_builtin_sym_end,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(8)] = 0,
  [SMALL_STATE(9)] = 20,
  [SMALL_STATE(10)] = 42,
  [SMALL_STATE(11)] = 62,
  [SMALL_STATE(12)] = 81,
  [SMALL_STATE(13)] = 100,
  [SMALL_STATE(14)] = 119,
  [SMALL_STATE(15)] = 138,
  [SMALL_STATE(16)] = 157,
  [SMALL_STATE(17)] = 176,
  [SMALL_STATE(18)] = 195,
  [SMALL_STATE(19)] = 214,
  [SMALL_STATE(20)] = 233,
  [SMALL_STATE(21)] = 252,
  [SMALL_STATE(22)] = 271,
  [SMALL_STATE(23)] = 290,
  [SMALL_STATE(24)] = 317,
  [SMALL_STATE(25)] = 336,
  [SMALL_STATE(26)] = 355,
  [SMALL_STATE(27)] = 381,
  [SMALL_STATE(28)] = 401,
  [SMALL_STATE(29)] = 427,
  [SMALL_STATE(30)] = 453,
  [SMALL_STATE(31)] = 467,
  [SMALL_STATE(32)] = 481,
  [SMALL_STATE(33)] = 495,
  [SMALL_STATE(34)] = 508,
  [SMALL_STATE(35)] = 521,
  [SMALL_STATE(36)] = 534,
  [SMALL_STATE(37)] = 544,
  [SMALL_STATE(38)] = 554,
  [SMALL_STATE(39)] = 564,
  [SMALL_STATE(40)] = 574,
  [SMALL_STATE(41)] = 581,
  [SMALL_STATE(42)] = 588,
  [SMALL_STATE(43)] = 592,
  [SMALL_STATE(44)] = 596,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 0),
  [5] = {.entry = {.count = 1, .reusable = true}}, SHIFT(29),
  [7] = {.entry = {.count = 1, .reusable = false}}, SHIFT(2),
  [9] = {.entry = {.count = 1, .reusable = true}}, SHIFT(34),
  [11] = {.entry = {.count = 1, .reusable = false}}, SHIFT(11),
  [13] = {.entry = {.count = 1, .reusable = false}}, SHIFT(21),
  [15] = {.entry = {.count = 1, .reusable = false}}, SHIFT(9),
  [17] = {.entry = {.count = 1, .reusable = true}}, SHIFT(38),
  [19] = {.entry = {.count = 1, .reusable = true}}, SHIFT(7),
  [21] = {.entry = {.count = 1, .reusable = true}}, SHIFT(37),
  [23] = {.entry = {.count = 1, .reusable = true}}, SHIFT(41),
  [25] = {.entry = {.count = 1, .reusable = true}}, SHIFT(28),
  [27] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_value_repeat1, 2),
  [29] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_value_repeat1, 2), SHIFT_REPEAT(11),
  [32] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_value_repeat1, 2), SHIFT_REPEAT(21),
  [35] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_value_repeat1, 2), SHIFT_REPEAT(9),
  [38] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_value_repeat1, 2), SHIFT_REPEAT(34),
  [41] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_value_repeat1, 2), SHIFT_REPEAT(38),
  [44] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_value_repeat1, 2), SHIFT_REPEAT(7),
  [47] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_value_repeat1, 2), SHIFT_REPEAT(37),
  [50] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_value_repeat1, 2), SHIFT_REPEAT(41),
  [53] = {.entry = {.count = 1, .reusable = true}}, SHIFT(12),
  [55] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_list_items_repeat1, 2), SHIFT_REPEAT(11),
  [58] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_list_items_repeat1, 2), SHIFT_REPEAT(21),
  [61] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_list_items_repeat1, 2), SHIFT_REPEAT(9),
  [64] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_list_items_repeat1, 2), SHIFT_REPEAT(34),
  [67] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_list_items_repeat1, 2), SHIFT_REPEAT(38),
  [70] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_list_items_repeat1, 2), SHIFT_REPEAT(7),
  [73] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_list_items_repeat1, 2),
  [75] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_list_items_repeat1, 2), SHIFT_REPEAT(37),
  [78] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_list_items_repeat1, 2), SHIFT_REPEAT(41),
  [81] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_value, 1, .dynamic_precedence = 1),
  [83] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_string_literal, 2),
  [85] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_string_literal, 2),
  [87] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_basic_value, 1, .dynamic_precedence = 3),
  [89] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_basic_value, 1, .dynamic_precedence = 3),
  [91] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_string_literal, 3),
  [93] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_string_literal, 3),
  [95] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_word, 1, .dynamic_precedence = 10),
  [97] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_word, 1, .dynamic_precedence = 10),
  [99] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_list_items, 3),
  [101] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_list_items, 3),
  [103] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_list, 3),
  [105] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_list, 3),
  [107] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_basic_value, 1, .dynamic_precedence = 1),
  [109] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_basic_value, 1, .dynamic_precedence = 1),
  [111] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_macro, 3),
  [113] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_macro, 3),
  [115] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_macro, 2),
  [117] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_macro, 2),
  [119] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_basic_value, 1, .dynamic_precedence = 2),
  [121] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_basic_value, 1, .dynamic_precedence = 2),
  [123] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_list, 1),
  [125] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_list, 1),
  [127] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_basic_value, 1, .dynamic_precedence = 4),
  [129] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_basic_value, 1, .dynamic_precedence = 4),
  [131] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_basic_value, 1),
  [133] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_basic_value, 1),
  [135] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_dimensions, 2),
  [137] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_dimensions, 2),
  [139] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2),
  [141] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(23),
  [144] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(2),
  [147] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2), SHIFT_REPEAT(34),
  [150] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_list, 2),
  [152] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_list, 2),
  [154] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_dimensions, 3),
  [156] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_dimensions, 3),
  [158] = {.entry = {.count = 1, .reusable = true}}, SHIFT(23),
  [160] = {.entry = {.count = 1, .reusable = true}}, SHIFT(32),
  [162] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_value, 1, .dynamic_precedence = 2),
  [164] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_value_repeat1, 1),
  [166] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_value_repeat1, 1),
  [168] = {.entry = {.count = 1, .reusable = true}}, SHIFT(26),
  [170] = {.entry = {.count = 1, .reusable = true}}, SHIFT(30),
  [172] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 1),
  [174] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_dict, 3, .production_id = 1),
  [176] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_dict, 3, .production_id = 1),
  [178] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_keyvalue, 3, .production_id = 2),
  [180] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_keyvalue, 3, .production_id = 2),
  [182] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_dict, 4, .production_id = 3),
  [184] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_dict, 4, .production_id = 3),
  [186] = {.entry = {.count = 1, .reusable = false}}, SHIFT(10),
  [188] = {.entry = {.count = 1, .reusable = true}}, SHIFT(35),
  [190] = {.entry = {.count = 1, .reusable = false}}, SHIFT(35),
  [192] = {.entry = {.count = 1, .reusable = false}}, SHIFT(8),
  [194] = {.entry = {.count = 1, .reusable = true}}, SHIFT(33),
  [196] = {.entry = {.count = 1, .reusable = false}}, SHIFT(33),
  [198] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_string_literal_repeat1, 2),
  [200] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_string_literal_repeat1, 2), SHIFT_REPEAT(35),
  [203] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_string_literal_repeat1, 2), SHIFT_REPEAT(35),
  [206] = {.entry = {.count = 1, .reusable = true}}, SHIFT(39),
  [208] = {.entry = {.count = 1, .reusable = true}}, SHIFT(25),
  [210] = {.entry = {.count = 1, .reusable = true}}, SHIFT(36),
  [212] = {.entry = {.count = 1, .reusable = true}}, SHIFT(22),
  [214] = {.entry = {.count = 1, .reusable = true}}, SHIFT(40),
  [216] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_dimensions_repeat1, 2), SHIFT_REPEAT(39),
  [219] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_dimensions_repeat1, 2),
  [221] = {.entry = {.count = 1, .reusable = true}}, SHIFT(16),
  [223] = {.entry = {.count = 1, .reusable = true}}, SHIFT(42),
  [225] = {.entry = {.count = 1, .reusable = true}}, SHIFT(15),
  [227] = {.entry = {.count = 1, .reusable = true}}, SHIFT(31),
  [229] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
};

#ifdef __cplusplus
extern "C" {
#endif
#ifdef _WIN32
#define extern __declspec(dllexport)
#endif

extern const TSLanguage *tree_sitter_foam(void) {
  static const TSLanguage language = {
    .version = LANGUAGE_VERSION,
    .symbol_count = SYMBOL_COUNT,
    .alias_count = ALIAS_COUNT,
    .token_count = TOKEN_COUNT,
    .external_token_count = EXTERNAL_TOKEN_COUNT,
    .state_count = STATE_COUNT,
    .large_state_count = LARGE_STATE_COUNT,
    .production_id_count = PRODUCTION_ID_COUNT,
    .field_count = FIELD_COUNT,
    .max_alias_sequence_length = MAX_ALIAS_SEQUENCE_LENGTH,
    .parse_table = &ts_parse_table[0][0],
    .small_parse_table = ts_small_parse_table,
    .small_parse_table_map = ts_small_parse_table_map,
    .parse_actions = ts_parse_actions,
    .symbol_names = ts_symbol_names,
    .field_names = ts_field_names,
    .field_map_slices = ts_field_map_slices,
    .field_map_entries = ts_field_map_entries,
    .symbol_metadata = ts_symbol_metadata,
    .public_symbol_map = ts_symbol_map,
    .alias_map = ts_non_terminal_alias_map,
    .alias_sequences = &ts_alias_sequences[0][0],
    .lex_modes = ts_lex_modes,
    .lex_fn = ts_lex,
  };
  return &language;
}
#ifdef __cplusplus
}
#endif
