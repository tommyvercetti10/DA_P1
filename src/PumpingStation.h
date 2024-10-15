#ifndef PUMPINGSTATION_H
#define PUMPINGSTATION_H


#include "WaterFacility.h"

class PumpingStation : public WaterFacility {
public:
    PumpingStation(const std::string& code, const int& id);
};


#endif
