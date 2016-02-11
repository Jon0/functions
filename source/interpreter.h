#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "program.h"

namespace core {


class interpreter {
public:
    interpreter(const std::string &filename);

    void run();

private:
    program prog;
};


}
