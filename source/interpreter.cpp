#include <chrono>
#include <iostream>
#include <thread>

#include "interpreter.h"
#include "parser.h"


namespace core {


interpreter::interpreter(const std::string &filename)
    :
    prog(read_file(filename)) {
}


void interpreter::run() {
    stream::ptr_t main = prog.get_main();
    if (main) {
        while (true) {
            main->print_state();
            main->test_input();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    }
    else {
        std::cout << "no main function found\n";
    }
}


}
