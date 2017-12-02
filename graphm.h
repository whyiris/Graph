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
#ifndef GRAPHM_H
#define GRAPHM_H

#include"limits.h"
#include <iomanip>
#include "nodedata.h"

const int MAXNODES = 101;  // maximum number of nodes

// the struct to keep the current shortest distance 
// and associated path info known at any point in the algorithm
struct TableType {
    bool visited = false; // whether node has been visited
    int dist = INT_MAX;   // the shortest distance from source known so far
    int path = 0;         // previous node in path of min dist
};


class GraphM {
public:

//-------------------------- Constructor ------------------------------------
// Default constructor for class graphm
    GraphM();

//---------------------------- buildGraph -----------------------------------
// buildGraph
// builds up graph node information and 
// adjacency matrix of edges between each node reading from a data file
    void buildGraph(istream&);

//---------------------------- insertEdge -----------------------------------
// insertEdge
// insert and edge into graph between two given nodes
    void insertEdge(int, int, int);

//---------------------------- removeEdge -----------------------------------
// removeEdge
// insert and edge into graph between two given nodes
    void removeEdge(int, int);

//---------------------------- displayAll -----------------------------------
// displayAll
// It uses displayPath as a helper function to display the path
// use couts to demonstrate that the algorithm works properly
    void displayAll() const;

//------------------------------ display ------------------------------------
// display
// It uses printLocation as a helper function to display the location
// uses couts to display the shortest distance with path info 
// between the fromNode to toNode  
    void display(int, int) const;

//------------------------- findShortestPath --------------------------------
// findShortestPath
// perform the Dijkstra's algorithm
// find the shortest path between 
// every node to every other node in the graph
// uses findShortestPathHelper to find the shortest path 
// in one part of the algorithm
    void findShortestPath();



private:
    NodeData data[MAXNODES];     // data for graph nodes
    int C[MAXNODES][MAXNODES];   // cost array, the adjacency matrix
    int size = 0;                // number of nodes in the graph

    // a 2-D array of structs to store visitedm distance, and path
    TableType T[MAXNODES][MAXNODES]; 

//---------------------------- displayPath ----------------------------------
// displayPath
// a helper function to display the path for displayAll
    void displayPath(int, int, int&, int[]) const;

//--------------------------- printLocation --------------------------------
// printLocation
// a helper function for display to display the location of the output
    void printLocation(const int[], const int) const;

//---------------------- findShortestPathHelper ----------------------------
// findShortestPathHelper
// a helper function to fint v
// which is the not visited, shortest distance at this point 
    int findShortestPathHelper(int);
};

#endif

