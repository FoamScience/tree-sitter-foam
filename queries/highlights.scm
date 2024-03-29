;; Comments
(comment) @comment

;; Generic Key-value pairs and dictionary keywords
(key_value
    keyword: (identifier) @function
)
(dict
    key: (identifier) @type
)

;; Macros
(macro
    "$" @conditional
    (prev_scope)* @conditional
    (identifier)* @namespace
)


;; Directives
"#" @conditional
(preproc_call
    directive: (identifier)* @conditional
    argument: (identifier)* @namespace
)
(
    (preproc_call
        argument: (identifier)* @namespace
    ) @conditional
    (#match? @conditional "ifeq")
)

(
    (preproc_call) @conditional
    (#match? @conditional "(else|endif)")
)

;; Literals

(number_literal) @float
(string_literal) @string
(escape_sequence) @escape
(boolean) @boolean

;; Treat [m^2 s^-2] the same as if it was put in numbers format
(dimensions dimension: (identifier) @float)

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
  ";"
] @punctuation

;; Special identifiers

((identifier) @attribute
  (#match? @attribute "^(uniform|non-uniform|and|or)$"))
