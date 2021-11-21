;; Pass code blocks to Cpp highlighter
(code (code_body) @cpp)

;; Pass identifiers to Go highlighter (Cheating I know)
((identifier) @go)

;; Highlight regex syntax inside literal strings
((string_literal) @regex)

