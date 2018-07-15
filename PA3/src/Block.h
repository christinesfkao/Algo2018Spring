#ifndef _BLOCK_H
#define _BLOCK_H

using namespace std;

class Block {

public:
	Block(){}
	~Block(){}

	Block(int A, int B, int C, int D){
		left = A;
		down = B;
		right = C;
		up = D;
	}

	int left;
	int down;
	int right;
	int up;

	void print() {
		cout << left << " " << down << " " << right << " " << up << endl;
	}
	
};

#endif

