#pragma once
//this programm transfers the BPSK modulated signal into boolean (1 and 0) messages

#include <vector>



using std::vector;
using std::pair;

vector<pair<double,double>> bpsk_priori_caculation(const vector<double>& input,const double snr);

vector<pair<double, double>> bpsk_priori_caculation_rayleigh(const vector<double>& input, const double snr, vector<double> rayleigh);