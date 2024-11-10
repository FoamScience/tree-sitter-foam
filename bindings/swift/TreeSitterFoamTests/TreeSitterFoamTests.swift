import XCTest
import SwiftTreeSitter
import TreeSitterFoam

final class TreeSitterFoamTests: XCTestCase {
    func testCanLoadGrammar() throws {
        let parser = Parser()
        let language = Language(language: tree_sitter_foam())
        XCTAssertNoThrow(try parser.setLanguage(language),
                         "Error loading Foam grammar")
    }
}
