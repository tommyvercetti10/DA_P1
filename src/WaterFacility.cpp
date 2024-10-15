#include "WaterFacility.h"

WaterFacility::WaterFacility(std::string code, const int& id) : code(std::move(code)), id(id){}


std::string WaterFacility::getCode() const {
    return code;
}


int WaterFacility::getId() const {
    return id;
}