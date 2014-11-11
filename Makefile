.PHONY=test check clean

#python cpplint.py  $1

LINTER_PARAMS=--extensions=hpp,cpp,h,c --filter=-legal/copyright,-whitespace/tab,-readability/casting

PHONY+=all test check

all: check test

test :
	make -C tests

check:
	find . -name "*.[hc]pp" | xargs python2 tools/cpplint.py $(LINTER_PARAMS)

clean:
	make -C tests clean


