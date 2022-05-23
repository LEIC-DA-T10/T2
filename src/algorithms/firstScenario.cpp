//
// Created by Eduardo Correia on 09/04/2022.
//


#include "firstScenario.h"
#include <climits>
#include <iostream>
#include <algorithm>

firstScenario::firstScenario(vector<request> requests, vector<truck> trucks) : abstractAlgorithm(requests, trucks) {}

//Main Computing Function
void firstScenario::compute() {
    int response = printMenu();
    vector<truck> a, b;
    string namee;
    switch (response){
        case 2:
            namee= "Sorted by Weight";
            computeWeightSort();
            a = execute(trucks);
            break;
        case 3:
            namee= "Sorted by Volume";
            computeVolumeSort();
            a = execute(trucks);
            break;
        case 4:
            namee= "Sorted by Time";
            computeTimeSort();
            a = execute(trucks);
            break;
        case 5:
            computeTimeSort();
            a = execute(trucks);
            namee= "Sorted by Time";
            computeVolumeSort();
            b = execute(trucks);

            if(a.size() > b.size()){
                a = b;
                namee= "Sorted by Volume";
            }
            computeWeightSort();
            b = execute(trucks);

            if(a.size() > b.size()){
                a = b;
                namee= "Sorted by Weight";
            }
            break;
        default:
            a = execute(trucks);

            break;
    }


    for(truck truck : a){
        if(truck.truckLoad.size() != 0){
            truckLoadPrint(truck.truckLoad);
            cout << endl;
        }
    }
    cout << namee << ":"<< a.size() << " trucks" <<endl<< endl;

}

//Function That Adds Requests To Trucks' Loads Using Bin Packing Best-fit Algorithm
vector<truck> firstScenario::execute(vector<truck> trucks){
    //Passar para uma func e mandar o discarted para outro scenario
    vector<request> discarted;
    unsigned int tempWeight, tempVolume, tempTime;
    auto tempVan =trucks.end();

    for (auto item = requests.begin(); item != requests.end(); item++) {
        tempWeight = UINT_MAX;
        tempTime = UINT_MAX;
        tempVolume = UINT_MAX;
        tempVan =trucks.end();

        if(item->duration >= 86400){ //Greater than 24H
            discarted.push_back(*item);
        } else{
            for (auto van = trucks.begin(); van != trucks.end(); van++) {
                if(van->truckLoad.empty())
                {
                    //Didnt find any containers where it fits
                    if(tempVan == trucks.end()){
                        //assumir que se tiver vazio cabe
                        van->truckLoad.push_back(*item);
                        van->availableWeight -= item->weight;
                        van->availableTime  -= item->duration;
                        van->availableVolume -= item->volume;
                    } else{
                        tempVan->truckLoad.push_back(*item);
                        tempVan->availableWeight -= item->weight;
                        tempVan->availableTime  -= item->duration;
                        tempVan->availableVolume -= item->volume;
                    }

                    break;
                } else{
                    if(!isNegative(*van, *item)){
                        if(tempWeight >= (van->availableWeight - item->weight)  &&  tempTime >= (van->availableTime - item->duration)  &&  tempVolume >= (van->availableVolume - item->duration)){
                            tempWeight = van->availableWeight - item->weight;
                            tempVolume = van->availableVolume - item->volume;
                            tempTime = van->availableTime - item->duration;
                            tempVan = van;
                        }
                    }
                }
            }
        }
    }

    vector<truck>trucks2;

    for (truck truck : trucks){
        if(truck.truckLoad.size() != 0) {
            trucks2.push_back(truck);
        }else{
            break;
        }
    }

    return trucks2;
}



// Funtion that receives a truck and request and compares if their weight, volume or duration returning a boolean value
bool isNegative(truck van, request item){
    return (van.availableWeight < item.weight || van.availableVolume < item.volume || van.availableTime < item.duration);
}


// Funtion that receives a vector of requests and Prints their attributes
void truckLoadPrint(vector<request> truckLoad){
    int sumWeight = 0;
    int sumVolume = 0;
    int sumTime = 0;

    for(request load : truckLoad){

        cout <<"Item Characteristics:"<< endl;
        cout << "Volume: "<< load.volume << endl;
        cout << "Weight: "<< load.weight << endl;
        cout << "Duration: "<< load.duration << endl << endl;
        sumWeight += load.weight;
        sumVolume += load.volume;
        sumTime += load.duration;
    }
    cout <<"-------------------------------------------" << endl;
    cout << "Truck's Load Characteristics:" << endl;
    cout <<"Total Weight: "<< sumWeight << endl;
    cout <<"Total Volume: "<< sumVolume << endl;
    cout <<"Total Time: "<< sumTime << endl;
    cout <<"-------------------------------------------" << endl;
}

//Funtion that sorts by Time
void firstScenario::computeTimeSort(){
    //Sera que altera o vec requests original?
    sort(requests.begin(), requests.end(), requestTimeSort);
}

//Funtion that sorts requests and trucks by Volume
void firstScenario::computeVolumeSort(){
    //Sera que altera o vec requests original?
    sort(requests.begin(), requests.end(), requestVolumeSort);
    sort(trucks.begin(), trucks.end(), truckVolumeSort);
}

//Funtion that sorts requests and trucks by Weight
void firstScenario::computeWeightSort(){
    //Sera que altera o vec requests original?
    sort(requests.begin(), requests.end(), requestWeightSort);
    sort(trucks.begin(), trucks.end(), truckWeightSort);
}

//Clears all truck's loads
void firstScenario::clearTruckLoad(vector<truck> *trucks) {
    for(auto it = trucks->begin(); it != trucks->end(); it++){
        it->availableTime = 86400;
        it->availableVolume = it->maxVolume;
        it->availableWeight = it->maxWeight;
        it->truckLoad.clear();
    }
}

//Prints Menu that Shows Sorting Options
int printMenu() {
    int response;

    cout << "---- Choose Sorting Option ----" << endl;
    cout << "   1 - No Sort" << endl;
    cout << "   2 - Sort By Weight " << endl;
    cout << "   3 - Sort By Volume" << endl;
    cout << "   4 - Sort By Time" << endl;
    cout << "   5 - Best Option" << endl;
    do{
        cin.clear();
        cin.ignore();
        cin >> response;
    }while(response < 1 || response > 5);

    return response;
}


//Sort requests by longest time
bool requestTimeSort(const request &a, const request &b){
    return (a.duration > b.duration);
}

//Sort trucks by heaviest load
bool truckWeightSort(const truck &a, const truck &b){
    return (a.maxWeight > b.maxWeight);
}

//Sort requests by heaviest
bool requestWeightSort(const request &a, const request &b){
    return (a.weight > b.weight);
}

//Sort by biggest truck
bool truckVolumeSort(const truck &a, const truck &b){
    return (a.maxVolume > b.maxVolume);
}

//Sort requests by biggest
bool requestVolumeSort(const request &a, const request &b){
    return (a.volume > b.volume);
}



