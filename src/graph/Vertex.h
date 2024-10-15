#ifndef VERTEX_H
#define VERTEX_H

#include <unordered_set>
#include "../WaterFacility.h"
#include "Edge.h"

class Edge;

class Vertex {
private:
    WaterFacility* info;
    int inDegree = 0;
    int maxIncomingFlow = 0;
    int low = 0;
    int num = 0;
    std::unordered_set<Edge*> adj;
    bool visited = false;
    bool processing = false;
    Edge *path = nullptr;
    std::unordered_set<Edge*> incoming;
public:
    explicit Vertex(WaterFacility* waterFacility);
    [[nodiscard]] WaterFacility* getInfo() const;
    void setVisited(const bool& flag);
    void setProcessing(const bool& flag);
    void setPath(Edge* path);
    Edge* getPath() const;
    void addIncomingEdge(Edge* edge);
    std::unordered_set<Edge*> getIncomingEdges() const;
    int getMaxIncomingFlow() const;
    [[nodiscard]] bool isVisited() const;
    [[nodiscard]] bool isProcessing() const;
    [[nodiscard]] int getInDegree() const;
    void addAdjacent(Edge* edge);
    [[nodiscard]] Edge* findEdge(const std::string& destCode) const;
    [[nodiscard]] std::unordered_set<Edge*> getAdj() const;
    void setNum(const int& a);
    void setLow(const int& a);
    int getNum() const;
    int getLow() const;
};


#endif
