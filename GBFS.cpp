
struct Point4 {
    int x, y;
    double h; // heuristic2 value 
};

bool operator<(const Point4& p1, const Point4& p2) {
    return p1.h > p2.h; // Min heap for priority queue
}

double heuristic2(Point4 p1, Point4 p2) {
    // Euclidean distance between p1 and p2
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

void GBFS(Point4 src, Point4 dest, int ROW, int COL, int** grid) {
    int nodes;
    // Create a 2D array to keep track of visited cells
    bool** visited = new bool*[ROW];
    for (int i = 0; i < ROW; i++) {
        visited[i] = new bool[COL];
        memset(visited[i], false, sizeof(bool) * COL);
    }

    // Create a priority queue to store the next Point4s to visit, sorted by their heuristic2 values
    priority_queue<Point4> pq;

    // Mark the source Point4 as visited and add it to the priority queue
    src.h = heuristic2(src, dest);
    visited[src.x][src.y] = true;
    pq.push(src);

    // Create a 2D array to keep track of the parent of each cell
    Point4** parent = new Point4*[ROW];
    for (int i = 0; i < ROW; i++) {
        parent[i] = new Point4[COL];
        memset(&parent[i][0], -1, sizeof(Point4) * COL);
    }

    // GBFS loop
    bool foundDest = false;
    while (!pq.empty()) {
        // Dequeue the next Point4 to visit
        Point4 curr = pq.top();
        pq.pop();

        nodes++;

        // Check if we have reached the destination
        if (curr.x == dest.x && curr.y == dest.y) {
            foundDest = true;
            break;
        }

        // Enqueue all adjacent Point4s that are valid and not visited, and update their heuristic2 values
        if (isValid(curr.x - 1, curr.y, ROW, COL, grid, visited)) {
            Point4 next = {curr.x - 1, curr.y};
            next.h = heuristic2(next, dest);
            visited[curr.x - 1][curr.y] = true;
            pq.push(next);
            parent[curr.x - 1][curr.y] = curr;
        }
        if (isValid(curr.x + 1, curr.y, ROW, COL, grid, visited)) {
            Point4 next = {curr.x + 1, curr.y};
            next.h = heuristic2(next, dest);
            visited[curr.x + 1][curr.y] = true;
            pq.push(next);
            parent[curr.x + 1][curr.y] = curr;
        }
        if (isValid(curr.x, curr.y - 1, ROW, COL, grid, visited)) {
            Point4 next = {curr.x, curr.y - 1};
            next.h = heuristic2(next, dest);
            visited[curr.x][curr.y - 1] = true;
            pq.push(next);
            parent[curr.x][curr.y - 1] = curr;
        }
        if (isValid(curr.x, curr.y + 1, ROW, COL, grid, visited)) {
            Point4 next = {curr.x, curr.y + 1};
            next.h = heuristic2(next, dest);
            visited[curr.x][curr.y + 1] = true;
            pq.push(next);
            parent[curr.x][curr.y + 1] = curr;
        }
    }
    
    // If the destination was found, print the path from source to destination
    if (foundDest) {
        vector<Point4> path;
        Point4 curr = dest;
        while (curr.x != -1 && curr.y != -1) {
            path.push_back(curr);
            curr = parent[curr.x][curr.y];
        }
        reverse(path.begin(), path.end());

        cout << "Nodes : " << nodes << endl;
        cout << "Greedy Best First Search Path:" << endl;
        for (int i = 0; i < path.size(); i++) {
            Point4 prev = path[i-1];
            Point4 curr = path[i];
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
            if (i != path.size() - 1) {
                cout << "-> ";
            }
        }
        cout << endl;
    } else {
        cout << "Destination not found." << endl;
    }

    // Deallocate the memory used by the 2D arrays
    for (int i = 0; i < ROW; i++) {
        delete[] visited[i];
        delete[] parent[i];
    }
    delete[] visited;
    delete[] parent;
}

void Research5(Point4 src, Point4 dest, Point4 dest2, int ROW, int COL, int** grid){
    int dist_a = abs(dest.x  - src.x);
    int dist_b = abs(dest2.x  - src.x);
    int dist_c = abs(dest.y  - src.y);
    int dist_d = abs(dest2.y  - src.y);

    if (dist_a < dist_b && dist_c < dist_d) {
        GBFS(src, dest, ROW, COL, grid); 
        GBFS(dest, dest2, ROW, COL, grid); 
    }
    else {
        GBFS(src, dest2, ROW, COL, grid); 
        GBFS(dest2, dest, ROW, COL, grid); 
    }
}


int run5(string filename) {

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
    Point4 src, dest, dest2;
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

    
    // Run GBFS on the input grid ==============================================
    Research5(src, dest, dest2, ROW, COL, grid); 

    // Free memory
    for (int i = 0; i < ROW; i++) {
        delete[] grid[i];
    }
    delete[] grid;
    
    return 0;
}