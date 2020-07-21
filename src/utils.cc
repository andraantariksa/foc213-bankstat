#include <vector>
#include <iostream>

double diceEyesProbability(int dice_total, int expected_eyes_total, int dice_side=6)
{
    if(expected_eyes_total < dice_total || expected_eyes_total > dice_total * 6)
    {
        return 0;
    }

    std::vector<double> single_dice_prob(dice_side, 1.0 / dice_side);
    std::vector<double> combined_prob(1, 1.0);
    int n_iter = dice_total;
    while(n_iter--)
    {
        auto start_prob = combined_prob;
        combined_prob.clear();

        int prob_a_i = 0;
        for (double prob_a : start_prob)
        {
            int prob_b_i = 0;
            for (double prob_b : single_dice_prob)
            {
                double val = 0.0;
                try
                {
                    val = combined_prob.at(prob_a_i + prob_b_i);
                    if (val == -1.0)
                    {
                        val = 0.0;
                    }
                }
                // Maybe overflow
                catch (std::exception &_)
                {
                    combined_prob.resize(prob_a_i + prob_b_i + 1, -1.0);
                }
                combined_prob[prob_a_i + prob_b_i] = val + prob_a * prob_b;

                prob_b_i++;
            }

            prob_a_i++;
        }
    }

    double val = 0.0;
    try
    {
        val = combined_prob.at(expected_eyes_total - dice_total);
    }
    // Maybe overflow
    catch (std::exception &_)
    {
    }

    return val;
}
