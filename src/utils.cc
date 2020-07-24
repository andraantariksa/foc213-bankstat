#include <iostream>
#include <vector>

#include "utils.h"

ResultDatingProb datingProb(double num_dates, double date_out, double date_in)
{
	double prob_both = (date_in + date_out - num_dates) / num_dates;
	double prob_out = date_out / num_dates;
	double prob_in = date_in / num_dates;

	double prob_out_given_in = prob_both / prob_in;
	double prob_in_given_out = prob_both / prob_out;
	ResultDatingProb output;
	output.a = prob_out_given_in;
	output.b = prob_in_given_out;
	return output;
}
