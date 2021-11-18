# OpenFOAM grammar for Tree-Sitter

> This project is in early phases of development; expect things to change considerably

> DISCLAIMER:
> This offering is not approved or endorsed by OpenCFD Limited, producer and distributor
> of the OpenFOAM software and owner of the OPENFOAM®  and OpenCFD®  trade marks.

This is a generic fail-tolerant parser for OpenFOAM case dictionaries. It does not try
to parse every OpenFOAM IO token correctly; but the goal is to reach a state that is
"good enough" for syntax highlighting and feasible symbols extraction.
