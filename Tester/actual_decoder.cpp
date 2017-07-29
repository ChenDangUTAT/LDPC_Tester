#include "actual_decoder.h"


#include <iostream>

// for easier understanding 
// note that there is a 's' at the end

#define check_nodes tanner_graph.first
#define vari_nodes tanner_graph.second 

// for Maximum Iterations 

#define MULTITHREAD
#define MAX_ITERATION 10
#define SUPPRESS_OUTPUT

vector<bool> actual_decoder(const vector<pair<double, double>>& priori_probablity, const pair<vector<vector<unsigned short int>>,vector<vector<unsigned short int>>>& tanner_graph) {



	// reserve the space for iteration and output
	
	unsigned short int output_size = (unsigned short int)(vari_nodes.size()- check_nodes.size());

	vector<bool> output;

	output.reserve(output_size);


	// database setup for information/extrinsic information

	vector<check_node_info> check_node_info_db;

	vector<vari_node_info> vari_node_info_db;

	check_node_info_db.reserve(check_nodes.size());

	vari_node_info_db.reserve(vari_nodes.size());

	// initialization phase

	for (unsigned short int c = 0; c < check_nodes.size(); c++) {
		check_node_info new_check_node(check_nodes[c], c);
		check_node_info_db.push_back(new_check_node);

	}

	for (unsigned short int c = 0; c < vari_nodes.size(); c++) {
		vari_node_info new_vari_node(vari_nodes[c], c, priori_probablity[c]);
		vari_node_info_db.push_back(new_vari_node);

	}






	// iteration starts here

	bool check_node_result = false;

	// ensure that we handle error
	bool break_check = false;

	unsigned short int iteration_counter = 0;

	bool first_success = false;

#ifdef MULTITHREAD
	const unsigned int thread_count = 4;
	std::thread threads[thread_count];

#endif // MULTITHREAD

	
	for (iteration_counter = 0; iteration_counter < MAX_ITERATION; iteration_counter++)
	{

		unsigned short int check_counter = 0;

		bool parity_check = true;

		for (check_counter = 0; check_counter < check_nodes.size(); check_counter++) {
			// covers all the check nodes
			// starts with false so that its intial value does not interfere
			bool single_check_node_result = false;

			for (unsigned short int d = 0; d < check_nodes[check_counter].size(); d++) {
				// estimate each check nodes results
				single_check_node_result = single_check_node_result^vari_node_info_db[check_nodes[check_counter][d]].estimation;


			}
			if (single_check_node_result == true) {
				// aka syndrome equals 1
				//break;
				parity_check = false;
				//std::cout << "The check node " << check_counter << " fails" << std::endl;
				
			}


		}

		//std::cout << std::endl << std::endl;
		first_success = (iteration_counter == 0);
		check_node_result = (parity_check);

		

		if (check_node_result) {

			// aka all check_node verified 
			break;
		}

		bool break_check = false;

		// message passing
#ifndef MULTITHREAD
		for (unsigned short int c = 0; c < check_nodes.size(); c++) {
			break_check = !check_node_info_db[c].update(vari_node_info_db);
			if (break_check)
				break;
		}
#else
		// using 4 thread for CN updates

		unsigned int size = check_nodes.size();
		
		const double parts = (double)1/(double)thread_count;


		// testing for false sharing



		for (unsigned int c = 0; c < thread_count; c++) {
		
			threads[c] = std::thread(partial_update_CN, std::ref(check_node_info_db), std::ref(vari_node_info_db), c*parts*size, (c+1)*parts*size);

		
		
		}


		for (unsigned int c = 0; c < thread_count; c++) {

			threads[c].join();



		}

		/*
		std::thread first_quarter(partial_update_CN,std::ref(check_node_info_db), vari_node_info_db, 0, (0.25)*size);
		std::thread second_quarter(partial_update_CN, std::ref(check_node_info_db), vari_node_info_db,(0.25)*size,(0.5)*size);
		std::thread third_quarter(partial_update_CN, std::ref(check_node_info_db), vari_node_info_db, (0.5)*size, (0.75)*size);
		std::thread last_quarter(partial_update_CN, std::ref(check_node_info_db), vari_node_info_db, (0.75)*size, size);

		first_quarter.join();
		second_quarter.join();
		third_quarter.join();
		last_quarter.join();
		*/

#endif

#ifndef MULTITHREAD		
		for (unsigned short int c = 0; c < vari_nodes.size(); c++) {

			// information updates

			break_check = !vari_node_info_db[c].update(check_node_info_db);

			if (break_check) {
				break;
			}


			// estimate the bits to be 1 and 0

			break_check = !vari_node_info_db[c].estimate(check_node_info_db);


			if (break_check) {
				break;
			}
		}
#else

		    size = vari_nodes.size();
			

			for (unsigned int c = 0; c < thread_count; c++) {

				threads[c] = std::thread(partial_update_VN, std::ref(check_node_info_db), std::ref(vari_node_info_db), c*parts*size, (c + 1)*parts*size);



			}


			for (unsigned int c = 0; c < thread_count; c++) {

				threads[c].join();



			}

			
			
			
			
			/*
			first_quarter =std::thread(partial_update_VN, check_node_info_db, std::ref(vari_node_info_db), 0, (0.25)*size);
			second_quarter = std::thread(partial_update_VN, check_node_info_db, std::ref(vari_node_info_db), (0.25)*size, (0.5)*size);
			third_quarter = std::thread(partial_update_VN, check_node_info_db, std::ref(vari_node_info_db), (0.5)*size, (0.75)*size);
			last_quarter = std::thread(partial_update_VN, check_node_info_db, std::ref(vari_node_info_db), (0.75)*size, size);

			first_quarter.join();
			second_quarter.join();
			third_quarter.join();
			last_quarter.join();
			*/


#endif
		

		




	}

	// iteration ends here
	// the program reached here because
	// 1. Decode success, all check nodes verified
	// 2. Maximum Iteration Reached
	// 3. Errors in the program

	if (break_check) {
		// the program ended with error
		// debugging needed
		std::cout << "The decoder has encountered an error" << std::endl;

		return output;


	}





	if (check_node_result) {
#ifndef SUPPRESS_OUTPUT
		if (first_success)
			std::cout << "The first attempt succeeded" << std::endl;
		else
			std::cout << "The decoder terminated at iteration "<<iteration_counter<<std::endl;
		// decode success
		// utilize systematic fact to decode
#endif
		for (unsigned c = 0; c < output_size; c++) {
			output.push_back(vari_node_info_db[c].estimation);

		}



	}
	else {
#ifndef SUPPRESS_OUTPUT
		// the maximum iteration reached without any fruit
		// ARQ perhaps?
		std::cout << "Maximum Iteration Reached" << std::endl;
#endif

	}





	
	return output;



}



// this function is the first attemp for multi-threading,
// this function is for Check Nodes(CNs) Update only
void partial_update_CN(vector<check_node_info>& check_nodes_db, vector<vari_node_info>& vari_node_info_db, unsigned int start, unsigned int ends) {

	bool break_check = false;


	for (unsigned short int c = start; c < ends; c++) {
		break_check = !check_nodes_db[c].update(vari_node_info_db);
		if (break_check)
			break;
	}

	







}



// this function is the first attemp for multi-threading,
// this function is for Variable Nodes(VNs) Update only
void partial_update_VN(vector<check_node_info>& check_nodes_db, vector<vari_node_info>& vari_node_info_db, unsigned int start, unsigned int ends) {


	bool break_check = false;


	for (unsigned short int c = start; c < ends; c++) {
		break_check = !vari_node_info_db[c].update(check_nodes_db);
		if (break_check)
			break;

		break_check = !vari_node_info_db[c].estimate(check_nodes_db);

				if (break_check)
			break;
	
	}


}