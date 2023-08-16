

struct Point {
    int x, y;
};

bool isValid(int row, int col, int ROW, int COL, int** grid, bool** visited) {
    // check if the cell is within the grid bounds, not a wall (represented by 1), and not visited
    return (row >= 0) && (row < ROW) &&
           (col >= 0) && (col < COL) &&
           (grid[row][col] == 0) && // check if the cell is not a wall (represented by 1)
           (!visited[row][col]);
}

void BFS(Point src, Point dest, int ROW, int COL, int** grid) {
    int nodes = 0;
    // Create a 2D array to keep track of visited cells
    bool** visited = new bool*[ROW];
    for (int i = 0; i < ROW; i++) {
        visited[i] = new bool[COL];
        memset(visited[i], false, sizeof(bool) * COL);
    }

    // Create a queue to store the next points to visit
    queue<Point> q;

    // Mark the source point as visited and enqueue it
    visited[src.x][src.y] = true;
    q.push(src);

    // Create a 2D array to keep track of the parent of each cell
    Point** parent = new Point*[ROW];
    for (int i = 0; i < ROW; i++) {
        parent[i] = new Point[COL];
        memset(&parent[i][0], -1, sizeof(Point) * COL);
    }

    // BFS loop
    bool foundDest = false;
    while (!q.empty()) {
        // Dequeue the next point to visit
        Point curr = q.front();
        q.pop();

        // Increment the count of visited nodes
        nodes++;

        // Check if we have reached the destination
        if (curr.x == dest.x && curr.y == dest.y) {
            foundDest = true;
            break;
        }

        // Enqueue all adjacent points that are valid and not visited
        if (isValid(curr.x - 1, curr.y, ROW, COL, grid, visited)) {
            visited[curr.x - 1][curr.y] = true;
            q.push({curr.x - 1, curr.y});
            parent[curr.x - 1][curr.y] = curr;
        }
        if (isValid(curr.x + 1, curr.y, ROW, COL, grid, visited)) {
            visited[curr.x + 1][curr.y] = true;
            q.push({curr.x + 1, curr.y});
            parent[curr.x + 1][curr.y] = curr;
        }
        if (isValid(curr.x, curr.y - 1, ROW, COL, grid, visited)) {
            visited[curr.x][curr.y - 1] = true;
            q.push({curr.x, curr.y - 1});
            parent[curr.x][curr.y - 1] = curr;
        }
        if (isValid(curr.x, curr.y + 1, ROW, COL, grid, visited)) {
            visited[curr.x][curr.y + 1] = true;
            q.push({curr.x, curr.y + 1});
            parent[curr.x][curr.y + 1] = curr;
        }
    }
       // Print the shortest path if it exists
    if (foundDest) {
        cout << "Nodes : " << nodes << endl;
        cout << "Breadth-First Search Path:" << endl;
        vector<Point> path;
        Point curr = dest;
        while (!(curr.x == src.x && curr.y == src.y)) {
            path.push_back(curr);
            curr = parent[curr.x][curr.y];
        }
        path.push_back(src);
        for (int i = path.size() - 1; i >= 0; i--) {

            cout << "(" << path[i].x << ", " << path[i].y << ")";
            if (i != 0) {
                cout << " -> ";
            }

            Point prev = path[i-1];
            Point curr = path[i];
            int dx = curr.x - prev.x;
            int dy = curr.y - prev.y;
            if (dx == -1) {
                cout << "DOWN ";
            } else if (dx == 1) {
                cout << "UP ";
            } else if (dy == -1) {
                cout << "RIGHT ";
            } else if (dy == 1) {
                cout << "LEFT ";
            }
        }

        cout << endl;
    } else {
        cout << "There is no path from (" << src.x << ", " << src.y << ") to (" << dest.x << ", " << dest.y << ")" << endl;
    }

    // Free memory
    for (int i = 0; i < ROW; i++) {
        delete[] visited[i];
        delete[] parent[i];
    }
    delete[] visited;
    delete[] parent;
}

void Research(Point src, Point dest, Point dest2, int ROW, int COL, int** grid){
    int dist_a = abs(dest.x  - src.x);
    int dist_b = abs(dest2.x  - src.x);
    int dist_c = abs(dest.y  - src.y);
    int dist_d = abs(dest2.y  - src.y);

    if (dist_a < dist_b && dist_c < dist_d) {
        BFS(src, dest, ROW, COL, grid); 
        BFS(dest, dest2, ROW, COL, grid); 
    }
    else {
        BFS(src, dest2, ROW, COL, grid); 
        BFS(dest2, dest, ROW, COL, grid); 
    }
}



int run(string filename) {

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
    Point src, dest, dest2;
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
    // Run BFS on the input grid  ==============================================
    Research(src, dest, dest2, ROW, COL, grid); 

    // Free memory
    for (int i = 0; i < ROW; i++) {
        delete[] grid[i];
    }
    delete[] grid;
    
    return 0;
}