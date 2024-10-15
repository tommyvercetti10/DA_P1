#ifndef DELIVERYSITE_H
#define DELIVERYSITE_H


#include "WaterFacility.h"

class DeliverySite : public WaterFacility{
private:
    std::string city;
    int population;
    int demand;
public:
    DeliverySite(const std::string& code, const int& id, const std::string& city, const int& population, const int& demand);
    [[nodiscard]] std::string getCity() const;
    [[nodiscard]] int getPopulation() const;
    [[nodiscard]] int getDemand() const;
};


#endif
