module.exports = grammar({
  name: 'foam',

  rules: {
    source_file: $ => repeat($._statement),

    // Every statement is either a comment, a dictionary,
    // a key-value pair or a preprocessor directive
    _statement: $ => choice(
        $.comment,
        $.keyvalue,
        $.dict,
        //$.directive,
    ),

    // C-like comments, not as good as using a preprocessor, but does the job just fine
    comment: $ => token(choice(
      seq('//', /(\\(.|\r?\n)|[^\\\n])*/),
      seq(
        '/*',
        /[^*]*\*+([^/*][^*]*\*+)*/,
        '/'
      )
    )),

    // Key-Value pairs
    keyvalue: $ => prec.left(3,seq(
        prec.left(4, field("key", choice($.identifier, $.string_literal))),
        //prec.right(1, field("value",$.valueOrGeneric)),
        field("value", prec.right(3, $.value)),
        ';' 
    )),

    // A word, assign insane precedence value for this thing
    word: $ => prec.dynamic(10,/\w+/),

    // This should match a keyword name if it's not a RegExp
    identifier: $ => token(seq(
        /[a-zA-Z_]\w*/,
        optional(
            choice (
                token.immediate(seq(
                    token.immediate('('), 
                    optional(seq(token.immediate(/[\w\.]+/), repeat(seq(',', token.immediate(/[\w\.]+/))))),
                    token.immediate(')')
                )),
                token.immediate(seq(
                    token.immediate('<'), 
                    optional(seq(token.immediate(/[\w\.]+/), repeat(seq(',', token.immediate(/[\w\.]+/))))),
                    token.immediate('>')
                )),
            ),
    ))),


    // This should match a keyword's value
    value: $ => prec.right(2,choice(
        prec.dynamic(2, $.basic_value),
        prec.dynamic(1, repeat1($.basic_value))
    )),

    // Primitive supported values
    basic_value: $ => prec.left(4,choice(
        prec.dynamic(4, $.macro),
        prec.dynamic(3, $.dimensions),
        prec.dynamic(3, $.number_literal),
        prec.dynamic(2, $.string_literal),
        prec.dynamic(1, $.word),
        prec.dynamic(1, $.list),
        prec.dynamic(0, $.identifier),
    )),

    // Primitive floating number
    number_literal: $ => token(seq(/[+-]?([0-9]*[.])?[0-9]+/, token.immediate(optional(/[eE][-+]?[0-9]+/)))),

    // C-style string
    string_literal: $ => seq(
      choice('L"', 'u"', 'U"', 'u8"', '"'),
      repeat(choice(
        token.immediate(prec(1, /[^\\"\n]+/)),
        $.escape_sequence
      )),
      '"',
    ),
    escape_sequence: $ => token(prec(1, seq(
      '\\',
      choice(
        /[^xuU]/,
        /\d{2,3}/,
        /x[0-9a-fA-F]{2,}/,
        /u[0-9a-fA-F]{4}/,
        /U[0-9a-fA-F]{8}/
      )
    ))),

    // (OpenFOAM) list of value
    // Also supports vector-like notation
    list_head: $ => 'List<scalar>',
    list_items: $ => seq(
      '(',
      prec.left(3,repeat1(choice(
        prec.dynamic(3, $.basic_value),
        //prec.dynamic(2, $.dict),
      ))),
      alias(token(prec(1, ')')), ')')
    ),
    list: $ => seq(optional($.list_head), optional($.number_literal), $.list_items),

    // Dimensions entry
    dimensions: $ => seq(
        '[',
        repeat($.number_literal),
        alias(token(prec(1, ']')), ']')
    ),

    // OpenFOAM macros
    macro: $ => seq(
        '$',
        optional($.prev_scope),
        $.identifier
    ),
    prev_scope: $ => /\.+/,

    // Dictionaries
    dict: $ => seq (
        prec.left(4, field("key", choice($.identifier, $.string_literal))),
        '{',
        field("body", prec.right(3, repeat($._statement))),
        '}'
    ),

    //// Directives
    //directive: $ => seq (
    //    '#',
    //    $.word,
    //    $.filename
    //),
    //filename: $ => choice (
    //    $.string_literal,
    //    /[^\s]+/
    //),
  },
});
