#ifndef _PIN_H
#define _PIN_H

using namespace std;

class Pin {

public:
	Pin(){}
	~Pin(){}

	Pin(int A, int B, int C){
		ID = A;
		X = B;
		Y = C;
		connected = false;
	}

	int ID;
	int X;
	int Y;
	bool connected;

	void print() {
		cout << ID << " " << X << " " << Y << endl;
	}
	
};

#endif

