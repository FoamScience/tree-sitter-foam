package tree_sitter_foam_test

import (
	"testing"

	tree_sitter "github.com/tree-sitter/go-tree-sitter"
	tree_sitter_foam "github.com/tree-sitter/tree-sitter-foam/bindings/go"
)

func TestCanLoadGrammar(t *testing.T) {
	language := tree_sitter.NewLanguage(tree_sitter_foam.Language())
	if language == nil {
		t.Errorf("Error loading Foam grammar")
	}
}
