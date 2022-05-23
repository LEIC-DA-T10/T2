
#include <gtest/gtest.h>
#include "dataIO.h"
#include "applicationController.h"


using namespace std;




int main(){
    applicationController controller;
    int state;
    while(true){
        applicationController::printMainMenu();
        cin >> state;
        controller.setState(state);
        if(!controller.run()) break;
    }
    cout << "Exiting application, Goodbye! " << endl;
    return 0;
}
