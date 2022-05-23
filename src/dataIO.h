#ifndef DA_T1_DATAIO_H
#define DA_T1_DATAIO_H


#include <vector>
#include "dataStructs.h"
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class dataIO {
private:
    /**
     * vector of route vectors, which represents the various nodes, and their respective destinations.
     */
    vector<vector<Route>> nodes;
    /**
     * variable that stores the number of nodes read.
     */
    unsigned int numberNodes = 0;
    /**
     * char array which stores the path where the route data is read from.
     */
    const char* inputPath;
public:
    /**
     * Constructor for the dataIO class, receives the path to the request and truck datasets.
     * @param inputPath truck dataset path.
     */
    dataIO(const char* inputPath);
    /**
     * Reads from the truck dataset from the starting index to the finish index.
     * @param start starting index for reading from the dataset.
     * @param finish finishing index for reading from the dataset.
     * @return boolean corresponding to whether the reading of the data was successful
     */
    bool readTrucksFixed(int start, int finish);
    /**
     * Reads from the request dataset from the starting index to the finish index.
     * @param start starting index for reading from the dataset.
     * @param finish finishing index for reading from the dataset.
     * @return boolean corresponding to whether the reading of the data was successful
     */
    bool readRequestsFixed(int start, int finish);
    /**
     * Reads a number of random trucks from the dataset.
     * @param n number of random trucks to read.
     * @return boolean corresponding to whether the reading of the data was successful
     */
    bool readTrucksRandom(int n);
    /**
     * Reads a number of random requests from the dataset.
     * @param n number of random requests to read.
     * @return boolean corresponding to whether the reading of the data was successful
     */
    bool readRequestsRandom(int n);
    /**
     * Gets the number of trucks that haven been read.
     * @return returns the number of trucks that are in the truck vector.
     */
    unsigned int getNumberTrucks();
    /**
     * Gets the number of requests that haven been read.
     * @return returns the number of requests that are in the truck vector.
     */
    unsigned int getNumberRequests();
    /**
     * Gets the vector containing the requests that haven been read.
     * @return returns the request vector.
     */
    std::vector<request> getRequests();
    /**
     * Gets the vector containing the trucks that haven been read.
     * @return returns the truck vector.
     */
    std::vector<truck> getTrucks();
    /**
     * Gets the relative file path for the truck dataset.
     * @return returns char array containing the relative file path to the truck dataset.
     */
    const char* getTruckPath();
    /**
     * Gets the relative file path for the request dataset.
     * @return  returns char array containing the relative file path to the request dataset.
     */
    const char* getRequestPath();
    /**
     * Prints the requests present in the request vector to the terminal or to an external file, depending on the user's answer.
     * @param answer user's option that determines whether the output is written to the terminal or to an external file.
     */
    void printRequests(char answer);
    /**
     * Prints the trucks present in the truck vector to the terminal or to an external file, depending on the user's answer.
     * @param answer user's option that determines whether the output is written to the terminal or to an external file.
     */
    void printTrucks(char answer);
    /**
     * Checks how many trucks are in the dataset, and returns true or false, depending on the success of opening the file.
     * @return boolean that depends on the success of reading the truck dataset.
     */
    bool checkNumberTrucks();
    /**
     * Checks how many requests are in the dataset, and returns true or false, depending on the success of opening the file.
     * @return boolean that depends on the success of reading the truck dataset.
     */
    bool checkNumberRequests();
};


#endif //DA_T1_DATAIO_H