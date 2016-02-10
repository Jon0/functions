#include <iostream>

#include <source/interpreter.h>


int main(int argc, char *argv[]) {
	if (argc > 1) {
		std::string filename = argv[1];
		core::interpreter i(filename);
		i.run();
	}
	return 0;
}
