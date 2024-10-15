#ifndef EDGE_H
#define EDGE_H


#include "Vertex.h"
#include "../Pipe.h"

class Vertex;

class Edge {
private:
    Pipe* info;
    Vertex* src;
    Vertex* dest;
    Edge* reverse = nullptr;
public:
    Edge(Vertex* src, Vertex* dest, Pipe* info);
    [[nodiscard]] Pipe* getPipe();
    [[nodiscard]] Vertex* getSource() const;
    [[nodiscard]] Vertex* getDest() const;
    void setReverse(Edge* edge);
    [[nodiscard]] Edge* getReverse() const;
};

#endif
