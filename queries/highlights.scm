;; Comments
(comment) @comment

;; FoamFile dictionary;; highlight all of its keywords
(
    (dict
        key: (identifier) @property
        dict_body: (key_value keyword: (identifier) @type)
    (
        (#match? @property "FoamFile")
        (#match? @type "^(version|format)$")
    )
    )
)
(
    (dict
        key: (identifier) @property
        dict_body: (_) (key_value keyword: (identifier) @type)
    (
        (#match? @property "FoamFile")
        (#match? @type "format")
    )
    )
)

;; FoamFile dictionary;; Highlight class and object names as classes
(
    (key_value
        keyword: (identifier) @type
        value: (identifier) @class
    )
    (#match? @type "class")
)
(
    (key_value
        keyword: (identifier) @type
        value: (identifier) @class
    )
    (#match? @type "object")
)

;; Generic Key-value pairs and dictionary keywords
(key_value
    keyword: (identifier) @function.method
    value: (identifier)* @variable.parameter
)
(dict
    key: (identifier) @function.method
)

;; Macros
(macro
    (prev_scope)* @variable.builtin
    (identifier)* @variable.parameter
)


;; Directives
"#" @attribute
(preproc_call
    directive: (identifier)* @attribute
    argument: (identifier)* @variable.parameter
)
(
    (preproc_call
        argument: (identifier)* @variable.parameter
    ) @attribute
    (#match? @attribute "ifeq")
)
(
    (preproc_call) @attribute
    (#match? @attribute "else")
)
(
    (preproc_call) @attribute
    (#match? @attribute "endif")
)

;; Literal numbers and strings
(number_literal) @number
(string_literal) @string
(escape_sequence) @escape

;; Treat [m^2 s-2] the same as if it was put in numbers format
(dimensions dimension: (identifier) @number)

;; operator-like words
[
    "and"
    "or"
    "uniform"
    "non-uniform"
] @attribute
(boolean) @attribute

;; Punctuation
[
  "("
  ")"
  "["
  "]"
  "{"
  "}"
  "#{"
  "#}"
] @punctuation.bracket

[
  ";"
] @punctuation.delimiter
