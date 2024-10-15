#include "Pipe.h"

Pipe::Pipe(const int &capacity) : capacity(capacity) {}

int Pipe::getCapacity() const {
    return capacity;
}

int Pipe::getFlow() const {
    return flow;
}

void Pipe::setFlow(const int& flow) {
    this->flow = flow;
}

double Pipe::getRatio() const { return (double) flow / capacity; }

void Pipe::setCapacity(const int& cap) { this->capacity = cap; }