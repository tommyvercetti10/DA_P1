#include "RequestManager.h"


RequestManager::RequestManager(DataContainer& container) : container(container) { }

std::unordered_set<Vertex*> RequestManager::getMaxFlowPerCity() {
    container.getGraph()->getMaxFlow();
    return container.getGraph()->getCities();
}

std::pair<DeliverySite, int> RequestManager::getMaxFlowIn(const std::string& cityName) {
    container.getGraph()->getMaxFlow();
    int flow = 0;
    for(Vertex* v: container.getGraph()->getCities()) {
        DeliverySite info = *dynamic_cast<DeliverySite*>(v->getInfo());
        if(info.getCity() == cityName) {
            for (Edge* e: v->getIncomingEdges()) {
                flow += e->getPipe()->getFlow();
            }
            return std::pair<DeliverySite, int>{info, flow};
        }

    }

    return std::pair<DeliverySite, int>{DeliverySite("", -1, "", 0, 0), 0};
}

std::vector<std::pair<DeliverySite, int>> RequestManager::sufficientDelivery() {
    container.getGraph()->getMaxFlow();
    int difference;
    std::vector<std::pair<DeliverySite, int>> differences;
    for(Vertex* v: container.getGraph()->getCities()) {
        DeliverySite info = *dynamic_cast<DeliverySite*>(v->getInfo());
        int flow = 0;
        for (Edge* e: v->getIncomingEdges()) {
            flow += e->getPipe()->getFlow();
        }
        difference = flow - info.getDemand();
        if (difference < 0) {
            differences.emplace_back(info, difference);
        }
    }
    return differences;
}

void RequestManager::getMaxFlowAll() {
    container.getGraph()->getMaxFlow();
    for(Vertex* v: container.getGraph()->getCities()) {
        DeliverySite info = *dynamic_cast<DeliverySite*>(v->getInfo());
        int flow = 0;
        for (Edge* e: v->getIncomingEdges()) {
            flow += e->getPipe()->getFlow();
        }
        std::cout << info.getId() << ": " << info.getCity() << " ---> " << flow;
    }
}

void RequestManager::saveToFile() {
    std::fstream file;
    file.open("../cities_flow.csv", std::ios::out);
    container.getGraph()->getMaxFlow();
    if(file){
        file << "CODE,NAME,FLOW" << std::endl;
        for(Vertex* v : container.getGraph()->getCities()) {
            auto* info = dynamic_cast<DeliverySite*> (v->getInfo());
            std::string code = info->getCode();
            std::string name = info->getCity();
            int flow = 0;
            for(Edge* e : v->getIncomingEdges()) {
                flow += e->getPipe()->getFlow();
            }
            file << info->getCode() << "," << info->getCity() << "," << std::to_string(flow) << std::endl;
        }
        file.close();
    }
}

std::unordered_map<DeliverySite*, int> RequestManager::getAffectedCities(const std::string& code) {
    std::unordered_map<DeliverySite*, int> res;
    Graph* aux = container.getGraph()->removeVertex(code);
    if(aux == nullptr) return res;
    for(Vertex* originalVertex : container.getGraph()->getCities()) {
        Vertex* vertex = aux->getVertex(originalVertex->getInfo()->getCode());
        int flow = 0;
        int originalFlow = 0;
        for(Edge* e : originalVertex->getIncomingEdges()) {
            originalFlow += e->getPipe()->getFlow();
        }
        for(Edge* e : vertex->getIncomingEdges()) {
            flow += e->getPipe()->getFlow();
        }
        auto* info = dynamic_cast<DeliverySite*>(originalVertex->getInfo());
        if(flow < originalFlow) res.insert(std::make_pair(info, info->getDemand() - flow));
    }
    return res;
}

std::unordered_map<DeliverySite*, int> RequestManager::getAffectedCities(const std::string& source, const std::string& dest) {
    std::unordered_map<DeliverySite*, int> res;
    Graph* aux = container.getGraph()->removePipe(source, dest);
    if(aux == nullptr) return res;
    for(Vertex* originalVertex : container.getGraph()->getCities()) {
        Vertex* vertex = aux->getVertex(originalVertex->getInfo()->getCode());
        int flow = 0;
        int originalFlow = 0;
        for(Edge* e : originalVertex->getIncomingEdges()) {
            originalFlow += e->getPipe()->getFlow();
        }
        for(Edge* e : vertex->getIncomingEdges()) {
            flow += e->getPipe()->getFlow();
        }
        auto* info = dynamic_cast<DeliverySite*>(originalVertex->getInfo());
        if(flow < originalFlow) res.insert(std::make_pair(info, info->getDemand() - flow));
    }
    return res;
}
