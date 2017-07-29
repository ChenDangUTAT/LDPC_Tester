#pragma once

#include <vector>
#include <utility>


using std::vector;
using std::pair;


class vari_node_info
{
private:

	friend class check_node_info;
	// simliar to check node info, this is also correpsonds to the vari_node below
	// the first of the pair represents 0(false), second 1(true)

	vector<pair<double,double>> probablity;

public:
	vari_node_info(const vector<unsigned short>&, const unsigned short,const pair<double, double>);
	~vari_node_info();

	unsigned short ID;

	vector<unsigned short> vari_node;

	bool update(vector<check_node_info>&);

	pair<double, double> fetch(unsigned short int ID);

	bool estimate(vector<check_node_info>&);

	bool estimation;


};
