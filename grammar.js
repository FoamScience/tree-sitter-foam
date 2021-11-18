const IDENTIFIER_CHARS = /[^\x00\x1F\s;"$#{}]*/

module.exports = grammar({
  name: 'foam',

  externals: $ => [
    $.identifier,
  ],

  // Our extras are C's extras
  extras: $ => [
    /\s|\\\r?\n/,
    $.comment,
  ],

  rules: {
    source_file: $ => repeat($._statement),

    //identifier: $ => token(seq(/\w/, IDENTIFIER_CHARS, /(\?|\!)?/)),


    _statement: $ => choice(
        $.key_value,
    ),

    key_value: $ => prec.left(1,seq(
        prec.left(4, field("keyword", choice($.identifier, ))),
        optional(field("value", prec.right(3, $.identifier))),
        ';' 
    )),

    // C-like comments, not as good as using a preprocessor, but does the job just fine
    comment: $ => prec.left(4,token(choice(
      seq('//', /(\\(.|\r?\n)|[^\\\n])*/),
      seq(
        '/*',
        /[^*]*\*+([^/*][^*]*\*+)*/,
        '/'
    )))),
  }
});
