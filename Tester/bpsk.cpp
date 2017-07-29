#include "BPSK.h"

// this function is supposely my channel function, 

// which takes an input of vector<short int>, the desired SNR and code rate for coding scheme and power consistancy

// and output corresponding output of vector <double>

// the channel using BPSK which map bit 1 to symbol "-1" and bit 0 to symbol "+1"

// to ensure that the power remains constant for uncoded and coded system

// we normalize Es to 1 and adds in the code rate into the equation to ensure same power is used for uncoded/coded system.

// the snr input takes snr in Eb/No in DB


vector<double>  BPSK (const vector<bool>& input,const double snr) {
    // as of right now we have not yet call by reference the output.

	vector<double> output;

	output.clear();

	// empty input check
	
	if (input.empty()==true) {
	
		return output;
	
	}

	// initial an output 
	unsigned int size = input.size();

	output.reserve(size);

	// initial AWGN channel
	// beware that at this moment we have not yet ensure the uncoded channel and coded channel has same power

	double snr_ratio = std::pow(10,snr/10);


	// as for uncoded channel the code rate is supposelly to be 1

	// the variation calculation is 1/(2*M-ary modulator*Code Rate*SNR_Ratio)

	double variation = 1/(2*1*snr_ratio) ;

	double stdrev = std::sqrt(variation);

	std::random_device rd;

	default_random_engine generator(rd());

	normal_distribution<double> AWGN(0, stdrev);

	// modulation process


	for (unsigned int c = 0; c < size;c++) {

		output.push_back((input[c]) ? -1: 1);	
		output[c] += AWGN(generator);
	
	}



	return output;



}

const double rayleigh_variance = 1.526399745530;

vector<double>  BPSK_with_Rayleigh(const vector<bool>& input, const double snr,vector<double>& rayleigh) {
	// as of right now we have not yet call by reference the output.

	vector<double> output;

	output.clear();

	// empty input check

	if (input.empty() == true) {

		return output;

	}

	// initial an output 
	unsigned int size = input.size();

	output.reserve(size);

	// initial AWGN channel
	// beware that at this moment we have not yet ensure the uncoded channel and coded channel has same power

	double snr_ratio = std::pow(10, snr / 10);


	// as for uncoded channel the code rate is supposelly to be 1

	// the variation calculation is 1/(2*M-ary modulator*Code Rate*SNR_Ratio)

	double variation = 1 / (2 * 1 * snr_ratio);

	double stdrev = std::sqrt(variation);

	std::random_device seed_1;

	default_random_engine generator_1(seed_1());

	normal_distribution<double> AWGN(0, stdrev);


	// Addtional Rayleigh Distribution
	std::random_device seed_2;
	default_random_engine generator_2(seed_2());
	// unit variance
	normal_distribution<double> rayleigh_1(0, rayleigh_variance);

	std::random_device seed_3;
	default_random_engine generator_3(seed_3());
	// unit variance
	normal_distribution<double> rayleigh_2(0, rayleigh_variance);

	double rayleigh1;
	double rayleigh2;

	rayleigh.reserve(size);

	// Addtional Rayleigh Distribution


	// modulation process


	for (unsigned int c = 0; c < size; c++) {

		output.push_back((input[c]) ? -1 : 1);

		rayleigh1 = rayleigh_1(generator_2);
		rayleigh2 = rayleigh_2(generator_3);

		rayleigh.push_back(sqrt(rayleigh1*rayleigh1 + rayleigh2*rayleigh2));

		output[c] *= rayleigh[c];
		output[c] += AWGN(generator_1);

	}



	return output;



}