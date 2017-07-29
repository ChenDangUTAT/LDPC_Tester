#include "vari_node_info.h"
#include "check_node_info.h"
#include <iostream>

//#define SWITCH_CHECK


vari_node_info::vari_node_info(const vector<unsigned short>& vari_node_, const unsigned short ID_,const pair<double,double> priori) {

	ID = ID_;

	vari_node = vari_node_;

	// assign probability here

	probablity.reserve(vari_node_.size());

	channel_intput = (std::log(priori.first / priori.second));

	probablity.assign(vari_node_.size(), channel_intput);

	// assign the first estimation, aka the hard decision bits

	estimation = (priori.second > priori.first);




}


vari_node_info::~vari_node_info() {


	// do nothing



}


bool vari_node_info::update(vector<check_node_info> &check_node_info_db) {

	// the update here is relatively simpler then that of check_node upate

	unsigned short int size = (unsigned short int )vari_node.size();

	vector<double> message;

	message.reserve(size);

	for (unsigned short int c = 0; c < size; c++)
	{
		unsigned short int curr_check_node = vari_node[c];
		message.push_back(check_node_info_db[curr_check_node].fetch(ID));
		
		if (message[c] == -1) {
			//error handling
			return false;
		}


	}
	// the variable node update is relatively simpler 

	for (unsigned int c = 0; c < size; c++) {
	// ensure each probality updated
		double new_probablity = 0;


		// normalize comes in the last

		for (unsigned short int d = (c + 1) % size; d != c; d = (d + 1) % size) {
			new_probablity += message[d];


		}

		// questionable thing to do though.
		new_probablity += channel_intput;


		
		

		probablity[c] = new_probablity;






	}





	return true;



}





double vari_node_info::fetch(unsigned short int ID) {
	unsigned short int c = 0;
	for (; c < vari_node.size(); c++) {

		if (vari_node[c] == ID)
			break;



	}

	if (c == vari_node.size())
	{//error reached
		return -1;
	}

	return probablity[c];






}


bool vari_node_info::estimate(vector<check_node_info>& check_node_info_db) {

	// the estimation estimates the LLR is very simliart to that of an update
	unsigned short int size = (unsigned short int)vari_node.size();

	vector<double> message;

	message.reserve(size);

	for (unsigned short int c = 0; c < size; c++)
	{
		unsigned short int curr_check_node = vari_node[c];
		message.push_back(check_node_info_db[curr_check_node].fetch(ID));

		if (message[c] == -1) {
			//error handling
			return false;
		}


	}

	// estimates the probality of 1 and 0
	double LLR = 0;

	for (unsigned short int d = 0; d < message.size(); d++) {
		LLR += message[d];


	}

	// questionable thing to do though.
	 LLR += channel_intput;
#ifdef SWITCH_CHECK
	if (estimation ^ (LLR < 0)) {
		std::cout << "The bit " << ID << " has changed from " << estimation << " to " << (LLR < 0) << std::endl;
		std::cout << "The corresponding LLR is " << LLR << " and the original input is " << channel_intput << std::endl;
	}
#endif // SWITCH_CHECK



	estimation = LLR < 0;




	return true;











}