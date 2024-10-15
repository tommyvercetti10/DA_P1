#include "Menu.h"

void Menu::run() {
    container = DataContainer();
    loader = DataLoader();
    std::string pathCities, pathPipes, pathReservoir, pathStations;
    int in;
    dataSetPath:
    std::cout << "Which Data file you want to use?\n";
    std::cout << "1. Normal\n";
    std::cout << "2. Custom\n";
    std::cout << "\nChoose an option:";
    int option;
    std::string ai;
    std::cin >> option;
    if(std::cin.fail()) {
        failInt();
        goto dataSetPath;
    }
    if (option == 1) {
        pathCities = "../dataset/Cities.csv";
        pathPipes = "../dataset/Pipes.csv";
        pathReservoir = "../dataset/Reservoir.csv";
        pathStations = "../dataset/Stations.csv";
    }
    else if (option == 2) {
        std::cout << "\nPath Cities: \n";
        std::cin >> pathCities;
        std::cout << "Path Pipes: \n";
        std::cin >> pathPipes;
        std::cout << "Path Reservoirs: \n";
        std::cin >> pathReservoir;
        std::cout << "Path Stations: \n";
        std::cin >> pathStations;
    }
    else {
        std::cout << "\nInvalid Option. Try Again.\n";
        goto dataSetPath;
    }
    std::cout << "Loading the files...\n\n";
    loader.loadCities(container, pathCities);
    loader.loadReservoirs(container, pathReservoir);
    loader.loadStations(container, pathStations);
    loader.loadPipes(container, pathPipes);
    RequestManager requestManager(container);
    std::vector<std::pair<DeliverySite, int>> vec;
    std::unordered_map<DeliverySite*, int> auxMap;
    Graph* aux;
    int in1;
    MainMenu:
    std::cout << "\nWater-Supply-Management-System" << "\n";
    std::cout << "===============[ MENU ]===============\n";
    std::cout << "1. Max amount of water\n";
    std::cout << "2. Can all the water reservoirs supply enough water to all its delivery sites?\n";
    std::cout << "3. Balance water distribution\n";
    std::cout << "4. Structures out of service\n";
    std::cout << "\nChoose an option: ";

    do {
        std::cin >> in1;
        if(std::cin.fail()) {
            failInt();
            goto MainMenu;
        }
        switch (in1) {
            case 1:
                int in2;
                MaxWater:
                std::cout << "\n========[ Max amount of water ]=======\n";
                std::cout << "1. List the max amount of water that can reach all cities. \n";
                std::cout << "2. Select a city. \n";
                std::cout << "\nChoose an option:";
                std::cin >> in2;
                if(std::cin.fail()) {
                    failInt();
                    goto MaxWater;
                }
                if (in2 == 1) {
                    container.getGraph()->getMaxFlow();

                    for(Vertex* v: container.getGraph()->getCities()) {
                        DeliverySite info = *dynamic_cast<DeliverySite*>(v->getInfo());
                        int flow = 0;
                        for (Edge* e: v->getIncomingEdges()) {
                            flow += e->getPipe()->getFlow();
                        }
                        std::cout << "\n" << info.getId() << ": " << info.getCity() << " ---> " << flow;
                    }
                    requestManager.saveToFile();
                    in = finalMenu(0);
                    if (in == 1) goto MainMenu;
                    else if (in == 2) in1 = 5;
                }
                if (in2 == 2) {
                    CityMaxF:
                    std::string city;
                    std::cout << "\nEnter the desired city: ";
                    std::cin >> city;
                    std::pair<DeliverySite, int> cities = requestManager.getMaxFlowIn(city);
                    std::cout << "\n" << cities.first.getId() << ": " << cities.first.getCity() << " ---> " << cities.second;
                    in = finalMenu(1);
                    if (in == 1) goto CityMaxF;
                    if (in == 2) goto MainMenu;
                    else if (in == 3) in1 = 5;
                }
                break;
            case 2:
                vec = requestManager.sufficientDelivery();
                if (!requestManager.sufficientDelivery().empty()) std::cout << "\nThere are " << requestManager.sufficientDelivery().size() << " cities with less water arriving than demand.\n";
                std::cout << "===================================================\n";
                for (const auto& p: requestManager.sufficientDelivery()) {
                    std::cout << p.first.getId() << ": " << p.first.getCity() << " ---> " << -(p.second) << "\n";
                }
                in = finalMenu(0);
                if (in == 1) goto MainMenu;
                else if (in == 2) in1 = 5;
                break;
            case 3:
                container.getGraph()->getMaxFlow();
                aux = container.getGraph()->balanceFlow();
                std::cout << "\nVariance value:";
                std::cout << "\n==========================";
                std::cout << "\n RELATIVE VARIANCE:";
                std::cout << "\nBEFORE BALANCE -> " << container.getGraph()->getVarianceFlowToCapacity(container.getGraph()->getFlowToCapacityRatioAverage()) << std::endl;
                std:: cout << "AFTER BALANCE -> " << aux->getVarianceFlowToCapacity(aux->getFlowToCapacityRatioAverage()) << std::endl;
                std::cout << "\n ABSOLUTE VARIANCE:";
                std::cout << "\nBEFORE BALANCE -> " << container.getGraph()->getVarianceDifferenceCapacityFlow(container.getGraph()->getAverageCapacityFlowDifference()) << std::endl;
                std:: cout << "AFTER BALANCE -> " << aux->getVarianceDifferenceCapacityFlow(aux->getAverageCapacityFlowDifference()) << std::endl;
                std::cout << "\n AVERAGE DIFFERENCE: ";
                std::cout << "\nBEFORE BALANCE -> " << container.getGraph()->getAverageCapacityFlowDifference() << std::endl;
                std:: cout << "AFTER BALANCE -> " << aux->getAverageCapacityFlowDifference() << std::endl;
                std::cout << "\n MAX DIFFERENCE: ";
                std::cout << "\nBEFORE BALANCE -> " << container.getGraph()->getMaxFlowCapacityDifference() << std::endl;
                std:: cout << "AFTER BALANCE -> " << aux->getMaxFlowCapacityDifference() << std::endl;
                in = finalMenu(0);
                if (in == 1) goto MainMenu;
                else if (in == 2) in1 = 5;
                break;
            case 4:
                int in6;
                outSer:
                std::cout << "\n=========[ Out of service ]=========\n";
                std::cout << "1. Remove a delivery reservoir\n";
                std::cout << "2. Remove a station\n";
                std::cout << "3. Remove a pipe\n";
                std::cout << "\nChoose an option:";
                std::cin >> in6;
                if(std::cin.fail()) {
                    failInt();
                    goto outSer;
                }
                if (in6 == 1 || in6 ==2){
                    if (in6 == 1) std::cout << "\nChoose a code reservoir: ";
                    if (in6 == 2) std::cout << "\nChoose a code station: ";
                    std::string code;
                    std::cin >> code;
                    std::cout << "\nThe affected cities are:\n";
                    auxMap = requestManager.getAffectedCities(code);
                    for (auto p: auxMap) {
                        std::cout << "\n" << p.first->getId() << ": " << p.first->getCity() << " ---> " << p.second;
                    }
                }
                else if (in6 == 3){
                    std::cout << "\nChoose a code for source: ";
                    std::string source;
                    std::cin >> source;
                    std::cout << "\nChoose a code for destination: ";
                    std::string dest;
                    std::cin >> dest;
                    std::cout << "\nThe affected cities are: ";
                    auxMap = requestManager.getAffectedCities(source, dest);
                    for (auto p: auxMap) {
                        std::cout << "\n" << p.first->getId() << ": " << p.first->getCity() << " ---> " << p.second;
                    }
                }
                else {
                    std::cout << "\nInvalid Option. Try Again.\n";
                    goto outSer;
                }
                in = finalMenu(0);
                if (in == 1) goto MainMenu;
                else if (in == 2) in1 = 5;
                break;
            default:
                std::cout << "\nInvalid Option. Try Again.\n";
                goto MainMenu;
        }
    } while (in1 != 5);
}

void Menu::failInt() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "\nInvalid input. Please enter an integer." << std::endl;
}

int Menu::finalMenu(int prob) {
    finalmenu:
    int num = 0;
    std::cout << "\n\n============================\n";
    if (prob == 1) {
        num = 1;
        std::cout << "1. Choose other city\n";
    }
    std::cout << num + 1 <<". Return to main menu\n";
    std::cout << num + 2 <<". Exit\n";
    std::cout << "\nChoose an option: ";
    int in;
    std::cin >> in;
    if(std::cin.fail()) {
        failInt();
        goto finalmenu;
    }
    return in;
}