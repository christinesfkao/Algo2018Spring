// **************************************************************************
//  File       [main.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The main program of 2015 Spring Algorithm PA2]
//  Modify     [2015/03/20 Yu-Hao Ho]
// **************************************************************************

#include <cstring>
#include <iostream>
#include <fstream>
#include "../lib/tm_usage.h"
#include "WorkerAnt.h"
#include <vector>
#include <stack>

using namespace std;

void help_message()
{
    cout << "usage: WorkerAnt -[GD|DP] <input_file> <output_file>" << endl;
    cout << "options:" << endl;
    cout << "   GD  - Greedy" << endl;
    cout << "   DP  - Dynamic Programming" << endl;
}

int main(int argc, char *argv[])
{
    if (argc != 4) {
        help_message();
        return 0;
    }
    CommonNs::TmUsage tmusg;
    CommonNs::TmStat stat;

    //////////// read the input file /////////////

    fstream fin(argv[2]);
    fstream fout;
    fout.open(argv[3], ios::out);
    int capacity, num, temp0, temp1, temp2;
    WorkerAnt myAnt;

    fin >> myAnt.capacity >> num;

    while (fin >> temp0 >> temp1 >> temp2) {
        myAnt.push(temp0, temp1, temp2);
    }

    //////////// find the solution to pick up the food ////
    tmusg.periodStart();

    if (strcmp(argv[1], "-GD") == 0) {
        // greedy
        myAnt.gd();
    } else if (strcmp(argv[1], "-DP") == 0) {
        // dynamic programming
        myAnt.dp();
    } else {
        help_message();
        return 0;
    }

    tmusg.getPeriodUsage(stat);

    //////////// write the output file ///////////
    stack<int> path;
    if (strcmp(argv[1], "-GD") == 0) {
        for (auto &node : myAnt.greedypath) {
            fout << node << endl;
        }
        fout << myAnt.ans << endl;
    }  else if (strcmp(argv[1], "-DP") == 0) {
        int node = myAnt.dpbest.back();
        while (node != 0) {
            path.push(node);
            if (node == myAnt.dpbest.at(node)) {
                cout << node << "!\n";
                break;
            }
            node = myAnt.dpbest.at(node);
        }
        while (!path.empty()) {
            fout << path.top() << endl;
            path.pop();
        }
        fout << num << endl;
        fout << myAnt.ans << endl;
    }

    cout << "# run time = " << (stat.uTime + stat.sTime) / 1000000.0 << "sec" << endl;
    cout << "# memory =" << stat.vmPeak / 1000.0 << "MB" << endl;

    fin.close();
    fout.close();

    return 0;
}
