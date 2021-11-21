# OpenFOAM grammar for Tree-Sitter

> This project is in early phases of development; expect things to change considerably

> DISCLAIMER:
> This offering is not approved or endorsed by OpenCFD Limited, producer and distributor
> of the OpenFOAM software and owner of the OPENFOAM®  and OpenCFD®  trade marks.

![OpenFOAM dictionary syntax highlighting](syntax-highlighting.png)

This is a generic **fail-tolerant** parser for OpenFOAM case dictionaries.
The goal is to reach a state that is "good enough" for syntax highlighting
and feasible symbols extraction.

## Features

- Semantic understanding of OpenFOAM IO entries (Dictionaries, key-value pairs)
- Basic syntax highlighting (Targeting [nvim-treesitter](https://github.com/nvim-treesitter/nvim-treesitter) mainly)
- Highlighting of C++ code blocks and regular expressions (Also, keywords
  are highlighting using Golang grammar), so if your client does not install
  those grammars automatically, you might have to install them manually
- Scope-awareness is there (Per-dictionary) although not used yet

## Running tests

- Unit tests for both parsing and highlighting are executed with `tree-sitter test`
  (Check the `test` folder)
- `testOFFiles.sh` parses all OpenFOAM dictionaries in a directory
    - Currently, the parser works on almost all OpenFOAM 8 tutorial files
      (Well, two files are faulty from source!)

## Contributing

- Pull requests are welcome!
- And, no I'm not going to support specific keyword highlighting
  (eg. `scalarField` will never be treated in a special way)
