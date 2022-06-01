
#ifndef DA_T1_DATASTRUCTS_H
#define DA_T1_DATASTRUCTS_H

#include <vector>

struct Route{
    int destination = -1;
    int capacity = -1;
    int duration = -1;
    bool visited = false;
    int flow = 0;
};

#endif //DA_T1_DATASTRUCTS_H
