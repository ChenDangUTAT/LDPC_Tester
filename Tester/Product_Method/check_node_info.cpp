#include "check_node_info.h"
#include "vari_node_info.h"


check_node_info::check_node_info(const vector<unsigned short>& check_node_, const unsigned short ID_) {

	check_node.assign(check_node_.begin(), check_node_.end());

	ID = ID_;

	probablity.reserve(check_node.size());

	pair<double, double> dummy;
	
	dummy.first = 0;

	dummy.second = 0;

	probablity.assign(check_node.size(),dummy);

}



check_node_info::~check_node_info() {

	// do nothing for now

}

// this function updates, or iterates, for the check node, note that this action can only be performed after the variable node update
// the formula used on this implementation can be found on "Modern Digital and Analog signals" V5, Pg 963
bool check_node_info::update(vector<vari_node_info>& vari_node_info_db){

	unsigned short int size = (unsigned short int)check_node.size();

	vector<pair<double, double>> message;

	message.reserve(size);

	for (unsigned short int c = 0; c < size; c++)
	{
		message.push_back(vari_node_info_db[(check_node[c])].fetch(ID));

		if (message[c].first + message[c].second < 0.99 || message[c].first + message[c].second > 1.01) {
			//error handling
			return false;
		}
	
	
	}
	// the heuristic here is this
	// first the check node fullfillment depends only on how many '1' s in the correpsonding codeword
	// second if a code word is not satisfied for 1, then it must 0.
	// thus we use a for loop
	for (unsigned short c = 0; c < size; c++) {
	// traverse through every check node
		pair<double, double> new_probablity;
		new_probablity.first = 0.5;
		new_probablity.second = 0.5;
		double product_of_all_ones = 0.5;

		for (unsigned short d = (c + 1) % size; d != c; d = (d + 1) % size) {
			// the  loop ensures that every edge, apart from the c we desired to update
			// is traversed

			product_of_all_ones*= (1-2*message[d].second);

		}

		new_probablity.first = 0.5 + product_of_all_ones;
		new_probablity.second = 1 - new_probablity.first;

	
		probablity[c] = new_probablity;
	
	
	}

	return true;





}


// this function fetches the probablity for certain Varible Node specified on ID

pair<double, double> check_node_info::fetch(unsigned short int ID) {
	unsigned short int c = 0;
	for (; c < check_node.size(); c++) {
		if (check_node[c] == ID)
			break;
		// do nothing

	}

	if (c == check_node.size())
	{//error reached
		return std::make_pair((double)0, (double)0);
	}

	return probablity[c];






}