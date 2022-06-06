# [Logística Urbana para Entrega de Mercadorias]
> First delivery for the subject "Developing Algorithms"

## Compilation Instructions

The user should use Cmake to compile their program. Either download the already created cmake file from [here](https://drive.google.com/file/d/194_bxKhkXDc3hGlTG6jYInOKKfjvCFYs/view?usp=sharing), or create it with the following code.

```cmake
cmake_minimum_required(VERSION 3.15)
project(DA_T1)

add_executable(main src/main.cpp src/dataIO.cpp src/dataIO.h src/dataStructs.h src/applicationController.cpp src/applicationController.h src/abstractAlgorithm.cpp src/abstractAlgorithm.h src/algorithms/firstScenario.cpp src/algorithms/firstScenario.h src/algorithms/secondScenario.cpp src/algorithms/secondScenario.h src/algorithms/thirdScenario.cpp src/algorithms/thirdScenario.h src/deprecated/thirdScenario_.cpp src/deprecated/thirdScenario_.h)

```

## Execution instructions
When the user executes the program, they are greeted by a main menu.
> The menu allows for various operations, but its important to remind of the following

 * The user can reload the data without the need to exit the app.
 * Some scenarios have more than one execution option.
 * After computing a scenario, the loaded data will not be afected.

### Functionalities

* 1 - Reading Fixed data from the dataset.
* 2 - Reading Random data from the dataset.
* 3 - Compute Scenario 1
    * 3.1 - No Sorting
    * 3.2 - Sort By Weight
    * 3.3 - Sort By Volume  
    * 3.4 - Sort By Time
    * 3.5 - Sort by best option
* 4 - Compute Scenario 2
    * 4.1 - Compute Greedy
        * 4.1.1 - Export Truck Distribution to File
        * 4.1.2 - See Truck Distribution Details
    * 4.2 - Compute Backtracking
* 5 - Compute Scenario 3
    * 5.1 - Compute Greedy
        * 5.1.1 - See Truck Distribution Details
    * 5.2 - Compute Backtracking
* 6 - Print Read Request Data
    * 6.1 - Print to a file
    * 6.2 - Print to terminal
* 7 - Print Read Truck Data
    * 7.1 - Print to a file
    * 7.2 - Print to terminal
* 8 - Compare Scenario 2 Algorithms
    * 8.1 - Choose Number of Iterations

## Dependencies
> The program requires the existance of 2 dataset files to read from (**carrinhas.txt** and **encomendas.txt**). These should be located in the **data/input/** folder, starting from the root of your project. 

> Output files are written to the **data/output/** file from the root of your project. 

## GitHub Repository

The project was developed using github, the link to the repository can be found [here](https://github.com/LEIC-DA-T10/T1)

# Self-Avaluation
 * 33% [(@InsertNamePls) | 202005827 | José Carvalho](https://github.com/InsertNamePls) 
 * 33% [(@eduardo-mdc ) | 201909914 | Eduardo Correia](https://github.com/eduardo-mdc) 
 * 33% [(@up201604906 ) | 201604906 | Carlos Madaleno](https://github.com/up201604906)
