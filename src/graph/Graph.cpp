#include "Graph.h"


/**
 * @brief Function to add a vertex to the Graph
 * @details Time Complexity O(1)
 * @param vertex to be added
 */
void Graph::addVertex(Vertex* vertex) {
    vertices.emplace(std::pair<std::string, Vertex*>(vertex->getInfo()->getCode(), vertex));
}


void Graph::addCity(Vertex* vertex) {
    this->deliverySites.emplace(vertex);
    this->addVertex(vertex);
}

void Graph::addStation(Vertex *vertex) {
    this->pumpingStations.emplace(vertex);
    this->addVertex(vertex);
}

void Graph::addReservoir(Vertex* vertex) {
    this->waterReservoirs.emplace(vertex);
    this->addVertex(vertex);
}

std::unordered_set<Vertex*> Graph::getCities() const {
    return this->deliverySites;
}

std::unordered_set<Vertex*> Graph::getStations() const {
    return this->pumpingStations;
}

std::unordered_set<Vertex*> Graph::getReservoirs() const {
    return this->waterReservoirs;
}

/**
 * @brief Function to remove vertex from the Graph
 * @details Time Complexity O(n), where n is the number of edges of the vertex
 * @param vertex to be removed
 * @return whether the operation ended successfully
 */
bool Graph::removeVertex(Vertex* vertex) {
    std::string code = vertex->getInfo()->getCode();
    if(vertices.find(code) != vertices.end()) {
        Vertex* v = vertices.find(code)->second;
        for(Edge* e : v->getAdj()) {
            if(e->getReverse() != nullptr) {
                e->getReverse()->setReverse(nullptr);
            }
            e->getDest()->getIncomingEdges().erase(e);
            v->getAdj().erase(e);
        }
        vertices.erase(code);
        return true;
    }
    return false;
}

/**
 * @brief Function to get vertex with code 'code'
 * @details Time Complexity O(1)
 * @param code to be searched
 * @return vertex with the given code
 */
Vertex* Graph::getVertex(const std::string& code) {
    return vertices[code];
}

/**
 * @brief Function to add edge to the Graph
 * @details Time Complexity O(1)
 * @param source of the edge
 * @param dest of the edge
 * @param w weight of the edge
 * @return whether the operation ended successfully
 */
bool Graph::addEdge(const std::string& source, const std::string& dest, const int& w) {
    if(vertices.find(source) == vertices.end() || vertices.find(dest) == vertices.end()) return false;
    Vertex* src = vertices[source];
    Vertex* destination = vertices[dest];
    Edge* edge = new Edge(src, destination, new Pipe(w));
    vertices[source]->addAdjacent(edge);
    vertices[dest]->addIncomingEdge(edge);
    return true;
}

/**
 * @brief Function to add edge and its reverse
 * @details Time Complexity O(1)
 * @param source of the edge
 * @param dest of the edge
 * @param w weight of the edge
 * @return whether the operation ended successfully
 */
bool Graph::addEdgeAndReverse(const std::string& source, const std::string& dest, int w) {
    if (vertices.find(source) == vertices.end() || vertices.find(dest) == vertices.end()) return false;

    Vertex* src = vertices[source];
    Vertex* destination = vertices[dest];

    Edge* forwardEdge = new Edge(src, destination, new Pipe(w));
    Edge* reverseEdge = new Edge(destination, src, new Pipe(0));

    forwardEdge->setReverse(reverseEdge);
    reverseEdge->setReverse(forwardEdge);

    src->addAdjacent(forwardEdge);
    src->addIncomingEdge(reverseEdge);
    destination->addIncomingEdge(forwardEdge);
    destination->addAdjacent(reverseEdge);

    return true;
}

/**
 * @brief Function to add a bidirectional edge to the Graph
 * @details Time Complexity O(1)
 * @param source of the edge
 * @param dest of the edge
 * @param w weight of the edge
 * @return whether the operation ended successfully
 */
bool Graph::addBidirectionalEdge(const std::string& source, const std::string& dest, int w) {
    if(vertices.find(source) == vertices.end() || vertices.find(dest) == vertices.end()) return false;
    Vertex* src = vertices[source];
    Vertex* destination = vertices[dest];
    Edge* a = new Edge(src, destination, new Pipe(w));
    Edge* b = new Edge(destination, src, new Pipe(w));
    a->setReverse(b);
    b->setReverse(a);
    vertices[source]->addAdjacent(a);
    vertices[source]->addIncomingEdge(b);
    vertices[dest]->addAdjacent(b);
    vertices[dest]->addIncomingEdge(a);
    return true;
}

/**
 * @brief Function to get graph's copy
 * @details Time Complexity O(n) where n is the total number of edges
 * @return the graph's copy
 */
Graph* Graph::getCopy() const {
    auto* newGraph = new Graph();

    for(const auto& vertex : this->getCities()) {
        auto* info = dynamic_cast<DeliverySite*>(vertex->getInfo());

        auto* deliverySite = new DeliverySite(info->getCode(), info->getId(), info->getCity(), info->getPopulation(), info->getDemand());
        auto* newVertex = new Vertex(deliverySite);
        newGraph->addCity(newVertex);
    }

    for(const auto& vertex : this->getReservoirs()) {
        auto* info = dynamic_cast<WaterReservoir*>(vertex->getInfo());

        auto* waterReservoir = new WaterReservoir(info->getCode(), info->getId(), info->getName(), info->getMunicipality(), info->getMaxDelivery());
        auto* newVertex = new Vertex(waterReservoir);
        newGraph->addReservoir(newVertex);
    }

    for(const auto& vertex : this->getStations()) {
        auto* info = dynamic_cast<PumpingStation*>(vertex->getInfo());

        auto* pumpingStation = new PumpingStation(info->getCode(), info->getId());
        auto* newVertex = new Vertex(pumpingStation);
        newGraph->addStation(newVertex);
    }

    for(const auto& p : this->vertices) {
        Vertex* v = p.second;
        if(v == nullptr) continue;
        for(Edge* edge : v->getAdj()) {
            newGraph->addEdge(v->getInfo()->getCode(), edge->getDest()->getInfo()->getCode(), edge->getPipe()->getCapacity());
        }
    }
    return newGraph;
}

void Graph::resetAll() {
    for(const auto& p: vertices) {
        Vertex* v = p.second;
        for(Edge* e : v->getAdj()) {
            e->getPipe()->setFlow(0);
        }
        v->setVisited(false);
        v->setPath(nullptr);
        v->setProcessing(false);
    }
}

/**
 * @brief Adds a super source and a super sink to an auxiliary graph, in order to then run max-flow algorithm
 * @details Time Complexity O(E) where E is the number of edges in the original Graph
 * @return the auxiliary graph with a super source and a super sink
 */
Graph* Graph::getMaxFlowAuxGraph() const {
    Graph* aux = getCopy();
    auto* src = new Vertex(new WaterFacility("source", -1));
    auto* sink = new Vertex(new WaterFacility("sink", -2));
    aux->addVertex(src);
    aux->addVertex(sink);
    for(const auto& vertex : aux->getCities()) {
        auto* info = dynamic_cast<DeliverySite*>(vertex->getInfo());
        aux->addEdge(vertex->getInfo()->getCode(), "sink", info->getDemand());
    }

    for(const auto& vertex : aux->getReservoirs()) {
        auto* info = dynamic_cast<WaterReservoir*>(vertex->getInfo());
        aux->addEdge("source", info->getCode(), info->getMaxDelivery());
    }
    return aux;
}


/**
 * @brief Function to compute the max flow in the graph
 * @details Time Complexity O(V E^2), where V is the number of Vertices and E the number of Edges
 */
void Graph::getMaxFlow() {
    Graph* aux = getMaxFlowAuxGraph();
    auto* src = aux->getVertex("source");
    auto* sink = aux->getVertex("sink");
    while (bfsEdmondsKarp(aux, src, sink)) {
        int path_flow = INT_MAX;

        // Find minimum residual capacity along the path
        for (Vertex* v = sink; v != src; v = v->getPath()->getSource()) {
            Edge* e = v->getPath();
            Pipe* pipe = e->getPipe();
            path_flow = std::min(path_flow, pipe->getCapacity() - pipe->getFlow());
        }

        // Update flows along the path and reverse flows
        for (Vertex* v = sink; v != src; v = v->getPath()->getSource()) {
            Edge* edge = v->getPath();
            int flow = edge->getPipe()->getFlow();
            edge->getPipe()->setFlow(flow + path_flow);

            Edge* reverseEdge = edge->getReverse();
            if (reverseEdge != nullptr) {
                reverseEdge->getPipe()->setFlow(reverseEdge->getPipe()->getFlow() - path_flow);
            }
            else {
                Edge* e = new Edge(v, edge->getSource(), new Pipe(0));
                e->setReverse(edge);
                edge->setReverse(e);
                aux->addEdge(v, edge->getSource(), e);
                e->getPipe()->setFlow(-path_flow);
            }
        }
    }

    aux->removeVertex(sink);
    aux->removeVertex(src);

    // set the flows in the original graph
    for(const auto& p: aux->vertices) {
        auto v = p.second;
        auto original = this->getVertex(v->getInfo()->getCode());
        for(auto e : v->getAdj()) {
            if(e->getPipe()->getCapacity() == 0) continue;
            for(auto e1: original->getAdj()) {
                if(e1->getDest()->getInfo()->getCode() == e->getDest()->getInfo()->getCode()) {
                    e1->getPipe()->setFlow(e->getPipe()->getFlow());
                }
            }
        }
    }

}

/**
 * @brief Function to add edge to the graph
 * @param src edge's source
 * @param dest edge's destination
 * @param edge edge to be added
 * @return whether the operation ended successfully
 */
bool Graph::addEdge(Vertex* src, Vertex* dest, Edge* edge) {
    if(getVertex(src->getInfo()->getCode()) == nullptr || getVertex(dest->getInfo()->getCode()) == nullptr) return false;
    src->addAdjacent(edge);
    dest->addIncomingEdge(edge);
    return true;
}

/**
 * @brief BFS to set the path, especially useful in the Max-Flow algorithm
 * @param g graph to search
 * @param source path source
 * @param sink path sink
 * @details Time Complexity O(n), where n = V + E, V is the number of vertices and E the number of edges
 * @return whether there is a path
 */
bool Graph::bfsEdmondsKarp(Graph* g, Vertex* source, Vertex* sink) {
    for (const auto& pair : g->vertices) {
        Vertex* v = pair.second;
        v->setVisited(false);
        v->setPath(nullptr);
    }

    std::queue<Vertex*> queue;
    queue.push(source);
    source->setVisited(true);

    while (!queue.empty()) {
        Vertex* u = queue.front();
        queue.pop();

        for (Edge* edge : u->getAdj()) {
            Vertex* v = edge->getDest();
            Pipe* pipe = edge->getPipe();
            if (!v->isVisited() && pipe->getCapacity() - pipe->getFlow() > 0) {
                v->setVisited(true);
                v->setPath(edge);
                queue.push(v);
                if(v == sink) {
                    return true;
                }
            }
        }
    }

    return false;
}

/**
 * @brief Function to get the scc's
 * @details Time Complexity O(V(V + E)), where V is the number of vertices and E the number of edges
 * @return vector with unordered sets with each scc (strongly connected component)
 */
std::vector<std::unordered_set<Vertex*>> Graph::getSCC() {
    std::vector<std::unordered_set<Vertex*>> res;
    std::stack<Vertex*> s;
    int index = 1;
    for (const auto& p : vertices) {
        Vertex* v = p.second;
        v->setVisited(false);
    }


    for (const auto& p : vertices) {
        Vertex* v = p.second;
        if (! v->isVisited())
            dfs_scc(this, v, s, res, index);
    }

    return res;
}

/**
 * @brief Auxiliary dfs function to scc detection
 * @param g the target graph
 * @param v starting Vertex
 * @param s auxiliary stack
 * @param l list of scc's
 * @param i current number
 * @details Time Complexity O(n), where n = V + E (V is the number of vertices and E the number of edges)
 */
void Graph::dfs_scc(Graph *g, Vertex *v, std::stack<Vertex*> &s, std::vector<std::unordered_set<Vertex*>> &l, int &i) {
    v->setVisited(true);

    v->setLow(i);
    v->setNum(i);
    v->setProcessing(true);
    s.push(v);
    i++;

    for (auto & e : v->getAdj()) {
        auto w = e->getDest();
        if (!w->isVisited()) {
            dfs_scc(g, w, s, l, i);
            v->setLow(std::min(v->getLow(), w->getLow()));
        } else if (w->isProcessing())
            v->setLow(std::min(v->getLow(), w->getNum()));
    }

    if (v->getNum() == v->getLow()) {
        Vertex *w;
        std::unordered_set<Vertex*> scc;
        do {
            w = g->getVertex(s.top()->getInfo()->getCode());
            w->setProcessing(false);
            scc.insert(w);
            s.pop();
        } while (w != v);

        l.emplace_back(scc);

    }
}

/**
 * @brief Heuristic function to minimize variance of the flow / capacity edge's ratio
 * @details Time Complexity O(s(d n log(n))), where s is the number of scc,
 * d the difference between 2 edges and n the number of edges per scc
 * @return Graph with the flow balanced
 */
 Graph* Graph::balanceFlow() {
    Graph* aux = getCopy();
    aux->getMaxFlow();
    std::vector<std::unordered_set<Vertex*>> sccs = aux->getSCC();
    double average = getFlowToCapacityRatioAverage();
    for(auto scc : sccs) {
        std::vector<Edge*> sccEdges;


        for(const Vertex* v : scc) {
            for(Edge* e : v->getAdj()) {
                if(scc.find(e->getDest()) != scc.end()) {
                    sccEdges.emplace_back(e);
                }
            }
        }
        int start = 0;
        int end = (int)sccEdges.size() - 1;
        while (start <= end) {
            bool updateLeft = false;
            bool updateRight = false;
            std::sort(sccEdges.begin(), sccEdges.end(), [](Edge* a, Edge* b) { //sort in flow ascending order
                return a->getPipe()->getFlow() < b->getPipe()->getFlow();
            });
            Edge* fromStart = sccEdges[start];
            Edge* fromEnd = sccEdges[end];
            while(true) {

                if(abs(fromEnd->getPipe()->getRatio() - fromStart->getPipe()->getRatio()) < 0.02) {
                    updateLeft = true;
                    updateRight = true;
                    break;
                }

                if(fromEnd->getPipe()->getRatio() <= average) {
                    updateRight = true;
                    break;
                }
                if(fromStart->getPipe()->getRatio() >= average) {
                    updateLeft = true;
                    break;
                }


                int startFlow = fromStart->getPipe()->getFlow();
                int endFlow = fromEnd->getPipe()->getFlow();

                if(fromEnd->getPipe()->getFlow() - 1 > 0) {
                    fromEnd->getPipe()->setFlow(--endFlow);
                }
                if(fromStart->getPipe()->getFlow() + 1 < fromStart->getPipe()->getCapacity()) {
                    fromStart->getPipe()->setFlow(++startFlow);
                }
            }
            if(updateRight) { end--; }
            if(updateLeft) { start++; }
        }
    }
    return aux;
}

/**
 * @brief Function to get the flow / capacity edge's ratio average
 * @details Time Complexity O(n), where n is the number of edges
 * @return flow / capacity edge's ratio average
 */
double Graph::getFlowToCapacityRatioAverage() {
    double totalRatio = 0;
    int totalEdges = 0;
    for(const auto& p : vertices) {
        Vertex* v = p.second;
        for(Edge* e : v->getAdj()) {
            Pipe* pipe = e->getPipe();
            totalRatio += pipe->getRatio();
            totalEdges++;
        }
    }
    return totalRatio / totalEdges;
}

/**
 * @brief get flow / capacity ratio variance
 * @details Time Complexity O(n), where n is the number of edges
 * @param average of the flow / capacity ratio
 * @return the variance
 */
double Graph::getVarianceFlowToCapacity(const double& average) {
    double sum = 0;
    int edgesNum = 0;
    for(const auto& p: vertices) {
        Vertex* v = p.second;
        for(Edge* e : v->getAdj()) {
            double dif = average - e->getPipe()->getRatio();
            sum += dif * dif;
            edgesNum++;
        }
    }
    return sum / edgesNum;
}

/**
 * @brief get difference between capacity and flow variance
 * @details Time Complexity O(n), where n is the number of edges
 * @param variance of the difference between capacity and flow
 * @return the variance
 */
double Graph::getVarianceDifferenceCapacityFlow(const double& average) {
    double sum = 0;
    int edgesNum = 0;
    for(const auto& p: vertices) {
        Vertex* v = p.second;
        for(Edge* e : v->getAdj()) {
            Pipe* pipe = e->getPipe();
            if(pipe->getFlow() < 0) continue;
            double dif = average - pipe->getCapacity() - pipe->getFlow();
            sum += dif * dif;
            edgesNum++;
        }
    }
    return sum / edgesNum;
}

/**
 * @brief get average of difference between capacity and flow
 * @details Time Complexity O(n), where n is the number of edges
 * @param average of the difference between capacity and flow
 * @return the average
 */
double Graph::getAverageCapacityFlowDifference() {
    int sum = 0;
    int n = 0;
    for(const auto& p: vertices) {
        Vertex* v = p.second;
        for(Edge* e : v->getAdj()) {
            Pipe* pipe = e->getPipe();
            if(e->getPipe()->getFlow() >= 0) {
                sum += pipe->getCapacity() - pipe->getFlow();
                n++;
            }
        }
    }
    return (double)sum / n;
}


/**
 * @brief iterate over all edges to determine the max difference (capacity - flow)
 * @return max difference between capacity and flow
 */
int Graph::getMaxFlowCapacityDifference() {
    int max = 0;
    for(const auto& p: vertices) {
        Vertex* v = p.second;
        for(Edge* e : v->getAdj()) {
            Pipe* pipe = e->getPipe();
            if(e->getPipe()->getFlow() >= 0 && max < pipe->getCapacity() - pipe->getFlow()) {
                max = pipe->getCapacity() - pipe->getFlow();
            }
        }
    }
    return max;
}


Edge* Graph::getEdge(const std::string& src, const std::string& dest) {
    Vertex* source = getVertex(src);
    if(source == nullptr || getVertex(dest) == nullptr) return nullptr;
    for(Edge* e : source->getAdj()) {
        if(e->getDest()->getInfo()->getCode() == dest) return e;
    }
    return nullptr;
}


Graph* Graph::removeVertex(const std::string& code) {
    this->resetAll();
    Graph* aux = getCopy();
    this->getMaxFlow();
    std::vector<DeliverySite*> most_affected;
    Vertex* v = aux->getVertex(code);
    if(v == nullptr) return nullptr;
    aux->removeVertex(v);
    aux->getMaxFlow();
    return aux;
}


Graph* Graph::removePipe(const std::string& source, const std::string& dest) {
    this->resetAll();
    Graph* aux = getCopy();
    this->getMaxFlow();
    Edge* edge = aux->getEdge(source, dest);
    if(edge == nullptr) return nullptr;
    edge->getPipe()->setCapacity(0);
    aux->getMaxFlow();
    return aux;
}