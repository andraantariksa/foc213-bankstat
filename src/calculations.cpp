//
// Created by naavadi64 on 6/13/20.
//

// Arguments:
// CovPositive: virus positive with positive test (True Positive)
// CovNegative: virus positive with negative test (False Negative)
// FreePositive: virus free with positive test (False Positive)
// FreeNegative: virus free with negative test (True Negative)
double Probability(double CovPositive, double CovNegative, double FreePositive, double FreeNegative, int Selector){
    double TotalCov = CovPositive + CovNegative;
    double TotalFree = FreePositive + FreeNegative;
    double TotalPositive = CovPositive + FreePositive;
    double TotalNegative = CovNegative + FreeNegative
    double Total = TotalCov + Totalfree;

    double ProbCov = TotalCov / Total;  // Probability of virus positive in general
    double ProbPositiveCov = CovPositive / TotalCov;  // Probability of testing positive given virus positive
    double ProbNegativeCov = CovNegative / TotalCov;  // Probability of testing negative given virus positive
    double ProbFree = TotalFree / Total;  // Probability of virus negative in general
    double ProbPositiveFree = FreePositive / TotalFree;  // Probability of testing positive given virus negative
    double PronNegativeFree = FreeNegative / TotalFree;  // Probability of testing negative given virus negative
    double result = 0;

    switch(Selector){
        case 1:
            // Calculate the probability of being virus positive (cov) given that the tests indicates positive (+)
            // P(cov|+)
            result = (ProbPositiveCov*ProbCov) / ((ProbPositiveCov*ProbCov) + (ProbPositiveFree*ProbFree));
            break;

        case 2:
            // Calculate the probability of being virus positive (cov) given that the tests indicates negative (-)
            // P(cov|-)
            result = (ProbNegativeCov*ProbCov) / ((ProbNegativeCov*ProbCov) + (ProbNegativeFree*ProbFree));
            break;

        case 3:
            // Calculate the probability of being virus negative (cov) given that the tests indicates positive (+)
            // P(free|+)
            result = (ProbPositiveFree*ProbFree) / ((ProbPositiveFree*ProbFree) + (ProbPositiveCov*ProbCov));
            break;

        case 4:
            // Calculate the probability of being virus negative (cov) given that the tests indicates negative (-)
            // P(free|-)
            result = (ProbNegativeFree*ProbFree) / ((ProbNegativeFree*ProbFree) + (ProbNegativeCov*ProbCov));
            break;

        default:
            cout>>"Invalid selector, try again bucko!">>endl;
            break;
    };
};
