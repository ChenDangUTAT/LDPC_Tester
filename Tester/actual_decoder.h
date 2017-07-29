#pragma once




#include <vector>
#include <algorithm>
#include <thread>

#include "vari_node_info.h"
#include "check_node_info.h"

using std::pair;
using std::vector;

vector<bool> actual_decoder(const vector<pair<double,double>>& input, const pair<vector<vector<unsigned short int>>, vector<vector<unsigned short int>>>& tanner_graph);

void partial_update_VN(vector<check_node_info>& check_nodes_db, vector<vari_node_info>& vari_node_info_db, unsigned int start, unsigned int ends);

void partial_update_CN(vector<check_node_info>& check_nodes_db, vector<vari_node_info>& vari_node_info_db, unsigned int start, unsigned int ends);