cmake_minimum_required(VERSION 3.15)
project(DA_T1)

add_executable(main src/main.cpp src/dataIO.cpp src/dataIO.h src/dataStructs.h src/applicationController.cpp src/applicationController.h src/abstractAlgorithm.cpp src/abstractAlgorithm.h src/algorithms/firstScenario.cpp src/algorithms/firstScenario.h src/algorithms/secondScenario.cpp src/algorithms/secondScenario.h src/algorithms/thirdScenario.cpp src/algorithms/thirdScenario.h src/algorithms/thirdScenario_.cpp src/algorithms/thirdScenario_.h)
target_link_libraries(main gtest_main)

