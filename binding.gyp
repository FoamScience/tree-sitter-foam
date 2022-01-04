{
  "targets": [
    {
      "target_name": "tree_sitter_foam_binding",
      "include_dirs": [
        "<!(node -e \"require('nan')\")",
        "src"
      ],
      "sources": [
        "src/parser.c",
        "bindings/node/binding.cc",
        "src/scanner.cc",
        # If your language uses an external scanner, add it here.
      ],
      "cflags_cc": [
        "-lstdc++", "--std=c++14"
      ],
    }
  ]
}
