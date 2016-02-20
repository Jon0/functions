#include "algorithm.h"

namespace core {


string::string() {

}


int string::size() const {
    int i = 1;
    for (auto t : type) {
        i *= t;
    }
    return i;
}


int string::length() const {
    return value.size();
}


node::node() {

}


int node::eval(int input) const {
    if (edge_map.empty()) {
        return 0;
    }
    return edge_map.at(input % edge_map.size());
}


graph::graph() {

}


int graph::size() const {
    return nodes.size();
}


void graph::reduce() {

}


int graph::eval(int state, int input) const {
    if (nodes.empty()) {
        return 0;
    }
    const node &n = nodes.at(state % nodes.size());
    return n.eval(input);
}


graph_state::graph_state()
    :
    state(0) {
}


}
