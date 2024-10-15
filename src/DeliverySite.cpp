#include "DeliverySite.h"


DeliverySite::DeliverySite(const std::string& code,
                           const int& id,
                           const std::string& city,
                           const int& population,
                           const int& demand) :
                           WaterFacility(code, id) {
    this->city = city;
    this->population = population;
    this->demand = demand;
}


std::string DeliverySite::getCity() const {
    return city;
}


int DeliverySite::getPopulation() const {
    return population;
}


int DeliverySite::getDemand() const {
    return demand;
}