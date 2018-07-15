// **************************************************************************
//  File       [main.cpp]
//  Author     [Jheng-Ying Yu]
//  Synopsis   [The main program of 2018 Spring Algorithm PA3]
//  Modify     [2018/04/08 Jheng-Ying Yu]
// **************************************************************************

#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "../lib/tm_usage.h"
#include "Routing.h"
#include "Pin.h"
#include "Block.h"
#include "Net.h"

using namespace std;

void help_message()
{
    cout << "usage: Routing <input_file_pin> <input_file_block> <input_file_net> <output_file>" << endl;
}

int main(int argc, char *argv[])
{
    if (argc != 5) {
        help_message();
        return 0;
    }
    CommonNs::TmUsage tmusg;
    CommonNs::TmStat stat;

    //////////// read the input file /////////////
    fstream fin_pin(argv[1]);   // <input_file_pin>
    fstream fin_block(argv[2]); // <input_file_block>
    fstream fin_net(argv[3]);   // <input_file_net>

    // destinated data structures
    Routing myRouting;

    // pin
    int tempID, tempX, tempY;

    while (fin_pin >> tempID) {
        fin_pin >> tempX;
        fin_pin >> tempY;
        Pin tempPIN(tempID, tempX, tempY);
        myRouting.pinlist.push_back(tempPIN);
    }

    // block
    int tempL, tempD, tempR, tempU;
    while (fin_block >> tempL) {
        fin_block >> tempD;
        fin_block >> tempR;
        fin_block >> tempU;
        Block tempBLOCK(tempL, tempD, tempR, tempU);
        myRouting.blocklist.push_back(tempBLOCK);
    }

    // net
    int tempnetID;     // netID
    string tempstring; // pins for that net
    int tempint;       // pins for that net
    vector<Pin> pins; // vector of pins (Pin as a class)

    while (getline(fin_net, tempstring, '\n')) { // for each net
        stringstream ss(tempstring);

        ss >> tempnetID; // netID

        int up = -1, right = -1, down = 2000, left = 2000;

        while (ss >> tempint) { // remaining content into ss
        
            // record border of net for HPWL
            right = max(right, myRouting.pinlist[tempint - 1].X);
            left = min(left, myRouting.pinlist[tempint - 1].X);
            up = max(up, myRouting.pinlist[tempint - 1].Y);
            down = min(down, myRouting.pinlist[tempint - 1].Y);
            
            // use pinlist[INDEX] to get the pin, inelegant but effeective
            pins.push_back(myRouting.pinlist[tempint - 1]);
        }

        // important to init stringstream
        ss.clear();
        ss.str("");

        // construct a net and put it in
        Net tempNET(tempnetID, pins);
        tempNET.getRange(up, down, left, right);
        myRouting.netlist.push_back(tempNET);

        pins.clear();
    }

    fin_pin.close();
    fin_net.close();
    fin_block.close();

    //////////// perform routing on the nets ////
    tmusg.periodStart();

    myRouting.connectNet();

    tmusg.getPeriodUsage(stat);

    cout << "# run time = " << (stat.uTime + stat.sTime) / 1000000.0 << "sec" << endl;
    cout << "# memory =" << stat.vmPeak / 1000.0 << "MB" << endl;

    //////////// write the output file ///////////

    fstream fout;
    fout.open(argv[4], ios::out); // <output_file>

    for (auto &net : myRouting.netlist) {
        fout << "Net: " << net.ID << "\n";
        bool start = true;
        for (auto &wire : net.wirelist) {
            fout << wire.first << " " << wire.second;
            if (start == true) {
                fout << " ";
            }
            else {
                fout << "\n";
            }
            start = !start;
        }
    }

    fout.close();

    return 0;
}
