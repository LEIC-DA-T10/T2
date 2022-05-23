//
// Created by Eduardo Correia on 09/04/2022.
//


#define TRUCK_PATH "..input/"



#ifndef DA_T1_APPLICATIONCONTROLLER_H
#define DA_T1_APPLICATIONCONTROLLER_H
#include "dataIO.h"
#include <cstdlib>
#include "algorithms/firstScenario.h"
#include "algorithms/secondScenario.h"
#include "algorithms/thirdScenario.h"



class applicationController {
private:
    /**
     * State variable, stores which option the user choose to run.
     */
    unsigned int state;
    /**
     * Data variable, stores an instantiated dataIO class for reading and outputting data to/from files.
     */
    dataIO data = dataIO(TRUCK_PATH, REQUEST_PATH);
    /**
     * reads fixed data from the dataset and stores it in the data class.
     */
    void readFixed();
    /**
     * reads random data from the dataset and stores it in the data class.
     */
    void readRandom();
    /**
     * Computes the first scenario algorithm with the data on the data class.
     */
    void computeFirst();
    /**
     * Computes the second scenario algorthm with the data on the data class.
     */
    void computeSecond();
    /**
     * Computes the third scenario algorithm with the data on the data class.
     */
    void computeThird();
    /**
     * Prints the truck related data present on the data class to either the terminal screen or a file.
     */
    void printTruck();
    /**
      * Prints the request related data present on the data class to either the terminal screen or a file.
     */
    void printRequest();
    /**
     * Checks whether a given request vector is empty or not, and prints out an error message if given vector is indeed empty.
     * @param vector request vector to check emptiness.
     * @return returns corresponding boolean to vector emptiness.
     */
    static bool checkForEmpty(const std::vector<request> &vector);
    /**
     * Checks whether a given request vector is empty or not, and prints out an error message if given vector is indeed empty.
     * @param truck truck vector to check emptiness.
     * @return returns corresponding boolean to vector emptiness.
     */
    static bool checkForEmpty(const std::vector<truck> &vector);
public:
    /**
     * Constructor for the application controller class, initializes the state variable.
     */
    applicationController();
    /**
     * Main menu loop, function which reads user input and runs the corresponding code.
     * @return
     */
    bool run();
    /**
     * the setState function sets the application controller state to a given state.
     * @param state returns application state, which if == false, exits the application.
     */
    void setState(int state);
    /**
     * Prints the main menu on the terminal screen.
     */
    static void printMainMenu();
    /**
     * Compares the 2 alternative algorithms for the second scenario.
     */
    static void compareSecond();
    void computeThird_();

    void printRoutes();
};


#endif //DA_T1_APPLICATIONCONTROLLER_H
