all: build

build:
	@cmake -S. -Bbuild 
	@cmake --build build

run:
	@cd ./build && ctest

clean:
	@rm -rf build

cov:
	@mkdir -p ./build/cov
	@gcovr . -f $(CURDIR)/src --html-details -o ./build/cov/coverage.html
	firefox ./build/cov/coverage.html

.PHONY: build run clean coverage
