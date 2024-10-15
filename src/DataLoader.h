#ifndef DATALOADER_H
#define DATALOADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <typeinfo>
#include "DataContainer.h"
#include "DeliverySite.h"
#include "WaterReservoir.h"
#include "PumpingStation.h"
#include "graph/Vertex.h"



class DataLoader {
private:
    Graph graph;
public:
    static void trimLine(std::string& line);
    static void loadCities(DataContainer& container, std::string& path);
    static void loadReservoirs(DataContainer& container, std::string& path);
    static void loadPipes(DataContainer& container, std::string& path);
    static void loadStations(DataContainer& container, std::string& path);
};


#endif
