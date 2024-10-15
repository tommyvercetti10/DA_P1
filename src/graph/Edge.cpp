#include "Edge.h"

Edge::Edge(Vertex* src, Vertex* dest, Pipe* info) : src(src), dest(dest), info(info){ }

Pipe* Edge::getPipe() {
    return info;
}

Vertex* Edge::getSource() const {
    return src;
}

Vertex* Edge::getDest() const {
    return dest;
}

void Edge::setReverse(Edge* edge) {
    this->reverse = edge;
}

Edge* Edge::getReverse() const {
    return reverse;
}

