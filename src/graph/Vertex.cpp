#include "Vertex.h"

Vertex::Vertex(WaterFacility* waterFacility) : info(waterFacility) {}

WaterFacility* Vertex::getInfo() const {
    return info;
}

void Vertex::setVisited(const bool& flag) {
    this->visited = flag;
}

void Vertex::setProcessing(const bool& flag) {
    this->processing = flag;
}

bool Vertex::isVisited() const { return visited; }

bool Vertex::isProcessing() const { return processing; }

int Vertex::getInDegree() const { return inDegree; }

void Vertex::addAdjacent(Edge* edge) {
    adj.emplace(edge);
}

std::unordered_set<Edge*> Vertex::getAdj() const {
    return this->adj;
}

Edge* Vertex::findEdge(const std::string& destCode) const {
    for(Edge* edge : this->adj) {
        if(edge->getDest()->getInfo()->getCode() == destCode) {
            return edge;
        }
    }
    return nullptr;
}

void Vertex::setPath(Edge* edge) {
    this->path = edge;
}

Edge* Vertex::getPath() const { return path; }

void Vertex::addIncomingEdge(Edge* edge) {
    incoming.emplace(edge);
    inDegree++;
    maxIncomingFlow += edge->getPipe()->getCapacity();
}

std::unordered_set<Edge*> Vertex::getIncomingEdges() const {
    return this->incoming;
}

int Vertex::getMaxIncomingFlow() const {
    return this->maxIncomingFlow;
}

void Vertex::setNum(const int& a) {
    this->num = a;
}

void Vertex::setLow(const int& a) {
    this->low = a;
}

int Vertex::getNum() const {
    return this->num;
}

int Vertex::getLow() const {
    return this->low;
}

