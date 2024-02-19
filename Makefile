CXX=clang++
CXX_FLAGS=-std=c++20 -Iincludes -Wall -Wextra -Werror -O0 -gdwarf-4

exec: bin/exec

bin/exec: ./src/driver.cc
	$(CXX) $(CXX_FLAGS) ./src/driver.cc -o $@

.DEFAULT_GOAL := exec
.PHONY: exec clean

clean:
	rm -rf bin/*