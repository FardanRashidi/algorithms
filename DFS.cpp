
void DFSUtil(Point pt, Point dest, int ROW, int COL, int** grid, bool** visited, vector<Point>& path, int nodes) {
    // Mark the current cell as visited and add it to the path
    visited[pt.x][pt.y] = true;
    path.push_back(pt);
    nodes++;
    

    // If we have reached the destination, print the path and return

    if (pt.x == dest.x && pt.y == dest.y) {
        cout << "Nodes : " << nodes << endl;
        cout << "Depth-First Search Path:" << endl;
        for (int i = 0; i < path.size(); i++) {
            if (i > 0) {
                Point prev = path[i-1];
                Point curr = path[i];
                if (prev.x < curr.x) {
                    cout << "DOWN ";
                } else if (prev.x > curr.x) {
                    cout << "UP ";
                } else if (prev.y < curr.y) {
                    cout << "RIGHT ";
                } else {
                    cout << "LEFT ";
                }
            }
            cout << "(" << path[i].x << ", " << path[i].y << ")";
            if (i != path.size() - 1) {
                cout << " -> ";
            }
        }
        cout << endl;
        return;
    }
 
    // Recur for all adjacent cells
    if (isValid(pt.x - 1, pt.y, ROW, COL, grid, visited)) {
        DFSUtil({pt.x - 1, pt.y}, dest, ROW, COL, grid, visited, path, nodes);
    }
    if (isValid(pt.x + 1, pt.y, ROW, COL, grid, visited)) {
        DFSUtil({pt.x + 1, pt.y}, dest, ROW, COL, grid, visited, path, nodes);
    }
    if (isValid(pt.x, pt.y - 1, ROW, COL, grid, visited)) {
        DFSUtil({pt.x, pt.y - 1}, dest, ROW, COL, grid, visited, path, nodes);
    }
    if (isValid(pt.x, pt.y + 1, ROW, COL, grid, visited)) {
        DFSUtil({pt.x, pt.y + 1}, dest, ROW, COL, grid, visited, path, nodes);
    }
    
    // If we have not reached the destination, backtrack by removing the last cell from the path and unmarking the current cell
    path.pop_back();
    visited[pt.x][pt.y] = false;
}

void DFS(Point src, Point dest, int ROW, int COL, int** grid) {
    // Create a 2D array to keep track of visited cells
    bool** visited = new bool*[ROW];
    for (int i = 0; i < ROW; i++) {
        visited[i] = new bool[COL];
        for (int j = 0; j < COL; j++) {
            visited[i][j] = false;
        }
    }
    int nodes;

    // Create a vector to store the current path
    vector<Point> path;
 
    // Perform DFS starting from the source point
    DFSUtil(src, dest, ROW, COL, grid, visited, path, nodes);

    // Free memory
    for (int i = 0; i < ROW; i++) {
        delete[] visited[i];
    }
    delete[] visited;
}

void Research2(Point src, Point dest, Point dest2, int ROW, int COL, int** grid){
    int dist_a = abs(dest.x  - src.x);
    int dist_b = abs(dest2.x  - src.x);
    int dist_c = abs(dest.y  - src.y);
    int dist_d = abs(dest2.y  - src.y);

    if (dist_a < dist_b && dist_c < dist_d) {
        DFS(src, dest, ROW, COL, grid); 
        DFS(dest, dest2, ROW, COL, grid); 
    }
    else {
        DFS(src, dest2, ROW, COL, grid); 
        DFS(dest2, dest, ROW, COL, grid); 
    }
}


int run2(string filename) {

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
    // Run DFS on the input grid  ==============================================
    Research2(src, dest, dest2, ROW, COL, grid); 

    // Free memory
    for (int i = 0; i < ROW; i++) {
        delete[] grid[i];
    }
    delete[] grid;

    

    return 0;
}