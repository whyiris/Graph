//---------------------------------------------------------------------------
// graphl.h
// Simple class graphl
// Authors: Hoi Yan Wu
//---------------------------------------------------------------------------
// graphl class:  the graph implementation
//   for depth-first search
//   by using adjacency list (array of lists)
//
// Assumptions:
//   -- no more than 100 nodes
//---------------------------------------------------------------------------
#ifndef GRAPHL_H
#define GRAPHL_H
#include "nodedata.h"


struct EdgeNode;      // store edge info

struct GraphNode {
    EdgeNode* edgeHead;   // head of the list of edges
    NodeData data;        // data information about each node

	// for depth-first search to see wheather the node is visited
    bool visited = false; 
};


struct EdgeNode {
    int adjGraphNode;     // subscript of the adjacent graph node
    EdgeNode* nextEdge;   // the next EdgeNode in the list
};


class GraphL {
public:

//-------------------------- Constructor ------------------------------------
// Default constructor for class graphl
// 
    GraphL();

//---------------------------- Destructor -----------------------------------
// Destructor for class graphl
// deallocate the memory by using makeEmpty helper function
    ~GraphL();

//---------------------------- buildGraph -----------------------------------
// buildGraph
// builds up graph node information and 
// adjacency list of edges between each node reading from a data file
// the edgenode is inserted at the beginnig of adjacency list 
    void buildGraph(istream&);

//--------------------------- displayGraph ----------------------------------
// displayGraph
// display each node information and edge in the graph
    void displayGraph() const;

//-------------------------- depthFirstSearch -------------------------------
// depthFirstSearch
// makes a depth-first search by using depthFirstSearchHelper
// displays each node in depth-first order
    void depthFirstSearch() const;


//------------------------------ makeEmpty ----------------------------------
// makeEmpty
// Empty the adjacency list, deallocate all the memory
    void makeEmpty();

    //void displayGraphHelper(EdgeNode*, int &);

private:
    int size;                         // the number of nodes
    GraphNode *adjList[100]{ NULL };  // array of GraphNodes


//----------------------- depthFirstSearchHelper ----------------------------
// depthFirstSearchHelper
// a helper function to perform depth-first search
// displays each node in depth-first order
    void depthFirstSearchHelper(int) const;

};
#endif