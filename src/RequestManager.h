#ifndef REQUESTMANAGER_H
#define REQUESTMANAGER_H

#include <unordered_map>
#include <fstream>
#include "DataContainer.h"

class RequestManager {
private:
    DataContainer container;
public:
    RequestManager(DataContainer& container);
    std::unordered_set<Vertex*> getMaxFlowPerCity();
    std::pair<DeliverySite, int> getMaxFlowIn(const std::string& cityName);
    std::vector<std::pair<DeliverySite, int>> sufficientDelivery();
    void getMaxFlowAll();
    void saveToFile();
    std::unordered_map<DeliverySite*, int> getAffectedCities(const std::string& source, const std::string& dest);
    std::unordered_map<DeliverySite*, int> getAffectedCities(const std::string& code);
};


#endif
