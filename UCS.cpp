
struct Point2 {
    int x, y;
    bool operator<(const Point2& other) const {
    return (x < other.x) || (x == other.x && y < other.y);
}
};


void UCS(Point2 src, Point2 dest, int ROW, int COL, int** grid) {
    // Initialize the visited matrix and cost matrix
    bool** visited = new bool*[ROW];
    int** cost = new int*[ROW];
    Point2** parent = new Point2*[ROW];
    for (int i = 0; i < ROW; i++) {
        visited[i] = new bool[COL];
        cost[i] = new int[COL];
        parent[i] = new Point2[COL];
        for (int j = 0; j < COL; j++) {
            visited[i][j] = false;
            cost[i][j] = INT_MAX; // initialize all costs to infinity
        }
    }

    // Create a priority queue to store the Point2s to visit
    priority_queue<pair<int, Point2>, vector<pair<int, Point2>>, greater<pair<int, Point2>>> pq;
    pq.push(make_pair(0, src)); // push the source Point2 with a cost of 0

    // Initialize the cost of the source Point2 to 0
    cost[src.x][src.y] = 0;

    // Initialize the node count
    int nodes = 0;

    // While the queue is not empty
    while (!pq.empty()) {
        // Get the current Point2 from the queue
        Point2 curr = pq.top().second;
        pq.pop();

        // If the current Point2 is the destination, return the cost and path
        if (curr.x == dest.x && curr.y == dest.y) {
            cout << "Nodes : " << nodes << endl;
            cout << "Cost to reach (" << dest.x << ", " << dest.y << "): " << cost[dest.x][dest.y] << endl;
            cout << "Path: ";
            Point2 p = dest;
            while (!(p.x == src.x && p.y == src.y)) {
                cout << "(" << p.x << ", " << p.y << ") " << "<- ";
                p = parent[p.x][p.y];
            }
            cout << "(" << src.x << ", " << src.y << ")" << endl;
            return;
        }

        // If the current Point2 has already been visited, continue to the next Point2
        if (visited[curr.x][curr.y]) {
            continue;
        }

        // Mark the current Point2 as visited
        visited[curr.x][curr.y] = true;

        nodes++;

        // Generate the neighboring Point2s
        int dx[4] = {1, -1, 0, 0};
        int dy[4] = {0, 0, 1, -1};
        for (int i = 0; i < 4; i++) {
            int row = curr.x + dx[i];
            int col = curr.y + dy[i];

            // Check if the neighboring Point2 is valid
            if (isValid(row, col, ROW, COL, grid, visited)) {
                // Calculate the cost to reach the neighboring Point2 from the current Point2
                int newCost = cost[curr.x][curr.y] + 1; // uniform cost

                // Update the cost of the neighboring Point2 if it is lower than the current cost
                if (newCost < cost[row][col]) {
                    cost[row][col] = newCost;
                    parent[row][col] = curr;
                    pq.push(make_pair(newCost, Point2{row, col}));
                }
            }
        }
    }

    // If the destination cannot be reached, print an error message
    cout << "Destination cannot be reached" << endl;

    // Free memory
    for (int i = 0; i < ROW; i++) {
        delete[] visited[i];
        delete[] cost[i];
    }
    delete[] visited;
    delete[] cost;
    return;
}

void Research3(Point2 src, Point2 dest, Point2 dest2, int ROW, int COL, int** grid){
    int dist_a = abs(dest.x  - src.x);
    int dist_b = abs(dest2.x  - src.x);
    int dist_c = abs(dest.y  - src.y);
    int dist_d = abs(dest2.y  - src.y);

    if (dist_a < dist_b && dist_c < dist_d) {
        UCS(src, dest, ROW, COL, grid); 
        UCS(dest, dest2, ROW, COL, grid); 
    }
    else {
        UCS(src, dest2, ROW, COL, grid); 
        UCS(dest2, dest, ROW, COL, grid); 
    }
}


int run3(string filename) {
    
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
    Point2 src, dest, dest2;
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

    // Run UCS on the input grid  ==============================================
    Research3(src, dest, dest2, ROW, COL, grid); 

    // Free memory
    for (int i = 0; i < ROW; i++) {
        delete[] grid[i];
    }
    delete[] grid;

    

    return 0;
}