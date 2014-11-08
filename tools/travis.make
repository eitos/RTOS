linter:
	chmod +x check_all.sh
	$$SHELL check_all.sh

tests:
	cd ../tests; make

all: linter tests