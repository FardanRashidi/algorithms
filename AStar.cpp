
struct Point3 {
    int x, y;
    double f, g, h;
};


double heuristic(Point3 p, Point3 dest) {
    // Calculate the heuristic function value using Euclidean distance
    return sqrt((p.x - dest.x) * (p.x - dest.x) + (p.y - dest.y) * (p.y - dest.y));
}

void AStar(Point3 src, Point3 dest, int ROW, int COL, int** grid) {
    // Create a 2D array to keep track of visited cells
    bool** visited = new bool*[ROW];
    for (int i = 0; i < ROW; i++) {
        visited[i] = new bool[COL];
        memset(visited[i], false, sizeof(bool) * COL);
    }

    // Create a priority queue to store the next Point3s to visit
    priority_queue<Point3, vector<Point3>, function<bool(Point3, Point3)>> pq([](Point3 a, Point3 b) { return a.f > b.f; });

    // Mark the source Point3 as visited and add it to the queue
    src.f = 0;
    src.g = 0;
    src.h = heuristic(src, dest);
    visited[src.x][src.y] = true;
    pq.push(src);

    // Create a 2D array to keep track of the parent of each cell
    Point3** parent = new Point3*[ROW];
    for (int i = 0; i < ROW; i++) {
        parent[i] = new Point3[COL];
        memset(&parent[i][0], -1, sizeof(Point3) * COL);
    }

    int nodes;

    // A* loop
    bool foundDest = false;
    while (!pq.empty()) {
        // Dequeue the next Point3 to visit
        Point3 curr = pq.top();
        pq.pop();

        nodes++;

        // Check if we have reached the destination
        if (curr.x == dest.x && curr.y == dest.y) {
            foundDest = true;
            break;
        }

        // Enqueue all adjacent Point3s that are valid and not visited
        if (isValid(curr.x - 1, curr.y, ROW, COL, grid, visited)) {
            Point3 next = {curr.x - 1, curr.y};
            next.g = curr.g + 1;
            next.h = heuristic(next, dest);
            next.f = next.g + next.h;
            visited[next.x][next.y] = true;
            pq.push(next);
            parent[next.x][next.y] = curr;
            // cout << "First if(): " << endl;
            // cout << "g: " << next.g << endl; 
            // cout << "h: " << next.h << endl; 
            // cout << "f: " << next.f << endl; 
        }
        if (isValid(curr.x + 1, curr.y, ROW, COL, grid, visited)) {
            Point3 next = {curr.x + 1, curr.y};
            next.g = curr.g + 1;
            next.h = heuristic(next, dest);
            next.f = next.g + next.h;
            visited[next.x][next.y] = true;
            pq.push(next);
            parent[next.x][next.y] = curr;
            // cout << "Second if(): " << endl;
            // cout << "g: " << next.g << endl; 
            // cout << "h: " << next.h << endl; 
            // cout << "f: " << next.f << endl; 
        }
        if (isValid(curr.x, curr.y - 1, ROW, COL, grid, visited)) {
            Point3 next = {curr.x, curr.y - 1};
            next.g = curr.g + 1;
            next.h = heuristic(next, dest);
            next.f = next.g + next.h;
            visited[next.x][next.y] = true;
            pq.push(next);
            parent[next.x][next.y] = curr;
            // cout << "Third if(): " << endl;
            // cout << "g: " << next.g << endl; 
            // cout << "h: " << next.h << endl; 
            // cout << "f: " << next.f << endl; 
        }
        if (isValid(curr.x, curr.y + 1, ROW, COL, grid, visited)) {
            Point3 next = {curr.x, curr.y + 1};
            next.g = curr.g + 1;
            next.h = heuristic(next, dest);
            next.f = next.g + next.h;
            visited[next.x][next.y] = true;
            pq.push(next);
            parent[next.x][next.y] = curr;
            // cout << "Fourth if(): " << endl;
            // cout << "g: " << next.g << endl; 
            // cout << "h: " << next.h << endl; 
            // cout << "f: " << next.f << endl; 
        }
    }
    
    // Print the path if it exists

    if (foundDest) {
        vector<Point3> path;
        Point3 curr = dest;
        while (curr.x != src.x || curr.y != src.y) {
        path.push_back(curr);
        curr = parent[curr.x][curr.y];
    }
    path.push_back(src);
    reverse(path.begin(), path.end());
    cout << "Nodes : " << nodes << endl;
    cout << "A STAR Path found: " << endl;
    for (int i = 1; i < path.size(); i++) {
        Point3 curr = path[i];
        Point3 parent = path[i - 1];
        if (curr.x < parent.x) {
            cout << "UP ";
        } else if (curr.x > parent.x) {
            cout << "DOWN ";
        } else if (curr.y < parent.y) {
            cout << "LEFT ";
        } else if (curr.y > parent.y) {
            cout << "RIGHT ";
        }
        cout << "(" << path[i].x << "," << path[i].y << ")";
        if (i != path.size() - 1) {
            cout << "-> ";
        }
    }
     cout << endl;
    } else {
     cout << "No path found" << endl;
    }

    // Deallocate memory
    for (int i = 0; i < ROW; i++) {
        delete[] visited[i];
        delete[] parent[i];
    }
    delete[] visited;
    delete[] parent;
}

void Research4(Point3 src, Point3 dest, Point3 dest2, int ROW, int COL, int** grid){
    int dist_a = abs(dest.x  - src.x);
    int dist_b = abs(dest2.x  - src.x);
    int dist_c = abs(dest.y  - src.y);
    int dist_d = abs(dest2.y  - src.y);

    if (dist_a < dist_b && dist_c < dist_d) {
        AStar(src, dest, ROW, COL, grid); 
        AStar(dest, dest2, ROW, COL, grid); 
    }
    else {
        AStar(src, dest2, ROW, COL, grid); 
        AStar(dest2, dest, ROW, COL, grid); 
    }
}


int run4(string filename) {

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
    Point3 src, dest, dest2;
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
    
    // Run A* on the input grid   ==============================================
    Research4(src, dest, dest2, ROW, COL, grid); 

    // Free memory
    for (int i = 0; i < ROW; i++) {
        delete[] grid[i];
    }
    delete[] grid;

    return 0;
}