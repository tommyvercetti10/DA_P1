#ifndef GRAPH_H
#define GRAPH_H

#include "../WaterFacility.h"
#include "../WaterReservoir.h"
#include "../DeliverySite.h"
#include "../PumpingStation.h"
#include "Vertex.h"
#include "Edge.h"
#include <unordered_map>
#include <queue>
#include <stack>
#include <algorithm>
#include <climits>
#include <iostream>
#include <stack>
#include <algorithm>

class Graph {
private:

    /*
     * the 3 unordered sets are specially useful to determine from which type a
     * certain vertex is as dynamic cast is quite expensive in terms of performance and
     * as we are using pointers, it is not specially expensive in terms of memory
     */
    std::unordered_map<std::string, Vertex*> vertices;
    std::unordered_set<Vertex*> deliverySites;
    std::unordered_set<Vertex*> pumpingStations;
    std::unordered_set<Vertex*> waterReservoirs;
public:
    void addVertex(Vertex* vertex);
    void addCity(Vertex* vertex);
    void addStation(Vertex* vertex);
    void addReservoir(Vertex* vertex);
    [[nodiscard]] std::unordered_set<Vertex*> getReservoirs() const;
    [[nodiscard]] std::unordered_set<Vertex*> getStations() const;
    [[nodiscard]] std::unordered_set<Vertex*> getCities() const;
    Vertex* getVertex(const std::string& code);
    bool addEdge(const std::string& source, const std::string& dest, const int& w);
    bool addEdge(Vertex* src, Vertex* dest, Edge* edge);
    bool addBidirectionalEdge(const std::string& source, const std::string& dest, int w);
    bool addEdgeAndReverse(const std::string& source, const std::string& dest, int w);
    Edge* getEdge(const std::string& src, const std::string& dest);
    [[nodiscard]] Graph* getCopy() const;
    Graph* getMaxFlowAuxGraph() const;
    void getMaxFlow();
    Graph* balanceFlow();
    static bool bfsEdmondsKarp(Graph* g, Vertex* source, Vertex* sink);
    std::vector<std::unordered_set<Vertex*>> getSCC();
    void dfs_scc(Graph *g, Vertex *v, std::stack<Vertex*> &s, std::vector<std::unordered_set<Vertex*>> &l, int &i);
    bool removeVertex(Vertex* vertex);
    void resetAll();
    Graph* removeVertex(const std::string& code);
    Graph* removePipe(const std::string& source, const std::string& dest);
    int getMaxFlowCapacityDifference();
    double getFlowToCapacityRatioAverage();
    double getVarianceFlowToCapacity(const double& average);
    double getVarianceDifferenceCapacityFlow(const double& average);
    double getAverageCapacityFlowDifference();
};


#endif
