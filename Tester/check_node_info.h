#pragma once


#include <vector>
#include <cmath>
using std::vector;
using std::pair;
using std::tanh;
using std::atanh;

class check_node_info {
private:
	friend class vari_node_info;
	// this probablity queue corresponds to the check_node variable above
	// the first stands for 0(false), second stands for 1(true);
	// we use the linear array now
	// may switch to the hash map for KEY-VARI referencing later
	// but considering the check_node is short, this may be unnecessary
	vector<double> probablity;


public:
	check_node_info(const vector<unsigned short>&,const unsigned short);
	~check_node_info();
	
	unsigned short int ID;

	vector<unsigned short> check_node;

	// the update function updates the probablity using the database of other
	bool update(vector<vari_node_info>&);


	double fetch(unsigned short int ID);

	




};