#pragma once


#include <vector>
#include <random>
#include <cmath>
#include <random>

using std::default_random_engine;
using std::normal_distribution;
using std::vector;
using std::log10;	


vector<double>  BPSK(const vector<bool>& input, const double snr);


vector<double>  BPSK_with_Rayleigh(const vector<bool>& input, const double snr, vector<double>& rayleigh);