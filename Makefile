all: build

build:
	cmake --build build --verbose

release:
	@cmake -S. -Bbuild 
	cmake --build build --verbose

debug:
	@cmake -S. -Bbuild -DCMAKE_BUILD_TYPE=Debug
	cmake --build build --verbose

test:
	@cd ./build && ctest

run:
	@./build/bin/main

clean:
	@rm -rf build

cov:
	@rm -rf ./build/cov && mkdir -p ./build/cov
	gcovr -r ./build/src -f $(CURDIR)/src --html-details -o ./build/cov/coverage.html
	firefox ./build/cov/coverage.html

.PHONY: build debug run test clean coverage
