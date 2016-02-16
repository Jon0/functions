#include <iostream>
#include <vector>

#include <source/function.h>

int main(int argc, char *argv[]) {

	// test conversions
	std::cout << "testing\n";
	core::state_size_t s = 13;
    std::vector<int> base {5, 5, 2};
	std::cout << s << "\n";

	std::vector<int> a = core::to_array(base, s);
    std::cout << a.size() << "\n";
    for (auto i : a) {
        std::cout << i << " : ";
    }
    std::cout << "\n";

    core::state_size_t s2 = core::to_state(base, a);
	std::cout << s2 << "\n";
	return 0;
}
