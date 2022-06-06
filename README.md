# [Agência de Viagenss]
> Second delivery for the subject "Developing Algorithms"

## Compilation Instructions

The user should use Cmake to compile their program. Either download the already created cmake file from [here](https://drive.google.com/file/d/194_bxKhkXDc3hGlTG6jYInOKKfjvCFYs/view?usp=sharing), or create it with the following code.

```cmake
cmake_minimum_required(VERSION 3.15)
project(DA_T1)

add_executable(main src/main.cpp src/dataIO.cpp src/dataIO.h src/dataStructs.h src/applicationController.cpp src/applicationController.h src/abstractAlgorithm.cpp src/abstractAlgorithm.h src/algorithms/firstScenario.cpp src/algorithms/firstScenario.h src/algorithms/secondScenario.cpp src/algorithms/secondScenario.h)

```

## Execution instructions
When the user executes the program, they are greeted by a main menu.
> The menu allows for various operations, but its important to remind of the following

 * The user can reload the data without the need to exit the app.
 * Some scenarios have more than one execution option.
 * After computing a scenario, the loaded data will not be afected.

### Functionalities

* 1 - Reading Fixed data from the dataset.
* 2 - Compute Scenario 1
    * 2.1 - Max Flow
    * 2.2 - Max Flow, Min Transfers,Pareo-Optimal Solutions
* 3 - Compute Scenario 2
    * 3.1 - Find Path given Group Size
    * 3.2 - Fix path
    * 3.3 - Max Group Size and Path
    * 3.4 - Find meting time
    * 3.5 - Max waiting time
* 4 - Print Routes

## Dependencies
> The program requires the existance of 10 dataset files to read from (** in[1-9]_b.txt **). These should be located in the **input/** folder, starting from the root of your project. 

> Output files are written to the **output/** file from the root of your project. 

## GitHub Repository

The project was developed using github, the link to the repository can be found [here](https://github.com/LEIC-DA-T10/T2)

# Self-Avaluation
 * 33% [(@InsertNamePls) | 202005827 | José Carvalho](https://github.com/InsertNamePls) 
 * 33% [(@eduardo-mdc ) | 201909914 | Eduardo Correia](https://github.com/eduardo-mdc) 
 * 33% [(@up201604906 ) | 201604906 | Carlos Madaleno](https://github.com/up201604906)
