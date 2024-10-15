#ifndef DATACONTAINER_H
#define DATACONTAINER_H

#include "graph/Graph.h"

class DataContainer {
private:
    Graph* g = new Graph();
public:
    Graph* getGraph();
};


#endif
