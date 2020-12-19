#define V 15

#include <iostream>
#include <vector>

using namespace std;

int** Map() {                                               // creates the 15 node map
    int** map;
    map = new int*[V];

    for(int i = 0; i < V; i++) {                            // initializes all of the values in the map
        map[i] = new int[V];
        for(int j = 0; j < V; j++) { map[i][j] = 0; }
    }

    map[0][1] = 14;
    map[0][11] = 14;
    map[0][12] = 9;

    map[1][0] = 14;
    map[1][2] = 9;
    map[1][10] = 17;
    map[1][11] = 11;

    map[2][1] = 9;
    map[2][3] = 5;
    map[2][9] = 20;
    map[2][10] = 13;

    map[3][2] = 5;
    map[3][4] = 17;
    map[3][9] = 19;

    map[4][3] = 17;
    map[4][5] = 16;
    map[4][9] = 4;

    map[5][4] = 16;
    map[5][6] = 8;
    map[5][7] = 9;
    map[5][9] = 12;

    map[6][5] = 8;
    map[6][7] = 6;

    map[7][5] = 9;
    map[7][6] = 6;
    map[7][8] = 7;
    map[7][9] = 12;
    map[7][13] = 23;
    map[7][14] = 10;

    map[8][7] = 7;
    map[8][9] = 13;
    map[8][10] = 5;
    map[8][14] = 6;

    map[9][2] = 20;
    map[9][3] = 19;
    map[9][4] = 4;
    map[9][5] = 12;
    map[9][7] = 12;
    map[9][8] = 13;
    map[9][10] = 7;

    map[10][1] = 17;
    map[10][2] = 13;
    map[10][8] = 5;
    map[10][9] = 7;
    map[10][11] = 18;
    map[10][14] = 8;

    map[11][0] = 14;
    map[11][1] = 11;
    map[11][10] = 18;
    map[11][12] = 15;
    map[11][14] = 9;

    map[12][0] = 9;
    map[12][11] = 15;
    map[12][13] = 11;
    map[12][14] = 15;

    map[13][7] = 23;
    map[13][12] = 11;
    map[13][14] = 18;

    map[14][7] = 10;
    map[14][8] = 6;
    map[14][10] = 8;
    map[14][11] = 9;
    map[14][12] = 15;
    map[14][13] = 18;

    return map;
}

int minDistance(const int dist[], const bool sptSet[]) {    // min distance between nodes
    int min = INT_MAX;
    int min_index;

    /*
     * checks if there is a connection and if the distance is less than the current min
     * sets the new min and changes in the min index to i
     */
    for (int i = 0; i < V; i++) {
        if (!sptSet[i] && dist[i] <= min) {
            min = dist[i];
            min_index = i;
        }
    }

    /*
     * return min index
     * used in the getDistance function
     */
    return min_index;
}

int getDistance(int** graph, int src, int end) {            // Dijkstra’s shortest path algorithm
    /*
     * integer distance array to solve for the shortest path to each vertex from the source vertex
     * boolean shortest path tree array to store if if the vertex i is included
     */
    int dist[V];
    bool sptSet[V];

    for (int i = 0; i < V; i++) {                           // initialize dist and spt
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    dist[src] = 0;                                          // set the start value to 0

    /*
     * loops through all of the values in the map
     * finds the min distance
     */
    for (int i = 0; i < V - 1; i++) {
        int u = minDistance(dist, sptSet);

        sptSet[u] = true;

        /*
         * creates a list of all the min distances
         * organized by distance from source node to...
         */
        for (int j = 0; j < V; j++) {
            if (!sptSet[j] && graph[u][j] && dist[u] != INT_MAX && dist[u] + graph[u][j] < dist[j]) {
                dist[j] = dist[u] + graph[u][j];
            }
        }
    }

    return dist[end];
}

int* getNeighbors(int** map, int v) {                       // return all the adjacent nodes to a source node
    int* connectedV = new int[V];

    /*
     * checks if connection is greater than zero
     * stores the nodes greater than zero and returns
     */
    for(int i = 0; i < V; i++) { if(map[v][i] > 0) { connectedV[i] = i; }}

    return connectedV;
}

void display(int** m) {                                     // display all adjacent nodes
    /*
     * nested for loop running through all values in the map
     * couts all outputs
     */
    for(int i = 0; i < 15; i++) { for(int j = 0; j < 15; j++) { cout << m[i][j] << "\t"; }
        cout << endl;
    }
}

int main() {
    int vertex, start, end;
    int** newMap = Map();

    display(newMap);

    cout << endl;

    cout << "Vertex to Analyze (1-15): "; cin >> vertex; cout << endl;
    int* connectedV = getNeighbors(newMap, vertex);
    for(int i = 0; i < V; i++) { if(connectedV[i] > 0) { cout << connectedV[i] << endl; }}

    cout << endl;

    cout << "Enter a Start and End Value (1-15): "; cin >> start >> end; cout << endl;
    cout << getDistance(newMap, start, end);

    return 0;
}
