#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "type.h"

namespace core {


/**
 * functions used for transforming input streams
 */
class symbol {
public:
    using ptr_t = std::shared_ptr<symbol>;

    symbol(state_space::ptr_t value_type);
    const state_space::ptr_t type() const;
    state_size index() const;
    std::vector<symbol::ptr_t> subsymbols() const;
    virtual const char *state() const = 0;
    virtual const symbol::ptr_t eval(const symbol *in) const = 0;

private:
    const state_space::ptr_t value_type;

};


class memory : public symbol {
public:

    /**
     * initialise a new block of memory
     */
    memory(state_space::ptr_t value_type, state_size b);
    memory(state_space::ptr_t value_type, const char *b);

    /**
     * combine two types into one
     */
    memory(symbol *a, symbol *b);

    const char *state() const override;
    const symbol::ptr_t eval(const symbol *in) const override;

private:
    std::unique_ptr<char[]> block;

};


class submemory : public symbol {
public:
    submemory(state_space::ptr_t value_type, const char *mem);

    const char *state() const override;
    const symbol::ptr_t eval(const symbol *in) const override;

private:
    const char *block;

};


state_space::ptr_t type_mix(symbol *a, symbol *b);


}
