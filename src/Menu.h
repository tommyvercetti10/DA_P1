#ifndef DA1_MENU_H
#define DA1_MENU_H

#include "DataLoader.h"
#include "RequestManager.h"
#include <limits>

class Menu {
    private:
        DataLoader loader;
        DataContainer container;
    public:
        void run();
        static void failInt();
        static int finalMenu(int prob);
};


#endif //DA1_MENU_H
