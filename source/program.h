#pragma once

#include "function.h"

namespace core {


class stream {
public:
    using ptr_t = std::shared_ptr<stream>;

    stream(symbol::ptr_t initial_state, symbol::ptr_t transition);

    void print_state() const;
    void process(symbol::ptr_t input);
    void test_input();

private:
    symbol::ptr_t state;
    symbol::ptr_t function;

};


class program : public type_context {
public:
    program();

    bool has_func(const std::string &name) const;
    stream::ptr_t get_main();
    symbol::ptr_t get_func(const std::string &name);
    stream::ptr_t get_stream(const std::string &name);
    void add_symbol(const std::string &name, symbol::ptr_t s);
    void add_stream(const std::string &name, stream::ptr_t s);

private:
    std::unordered_map<std::string, symbol::ptr_t> symbols;
    std::unordered_map<std::string, stream::ptr_t> streams;

    // queues
    // {position -> data_type}

};


}
