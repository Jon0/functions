#include <iostream>

#include <source/parser.h>

int main(int argc, char *argv[]) {
	if (argc > 1) {
		std::string filename = argv[1];
		std::cout << "reading file " << filename << "\n";
		core::read_file(filename);
	}
	return 0;
}
