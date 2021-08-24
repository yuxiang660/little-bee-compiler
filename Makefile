PY := python3
PIP := pip3

all: tests

tests:
	@$(PY) -m pytest tests

clean:
	@rm -rf .pytest_cache

.PHONY: tests clean
