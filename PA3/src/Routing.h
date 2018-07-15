// **************************************************************************
//  File       [Routing.h]
//  Author     [Jheng-Ying Yu]
//  Synopsis   [The header file of routing]
//  Modify     [2018/04/06 Jheng-Ying Yu]
// **************************************************************************

#ifndef _ROUTING_H
#define _ROUTING_H

#include <vector>
#include "Pin.h"
#include "Block.h"
#include "Net.h"
using namespace std;

class Routing{
    
public:
    Routing(); // constructor

    vector<Pin> pinlist;
    vector<Block> blocklist; 
    vector<Net> netlist;
    
    void connectNet();
    // Perform routing
    // vector < vector<int*> > ConnectNets(vector<int*>& pins, vector<int*>& blockages, vector<int*>& nets);
    // Connect all pins of in a net and return a set of wires for this net
    // vector <int*> ConnectOneNet(vector<int*>& pins, vector<int*>& blockages, int* net);
    
    private:
    // bool** layout; // Record the occupied conditions of all positions in the layout
    
};

#endif
