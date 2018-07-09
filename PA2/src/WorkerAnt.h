// **************************************************************************
//  File       [WorkerAnt.h]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The header file of worker ant]
//  Modify     [2015/03/20 Yu-Hao Ho]
// **************************************************************************

#ifndef _WORKERANT_H
#define _WORKERANT_H

#include <vector>
#include <cmath>

using namespace std;

struct Food{
	int x;
	int y;
	int weight;
};

struct WorkerAnt {
	int capacity;
	int ans;
	vector<Food> foodlist;
	vector<int> distlist;
	vector<int> d;
	vector<int> dpbest;
	vector<int> greedypath;
	
	void push(int x, int y, int w);
	
	int dist2origin(int i);
	int dist(int i, int j);
	int getweight(int i);
	void init();
	
	void dp();
	void gd();
};



#endif
