#pragma once


#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm>


using std::vector;
using std::pair;
typedef unsigned short int model_int;

pair<vector<vector<unsigned short int>>, vector<vector<unsigned short int>>> tanner_graph(double r, char type, unsigned short int z);
// this is a function for generating Tanner Graph, for now it only generate the Tanner Graph suitable for 802.16e, this could be overloaded to change
// the first vector in pair is check nodes while the second variable nodes



void model_matrix_row_push_back(vector<model_int> val, vector<model_int> pos, model_int z, vector<pair<unsigned short int, unsigned short int>>& row);
// function used to generate tanner graph

void model_matrix_push_back(unsigned short int val, unsigned short int pos, unsigned short int z, vector<pair<unsigned short int, unsigned short int>>& row);
// function used to generate tanner graph



pair<vector<vector<unsigned short int>>, vector<vector<unsigned short int>>> easy_tanner_graph(void);

// this will provide an easy version of tanner graph
// this takes the (3,6) Pairity Check Matrix from RU paper



