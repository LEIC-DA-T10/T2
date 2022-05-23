//
// Created by Eduardo Correia on 09/04/2022.
//

#include "applicationController.h"

using namespace std;

applicationController::applicationController() {
    state = 0;
}

bool applicationController::run() {
    switch (state) {
        case 1:
            readFixed();
            return true;
        case 2:
            readRandom();
            return true;
        case 3:
            computeFirst();
            return true;
        case 4:
            computeSecond();
            return true;
        case 5:
            printRoutes();
            return true;
        default:
            return false;
    }
}

void applicationController::setState(int new_state) {
    this->state = new_state;
}

void applicationController::printMainMenu(){
    cout << "-*-------------  Main Menu  --------------------------*-" << endl;
    cout << " |--> Input: " << endl;
    cout << " |        1 - Fixed input" << endl;
    cout << " |        2 - Random input" << endl;
    cout << " |--> Computing Scenarios: " << endl;
    cout << " |        3 - Compute Scenario 1 " << endl;
    cout << " |        4 - Compute Scenario 2"  << endl;
    cout << " |--> Printing Data: " << endl;
    cout << " |        5 - Print Routes"<< endl;
    cout << " |--> Exit " << endl;
    cout << " |        0 - Exit application "<< endl;
    cout << "-*----------------------------------------------------*-" << endl;
}

void applicationController::readFixed() {
    char fileIndex;
    string newInputPath;
    cout << "Choose which file to read from [1,10]"<< endl;
    cin >> fileIndex;
    newInputPath = string(INPUT_PATH) + string("in") + fileIndex;
    data = dataIO(newInputPath);
    data.readNodes();
    cout << "---- Finished reading data ----" << endl;
}

void applicationController::readRandom() {
    int number;
    cout << "---- Truck Dataset ----" << endl;
    cout << "Number of Random Trucks : [1,"<< data.getNumberTrucks() <<"] : " << endl;
    cin >> number;
    data.readTrucksRandom(number);
    cout << "---- Request Dataset ----" << endl;
    cout << "Number of Random Requests : [1,"<< data.getNumberRequests() <<"] : " << endl;
    cin >> number;
    data.readRequestsRandom(number);
    cout << "---- Finished reading data ----" << endl;
}

void applicationController::printTruck() {
    char answer;
    if(checkForEmpty(data.getTrucks())) return;
    cout << "Do you want to print the data to a file? (y/n)" << endl;
    cin >> answer;
    data.printTrucks(answer);
}

void applicationController::printRequest() {
    char answer;
    if(checkForEmpty(data.getRequests())) return;
    cout << "Do you want to print the data to a file? (y/n)" << endl;
    cin >> answer;
    data.printRequests(answer);
}

void applicationController::computeFirst() {
    if(checkForEmpty(data.getRequests()) || checkForEmpty(data.getTrucks())) return;    // Verificacao se vecs vazios
    firstScenario algorithm(data.getRequests(),data.getTrucks());
    algorithm.compute();
}

void applicationController::computeSecond() {
    if(checkForEmpty(data.getRequests()) || checkForEmpty(data.getTrucks())) return;
    secondScenario algorithm(data.getRequests(),data.getTrucks());
    algorithm.compute();
}

bool applicationController::checkForEmpty(const vector<request>& vector){
    if(vector.empty()){
        cout << "---- ERROR : You must read from Vector dataset before attempting this operation !!! ----" << endl;
        return true;
    }
    return false;
}

bool applicationController::checkForEmpty(const vector<truck>& vector){
    if(vector.empty()){
        cout << "---- ERROR : You must read from the Truck dataset before attempting this operation !!! ----" << endl;
        return true;
    }
    return false;
}

void applicationController::printRoutes() {

}



