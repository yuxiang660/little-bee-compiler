all: build

build:
	@cmake -S. -Bbuild 
	cmake --build build --verbose

debug:
	@cmake -S. -Bbuild -DCMAKE_BUILD_TYPE=Debug
	cmake --build build --verbose

run:
	@cd ./build && ctest

clean:
	@rm -rf build

cov:
	@rm -rf ./build/cov && mkdir -p ./build/cov
	gcovr -r ./build/src -f $(CURDIR)/src --html-details -o ./build/cov/coverage.html
	firefox ./build/cov/coverage.html

.PHONY: build debug run clean coverage
