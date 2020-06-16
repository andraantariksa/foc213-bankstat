#ifndef CALCULATIONS_H
#define CALCULATIONS_H


// Arguments:
// CovPositive: virus positive with positive test (True Positive)
// CovNegative: virus positive with negative test (False Negative)
// FreePositive: virus free with positive test (False Positive)
// FreeNegative: virus free with negative test (True Negative)
namespace Calc{
    double ProbTruePositive(int CovPositive, int FreePositive, int TotalCov, int TotalFree);
    double ProbFalsePositive(int CovPositive, int FreePositive, int TotalCov, int TotalFree);
    double ProbTrueNegative(int CovNegative, int FreeNegative, int TotalCov, int TotalFree);
    double ProbFalseNegative(int CovNegative, int FreeNegative, int TotalCov, int TotalFree);
}
#endif // CALCULATIONS_H
