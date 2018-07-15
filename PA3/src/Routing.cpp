// **************************************************************************
//  File       [Routing.cpp]
//  Author     [Jheng-Ying Yu]
//  Synopsis   [The implementation of routing]
//  Modify     [2018/04/06 Jheng-Ying Yu]
// **************************************************************************

//#include "Routing.h"
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>
#include <climits>
#include "Routing.h"
#include "Pin.h"
#include "Block.h"
#include "Net.h"

using namespace std;

int dist[1000][1000];

Routing::Routing(){}

void Routing::connectNet() {
    
    queue<pair<int, int>> bfs_que;

    bool wire[1000][1000];
    bool barrier[1000][1000];

    int tx, ty;
    int dirx[] = {1, 0, -1, 0};
    int diry[] = {0, 1, 0, -1};
    int track;
    bool firstpin;
    bool done;

    // sort nets by HPWL
    sort(netlist.begin(), netlist.end(),
         [](const Net &a, const Net &b) -> bool {
             return a.range < b.range;
         });

    // set blockage
    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < 1000; j++) {
            barrier[i][j] = 0;
        }
    }
    for (auto &block : blocklist) {
        for (int i = block.left; i <= block.right; i++) {
            for (int j = block.down; j <= block.up; j++) {
                barrier[i][j] = 1;
            }
        }
    }

    // connect nets
    for (auto &net : netlist) {

        // set wire on each pin
        for (int i = 0; i < 1000; i++) {
            for (int j = 0; j < 1000; j++) {
                wire[i][j] = false;
            }
        }
        for (auto &pin : net.pins) {
            wire[pin.X][pin.Y] = true;
        }
        firstpin = true;

        // connect pins to nearest wire by Lee algorithm
        for (auto &pin : net.pins) {

            if (pin.connected == true) {
                continue;
            }

            // set unvisited as -1
            for (int i = 0; i < 1000; i++) {
                for (int j = 0; j < 1000; j++) {
                    dist[i][j] = -1;
                }
            }
            
            // start bfs
            bfs_que.push(make_pair(pin.X, pin.Y));
            dist[pin.X][pin.Y] = 0;
            done = false;

            while (!bfs_que.empty()) {
                tx = bfs_que.front().first;
                ty = bfs_que.front().second;
                bfs_que.pop();
  
                for (int i = 0; i < 4; i++) {
                    // check: out of border
                    if (tx + dirx[i] >= 1000 ||
                        tx + dirx[i] < 0 ||
                        ty + diry[i] >= 1000 ||
                        ty + diry[i] < 0) {
                        continue;
                    }
                    // check: visited 
                    if(dist[tx + dirx[i]][ty + diry[i]] >= 0){
                        continue;   
                    }
                    // find wire
                    if (wire[tx + dirx[i]][ty + diry[i]] == true) {
                        done = true;
                        pin.connected = true;
                        if (firstpin == true) {
                            firstpin = false;
                            for (int i = 0; i < 1000; i++) {
                                for (int j = 0; j < 1000; j++) {
                                    wire[i][j] = false;
                                }
                            }
                        }
                        wire[tx + dirx[i]][ty + diry[i]] = true;
                        while (!bfs_que.empty()) {
                            bfs_que.pop();
                        }
                        break;
                    }
                    
                    // check: it's blockage or other nets
                    if(barrier[tx + dirx[i]][ty + diry[i]] == true){
                        continue;   
                    }
                    
                    dist[tx + dirx[i]][ty + diry[i]] = dist[tx][ty] + 1;
                    bfs_que.push(make_pair(tx + dirx[i], ty + diry[i]));
                    
                }
                if (done) {
                    break;
                }
            }
            
            // update wire
            if (done == false) {
                net.fail = true;
            } else {
                track = dist[tx][ty];
                while (track >= 0) {
                    wire[tx][ty] = true;
                    track--;
                    for (int i = 0; i < 4; i++) {
                        if (dist[tx + dirx[i]][ty + diry[i]] == track) {
                            tx = tx + dirx[i];
                            ty = ty + diry[i];
                            break;
                        }
                    }
                }
            }
        }

        // record wire
        bool wireStart;
        
        for (int i = 0; i < 1000; i++) {
            wireStart = false;
            for (int j = 0; j < 1000; j++) {
                if (wire[i][j] == true && wireStart == false) {
                    tx = i;
                    ty = j;
                    wireStart = true;
                }
                if (wire[i][j] == false && wireStart == true) {
                    wireStart = false;
                    if (ty != j - 1) {
                        net.wirelist.push_back(make_pair(tx, ty));
                        net.wirelist.push_back(make_pair(i, j - 1));
                    }
                }
            }
            if (wireStart == true && ty != 1000 - 1) {
                net.wirelist.push_back(make_pair(tx, ty));
                net.wirelist.push_back(make_pair(i, 1000 - 1));
            }
        }
        for (int j = 0; j < 1000; j++) {
            wireStart = false;
            for (int i = 0; i < 1000; i++) {
                if (wire[i][j] == true && wireStart == false) {
                    tx = i;
                    ty = j;
                    wireStart = true;
                }
                if (wire[i][j] == false && wireStart == true) {
                    wireStart = false;
                    if (tx != i - 1) {
                        net.wirelist.push_back(make_pair(tx, ty));
                        net.wirelist.push_back(make_pair(i - 1, j));
                    }
                }
            }
            if (wireStart == true && tx != 1000 - 1) {
                net.wirelist.push_back(make_pair(tx, ty));
                net.wirelist.push_back(make_pair(1000 - 1, j));
            }
        }
        
        // set wire as barrier
        for (int i = 0; i < 1000; i++) {
            for (int j = 0; j < 1000; j++) {
                if (wire[i][j] == true) {
                    barrier[i][j] = true;
                }
            }
        }
    }

    return;
}