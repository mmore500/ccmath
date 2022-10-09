TEST_NAMES += abs
TEST_NAMES += ceil
TEST_NAMES += div
TEST_NAMES += fabs
TEST_NAMES += fdim
TEST_NAMES += floor
TEST_NAMES += fma
TEST_NAMES += fmax
TEST_NAMES += fmin
TEST_NAMES += fpclassify
TEST_NAMES += frexp
TEST_NAMES += ilogb
TEST_NAMES += isfinite
TEST_NAMES += isgreater
TEST_NAMES += isgreaterequal
TEST_NAMES += isinf
TEST_NAMES += isless
TEST_NAMES += islessequal
TEST_NAMES += isnan
TEST_NAMES += isnormal
TEST_NAMES += isunordered
TEST_NAMES += ldexp
TEST_NAMES += logb
TEST_NAMES += modf
TEST_NAMES += round
TEST_NAMES += scalbln
TEST_NAMES += scalbn
TEST_NAMES += sqrt
TEST_NAMES += trunc

TO_ROOT := $(shell git rev-parse --show-cdup)

CXX ?= g++

FLAGS = -I$(TO_ROOT)/include/ -std=c++20

default: test

test-%: %.cpp
	$(CXX) $(FLAGS) $< -o $@.out $$(python3.7-config --ldflags)
	# execute test
	./$@.out

# Test in debug mode without pointer tracker
test: $(addprefix test-, $(TEST_NAMES))
	rm -rf test*.out

clean:
	rm -f *.out
	rm -f *.o
	rm -f *.gcda
	rm -f *.gcno
	rm -f *.info
	rm -f *.gcov
	rm -f ./Coverage*
	rm -rf ./temp
