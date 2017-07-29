#include "vari_node_info.h"
#include "check_node_info.h"

vari_node_info::vari_node_info(const vector<unsigned short>& vari_node_, const unsigned short ID_,const pair<double,double> priori) {

	ID = ID_;

	vari_node = vari_node_;

	// assign probability here

	probablity.reserve(vari_node_.size());

	probablity.assign(vari_node_.size(),priori);

	// assign the first estimation, aka the hard decision bits

	estimation = (priori.second > priori.first);




}


vari_node_info::~vari_node_info() {


	// do nothing



}


bool vari_node_info::update(vector<check_node_info> &check_node_info_db) {

	// the update here is relatively simpler then that of check_node upate

	unsigned short int size = (unsigned short int )vari_node.size();

	vector<pair<double, double>> message;

	message.reserve(size);

	for (unsigned short int c = 0; c < size; c++)
	{
		unsigned short int curr_vari_node = vari_node[c];
		pair<double, double> new_message = check_node_info_db[curr_vari_node].fetch(ID);
		message.push_back(check_node_info_db[(vari_node[c])].fetch(ID));
		
		if (message[c].first + message[c].second != 1) {
			//error handling
			return false;
		}


	}
	// the variable node update is relatively simpler 

	for (unsigned int c = 0; c < size; c++) {
	// ensure each probality updated
		pair<double, double> new_probablity;

		new_probablity.first = 1;

		new_probablity.second = 1;

		// normalize comes in the last

		for (unsigned short int d = (c + 1) % size; d != c; d = (d + 1) % size) {

			new_probablity.first *= message[d].first;

			new_probablity.second *= message[d].second;

		}

		//normalization

		double normalization_factor = new_probablity.first + new_probablity.second;

		new_probablity.first /= normalization_factor;

		new_probablity.second /= normalization_factor;

		if (new_probablity.first + new_probablity.second < 0.99 || new_probablity.first + new_probablity.second > 1.01) {
			// normalization fail
			return false;

		}

		probablity[c] = new_probablity;






	}





	return true;



}





pair<double, double> vari_node_info::fetch(unsigned short int ID) {
	unsigned short int c = 0;
	for (; c < vari_node.size(); c++) {

		if (vari_node[c] == ID)
			break;



	}

	if (c == vari_node.size())
	{//error reached
		return std::make_pair((double)0, (double)0);
	}

	return probablity[c];






}


bool vari_node_info::estimate(vector<check_node_info>& check_node_info_db) {

// the estimation estimates the LLR is very simliart to that of an update
	unsigned short int size = (unsigned short int)vari_node.size();

	vector<pair<double, double>> message;

	message.reserve(size);

	for (unsigned short int c = 0; c < size; c++)
	{
		message.push_back(check_node_info_db[(vari_node[c])].fetch(ID));

		if (message[c].first + message[c].second != 1) {
			//error handling
			return false;
		}


	}
	
	// estimates the probality of 1 and 0
	
		pair<double, double> new_probablity;

		new_probablity.first = 1;

		new_probablity.second = 1;

		for (unsigned short int d =  0; d < size; d = (d + 1)) {

			new_probablity.first *= message[d].first;

			new_probablity.second *= message[d].second;

		}

		estimation = (new_probablity.second > new_probablity.first);




	return true;











}