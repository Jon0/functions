#include <cstring>
#include <stack>

#include "function.h"

namespace core {


symbol::symbol(state_space::ptr_t value_type)
    :
    value_type(value_type) {}


const state_space::ptr_t symbol::type() const {
    return value_type;
}


state_size symbol::index() const {
    auto t_size = static_cast<long unsigned int>(value_type->bytes());
    int copy_size = std::min(sizeof(state_size), t_size);
    state_size i = 0;
    std::memcpy(&i, state(), copy_size);
    i %= value_type->size();
    return i;
}


std::vector<symbol::ptr_t> symbol::subsymbols() const {
    std::vector<symbol::ptr_t> result;
    for (auto &t : value_type->subtypes()) {
        // todo
    }
    return result;
}

memory::memory(state_space::ptr_t value_type, state_size b)
    :
    symbol(value_type) {
    auto t_size = static_cast<long unsigned int>(value_type->bytes());
    int copy_size = std::min(sizeof(state_size), t_size);
    int size = type()->bytes();
    block = std::make_unique<char[]>(size);
    b %= value_type->size();
    std::memcpy(block.get(), &b, copy_size);
}


memory::memory(state_space::ptr_t value_type, const char *b)
    :
    symbol(value_type) {
    int size = type()->bytes();
    block = std::make_unique<char[]>(size);
    std::memcpy(block.get(), b, size);
}


memory::memory(symbol *a, symbol *b)
    :
    symbol(type_mix(a, b)) {
    block = std::make_unique<char[]>(type()->bytes());
    std::memcpy(&block[0], a->state(), a->type()->bytes());
    std::memcpy(&block[a->type()->bytes()], b->state(), b->type()->bytes());
}


const char *memory::state() const {
    return block.get();
}


const symbol::ptr_t memory::eval(const symbol *in) const {
    int index = 0;
    std::memcpy(&index, in->state(), in->type()->bytes());
    index %= type()->lhs()->size();
    index *= type()->rhs()->bytes();
    return std::make_shared<submemory>(type()->rhs(), &block[index]);
}


submemory::submemory(state_space::ptr_t value_type, const char *mem)
    :
    symbol(value_type),
    block(mem) {
}


const char *submemory::state() const {
    return block;
}


const symbol::ptr_t submemory::eval(const symbol *in) const {
    int index = 0;
    std::memcpy(&index, in->state(), in->type()->bytes());
    index %= type()->lhs()->size();
    index *= type()->rhs()->bytes();
    return std::make_shared<submemory>(type()->rhs(), &block[index]);
}


std::vector<int> to_array(std::vector<int> base, state_size_t state) {
    std::stack<int> sums;
    state_size_t offset = 1;
    for (auto b : base) {
        sums.push(offset);
        offset *= b;
    }

    std::stack<int> components;
    while(!sums.empty()) {
        auto div_val = state / sums.top();
        auto mod_val = state % sums.top();
        state = mod_val;
        components.push(div_val);
        sums.pop();
    }

    std::vector<int> result;
    while(!components.empty()) {
        result.push_back(components.top());
        components.pop();
    }
    return result;
}


state_size_t to_state(std::vector<int> base, std::vector<int> state) {
    state_size_t total = 0;
    state_size_t offset = 1;
    state_size_t index = 0;
    for (auto b : base) {
        total += offset * state.at(index++);
        offset *= b;
    }
    return total;
}


state_space::ptr_t type_mix(symbol *a, symbol *b) {
    std::vector<state_space::ptr_t> types({a->type(), b->type()});
    return std::make_shared<state_multiply>(types);
}



}
