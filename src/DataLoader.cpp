#include "DataLoader.h"



/**
 * @brief Due to the the fact that different OS do not end a line in the same way,
 * windows does it with \r\n while, unix with just \n,
 * we have to trim each line, if needed
 */
void DataLoader::trimLine(std::string& line) {
    if(line.back() == '\r') line.pop_back();
}


void DataLoader::loadCities(DataContainer& container, std::string& path) {
    std::string line;
    std::ifstream stream(path);
    std::getline(stream, line);
    while(std::getline(stream, line)) {
        try {
            trimLine(line);
            std::istringstream iss(line);

            std::string city, code, idStr, demandStr, populationStr, ignore;
            int id, population;
            float demand;

            std::getline(iss, city, ',');
            std::getline(iss, idStr, ',');
            std::getline(iss, code, ',');
            std::getline(iss, demandStr, ',');
            std::getline(iss, populationStr);

            population = std::stoi(populationStr);
            id = std::stoi(idStr);
            demand = std::stof(demandStr);
            auto* deliverySite = new DeliverySite(code, id, city, population, demand);
            auto* vertex = new Vertex(deliverySite);
            container.getGraph()->addCity(vertex);

        } catch (...) {
            continue;
        }
    }
}


void DataLoader::loadReservoirs(DataContainer& container, std::string& path) {
    std::string line;
    std::ifstream stream(path);
    std::getline(stream, line);
    while(std::getline(stream, line)) {
        try {
            trimLine(line);
            std::istringstream iss(line);

            std::string reservoir, municipality, idStr, code, maxDeliveryStr;
            int id, maxDelivery;

            std::getline(iss, reservoir, ',');
            std::getline(iss, municipality, ',');
            std::getline(iss, idStr, ',');
            std::getline(iss, code, ',');
            std::getline(iss, maxDeliveryStr, ',');

            id = std::stoi(idStr);
            maxDelivery = std::stoi(maxDeliveryStr);
            auto* waterReservoir = new WaterReservoir(code, id, reservoir, municipality, maxDelivery);
            auto* vertex = new Vertex(waterReservoir);
            container.getGraph()->addReservoir(vertex);

        } catch (...) {
            std::cout << "Failed while loading reservoirs" << std::endl;
        }

    }
}


void DataLoader::loadPipes(DataContainer& container, std::string& path) {
    std::string line;
    std::ifstream stream(path);
    std::getline(stream, line);
    while(std::getline(stream, line)) {
        try {
            trimLine(line);
            std::istringstream iss(line);

            std::string pointA, pointB, capacityStr, directionStr;
            int capacity, direction;

            std::getline(iss, pointA, ',');
            std::getline(iss, pointB, ',');
            std::getline(iss, capacityStr, ',');
            std::getline(iss, directionStr, ',');

            capacity = std::stoi(capacityStr);
            direction = std::stoi(directionStr);

            if(direction == 0) { // bidirectional pipe
                container.getGraph()->addBidirectionalEdge(pointA, pointB, capacity);
            }
            else {
                container.getGraph()->addEdge(pointA, pointB, capacity);
            }

        } catch (...) {
            std::cout << "Failed while loading pipes" << std::endl;
        }

    }
}


void DataLoader::loadStations(DataContainer& container, std::string& path) {
    std::string line;
    std::ifstream stream(path);
    std::getline(stream, line);
    while(std::getline(stream, line)) {
        try {
            trimLine(line);
            std::istringstream iss(line);

            std::string idStr, code;
            int id;

            std::getline(iss, idStr, ',');
            std::getline(iss, code, ',');

            id = std::stoi(idStr);
            auto* pumpingStation = new PumpingStation(code, id);
            auto* vertex = new Vertex(pumpingStation);
            container.getGraph()->addStation(vertex);
        }
        catch(...) {
            std::cout << "Failed while loading pumping stations" << std::endl;
        }
    }
}

