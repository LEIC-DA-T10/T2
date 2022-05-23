//
// Created by Eduardo Correia on 09/04/2022.
// Developed by José Carvalho
//

#include <chrono>
#include "thirdScenario.h"

thirdScenario::thirdScenario(const vector<request>& requests1, const vector<truck>& trucks1) : abstractAlgorithm(requests1, trucks1){
    requests = requests1;
    trucks = trucks1;
}

///Major controllers
void thirdScenario::compute() {
    auto start = std::chrono::system_clock::now();
    if (trucks.size() > 1)
        cout << "---- WARNING : MORE THAN 1 TRUCK PROVIDED ONLY THE FIRST WILL BE CONSIDERED ----" << endl;

    int key;
    cout << "Choose which Algorithm to use :" << endl;
    cout << "1 - Greedy (Faster, but less accurate)" << endl;
    cout << "2 - Backtracking (Slower, but guarantees best result)" << endl;
    cin >> key;

    switch (key) {
        case 1:
            compute1();
            break;
        case 2:
            compute2();
            break;
    }

    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    printComputationTime(elapsed_seconds,end_time);
}

void thirdScenario::compute1(){
    std::sort(requests.begin(), requests.end(), lDeliveryTime);
    loadTruck();

    for (int i = 0; i < requests.size();i++)
        if (isDeliverable(i))deliver(requests.at(i));
    printStats();
}

void thirdScenario::compute2(){
    loadTruck();
    vector<int> requestsDuration;
    vector<int> bestDelivery;
    vector<vector<int>> res;
    requests = fitsTruck();
    for (auto & request : requests) requestsDuration.push_back(request.duration);
    res = subsets(requestsDuration);
    bestDelivery = bestOption(res);
    printTruckDetails();
    printOnlyMax(bestDelivery);
}
///Auxiliary Function

void thirdScenario:: loadTruck(){
    express.maxVolume = trucks.at(0).maxVolume;
    express.maxWeight = trucks.at(0).maxWeight;
    express.cost = trucks.at(0).cost;
}

///Logical functions
/// recursive function to find all the subsets following the backtracking implementation
/// designed to function with positive numbers not tested for negative



void thirdScenario::calculateDeliverySubsets(vector<int>& deliveryVector, vector<vector<int>>& res, vector<int>& subset, int index){
    res.push_back(subset);
    for (int i = index; i < deliveryVector.size(); i++) {
        subset.push_back(deliveryVector[i]);
        calculateDeliverySubsets(deliveryVector, res, subset, i + 1);
        subset.pop_back();
    }
}

vector<vector<int>> thirdScenario::subsets(vector<int>& deliveryVector){
    int index = 0;
    vector<int> subset;
    vector<vector<int> > res;
    calculateDeliverySubsets(deliveryVector, res, subset, index);
    res = analiseRes(res);
    return res;
}

///Screening functions

vector<int> thirdScenario::bestOption(vector<vector<int>> &res) {
    int bestNum = -1;
    int bestTime = INT32_MAX;
    vector<int> bestOption;
    int time;
    int numReq;
    for ( int i = 0 ; i < res.size(); i++){
        time = res[res.size()-1][i];
        numReq = res[res.size()-1][i+1];
        if(bestNum < numReq){
            bestTime = time;
            bestNum = numReq;
        }
        else if (bestNum == numReq && bestTime > time){
            bestTime = time;
        }
        i++;
    }

    bestOption.push_back(bestTime);
    bestOption.push_back(bestNum);
    return bestOption;
}

vector<vector<int>> thirdScenario::analiseRes(const vector<vector<int>>& res) const {
    int subsetValue;
    vector<int> validValue;
    vector<vector<int>> validVector;
    for (const auto & re : res) {
        subsetValue = 0;
        for (int j = 0; j < re.size(); j++){
            subsetValue += re[j];
        }
        if (subsetValue <= timeFrame) {
            validValue.push_back(subsetValue);
            validValue.push_back(re.size());
            validVector.push_back(validValue);
        }
    }
    sort(validVector.begin(), validVector.end());
    return validVector;
}

bool thirdScenario::lDeliveryTime(const request &a, const request &b) {
    return  a.duration < b.duration;
}

void thirdScenario::deliver(request &request) {
    usedTime += request.duration;
    income += request.reward;
    nReq ++;
    deliveryList.push_back(request);
}

bool thirdScenario::isDeliverable(int i) const {
    auto request = requests.at(i);
    if (express.maxVolume > request.volume && express.maxWeight > request.weight && request.duration + usedTime <= timeFrame) return true;
    return false;
}

vector<request> thirdScenario::fitsTruck() {
    vector<request> deliverable;
    for (int i = 0 ; i < requests.size();i ++){
        if (isDeliverable(i)) deliverable.push_back(requests.at(i));
    }
    return deliverable;
}

///Printing functions

void thirdScenario::printTruckDetails() const {
    cout << "-*-------------  Report Scenario 3  ------------------*-" << endl;
    cout << " |--> Truck Details: " << endl;
    cout << " |        Truck Maximum Weight: " <<express.maxWeight <<  endl;
    cout << " |        Truck Maximum Volume: " <<express.maxVolume << endl;
    cout << " |        Truck Cost: " <<express.cost << " $"<< endl;
}

void thirdScenario::printOnlyMax(vector<int> bestDelivery) {
    cout << " |-->  Successfully delivered : "<< (double)((double)bestDelivery[1] / (double)requests.size())*100 << "%"<< endl;
    cout << " |-->  Delivery Time : "<< bestDelivery[0] << " s"<< endl;
    cout << "-*----------------------------------------------------*-" << endl;
}

void thirdScenario::printComputationTime(chrono::duration<double> elapsed_seconds, time_t end_time) {
    cout << "-*-------------  Computation Time --------------------*-" << endl;
    cout << " |--> Time Details: " << endl;
    cout << " |        Elapsed Time: " << elapsed_seconds.count() << "s" << endl;
    cout << " |        Finished Computation At: " << std::ctime(&end_time);
    cout << "-*----------------------------------------------------*-" << endl;
}

void thirdScenario::printStats(){
    auto deliPerc = (double)(((double)nReq / (double)requests.size()) * (double)100.0);
    double avgTime = usedTime/nReq;
    int avgTimeM = avgTime/60;
    int avgTimeS = int(avgTime)%60;

    cout << "-*-------------  Report Scenario 3  ------------------*-" << endl;
    cout << " |--> Truck Details: " << endl;
    cout << " |        Truck Maximum Weight: " <<express.maxWeight <<endl;
    cout << " |        Truck Maximum Volume: " <<express.maxVolume <<endl;
    cout << " |        Truck Cost: " <<express.cost << "$"<< endl;
    cout << " |--> Deliveries: " << endl;

    cout << " |        Delivered: " << deliPerc << "% ("<<nReq<<")"<< endl;

    if (requests.size() - nReq == 0){
        cout << " |        Rejected: 0%" << endl;
    }else
        cout << " |        Rejected: " << 100 - deliPerc << "%" << endl;
    cout << " |        Average Time per Delivery: "<< avgTimeM << "min "<<avgTimeS<<"secs"<<endl;
    cout << " |--> Balance: " << endl;
    cout << " |       Gains from Deliveries: " << income << "$" << endl;
    cout << " |       Total profit: " <<income - express.cost<< "$"<< endl;

    cout << "-*----------------------------------------------------*-" << endl;
    cout << "    Do you want to see the request details? (y/n)" << endl;
    char answer;
    cin >> answer;
    if(answer == 'y'){
        cout << "[Id] [Weight] [Volume] [Reward] [Delivery time]"<< endl;
        for (int i = 0 ; i < deliveryList.size(); i++){
            cout << "[" <<i+1<<"] "<< deliveryList.at(i).weight<<"Kg "<< deliveryList.at(i).volume <<"m3 " << deliveryList.at(i).reward<<"$ "<<deliveryList.at(i).duration <<"s"<< endl;
        }
    }
    cout << "------  End Of Scenario 3  -------"<< endl<< endl<< endl;
    }
