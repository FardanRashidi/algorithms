#include <iostream>
#include <queue>
#include <cstring>
#include <fstream>
#include <vector>
#include <cmath>
#include <functional> 
#include <climits>
using namespace std;

#include "BFS.cpp"
#include "DFS.cpp"
#include "GBFS.cpp"
#include "AStar.cpp"    
#include "UCS.cpp"
#include "BeamSearch.cpp"


using namespace std;

int main(int argc, char** argv){
    // Check if the argument is provided
    if (argc < 3) {
        cout << "No argument provided." << endl;
        return 1;
    }
    
    string filename = argv[1];
    string algorithm = argv[2];
    if (algorithm == "BFS") {
        run(filename);
    } else if (algorithm == "DFS") {
        run2(filename);
    } else if (algorithm == "UCS") {
        run3(filename);
    } else if (algorithm == "AStar") {
        run4(filename);
    } else if (algorithm == "GBFS") {
        run5(filename);
    } else if (algorithm == "BeamSearch") {
        run6(filename);
    } else {
        cout << "Invalid algorithm specified." << endl;
    }

    return 0;
}