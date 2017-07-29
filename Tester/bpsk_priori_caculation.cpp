#include "bpsk_priori_caculation.h"

using std::exp;

vector<pair<double,double>> bpsk_priori_caculation(const vector<double>& input,const double snr) {

	vector<pair<double, double>> result;

	result.reserve(input.size());


	//following the same pattern, the first is the probalbity of 0 and last 1;

	pair<double, double> priori_probablity;

	priori_probablity.first = 0;

	priori_probablity.second = 0;

	// the priori probablity is dependent on how the channel works,
	// The calcualtion here is carried out within BPSK channel with code rate modification to ensure same power with uncoded signal
	// to ensure that this agrees with the channel cpp file
	// the snr are taken in terms of db


	double snr_ratio = std::pow(10, snr / 10);

	double variation = 1 / (2*1*snr_ratio);


	for (unsigned int c = 0; c < input.size(); c++){
		// put the priori probablity calculation here, this should change accordingly to the modulation scheme
		double priori_1 = 1/(1+std::exp(2*input[c]/variation));

		double priori_0 = 1 / (1 + std::exp(-2 * input[c] / variation));

		// Note that for the Modern Ananlog and Digital Signal V5, the probablity should be normalized to 1, aka p(1)+p(0) = 1;
		
		priori_probablity.first = priori_0;

		priori_probablity.second = priori_1;


		// priori probablity calculation ends

		
		result.push_back(priori_probablity);	
	}


	return result;

}



vector<pair<double, double>> bpsk_priori_caculation_rayleigh(const vector<double>& input, const double snr, vector<double> rayleigh) {
	vector<pair<double, double>> result;

	result.reserve(input.size());


	//following the same pattern, the first is the probalbity of 0 and last 1;

	pair<double, double> priori_probablity;

	priori_probablity.first = 0;

	priori_probablity.second = 0;

	// the priori probablity is dependent on how the channel works,
	// The calcualtion here is carried out within BPSK channel with code rate modification to ensure same power with uncoded signal
	// to ensure that this agrees with the channel cpp file
	// the snr are taken in terms of db


	double snr_ratio = std::pow(10, snr / 10);

	double variation = 1 / (2 * 1 * snr_ratio);


	for (unsigned int c = 0; c < input.size(); c++) {
		// put the priori probablity calculation here, this should change accordingly to the modulation scheme
		double priori_1 = 1 / (1 + std::exp(2 * input[c] * rayleigh[c] / variation));

		double priori_0 = 1 / (1 + std::exp(-2 * input[c] * rayleigh[c]/ variation));

		// Note that for the Modern Ananlog and Digital Signal V5, the probablity should be normalized to 1, aka p(1)+p(0) = 1;

		priori_probablity.first = priori_0;

		priori_probablity.second = priori_1;


		// priori probablity calculation ends


		result.push_back(priori_probablity);
	}


	return result;
}