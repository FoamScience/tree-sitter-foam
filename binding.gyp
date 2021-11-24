{
  "targets": [
    {
      "target_name": "tree_sitter_foam_binding",
      "include_dirs": [
        "<!(node -e \"require('nan')\")",
        "src"
      ],
      "sources": [
        "bindings/node/binding.cc",
        "src/parser.c",
        "src/scanner.cc",
        # If your language uses an external scanner, add it here.
      ],
      "cflags_cc": [
        "--std=c++14",
      ],
      "cflags_ellcc": [
        "--std=c++14",
      ]
    }
  ]
}
