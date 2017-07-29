#include "main.h"

using std::fstream;

#define check_nodes tanner_graph_.first
#define vari_nodes tanner_graph_.second
//#define ZERO_DEBUG

#define RAYLEIGH


#define TEST_INPUT 10000
#define SUPPRESS_OUTPUT

int main() {
	// this is a tester for Rate 1/2 and Rate 5/6 LDPC code specified
	// should the tester succeeds, all the Wimax LDPC should be handled with little addtion to Matrix Specification

	// fetching data from matlab output, yeah it is unorthodox...
	
	// time counter

	std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
	
	// code word gathering 
	fstream code_word_raw;

	code_word_raw.open("code_word.txt", std::fstream::in);

	unsigned long long total_success = 0;

	unsigned long long total_fails = 0;
	
	vector<bool> code_word;

	double snr = 12.5;

	unsigned short int z = 24;

	double r = 0.8333;

	char temp;

#ifdef RAYLEIGH

	vector<double> rayleigh;

#endif
	
	// grabbing tanner graph
	pair<vector<vector<unsigned short int>>, vector<vector<unsigned short int>>> tanner_graph_ = tanner_graph(r, 'A', z);

// now we will do many cases and hope we have a result that is good enough

	for (unsigned long long test_case = 0; test_case < TEST_INPUT; test_case++) {
		code_word.clear();

#ifdef RAYLEIGH
		rayleigh.clear();
#endif // RAYLEIGH

		

		code_word.assign((size_t)z * 24, false);


		for (model_int c = 0; c < z * 24; c++) {
			code_word_raw >> temp;

			if (temp == '0') {
				code_word[c] = false;

			}
			else if (temp == '1') {
				code_word[c] = true;

			}
			else {
				// encountered unexpected character
				std::cout << "Getting Input fails\n";
				system("pause");

			}


		}


		bool checker = false;

		for (unsigned short int c = 0; c < check_nodes.size(); c++) {

			checker = false;

			for (unsigned short int d = 0; d < check_nodes[c].size(); d++) {

				checker = checker^code_word[check_nodes[c][d]];

				

			}

			if (checker) {

				std::cout << "Parity Check fails" << std::endl;
				system("pause");
				break;
			}




		}

#ifndef RAYLEIGH

		vector<double> channel_output = BPSK(code_word, snr);

		vector<pair<double, double>> priori_probablity = bpsk_priori_caculation(channel_output, snr);

#else


		vector<double> channel_output = BPSK_with_Rayleigh(code_word, snr,rayleigh);

		vector<pair<double, double>> priori_probablity = bpsk_priori_caculation_rayleigh(channel_output, snr,rayleigh);

#endif // !RAYLEIGH

		vector<bool> decoded_data = actual_decoder(priori_probablity, tanner_graph_);

		bool success = true;

		if (decoded_data.empty()) {

			success = false;
			//total_fails++;

		}

		unsigned int k = (unsigned int)(z*r * 24);

		if (success) {
			for (unsigned int i = 0; i < k; i++) {
				if (decoded_data[i] == code_word[i]) {
					// do nothing
				}
				else {
					success = false;
				}


			}
		}
#ifdef ZERO_DEBUG
		if (!success&&!decoded_data.empty()) {
			unsigned int message_counter = 0;
			unsigned int output_counter = 0;

			for (unsigned int i = 0; i < k; i++) {
				if (decoded_data[i])
					message_counter++;


				if (code_word[i])
					output_counter++;


			}

			std::cout << "The decoded message has a weight of " << message_counter << std::endl << "While the original message has has a weight of " << output_counter << std::endl;
		}
#endif


		if (success) {
			total_success++;
#ifndef SUPPRESS_OUTPUT
			std::cout << "THe decoded message matches the original message" << std::endl;
#endif
		}
		else {
			total_fails++;
#ifndef SUPPRESS_OUTPUT
			std::cout << "THe decoded message does not match the original message" << std::endl;
#endif
		}


	}
	
	std::cout << "The success numbers out of all cases is " << total_success << " sucess(es) out of " << TEST_INPUT << std::endl;
	std::cout << "The fail numbers out of all cases is " << total_fails << " fail(s) out of " << TEST_INPUT << std::endl;

	std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now();

	std::chrono::duration<double> time_used = std::chrono::duration_cast<std::chrono::duration<double>>(end_time-start_time);

	std::cout << "This process has taken a time of " << time_used.count() << " seconds " << std::endl;

	code_word_raw.close();
	system("pause");
	return 0;




}
