#ifndef WATERRESERVOIR_H
#define WATERRESERVOIR_H


#include "WaterFacility.h"

class WaterReservoir: public WaterFacility {
private:
    std::string name, municipality;
    int maxDelivery;
public:
    WaterReservoir(const std::string& code, const int& id, const std::string& name, const std::string& municipality, const int& maxDelivery);
    [[nodiscard]] std::string getName() const;
    [[nodiscard]] std::string getMunicipality() const;
    [[nodiscard]] int getMaxDelivery() const;
};


#endif
