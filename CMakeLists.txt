cmake_minimum_required(VERSION 3.26)
project(da1)

set(CMAKE_CXX_STANDARD 17)

add_executable(da1 src/main.cpp
        src/DataLoader.h
        src/DataLoader.cpp
        src/graph/Graph.h
        src/WaterFacility.h
        src/WaterFacility.cpp
        src/graph/Graph.cpp
        src/graph/Vertex.h
        src/graph/Vertex.cpp
        src/WaterReservoir.h
        src/WaterReservoir.cpp
        src/PumpingStation.h
        src/PumpingStation.cpp
        src/DeliverySite.h
        src/DeliverySite.cpp
        src/graph/Edge.h
        src/graph/Edge.cpp
        src/Pipe.h
        src/Pipe.cpp
        src/RequestManager.cpp
        src/DataContainer.cpp
        src/DataContainer.h
        src/RequestManager.h
        src/Menu.cpp
)
