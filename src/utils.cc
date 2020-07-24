#include <utils.h>
#include <iostream>
#include <vector>

std::vector<double> datingProb(int num_dates, int date_out, int date_in) {
	double prob_both = (double)(date_in + date_out - num_dates) / num_dates;
	double prob_out = (double)date_out / num_dates;
	double prob_in = (double)date_in / num_dates;

	double prob_out_given_in = prob_both / prob_in;
	double prob_in_given_out = prob_both / prob_out;
	std::vector <double> prob_given = { prob_out_given_in, prob_in_given_out };
	return prob_given;
}