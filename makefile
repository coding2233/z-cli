# this is the build file for project 
# it is autogenerated by the xmake build system.
# do not edit by hand.

ifneq ($(VERBOSE),1)
VV=@
endif

CXX=/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang
CU=/usr/bin/clang
CC=/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang
AS=/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang
SC=/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/swift-frontend
MXX=/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang
MM=/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang

SH=/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang++
SCSH=/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/swiftc
AR=/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ar
LD=/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang++
SCLD=/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/swiftc

fanyi-cli_AR=/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ar
fanyi-cli_CXX=/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang
fanyi-cli_CXX=/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang
z-cli_LD=/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang++
z-cli_CXX=/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang
z-cli_CXX=/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang
z-core_AR=/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ar
z-core_CXX=/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang
z-core_CXX=/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang
excel-cli_AR=/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ar
excel-cli_CXX=/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang
excel-cli_CXX=/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang

fanyi-cli_CXXFLAGS=-Qunused-arguments -target arm64-apple-macos15.5 -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX15.5.sdk -std=c++17 -Isrc/core/spdlog-1.15.3/include -Isrc/core/vfspp/include -Isrc/core/vfspp/include/vfspp -Isrc/core/vfspp/vendor/miniz-cpp -Isrc/core/utf8cpp -framework Security -framework CoreFoundation -framework SystemConfiguration
fanyi-cli_CXXFLAGS=-Qunused-arguments -target arm64-apple-macos15.5 -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX15.5.sdk -std=c++17 -Isrc/core/spdlog-1.15.3/include -Isrc/core/vfspp/include -Isrc/core/vfspp/include/vfspp -Isrc/core/vfspp/vendor/miniz-cpp -Isrc/core/utf8cpp -framework Security -framework CoreFoundation -framework SystemConfiguration
fanyi-cli_ARFLAGS=-cr
z-cli_CXXFLAGS=-Qunused-arguments -target arm64-apple-macos15.5 -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX15.5.sdk -std=c++17 -Isrc/core/spdlog-1.15.3/include -Isrc/core/vfspp/include -Isrc/core/vfspp/include/vfspp -Isrc/core/vfspp/vendor/miniz-cpp -Isrc/core/utf8cpp -framework Security -framework CoreFoundation -framework SystemConfiguration
z-cli_CXXFLAGS=-Qunused-arguments -target arm64-apple-macos15.5 -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX15.5.sdk -std=c++17 -Isrc/core/spdlog-1.15.3/include -Isrc/core/vfspp/include -Isrc/core/vfspp/include/vfspp -Isrc/core/vfspp/vendor/miniz-cpp -Isrc/core/utf8cpp -framework Security -framework CoreFoundation -framework SystemConfiguration
z-cli_LDFLAGS=-target arm64-apple-macos15.5 -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX15.5.sdk -lz -Lbuild/macosx/arm64/release -L/Users/wanderer/.xmake/packages/l/libcurl/8.11.0/c6908fb716484af7b42137ccbb48e72a/lib -lexcel-cli -lfanyi-cli -lz-core -lcurl -framework Security -framework CoreFoundation -framework SystemConfiguration
z-core_CXXFLAGS=-Qunused-arguments -target arm64-apple-macos15.5 -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX15.5.sdk -std=c++17 -Isrc/core/spdlog-1.15.3/include -Isrc/core/vfspp/include -Isrc/core/vfspp/include/vfspp -Isrc/core/vfspp/vendor/miniz-cpp -Isrc/core/utf8cpp -framework Security -framework CoreFoundation -framework SystemConfiguration -isystem /Users/wanderer/.xmake/packages/l/libcurl/8.11.0/c6908fb716484af7b42137ccbb48e72a/include
z-core_CXXFLAGS=-Qunused-arguments -target arm64-apple-macos15.5 -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX15.5.sdk -std=c++17 -Isrc/core/spdlog-1.15.3/include -Isrc/core/vfspp/include -Isrc/core/vfspp/include/vfspp -Isrc/core/vfspp/vendor/miniz-cpp -Isrc/core/utf8cpp -framework Security -framework CoreFoundation -framework SystemConfiguration -isystem /Users/wanderer/.xmake/packages/l/libcurl/8.11.0/c6908fb716484af7b42137ccbb48e72a/include
z-core_ARFLAGS=-cr
excel-cli_CXXFLAGS=-Qunused-arguments -target arm64-apple-macos15.5 -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX15.5.sdk -std=c++17 -Isrc/core/spdlog-1.15.3/include -Isrc/core/vfspp/include -Isrc/core/vfspp/include/vfspp -Isrc/core/vfspp/vendor/miniz-cpp -Isrc/core/utf8cpp -framework Security -framework CoreFoundation -framework SystemConfiguration
excel-cli_CXXFLAGS=-Qunused-arguments -target arm64-apple-macos15.5 -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX15.5.sdk -std=c++17 -Isrc/core/spdlog-1.15.3/include -Isrc/core/vfspp/include -Isrc/core/vfspp/include/vfspp -Isrc/core/vfspp/vendor/miniz-cpp -Isrc/core/utf8cpp -framework Security -framework CoreFoundation -framework SystemConfiguration
excel-cli_ARFLAGS=-cr

default:  fanyi-cli z-cli z-core excel-cli

all:  fanyi-cli z-cli z-core excel-cli

.PHONY: default all  fanyi-cli z-cli z-core excel-cli

fanyi-cli: build/macosx/arm64/release/libfanyi-cli.a
build/macosx/arm64/release/libfanyi-cli.a: build/macosx/arm64/release/libz-core.a build/.objs/fanyi-cli/macosx/arm64/release/src/fanyi/fanyi_cli.cpp.o
	@echo linking.release libfanyi-cli.a
	@mkdir -p build/macosx/arm64/release
	$(VV)$(fanyi-cli_AR) $(fanyi-cli_ARFLAGS) build/macosx/arm64/release/libfanyi-cli.a build/.objs/fanyi-cli/macosx/arm64/release/src/fanyi/fanyi_cli.cpp.o

build/.objs/fanyi-cli/macosx/arm64/release/src/fanyi/fanyi_cli.cpp.o: src/fanyi/fanyi_cli.cpp
	@echo compiling.release src/fanyi/fanyi_cli.cpp
	@mkdir -p build/.objs/fanyi-cli/macosx/arm64/release/src/fanyi
	$(VV)$(fanyi-cli_CXX) -c $(fanyi-cli_CXXFLAGS) -o build/.objs/fanyi-cli/macosx/arm64/release/src/fanyi/fanyi_cli.cpp.o src/fanyi/fanyi_cli.cpp

z-cli: build/macosx/arm64/release/z-cli
build/macosx/arm64/release/z-cli: build/macosx/arm64/release/libz-core.a build/macosx/arm64/release/libexcel-cli.a build/macosx/arm64/release/libfanyi-cli.a build/.objs/z-cli/macosx/arm64/release/src/cli_app.cpp.o build/.objs/z-cli/macosx/arm64/release/src/main.cpp.o build/.objs/z-cli/macosx/arm64/release/src/update/update_cli.cpp.o
	@echo linking.release z-cli
	@mkdir -p build/macosx/arm64/release
	$(VV)$(z-cli_LD) -o build/macosx/arm64/release/z-cli build/.objs/z-cli/macosx/arm64/release/src/cli_app.cpp.o build/.objs/z-cli/macosx/arm64/release/src/main.cpp.o build/.objs/z-cli/macosx/arm64/release/src/update/update_cli.cpp.o $(z-cli_LDFLAGS)

build/.objs/z-cli/macosx/arm64/release/src/cli_app.cpp.o: src/cli_app.cpp
	@echo compiling.release src/cli_app.cpp
	@mkdir -p build/.objs/z-cli/macosx/arm64/release/src
	$(VV)$(z-cli_CXX) -c $(z-cli_CXXFLAGS) -o build/.objs/z-cli/macosx/arm64/release/src/cli_app.cpp.o src/cli_app.cpp

build/.objs/z-cli/macosx/arm64/release/src/main.cpp.o: src/main.cpp
	@echo compiling.release src/main.cpp
	@mkdir -p build/.objs/z-cli/macosx/arm64/release/src
	$(VV)$(z-cli_CXX) -c $(z-cli_CXXFLAGS) -o build/.objs/z-cli/macosx/arm64/release/src/main.cpp.o src/main.cpp

build/.objs/z-cli/macosx/arm64/release/src/update/update_cli.cpp.o: src/update/update_cli.cpp
	@echo compiling.release src/update/update_cli.cpp
	@mkdir -p build/.objs/z-cli/macosx/arm64/release/src/update
	$(VV)$(z-cli_CXX) -c $(z-cli_CXXFLAGS) -o build/.objs/z-cli/macosx/arm64/release/src/update/update_cli.cpp.o src/update/update_cli.cpp

z-core: build/macosx/arm64/release/libz-core.a
build/macosx/arm64/release/libz-core.a: build/.objs/z-core/macosx/arm64/release/src/core/cli_core.cpp.o
	@echo linking.release libz-core.a
	@mkdir -p build/macosx/arm64/release
	$(VV)$(z-core_AR) $(z-core_ARFLAGS) build/macosx/arm64/release/libz-core.a build/.objs/z-core/macosx/arm64/release/src/core/cli_core.cpp.o

build/.objs/z-core/macosx/arm64/release/src/core/cli_core.cpp.o: src/core/cli_core.cpp
	@echo compiling.release src/core/cli_core.cpp
	@mkdir -p build/.objs/z-core/macosx/arm64/release/src/core
	$(VV)$(z-core_CXX) -c $(z-core_CXXFLAGS) -o build/.objs/z-core/macosx/arm64/release/src/core/cli_core.cpp.o src/core/cli_core.cpp

excel-cli: build/macosx/arm64/release/libexcel-cli.a
build/macosx/arm64/release/libexcel-cli.a: build/macosx/arm64/release/libz-core.a build/.objs/excel-cli/macosx/arm64/release/src/excel/excel_cli.cpp.o
	@echo linking.release libexcel-cli.a
	@mkdir -p build/macosx/arm64/release
	$(VV)$(excel-cli_AR) $(excel-cli_ARFLAGS) build/macosx/arm64/release/libexcel-cli.a build/.objs/excel-cli/macosx/arm64/release/src/excel/excel_cli.cpp.o

build/.objs/excel-cli/macosx/arm64/release/src/excel/excel_cli.cpp.o: src/excel/excel_cli.cpp
	@echo compiling.release src/excel/excel_cli.cpp
	@mkdir -p build/.objs/excel-cli/macosx/arm64/release/src/excel
	$(VV)$(excel-cli_CXX) -c $(excel-cli_CXXFLAGS) -o build/.objs/excel-cli/macosx/arm64/release/src/excel/excel_cli.cpp.o src/excel/excel_cli.cpp

clean:  clean_fanyi-cli clean_z-cli clean_z-core clean_excel-cli

clean_fanyi-cli:  clean_z-core
	@rm -rf build/macosx/arm64/release/libfanyi-cli.a
	@rm -rf build/macosx/arm64/release/fanyi-cli.dSYM
	@rm -rf build/.objs/fanyi-cli/macosx/arm64/release/src/fanyi/fanyi_cli.cpp.o

clean_z-cli:  clean_z-core clean_excel-cli clean_fanyi-cli
	@rm -rf build/macosx/arm64/release/z-cli
	@rm -rf build/macosx/arm64/release/z-cli.dSYM
	@rm -rf build/.objs/z-cli/macosx/arm64/release/src/cli_app.cpp.o
	@rm -rf build/.objs/z-cli/macosx/arm64/release/src/main.cpp.o
	@rm -rf build/.objs/z-cli/macosx/arm64/release/src/update/update_cli.cpp.o

clean_z-core: 
	@rm -rf build/macosx/arm64/release/libz-core.a
	@rm -rf build/macosx/arm64/release/z-core.dSYM
	@rm -rf build/.objs/z-core/macosx/arm64/release/src/core/cli_core.cpp.o

clean_excel-cli:  clean_z-core
	@rm -rf build/macosx/arm64/release/libexcel-cli.a
	@rm -rf build/macosx/arm64/release/excel-cli.dSYM
	@rm -rf build/.objs/excel-cli/macosx/arm64/release/src/excel/excel_cli.cpp.o

