#ifndef _NET_H
#define _NET_H

#include "Pin.h"

using namespace std;

class Net
{

public:
	Net(){
		fail = false;
	}
	~Net(){}

	Net(int n, vector<Pin> p) {
		ID = n;
		pins = p;
	}

	int ID;
	vector<Pin> pins;
	int range;
	vector<pair<int, int>> wirelist;
	bool fail;

	void print() {
		cout << "ID: " << ID << " range: " << range << "\n";
		for (auto &pin : pins) {
			pin.print();
		}
	}

	void getRange(int up, int down, int left, int right) {
		range = up - down + right - left;
	}
	
};

#endif
