
#ifndef DA_T1_DATASTRUCTS_H
#define DA_T1_DATASTRUCTS_H

#include <vector>
#include <limits>

struct Route{
    int destination = -1;
    int source = -1;
    int capacity = -1;
    int duration = -1;
    bool visited = false;
    int flow = 0;
};

struct Vertex{
    int index{};
    int capacity{};
    int source = -1;
    int distance = std::numeric_limits<int>::max();
    std::vector<Route> linked_vertex{};
};

#endif //DA_T1_DATASTRUCTS_H
