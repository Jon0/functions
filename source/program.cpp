#include <iostream>

#include "program.h"

namespace core {


stream::stream(symbol::ptr_t initial_state, symbol::ptr_t transition)
    :
    state(initial_state),
    function(transition) {}


void stream::print_state() const {
    std::cout << "state: " << std::to_string(state->index()) << "\n";
}


void stream::process(symbol::ptr_t input) {
    auto m = std::make_shared<memory>(state.get(), input.get());
    auto r = function->eval(m.get());
    if (state->type() == r->type()) {
        state = r;
    }
}


void stream::test_input() {
    auto random = std::make_shared<memory>(state->type(), rand());
    std::cout << "input: " << std::to_string(random->index()) << "\n";
    process(random);
}


program::program() {}


bool program::has_func(const std::string &name) const {
    return symbols.count(name) > 0;
}


stream::ptr_t program::get_main() {
    return get_stream("main");
}


symbol::ptr_t program::get_func(const std::string &name) {
    if (symbols.count(name) == 0) {
        return nullptr;
    }
    else {
        return symbols.at(name);
    }
}


stream::ptr_t program::get_stream(const std::string &name) {
    if (streams.count(name) == 0) {
        return nullptr;
    }
    else {
        return streams.at(name);
    }
}


void program::add_symbol(const std::string &name, symbol::ptr_t s) {
    symbols.insert(std::make_pair(name, s));
}


void program::add_stream(const std::string &name, stream::ptr_t s) {
    streams.insert(std::make_pair(name, s));
}


state_space::ptr_t type_mix(symbol *a, symbol *b) {
    std::vector<state_space::ptr_t> types({a->type(), b->type()});
    return std::make_shared<state_multiply>(types);
}


}
