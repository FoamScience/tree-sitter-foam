// swift-tools-version:5.3
import PackageDescription

let package = Package(
    name: "TreeSitterFoam",
    products: [
        .library(name: "TreeSitterFoam", targets: ["TreeSitterFoam"]),
    ],
    dependencies: [
        .package(url: "https://github.com/ChimeHQ/SwiftTreeSitter", from: "0.8.0"),
    ],
    targets: [
        .target(
            name: "TreeSitterFoam",
            dependencies: [],
            path: ".",
            sources: [
                "src/parser.c",
                // NOTE: if your language has an external scanner, add it here.
            ],
            resources: [
                .copy("queries")
            ],
            publicHeadersPath: "bindings/swift",
            cSettings: [.headerSearchPath("src")]
        ),
        .testTarget(
            name: "TreeSitterFoamTests",
            dependencies: [
                "SwiftTreeSitter",
                "TreeSitterFoam",
            ],
            path: "bindings/swift/TreeSitterFoamTests"
        )
    ],
    cLanguageStandard: .c11
)
