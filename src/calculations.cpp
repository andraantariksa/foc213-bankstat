//
// Created by naavadi64 on 6/13/20.
//
#include "calculations.h"
// Arguments:
// CovPositive: virus positive with positive test (True Positive)
// CovNegative: virus positive with negative test (False Negative)
// FreePositive: virus free with positive test (False Positive)
// FreeNegative: virus free with negative test (True Negative)

// Contracted virus with result test positive
// Calculate the probability of being virus negative (cov) given that the tests indicates positive (+)
// P(free|+)
double Calc::ProbTruePositive(int CovPositive, int FreePositive, int TotalCov, int TotalFree){
    int Total = TotalCov + TotalFree;

    double ProbCov = double(TotalCov) / Total;  // Probability of virus positive in general
    double ProbPositiveCov = double(CovPositive) / TotalCov;  // Probability of testing positive given virus positive
    double ProbFree = double(TotalFree) / Total;  // Probability of virus negative in general
    double ProbPositiveFree = double(FreePositive) / TotalFree;  // Probability of testing positive given virus negative

    return (ProbPositiveCov*ProbCov) / ((ProbPositiveCov*ProbCov) + (ProbPositiveFree*ProbFree));
}


// Free virus with result test positive
// Calculate the probability of being virus negative (cov) given that the tests indicates positive (+)
// P(free|+)
double Calc::ProbFalsePositive(int CovPositive, int FreePositive, int TotalCov, int TotalFree) {
    int Total = TotalCov + TotalFree;

    double ProbCov = double(TotalCov) / Total;
    double ProbPositiveCov = double(CovPositive) / TotalCov;
    double ProbFree = double(TotalFree) / Total;
    double ProbPositiveFree = double(FreePositive) / TotalFree;

    return (ProbPositiveFree*ProbFree) / ((ProbPositiveFree*ProbFree) + (ProbPositiveCov*ProbCov));
}

// Free virus with result test negative
// Calculate the probability of being virus negative (cov) given that the tests indicates negative (-)
// P(free|-)
double Calc::ProbTrueNegative(int CovNegative, int FreeNegative, int TotalCov, int TotalFree){
    int Total = TotalCov + TotalFree;

    double ProbCov = double(TotalCov) / Total;
    double ProbNegativeCov = double(CovNegative) / TotalCov;    // Probability of testing negative given virus positive
    double ProbFree = double(TotalFree) / Total;
    double ProbNegativeFree = double(FreeNegative) / TotalFree; // Probability of testing negative given virus negative

    return (ProbNegativeFree*ProbFree) / ((ProbNegativeFree*ProbFree) + (ProbNegativeCov*ProbCov));
}

// Contracted virus with result test negative
// Calculate the probability of being virus positive (cov) given that the tests indicates negative (-)
// P(cov|-)
double Calc::ProbFalseNegative(int CovNegative, int FreeNegative, int TotalCov, int TotalFree) {
    int Total = TotalCov + TotalFree;

    double ProbCov = double(TotalCov) / Total;
    double ProbNegativeCov = double(CovNegative) / TotalCov;
    double ProbFree = double(TotalFree) / Total;
    double ProbNegativeFree = double(FreeNegative) / TotalFree;

    return (ProbNegativeCov*ProbCov) / ((ProbNegativeCov*ProbCov) + (ProbNegativeFree*ProbFree));
}
