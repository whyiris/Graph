//---------------------------------------------------------------------------
// graphm.h
// Simple class graphm
// Authors: Hoi Yan Wu
//---------------------------------------------------------------------------
// graphl class:  the graph implementation 
//   for Dijkstra's shortest path algorithm
//   by using adjacency matrix 
//
// Assumptions:
//   -- no more than 100 nodes
//---------------------------------------------------------------------------

#include "graphm.h"
#include "nodedata.h"

//-------------------------- Constructor ------------------------------------
// Default constructor for class graphm
GraphM::GraphM() {
    for (int i = 0; i < MAXNODES; i++) {
        for (int j = 0; j < MAXNODES; j++) {

			// initialize the adjacency matrix to 0
            C[i][j] = 0;

            T[i][j].path = 0;         // initialize the path to 0
            T[i][j].visited = false;  // set visited to false
            T[i][j].dist = INT_MAX;   // set all dist to infinity
        }
    }
} // end of Constructor

//---------------------------- buildGraph -----------------------------------
// buildGraph
// builds up graph node information and 
// adjacency matrix of edges between each node reading from a data file
void GraphM::buildGraph(istream & infile) {
    int fromNode, toNode, weight;      // from and to node ends of edge

    infile >> size;                   // read the number of nodes
    if (infile.eof()) return;         // stop if no more data

    string s;                         // used to read through to end of line
    getline(infile, s);

    // read graph node information
    for (int i = 1; i <= size; i++) {
        getline(infile, s);
        data[i].setData(s);
        // read using setData of the NodeData class,
        // something like: 
        //    adjList[i].data.setData(infile);
        // where adjList is the array of GraphNodes and
        // data is the NodeData object inside of GraphNode
    }

    // read the edge data and add to the adjacency list
    for (;;) {
        infile >> fromNode >> toNode>> weight;
		
		// end of edge data
        if (fromNode == 0 && toNode == 0 && weight==0) return;     

        // insert the edge into the adjacency list for fromNode
        C[fromNode][toNode] = weight;
    }
} // end of buildGraph


//---------------------------- insertEdge -----------------------------------
// insertEdge
// insert an edge into graph between two given nodes
void GraphM::insertEdge(int i, int j, int weight) {
    // if the node is not exist in the graph

    if (i > size || j > size) {
        return;
    }
    C[i][j] = weight;
} // end of insertEdge



//---------------------------- removeEdge -----------------------------------
// removeEdge
// remove an edge from graph between two given nodes
void GraphM::removeEdge(int i, int j) {
	C[i][j] = 0;
} // end of removeEdge




//---------------------------- displayAll -----------------------------------
// displayAll
// It uses displayPath as a helper function to display the path
// use couts to demonstrate that the algorithm works properly
void GraphM::displayAll() const{
    cout << "Description         ";
    cout << "From node   To node   Dijkstra\'s     ";
    cout << "Path      " << endl;
    for (int i = 1; i <=size; i++) {
        cout << data[i] << endl;
        for (int j = 1; j <= size; j++) {

            if (i!=j) {
                if (T[i][j].dist != INT_MAX) {
		    cout << setw(25) << i;
		    cout << setw(10) << j << setw(10) << T[i][j].dist;
                    if (T[i][j].path == i) {
                        cout << setw(13) << i << " " << j<< endl;

                    }
                    else {
                        int pathArray[MAXNODES] = { 0 };
                        int count = 0;
                        displayPath(i, j, count, pathArray);
                        cout << j << endl;
                    }
                }
                else {
		    cout << setw(25) << i;
		    cout << setw(10) << j << setw(10) << "----" << endl;
                }
            }
        }
    }
    cout << endl;
} // end of displayAll


//---------------------------- displayPath ----------------------------------
// displayPath
// a helper function to display the path for displayAll
// display the path recursively
void GraphM::displayPath(int i, int j, int& count, int pathArray[]) const {
	if (T[i][j].path == i) {
	    cout << setw(13) << T[i][j].path << " ";
	    pathArray[count] = T[i][j].path;
	    count++;
	}
	else {
	    displayPath(i, T[i][j].path, count, pathArray);
	    cout << T[i][j].path << " ";
	    pathArray[count] = T[i][j].path;
	    count++;
	}
} // end of displayPath





//------------------------- findShortestPath -------------------------------
// findShortestPath
// perform the Dijkstra's algorithm
// find the shortest path between 
// every node to every other node in the graph
// uses findShortestPathHelper to find the shortest path 
// in one part of the algorithm
void GraphM::findShortestPath() {

	// find the shortest distance for each source
    for (int source = 1; source <= size; source++) {
        T[source][source].dist = 0;
        T[source][source].visited = true;


        for (int i = 1; i <= size; i++) {
            if (C[source][i] != 0) {
                T[source][i].dist = C[source][i];
                T[source][i].path = source;
            }
        }

	// find the shortest distance from source to all other nodes
        for (int i = 1; i <= size; i++) {

	    // find v, which is the not visited, 
	    // shortest distance at this point 
            int v = findShortestPathHelper(source);

			// mark v visited
            T[source][v].visited = true;

	    // for each w adjacent to v
            for (int w = 1; w <= size; w++) {

		//for each w adjacent to v and w is not visited
                if (!T[source][w].visited && C[v][w]!=0) { 
                    if (T[source][w].dist > (T[source][v].dist + C[v][w])) {
                        T[source][w].dist = T[source][v].dist + C[v][w];
                        T[source][w].path = v;                        
                    }
                }
            }
        }
    }
} // end of findShortestPath


//---------------------- findShortestPathHelper ----------------------------
// findShortestPathHelper
// a helper function to fint v
// which is the not visited, shortest distance at this point 
int GraphM::findShortestPathHelper(int source) {
    int shortest = INT_MAX;
    int v = 0;
    for (int i = 1; i <= size; i++) {
        if (T[source][i].dist < shortest 
			&& T[source][i].dist>0 && ! T[source][i].visited) {
            shortest = T[source][i].dist;
            v = i;
        }
    }
    return v;
} // end of findShortestPathHelper





//------------------------------ display -----------------------------------
// display
// It uses printLocation as a helper function to display the location
// uses couts to display the shortest distance with path info 
// between the fromNode to toNode  
void GraphM::display(int i, int j) const{
    int pathArray[MAXNODES] = { 0 };
    int count = 0;

    if (T[i][j].dist != INT_MAX) {
        cout << setw(5) << i << setw(10) << j << setw(10) << T[i][j].dist;
        if (T[i][j].path == i) {
            cout << setw(13) << i << " " << j << endl;
        }
        else {
            displayPath(i, j, count, pathArray);
            cout << j << endl;

        }
        printLocation(pathArray, count);
        cout << data[j] << endl << endl;
    }
    else {
	cout << setw(5) << i << setw(10);
	cout << j << setw(10) << "----" << endl << endl;
    }
} // end of display


//--------------------------- printLocation --------------------------------
// printLocation
// a helper function for display to display the location of the output
void GraphM::printLocation(const int pathArray[], const int count) const {

    for (int i = 0; i < count; i++) {
        if (pathArray != 0) {
            cout << data[pathArray[i]] << endl;
        }
    }
} // end of printLocation