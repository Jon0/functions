#pragma once

#include <vector>

namespace core {


class string {
public:
    string();

    int size() const;
    int length() const;

private:
    std::vector<int> type;
    std::vector<int> value;

};


class node {
public:
     node();

     int eval(int input) const;

 private:
     std::vector<int> edge_map;

};


class graph {
public:
    graph();

    int size() const;

    void reduce();

    int eval(int state, int input) const;

private:
    std::vector<node> nodes;

};


class graph_state {
public:
    graph_state();

private:
    int state;

};

}
