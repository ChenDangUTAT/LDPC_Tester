#include "check_node_info.h"
#include "vari_node_info.h"
#include <iostream>
//#define VALUE_INSPECTION

check_node_info::check_node_info(const vector<unsigned short>& check_node_, const unsigned short ID_) {

	check_node.assign(check_node_.begin(), check_node_.end());

	ID = ID_;

	probablity.reserve(check_node.size());



	probablity.assign(check_node.size(),(double)0);

}



check_node_info::~check_node_info() {

	// do nothing for now

}

// this function updates, or iterates, for the check node, note that this action can only be performed after the variable node update
// the formula used on this implementation can be found on "Modern Digital and Analog signals" V5, Pg 963
bool check_node_info::update(vector<vari_node_info>& vari_node_info_db){

	unsigned short int size = (unsigned short int)check_node.size();

	vector<double> message;

	message.reserve(size);

	for (unsigned short int c = 0; c < size; c++)
	{
		message.push_back(vari_node_info_db[(check_node[c])].fetch(ID));

		if (message[c]==-1) {
			//error handling
			return false;
		}
	
	
	}

	double new_information;
	// the heuristic here is this
	// first the check node fullfillment depends only on how many '1' s in the correpsonding codeword
	// second if a code word is not satisfied for 1, then it must 0.
	// thus we use a for loop
	for (unsigned short c = 0; c < size; c++) {
		new_information = 1;



		for (unsigned short d = (c + 1) % size; d != c; d = (d + 1) % size) {
			new_information *= tanh(message[d]);
		}

		
#ifdef VALUE_INSPECTION

		std::cout << "the new information before inverse tanh is " << new_information << std::endl;
	
#endif

		new_information = 2 * atanh(new_information);
	   
		probablity[c] = new_information;

#ifdef VALUE_INSPECTION

		std::cout << "the new information after inverse tanh is " << new_information << std::endl;
		system("pause");
#endif
	}
	return true;





}


// this function fetches the probablity for certain Varible Node specified on ID

double check_node_info::fetch(unsigned short int ID) {
	unsigned short int c = 0;
	for (; c < check_node.size(); c++) {
		if (check_node[c] == ID)
			break;
		// do nothing

	}

	if (c == check_node.size())
	{//error reached
		return -1;
	}

	return probablity[c];






}