#ifndef WATERFACILITY_H
#define WATERFACILITY_H


#include <string>
#include <utility>

class WaterFacility {
protected:
    std::string code;
    int id;
public:
    WaterFacility(std::string  code, const int& id);
    virtual ~WaterFacility() = default;
    [[nodiscard]] std::string getCode() const;
    [[nodiscard]] int getId() const;
};


#endif
