//---------------------------------------------------------------------------
// graphl.cpp
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
#include "graphl.h"
#include "nodedata.h"
// Uses getline from string class, included in nodedata.h .
// Be sure to include nodedata.h which includes <string> .
// If you use dynamic memory (you don't use STL list), the makeEmpty()
// function deallocates all the memory; the destructor would call makeEmpty()


//-------------------------- Constructor ------------------------------------
// Default constructor for class graphl
GraphL::GraphL() {
    //adjList = new GraphNode[size]{ NULL };
} // end of Constructor

//---------------------------- Destructor -----------------------------------
// Destructor for class graphl
// deallocate the memory by using makeEmpty helper function
GraphL::~GraphL() {
    makeEmpty();
} // end of Destructor

//---------------------------- buildGraph -----------------------------------
// buildGraph
// builds up graph node information and 
// adjacency list of edges between each node reading from a data file
// the edgenode is inserted at the beginnig of adjacency list
void GraphL::buildGraph(istream& infile) {
    int fromNode, toNode;            // from and to node ends of edge

    makeEmpty();                     // clear the graph of memory 

    infile >> size;                  // read the number of nodes
    if (infile.eof()) return;        // stop if no more data
    string s;                        // used to read through to end of line
    getline(infile, s);

    // read graph node information
    for (int i = 1; i <= size; i++) {
        getline(infile, s);
        GraphNode* ptr = new GraphNode(); // create a GraphNode

        // initialized the adjacency list head to null
        ptr -> edgeHead = NULL;           
        ptr->data.setData(s);
        adjList[i] = ptr;

        //(*adjList[i]).data.setData(s);
        // read using setData of the NodeData class,
        // something like: 
        //    adjList[i].data.setData(infile);
        // where adjList is the array of GraphNodes and
        // data is the NodeData object inside of GraphNode
    }

    // read the edge data and add to the adjacency list
    for (;;) {
        infile >> fromNode >> toNode;
        if (fromNode == 0 && toNode == 0) {
            return;     // end of edge data
        }

        // insert the edge into the adjacency list for fromNode
        // if the adjacency list is empty
        if (adjList[fromNode]->edgeHead == NULL) {
            EdgeNode* edgePtr = new EdgeNode();
            edgePtr->nextEdge = NULL;
            edgePtr->adjGraphNode = toNode;
            adjList[fromNode]->edgeHead = edgePtr;
        }

        // if the adjacency list is not empty
        // insert EdgeNodes at the beginning of the adjacency list
        else {
            EdgeNode* current = adjList[fromNode]->edgeHead;
            EdgeNode* edgePtr = new EdgeNode();
            edgePtr->nextEdge = current;
            edgePtr->adjGraphNode = toNode;
            adjList[fromNode]->edgeHead = edgePtr;
        }
    }
} // end of buildGraph


//--------------------------- displayGraph ----------------------------------
// displayGraph
// display each node information and edge in the graph
void GraphL::displayGraph() const {
    cout << "Graph:" << endl;
    for (int i = 1; i <= size; i++) {

        // display the gernal information of GraphNode
        cout << "Node" << i << "        " << adjList[i]->data << endl;
        EdgeNode* current = adjList[i]->edgeHead;
        //if (current != NULL) {
        //    displayGraphHelper(current, i);
        //}
        
        // when the adjacency list is not end, display it
        while(current != NULL) {
            cout << "  edge " << i << "  " << current->adjGraphNode<< endl;
            current = current->nextEdge;
        }
    }
    cout << endl;

} // end of displayGraph

//-------------------------- depthFirstSearch -------------------------------
// depthFirstSearch
// makes a depth-first search by using depthFirstSearchHelper
// displays each node in depth-first order
void GraphL::depthFirstSearch() const {
    cout << "Depth-first ordering:";

    for (int i = 1; i <= size; i++) {  // go through each GraphNode
        if ( !adjList[i]->visited) {   // if it's not visited
            depthFirstSearchHelper(i); // perform depthFirstSearch
        }
    }
    cout << endl << endl;
} // end of depthFirstSearch


//----------------------- depthFirstSearchHelper ----------------------------
// depthFirstSearchHelper
// a helper function to perform depth-first search
// displays each node in depth-first order
void GraphL::depthFirstSearchHelper(int i) const {
    adjList[i]->visited = true;   // set the GraphNode to visited
    cout << "  " << i;
    EdgeNode* current = adjList[i]->edgeHead;
    
    // go through the adjacency node
    while (current != NULL) {     
        int adjNode = current->adjGraphNode;

        // if the adjacency node is not visited
        if (!adjList[adjNode]->visited) {  
            // perform depth-first search
            return depthFirstSearchHelper(adjNode);
        }
        break;
    }
} // end of depthFirstSearchHelper

//------------------------------ makeEmpty ----------------------------------
// makeEmpty
// Empty the adjacency list, deallocate all the memory
void GraphL::makeEmpty() {

    // go through GraphNode by GraphNode
    for (int i = 1; i <= size; i++) {

        // when there's adjacency node
        if (adjList[i]->edgeHead != NULL) {
            EdgeNode* current = adjList[i]->edgeHead;
            
            // make the list empty
            while (current->nextEdge != NULL) {
                adjList[i]->edgeHead = current->nextEdge;
				// delete the EdgeNode
                delete current;
                current = adjList[i]->edgeHead;
            }
            delete current;
            adjList[i]->edgeHead = NULL;
        }
		// delete the GraphNode
        delete adjList[i];
        adjList[i] = NULL;
    }
	// set the size to zero
    size = 0;
    return;
} // end of makeEmpty

//void GraphL::displayGraphHelper(EdgeNode * edge, int & i) {
//    if (edge->nextEdge == NULL) {
//        cout << "  edge " << i << "  " << edge->adjGraphNode << endl;
//        return;
//    }
//    displayGraphHelper(edge->nextEdge, i);
//    cout << "  edge " << i << "  " << edge->adjGraphNode << endl;
//}

