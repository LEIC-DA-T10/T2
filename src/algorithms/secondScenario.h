//
// Created by dudud on 09/04/2022.
//

#ifndef DA_T1_SECONDSCENARIO_H
#define DA_T1_SECONDSCENARIO_H

#define SMALLEST_LIMIT -10000
#define EXPORT_PATH "../data/output/scn2.txt"
#define TRUCK_PATH "../data/input/carrinhas.txt"
#define REQUEST_PATH "../data/input/encomendas.txt"

#include "../abstractAlgorithm.h"
#include <iostream>
#include <algorithm>
#include <queue>
#include <chrono>
#include <fstream>
#include "../dataIO.h"
#include <stdlib.h>



class secondScenario : abstractAlgorithm{
private:
    /**
     * Request vector which stores the requests that are then sorted to use in the greedy algorithm approach.
     */
    vector<request> sortedRequests;
    /**
     * Truck vector which stores the trucks that are then sorted to use in the greedy algorithm approach.
     */
    vector<truck> sortedTrucks;
    /**
     * Truck vector array which stores the trucks that each alternative computation outputs.\n
     * The vector in index 0 corresponds to the output of the computeByWeight approach.\n
     * The vector in index 1 corresponds to the output of the computebyVolume approach.\n
     * The vector in index 2 corresponds to the output of the computeByWeightAndVolume approach.\n
     */
    vector<truck> outputTrucks[3];
    int bestScenario;
    /**
     * Returns a boolean that checks whether truck a has a bigger weight to cost ratio than truck b, used as a sorting criteria
     * @param a first truck to check
     * @param b second truck to check
     * @return returns true if a has a bigger weight to cost ratio than b
     */
    static bool truckWeightToCost(const truck &a, const truck &b);
    /**
     * Returns a boolean that checks whether request a has a bigger weight to reward ratio than request b, used as a sorting criteria
     * @param a first request to check
     * @param b second request to check
     * @return returns true if a has a bigger weight to reward ratio than b
     */
    static bool requestWeightToReward(const request &a, const request &b);
    /**
     * Returns a boolean that checks whether request a has a bigger volume to cost ratio than request b, used as a sorting criteria
     * @param a first truck to check
     * @param b second truck to check
     * @return returns true if a has a bigger volume to cost ratio than b
     */
    static bool truckVolumeToCost(const truck &a, const truck &b);
    /**
     * Returns a boolean that checks whether request a has a bigger volume to reward ratio than request b, used as a sorting criteria
     * @param a first request to check
     * @param b second request to check
     * @return returns true if a has a bigger volume to reward ratio than b
     */
    static bool requestVolumeToReward(const request &a, const request &b);
    /**
     * Returns a boolean that checks whether request a has a bigger volume*weight to cost ratio than request b, used as a sorting criteria
     * @param a first truck to check
     * @param b second truck to check
     * @return returns true if a has a bigger volume*weight to cost ratio than b
     */
    static bool wvRatioToCost(const truck &a, const truck &b);
    /**
     * Returns a boolean that checks whether request a has a bigger volume*weight to reward ratio than request b, used as a sorting criteria
     * @param a first request to check
     * @param b second request to check
     * @return returns true if a has a bigger volume*weight to reward ratio than b
     */
    static bool wvRatioToReward(const request &a, const request &b);
    /**
     * Prints all trucks given in the terminal
     * @param trucks truck vector to print
     */
    static void printTrucks(const vector<truck> &trucks);
    /**
     * Prints all requests given in the terminal
     * @param requests request vector to print
     */
    static void printRequests(const vector<request> &requests);
    /**
     * Computes greedy algorithm, using weight as a sorting criteria, uses values stored in the trucks and requests vectors.
     * @return returns profit computed.
     */
    unsigned int computeByWeight();
    /**
     * Computes greedy algorithm, using volume as a sorting criteria, uses values stored in the trucks and requests vectors.
     * @return returns profit computed.
     */
    unsigned int computeByVolume();
    /**
     * Computes greedy algorithm, using weight*volume as a sorting criteria, uses values stored in the trucks and requests vectors.
     * @return returns profit computed.
     */
    unsigned int computeByWeightToVolume();
    /**
     * Tries to insert a given request in the given truck, returns false if the given request does not fit.
     * @param requestToInsert request to try and insert in truck
     * @param truckToInsert truck to insert request
     * @return returns a boolean corresponding to the insertion status.
     */
    static bool checkAndInsert(request requestToInsert, truck &truckToInsert);
    /**
     * Calculates profit with given trucks and request distribution, removing trucks that have profit smaller than 0.
     * @param trucks trucks to check profit from.
     * @return profit from truck and request distribution.
     */
    static int calculateProfit(vector<truck> &trucks);
    /**
     * Gets maximum of 3 values, also sets the bestScenario variable to the corresponding biggest value.
     * @param value1 first value to check
     * @param value2 second value to check
     * @param value3 third value to check
     * @return biggest of the 3 values.
     */
    unsigned int getMax3(unsigned int value1,unsigned int value2,unsigned int value3);
    /**
     * Calculates the cost of the given set of trucks.
     * @param trucks truck vector to check cost of.
     * @return returns an integer corresponding to the cost of the trucks.
     */
    static unsigned int calculateCost(const vector<truck> &trucks);
    /**
     * Gets the number requests distributed across the given trucks.
     * @param trucks truck vector to check.
     * @return returns the number of requests in the given trucks.
     */
    static unsigned int numberOfRequests(const vector<truck> &trucks);
    /**
     * Prints the scenario 2 report, used in the greedy for the greedy algorithm result
     * @param maximumValue output of the greedy algorithm.
     */
    void printResult(unsigned int maximumValue);
    /**
     * Prints the time it took to compute the algorithm, along with the time at which the computation finished.
     * @param elapsed_seconds number of seconds the computation took
     * @param end_time end time for the computation.
     */
    static void printComputationTime(chrono::duration<double> elapsed_seconds,time_t end_time);
    /**
     * Initializes the recursive backtrackingSolver() function.
     * @return maximum profit value.
     */
    unsigned int forceCompute();
    /**
     * Computes the backtracking algorithm, which guarantees the best distribution, however this algorithm is limited to 1 truck and takes a an exponential amount of time.
     * @param requests request vector to deliver.
     * @param truck truck vector to insert the requests into.
     * @param requestIndex current request index.
     * @param profit profit calculated so far.
     * @param toLoad boolean corresponding to whether the current request is loaded or not into the truck.
     * @return maximum profit with given truck and requests.
     */
    static int backtrackingSolver(const vector<request> &requests, loadLessTruck truck,int requestIndex, int profit, bool toLoad);
    /**
     * returns a loadLessTruck version of a truck, which is simply a truck struct, without the truckload vector.
     * @param truck truck to convert
     * @return returns a loadLessTruck version of the given truck.
     */
    static loadLessTruck getLoadlessTruck(const truck &truck);
    /**
     * Prints the result computed with the backtracking algorithm.
     * @param maximum profit calculated with the backtracking algorithm.
     */
    static void printOnlyMax(unsigned int maximum);
    /**
     * Writes a file containing more details about the greedy algorithm output.
     * @param maximum profit calculated with the greedy algorithm.
     */
    void exportResult(unsigned int maximum);
public:
    /**
     * Constructor for the secondScenario class, receives a request and truck vector that are used to compute the algorithms.
     * @param requests request vector.
     * @param trucks truck vector.
     */
    secondScenario(const vector<request>& requests, const vector<truck>& trucks);
    /**
     * Empty constructor for the secondScenario Class, used in the compare option.
     */
    secondScenario();
    /**
     * Used to ask which algorithm the user wants to use. Also handles the overall flow of the class.
     */
    void compute() override;
    /**
     * Compares both algorithms and writes the average difference to the terminal
     * @param number number of iterations.
     */
    void compare(int number);
};
#endif //DA_T1_SECONDSCENARIO_H
