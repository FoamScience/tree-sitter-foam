WEB_TREE_SITTER_FILES=README.md package.json tree-sitter-web.d.ts tree-sitter.js tree-sitter.wasm
TREE_SITTER_VERSION=v0.20.1

# Determine OS and set variables accordingly
OS := $(shell uname 2>/dev/null || echo Unknown)
ifeq ($(OS),Windows_NT)
    RM = del /Q /S
    MKDIR = mkdir
    CP = copy
    DEV_NULL = NUL
    SEP = \\
    SHARED_FLAG = /LD
    LIB_EXT = .lib
    OBJ_EXT = .obj
else
    RM = rm -rf
    MKDIR = mkdir -p
    CP = cp
    DEV_NULL = /dev/null
    SEP = /
    SHARED_FLAG = -shared
    LIB_EXT = .a
    OBJ_EXT = .o
endif

all: node_modules/web-tree-sitter tree-sitter-foam.wasm

# build parser.c
src/parser.c: grammar.js
	npx tree-sitter generate

# build patched version of web-tree-sitter
node_modules/web-tree-sitter:
	@$(RM) tmp$(SEP)tree-sitter
	@git clone                                       \
		-c advice.detachedHead=false --quiet           \
		--depth=1 --branch=$(TREE_SITTER_VERSION)      \
		https://github.com/tree-sitter/tree-sitter.git \
		tmp$(SEP)tree-sitter
	@$(CP) tree-sitter.patch tmp$(SEP)tree-sitter$(SEP)
	@echo $(DEV_NULL)                      \
		&& cd tmp$(SEP)tree-sitter          \
		&& git apply tree-sitter.patch      \
		&& ./script/build-wasm
	@$(MKDIR) node_modules$(SEP)web-tree-sitter
	@$(CP) tmp$(SEP)tree-sitter$(SEP)LICENSE node_modules$(SEP)web-tree-sitter
	@$(CP) $(addprefix tmp$(SEP)tree-sitter$(SEP)lib$(SEP)binding_web$(SEP),$(WEB_TREE_SITTER_FILES)) node_modules$(SEP)web-tree-sitter
	@$(RM) tmp$(SEP)tree-sitter

# build web version of tree-sitter-foam
# NOTE: requires patched version of web-tree-sitter
tree-sitter-foam.wasm: src/parser.c src/scanner.c
	npx tree-sitter build --wasm

CC := cc
OURCFLAGS := -fPIC -g -O0 -I src

clean:
	$(RM) debug$(LIB_EXT) *$(OBJ_EXT) *.a

debug$(LIB_EXT): src/parser.c src/scanner.cc
	$(CC) $(OURCFLAGS) $(CFLAGS) -c -o parser$(OBJ_EXT) src$(SEP)parser.c
	$(CC) $(OURCFLAGS) $(CFLAGS) -c -o scanner$(OBJ_EXT) src$(SEP)scanner.cc
	$(CC) $(OURCFLAGS) $(CFLAGS) $(SHARED_FLAG) -o debug$(LIB_EXT) parser$(OBJ_EXT) scanner$(OBJ_EXT)
	$(RM) $(HOME)$(SEP).cache$(SEP)tree-sitter$(SEP)lib$(SEP)foam$(LIB_EXT)
	$(CP) debug$(LIB_EXT) $(HOME)$(SEP).cache$(SEP)tree-sitter$(SEP)lib$(SEP)foam$(LIB_EXT)
