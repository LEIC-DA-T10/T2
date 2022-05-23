//
// Created by Eduardo Correia on 09/04/2022.
//


#include <random>
#include "secondScenario.h"



void secondScenario::compute() {
    unsigned int results[3];
    int option;
    unsigned int maximumValue = 0;

    cout << "Choose which Algorithm to use :" << endl;
    cout << "1 - Greedy (Faster, but less accurate)" << endl;
    cout << "2 - Backtracking (Slower, but guarantees best result, limit 1 truck)" << endl;
    cin >> option;

    auto start = std::chrono::system_clock::now();

    if(option == 1){
        maximumValue = getMax3(results[0] = computeByWeight(),results[1] = computeByVolume(),results[2] = computeByWeightToVolume());
    }
    else if(option == 2){
        if (requests.size() > 1)
            cout << "WARNING : More than 1 truck detected, only using first truck." << endl;
        maximumValue = forceCompute();
    }
    else{
        cout << "ERROR : Invalid Option" << endl;
        return;
    }
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    if(option == 1){
        char answer;
        printResult(maximumValue);
        printComputationTime(elapsed_seconds,end_time);
        cout << "Do you want to export the distribution to a file ? (y/n)" << endl;
        cin >> answer;
        if(answer == 'y')
            exportResult(maximumValue);
    }
    else if(option == 2){
        printOnlyMax(maximumValue);
        printComputationTime(elapsed_seconds,end_time);
    }

}

secondScenario::secondScenario(const vector<request>& requests, const vector<truck>& trucks) : abstractAlgorithm(requests, trucks) {
    sortedRequests = requests;
    sortedTrucks = trucks;
    bestScenario = 0;
}

secondScenario::secondScenario() : abstractAlgorithm() {
    bestScenario = 0;
}




void secondScenario::printTrucks(const vector<truck> &trucks) {
    for (const auto& truck: trucks) {
        cout << truck.maxVolume << " " << truck.maxWeight << " " << truck.cost << endl;
    }
}

void secondScenario::printRequests(const vector<request> &requests) {
    for (const auto& request: requests) {
        cout << request.volume << " " << request.weight << " " << request.reward << endl;
    }
}
//Sort requests by biggest weight to reward ratio
bool secondScenario::requestWeightToReward(const request &a, const request &b){
    return ((double)a.weight*a.reward) > ((double)b.weight*b.reward);
}

//Sort trucks by biggest weight to cost ratio
bool secondScenario::truckWeightToCost(const truck &a, const truck &b){
    return ((double)a.maxWeight/a.cost) > ((double)b.maxWeight/b.cost);
}

//Sort requests by biggest volume to reward ratio
bool secondScenario::requestVolumeToReward(const request &a, const request &b){
    return ((double)a.volume*a.reward) > ((double)b.volume*b.reward);
}

//Sort trucks by biggest volume to cost ratio
bool secondScenario::truckVolumeToCost(const truck &a, const truck &b){
    return ((double)a.maxVolume/a.cost) > ((double)b.maxVolume/b.cost);
}

//Sort requests by biggest V*W to reward ratio
bool secondScenario::wvRatioToReward(const request &a, const request &b){
    return ((double)a.volume*a.weight*a.reward) > ((double)b.volume*b.weight*b.reward);
}

//Sort trucks by biggest V*W to cost ratio
bool secondScenario::wvRatioToCost(const truck &a, const truck &b){
    return ((double)(a.maxVolume*a.maxVolume)/a.cost) > ((double)(b.maxVolume*b.maxWeight)/b.cost);
}



unsigned int secondScenario::computeByWeight() {

    std::queue<request> requestQueue;
    unsigned int truckIndex = 0;

    //Sort requests by weight * reward (higher first), and sort trucks by weight/cost (higher first)
    std::sort(sortedRequests.begin(), sortedRequests.end(), requestWeightToReward);
    std::sort(sortedTrucks.begin(), sortedTrucks.end(), truckWeightToCost);
    outputTrucks[0] = sortedTrucks;

    //Insert requests into a request queue
    for(auto request : sortedRequests)
        requestQueue.push(request);

    while(!requestQueue.empty()){
        request currentRequest = requestQueue.front();
        if(!checkAndInsert(currentRequest,outputTrucks[0].at(truckIndex))){
            truckIndex++;
            if(truckIndex >= outputTrucks[0].size()) break;
        }
        requestQueue.pop();
    }

    return calculateProfit(outputTrucks[0]);

}


bool secondScenario::checkAndInsert(request requestToInsert, truck &truckToInsert) {
    if(requestToInsert.weight <= truckToInsert.maxWeight && requestToInsert.volume <= truckToInsert.maxVolume){
        truckToInsert.truckLoad.push_back(requestToInsert);
        truckToInsert.maxWeight -= requestToInsert.weight;
        truckToInsert.maxVolume -= requestToInsert.volume;
        return true;
    }
    return false;
}

unsigned int secondScenario::computeByVolume() {
    std::queue<request> requestQueue;
    unsigned int truckIndex = 0;

    //Sort requests by weight * reward (higher first), and sort trucks by weight/cost (higher first)
    std::sort(sortedRequests.begin(), sortedRequests.end(), requestVolumeToReward);
    std::sort(sortedTrucks.begin(), sortedTrucks.end(), truckVolumeToCost);
    outputTrucks[1] = sortedTrucks;

    //Insert requests into a request queue
    for(auto request : sortedRequests)
        requestQueue.push(request);

    while(!requestQueue.empty()){
        request currentRequest = requestQueue.front();
        if(!checkAndInsert(currentRequest,outputTrucks[1].at(truckIndex))){
            truckIndex++;
            if(truckIndex >= outputTrucks[1].size()) break;
        }
        requestQueue.pop();
    }

    return calculateProfit(outputTrucks[1]);
}

unsigned int secondScenario::computeByWeightToVolume() {
    std::queue<request> requestQueue;
    unsigned int truckIndex = 0;

    //Sort requests by weight * reward (higher first), and sort trucks by weight/cost (higher first)
    std::sort(sortedRequests.begin(), sortedRequests.end(), wvRatioToReward);
    std::sort(sortedTrucks.begin(), sortedTrucks.end(), wvRatioToCost);
    outputTrucks[2] = sortedTrucks;

    //Insert requests into a request queue
    for(auto request : sortedRequests)
        requestQueue.push(request);

    while(!requestQueue.empty()){
        request currentRequest = requestQueue.front();
        if(!checkAndInsert(currentRequest,outputTrucks[2].at(truckIndex))){
            truckIndex++;
            if(truckIndex >= outputTrucks[2].size()) break;
        }
        requestQueue.pop();
    }

    return calculateProfit(outputTrucks[2]);
}

int secondScenario::calculateProfit(vector<truck> &trucks) {
    int profit = 0;
    vector<truck> profitableTrucks;
    for(auto truck : trucks){
        int truckReward = 0;
        for(auto request : truck.truckLoad){
            truckReward += (int)request.reward;
        }
        truckReward -= (int)truck.cost;

        if(truckReward > 0){
            truck.profit = truckReward;
            profitableTrucks.push_back(truck);
            profit += truckReward;
        }
    }
    trucks = profitableTrucks;

    return profit;
}

unsigned int secondScenario::getMax3(unsigned int value1,unsigned int value2,unsigned int value3) {
    unsigned int max = value1;
    if(value2 > value1 && value2 > value3){
        max = value2;
        bestScenario = 1;
    }
    else if(value3 > value1 && value3 > value2){
        max = value3;
        bestScenario = 2;
    }
    return max;
}

unsigned int secondScenario::calculateCost(const vector<truck> &trucks) {
    unsigned int cost = 0;
    for(const auto& truck : trucks){
        cost+= truck.cost;
    }
    return cost;
}

unsigned int secondScenario::numberOfRequests(const vector<truck> &trucks) {
    unsigned int counter = 0;
    for(const auto& truck : trucks){
        counter += truck.truckLoad.size();
    }
    return counter;
}

unsigned int secondScenario::forceCompute() {
    loadLessTruck truck = getLoadlessTruck(trucks.at(0));
    int value = max(backtrackingSolver(requests,truck,0,0,false), backtrackingSolver(requests,truck,0,0, true));
    return value;
}

int secondScenario::backtrackingSolver(const vector<request> &requests, loadLessTruck truck,int requestIndex, int profit, bool toLoad) {
    if (requestIndex >= requests.size()){
        return profit;
    }
    if (requests.at(requestIndex).weight > truck.maxWeight || requests.at(requestIndex).volume > truck.maxVolume)
        return SMALLEST_LIMIT;
    if(toLoad){
        truck.maxVolume -= requests.at(requestIndex).volume;
        truck.maxWeight -= requests.at(requestIndex).weight;
        profit += (int)requests.at(requestIndex).reward;
        if(!truck.used){
            profit -= (int)truck.cost;
            truck.used = true;
        }
    }
    return max(backtrackingSolver(requests,truck,requestIndex+1,profit,true),backtrackingSolver(requests,truck,requestIndex+1,profit,false));
}

loadLessTruck secondScenario::getLoadlessTruck(const truck &truck) {
    loadLessTruck toAdd;
    toAdd.cost = truck.cost;
    toAdd.maxWeight = truck.maxWeight;
    toAdd.maxVolume = truck.maxVolume;
    return toAdd;
}

void secondScenario::printResult(unsigned int maximumValue) {
    cout << "-*-------------  Report Scenario 2  ------------------*-" << endl;
    cout << " |--> Truck Details: " << endl;
    cout << " |        Number of Trucks: " << trucks.size() << endl;
    cout << " |        Percentage of Trucks used: " << (double)outputTrucks[bestScenario].size()/(double)trucks.size() * 100.0 << "%" << endl;
    cout << " |--> Deliveries: " << endl;
    cout << " |        Number of Deliveries: " << requests.size() << endl;
    cout << " |        Delivered: " << ((double)numberOfRequests(outputTrucks[bestScenario])/(double)requests.size()) * 100.0 << "%" << endl;
    cout << " |--> Balance: " << endl;
    cout << " |        Truck Cost: " << calculateCost(outputTrucks[bestScenario]) << "$" << endl;
    cout << " |        Total profit: " << maximumValue << "$" << endl;
    cout << "-*----------------------------------------------------*-" << endl;
}

void secondScenario::printComputationTime(chrono::duration<double> elapsed_seconds, time_t end_time) {
    cout << "-*-------------  Computation Time --------------------*-" << endl;
    cout << " |--> Time Details: " << endl;
    cout << " |        Elapsed Time: " << elapsed_seconds.count() << "s" << endl;
    cout << " |        Finished Computation At: " << std::ctime(&end_time);
    cout << "-*----------------------------------------------------*-" << endl;
}

void secondScenario::printOnlyMax(unsigned int maximum) {
    cout << "-*-------------  Scenario 2 --------------------------*-" << endl;
    cout << " |--> Maximum Profit : " << maximum <<endl;
    cout << "-*----------------------------------------------------*-" << endl;
}

void secondScenario::exportResult(unsigned int maximum) {
    ofstream file(EXPORT_PATH);
    int counter = 1;
    file << "-*-------------  Report Scenario 2  ------------------*-" << endl;
    file << " |--> Truck Details: " << endl;
    file << " |        Number of Trucks: " << trucks.size() << endl;
    file << " |        Percentage of Trucks used: " << (double)outputTrucks[bestScenario].size()/(double)trucks.size() * 100.0 << "%" << endl;
    file << " |--> Deliveries: " << endl;
    file << " |        Number of Deliveries: " << requests.size() << endl;
    file << " |        Delivered: " << ((double)numberOfRequests(outputTrucks[bestScenario])/(double)requests.size()) * 100.0 << "%" << endl;
    file << " |--> Balance: " << endl;
    file << " |        Truck Cost: " << calculateCost(outputTrucks[bestScenario]) << "$" << endl;
    file << " |        Total profit: " << maximum << "$" << endl;
    file << "-*-------------  Truck Distribution  -----------------*-" << endl;

    for(const auto& truck : outputTrucks[bestScenario]){
        file << " |--> Truck "<< counter <<" : " << endl;
        file << " |        Remaining Volume : " << truck.maxVolume << endl;
        file << " |        Remaining Weight : " << truck.maxWeight << endl;
        file << " |        Cost : " << truck.cost << endl;
        file << " |        Profit : " << truck.profit << endl;
        file << " |        --> Distribution : (Volume,Weight,Reward)" << endl;
        for(const auto &request : truck.truckLoad){
            file << " |                " << request.volume << " " << request.weight << " " << request.reward << endl;
        }
        counter++;
    }
    file << "-*----------------------------------------------------*-" << endl;
    cout << "Written results to : "<< realpath(EXPORT_PATH, nullptr) << endl;
    file.close();
}

void secondScenario::compare(int number) {
    double sum = 0;
    int counter = 0;

    auto start = std::chrono::system_clock::now();

    for(int i = 0; i < number; i++){
        dataIO data(TRUCK_PATH,REQUEST_PATH);

        //create random seed
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<double> dist(15, 25);

        //setup random data, gets a random truck and [15,25] random requests.
        data.readTrucksRandom(1);
        data.readRequestsRandom((int) dist(mt));
        sortedTrucks = data.getTrucks();
        trucks = data.getTrucks();
        sortedRequests = data.getRequests();
        requests = data.getRequests();

        //compare results
        unsigned int firstResult = getMax3(computeByWeight(),computeByVolume(),computeByWeightToVolume());
        unsigned int secondResult = forceCompute();

        if(firstResult && secondResult != 0){
            sum += 100.0-((firstResult*100.0)/(double)secondResult);
            counter++;
        }
        cout << "(" << i+1 << "/" << number << ")" << endl;
    }

    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    cout << "-*-------------  Comparison --------------------------*-" << endl;
    cout << " |--> Number of iterations : " << number << endl;
    cout << " |--> The Greedy is algorithm is : " << sum/(double)counter << "% less efficient." <<endl;
    cout << "-*----------------------------------------------------*-" << endl;

    printComputationTime(elapsed_seconds,end_time);

}




