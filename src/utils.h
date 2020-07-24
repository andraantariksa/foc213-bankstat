#ifndef RAVITPROB_UTILS_H
#define RAVITPROB_UTILS_H

#include <vector>

struct ResultDatingProb
{
	double a;
	double b;
};

ResultDatingProb datingProb(double num_dates, double date_out, double date_in);

#endif //RAVITPROB_UTILS_H
