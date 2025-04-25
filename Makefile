CXX=clang++
CXX_FLAGS=-std=c++20 -Iincludes -Wall -Wextra -Werror -O0 -gdwarf-4

exec: bin/exec
tests: bin/tests

#bin/exec: ./src/driver.cc
#	$(CXX) $(CXX_FLAGS) ./src/driver.cc -o $@
bin/exec: src/driver.cc src/rle_image_ppm.cc includes/rle_image_ppm.hpp 
	${CXX} ${CXX_FLAGS} src/driver.cc src/rle_image_ppm.cc -o bin/exec

bin/tests: tests/tests.cc src/rle_image_ppm.cc
	${CXX} ${CXX_FLAGS} tests/tests.cc src/rle_image_ppm.cc -o bin/tests

.DEFAULT_GOAL := exec
.PHONY: exec clean tests

clean:
	rm -rf bin/*