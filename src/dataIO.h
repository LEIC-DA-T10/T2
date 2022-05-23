#ifndef DA_T1_DATAIO_H
#define DA_T1_DATAIO_H


#include <vector>
#include "dataStructs.h"
#include <iostream>
#include <fstream>
#include <cstring>

#define NODE_PRINT_PATH "../output/nodes.txt"


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
    string inputPath;
public:
    /**
     * Constructor for the dataIO class, receives the input file.
     * @param inputPath route dataset path.
     */
    dataIO(string inputPath);
    /**
     * Gets the number of nodes that haven been read.
     * @return returns the number of nodes that are in the node vector.
     */
    unsigned int getNumberNodes();
    /**
     * Gets the vector containing the nodes that haven been read.
     * @return returns the node vector.
     */
    vector<vector<Route>> getNodes();
    /**
     * Gets the relative file path for the node dataset.
     * @return returns char array containing the relative file path to the node dataset.
     */
    string getInputPath();
    /**
     * Prints the nodes present in the node vector to the terminal or to an external file, depending on the user's answer.
     * @param answer user's option that determines whether the output is written to the terminal or to an external file.
     */
    void printNodes(char answer);

    bool readNodes();
};


#endif //DA_T1_DATAIO_H