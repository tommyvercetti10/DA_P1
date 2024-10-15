#include "WaterReservoir.h"

WaterReservoir::WaterReservoir(const std::string& code,
                               const int& id,
                               const std::string& name,
                               const std::string& municipality,
                               const int& maxDelivery) :
                               WaterFacility(code, id) {

    this->name = name;
    this->municipality = municipality;
    this->maxDelivery = maxDelivery;
}

std::string WaterReservoir::getName() const {
    return name;
}

std::string WaterReservoir::getMunicipality() const {
    return municipality;
}

int WaterReservoir::getMaxDelivery() const {
    return maxDelivery;
}