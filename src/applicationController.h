//
// Created by Eduardo Correia on 09/04/2022.
//


#define INPUT_PATH "../input/"



#ifndef DA_T1_APPLICATIONCONTROLLER_H
#define DA_T1_APPLICATIONCONTROLLER_H
#include "dataIO.h"
#include <cstdlib>
#include "algorithms/firstScenario.h"
#include "algorithms/secondScenario.h"



class applicationController {
private:
    /**
     * State variable, stores which option the user choose to run.
     */
    unsigned int state;
    /**
     * Data variable, stores an instantiated dataIO class for reading and outputting data to/from files.
     */
    dataIO data;
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
     * Computes the second scenario algorithm with the data on the data class.
     */
    void computeSecond();

    void printRoutes();

    static bool checkForEmpty(const map<int, vector<Route>> &vector);
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
};


#endif //DA_T1_APPLICATIONCONTROLLER_H
