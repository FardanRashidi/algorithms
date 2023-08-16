

struct Point5 {
    int x, y;
    double h; // heuristic value 
};

bool operator<(const Point5& p1, const Point5& p2) {
    return p1.h > p2.h; // Min heap for priority queue
}

void beamSearch(Point5 src, Point5 dest, int ROW, int COL, int** grid) {
    int nodes;
    // Create a 2D array to keep track of visited cells
    bool** visited = new bool*[ROW];
    for (int i = 0; i < ROW; i++) {
        visited[i] = new bool[COL];
        memset(visited[i], false, sizeof(bool) * COL);
    }

    // Create a priority queue to store the next Point5s to visit
    priority_queue<pair<int, Point5>, vector<pair<int, Point5>>, greater<pair<int, Point5>>> pq;

    // Mark the source Point5 as visited and add it to the queue
    visited[src.x][src.y] = true;
    pq.push(make_pair(0, src));

    // Create a 2D array to keep track of the parent of each cell
    Point5** parent = new Point5*[ROW];
    for (int i = 0; i < ROW; i++) {
        parent[i] = new Point5[COL];
        memset(&parent[i][0], -1, sizeof(Point5) * COL);
    }

    // Beam Search loop
    bool foundDest = false;
    while (!pq.empty()) {
        // Dequeue the next beamWidth Point5s to visit
        vector<pair<int, Point5>> nextPoint5s;
        int count = 0;
        while (!pq.empty() && count < COL) {
            pair<int, Point5> curr = pq.top();
            pq.pop();
            nextPoint5s.push_back(curr);
            count++;
        }
        nodes++;
        // Enqueue all adjacent Point5s that are valid and not visited, and update their distance to the destination
        vector<pair<int, Point5>> newPoint5s;
        for (int i = 0; i < nextPoint5s.size(); i++) {
            Point5 curr = nextPoint5s[i].second;
            int currDist = nextPoint5s[i].first;

            if (curr.x == dest.x && curr.y == dest.y) {
                foundDest = true;
                break;
            }

            if (isValid(curr.x - 1, curr.y, ROW, COL, grid, visited)) {
                visited[curr.x - 1][curr.y] = true;
                newPoint5s.push_back(make_pair(currDist + abs(curr.x - 1 - dest.x) + abs(curr.y - dest.y), Point5{curr.x - 1, curr.y}));
                parent[curr.x - 1][curr.y] = curr;
            }
            if (isValid(curr.x + 1, curr.y, ROW, COL, grid, visited)) {
                visited[curr.x + 1][curr.y] = true;
                newPoint5s.push_back(make_pair(currDist + abs(curr.x + 1 - dest.x) + abs(curr.y - dest.y), Point5{curr.x + 1, curr.y}));
                parent[curr.x + 1][curr.y] = curr;
            }
            if (isValid(curr.x, curr.y - 1, ROW, COL, grid, visited)) {
                visited[curr.x][curr.y - 1] = true;
                newPoint5s.push_back(make_pair(currDist + abs(curr.x - dest.x) + abs(curr.y - 1 - dest.y), Point5{curr.x, curr.y - 1}));
                parent[curr.x][curr.y - 1] = curr;
            }
            if (isValid(curr.x, curr.y + 1, ROW, COL, grid, visited)) {
            visited[curr.x][curr.y + 1] = true;
            newPoint5s.push_back(make_pair(currDist + abs(curr.x - dest.x) + abs(curr.y + 1 - dest.y), Point5{curr.x, curr.y + 1}));
            parent[curr.x][curr.y + 1] = curr;
            }
        }

           // Sort the new Point5s in ascending order of their distance to the destination
        sort(newPoint5s.begin(), newPoint5s.end());

        // Enqueue the first beamWidth Point5s in the sorted list into the priority queue
        for (int i = 0; i < min(COL, (int)newPoint5s.size()); i++) {
            pq.push(newPoint5s[i]);
        }

        if (foundDest) {
            break;
        }
    }

    // Print the shortest path from source to destination
    if (foundDest) {

        cout << "Nodes : " << nodes << endl;
        cout << "Shortest Path:" << endl;
        Point5 curr = dest;
        vector<Point5> path;
        while (curr.x != src.x || curr.y != src.y) {
            path.push_back(curr);
            curr = parent[curr.x][curr.y];
        }
        path.push_back(src);
        reverse(path.begin(), path.end());
        for (int i = 0; i < path.size(); i++) {
            Point5 prev = path[i-1];
            Point5 curr = path[i];
            if (prev.x < curr.x) {
                cout << "DOWN ";
            } else if (prev.x > curr.x) {
                cout << "UP ";
            } else if (prev.y < curr.y) {
                cout << "RIGHT ";
            } else {
                cout << "LEFT ";
            }
            cout << "(" << path[i].x << "," << path[i].y << ")";
            if (i < path.size() - 1) {
                cout << "->";
            }
        }
        cout << endl;
    } else {
        cout << "No path found" << endl;
    }

    // Free memory
    for (int i = 0; i < ROW; i++) {
        delete[] visited[i];
        delete[] parent[i];
    }
    delete[] visited;
    delete[] parent;
}


void Research6(Point5 src, Point5 dest, Point5 dest2, int ROW, int COL, int** grid){
    int dist_a = abs(dest.x  - src.x);
    int dist_b = abs(dest2.x  - src.x);
    int dist_c = abs(dest.y  - src.y);
    int dist_d = abs(dest2.y  - src.y);

    if (dist_a < dist_b && dist_c < dist_d) {
        beamSearch(src, dest, ROW, COL, grid); 
        beamSearch(dest, dest2, ROW, COL, grid); 
    }
    else {
        beamSearch(src, dest2, ROW, COL, grid); 
        beamSearch(dest2, dest, ROW, COL, grid); 
    }
}


int run6(string filename) {

    // Open the "input.txt" file for reading
    ifstream infile(filename);
    if (!infile) {
        cerr << "Error: could not open input file" << endl;
        return 1;
    }

    // Read in the row and column size from the first line
    int ROW, COL;
    char c;
    infile >> ROW >> c >> COL;

    // Read in the source and destination coordinates from the second and third lines
    Point5 src, dest, dest2;
    char tmp;
    infile >> src.y >> c >> src.x;
    infile >> dest.y >> c >> dest.x >> tmp >> dest2.y >> c >> dest2.x;

    // Allocate memory for grid
    int** grid = new int*[ROW];
    for (int i = 0; i < ROW; i++) {
        grid[i] = new int[COL];
    }

    // Read in the grid from the last line
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            infile >> grid[i][j];
        }
    }
    infile.close();

    // cout << "Rows: " << ROW << endl;
    // cout << "Columns: " << COL << endl;
    // cout << "Coordinate 1: (" << src.x << ", " << src.y << ")" << endl;
    // cout << "Coordinate 2: (" << dest.x << ", " << dest.y << ")" << endl;
    // cout << "Coordinate 3: (" << dest2.x << ", " << dest2.y << ")" << endl;
    // cout << "Input matrix:" << endl;
    // for (int i = 0; i < ROW; i++) {
    //     for (int j = 0; j < COL; j++) {
    //         cout << grid[i][j] << " ";
    //     }
    // cout << endl;
    // }


    cout << "Filename: " << filename << endl;

    
    // Run Beam Search on the input grid ==============================================
    Research6(src, dest, dest2, ROW, COL, grid); 
 

    // Free memory
    for (int i = 0; i < ROW; i++) {
        delete[] grid[i];
    }
    delete[] grid;
    
    return 0;
}