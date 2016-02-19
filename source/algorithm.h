#pragma once

#include <vector>

namespace core {


class string {
public:
    string();

    int length() const;

private:
    std::vector<int> type;
    std::vector<int> value;

};


class node {
public:
     node();
};


class graph {
public:
    graph();

    int size() const;

    void reduce();

private:
    std::vector<node> nodes;

};

}
