CXX=clang++
CXX_FLAGS=-std=c++20 -Iincludes -Wall -Wextra -Werror -O0 -gdwarf-4

exec: bin/exec

#bin/exec: ./src/driver.cc
#	$(CXX) $(CXX_FLAGS) ./src/driver.cc -o $@
bin/exec: src/driver.cc src/rle_image_ppm.cc includes/rle_image_ppm.hpp 
	${CXX} ${CXX_FLAGS} src/driver.cc src/rle_image_ppm.cc -o bin/exec

.DEFAULT_GOAL := exec
.PHONY: exec clean

clean:
	rm -rf bin/*