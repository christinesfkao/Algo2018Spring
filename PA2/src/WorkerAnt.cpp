// **************************************************************************
//  File       [main.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of worker ant function]
//  Modify     [2015/03/20 Yu-Hao Ho]
// **************************************************************************

#include <climits>
#include <iostream>
#include "WorkerAnt.h"

void WorkerAnt::push(int x, int y, int w)
{
	Food temp;
	temp.x = x;
	temp.y = y;
	temp.weight = w;
	foodlist.push_back(temp);
}

void WorkerAnt::init() //O(n)
{
	distlist.clear();

	bool first = true;
	Food lastfood;
	distlist.push_back(dist2origin(1));

	for (auto &food : foodlist) //O(n)
	{
		if (first) {
			first = false;
		} else {
			distlist.push_back(abs(food.x - lastfood.x) + abs(food.y - lastfood.y));
		}
			lastfood = food;
	}

	first = true;
	int lastdist;
	for (auto &dist : distlist) //O(n)
	{
		if (first) {
			first = false;
		} else {
			dist += lastdist;
		}
		lastdist = dist;
	}

	return;
}

int WorkerAnt::dist2origin(int i) //O(1)
{
	if (i == 0) {
		return 0;
	}
	return foodlist.at(i - 1).x + foodlist.at(i - 1).y;
}

int WorkerAnt::dist(int i, int j) //O(1)
{
	if (i == 0) {
		return distlist.at(j - 1);
	}
	return distlist.at(j - 1) - distlist.at(i - 1);
}

int WorkerAnt::getweight(int i) //O(1)
{
	if (i == 0) {
		return 0;
	}
	return foodlist.at(i - 1).weight;
}

void WorkerAnt::dp()
{
	d.clear();
	dpbest.clear();
	d.push_back(0);
	dpbest.push_back(0);
	init(); //O(n)
	int best;
	int weight;
	int mindist;
	int temp;
	int num = foodlist.size();
	for (int i = 1; i <= num; ++i) { //O(n^2)
		best = 0;
		mindist = INT_MAX;
		weight = getweight(i);  //O(1)
		for (int j = i - 1; j >= 0; --j) { // j < i, i < num, O(n)
			temp = d[j] + dist2origin(j + 1) + dist(j + 1, i) + dist2origin(i);
			// O(1) + O(1) + O(1) + O(1) = O(1)
			if (weight > capacity) {
				break;
			} else {
				if (mindist > temp) {
					best = j;
					mindist = min(mindist, temp);
				}
			}
			weight += getweight(j);
		}

		dpbest.push_back(best);
		d.push_back(mindist);
	}
	ans = mindist;
}

void WorkerAnt::gd()
{
	init();
	int carry = 0, count = 0;
	ans = 0;
	for (auto &food : foodlist) { // O(n)
		if (carry + food.weight > capacity) {
			ans += dist2origin(count) + dist2origin(count + 1);
			// O(1) + O(1) = O(1)
			carry = 0;
			greedypath.push_back(count);
		} else {
			ans += dist(count, count + 1);
		}
		carry += food.weight;
		count++;
	}
	greedypath.push_back(count);
	ans += dist2origin(count);
}
