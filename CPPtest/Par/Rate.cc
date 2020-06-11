#include <vector>

int Rate()
{
    std::vector<double> Weight_of_Cores =
        {
            0.0764138,
            0.0761638,
            0.0773795,
            0.0771245,
            0.078275,
            0.0780161,
            0.121396,
            0.121996,
            0.123435,
            0.124035,
            0.0275986,
            0.0181666};
    double rest = 0;
    for (int i = 0; i < 8; i++)
        rest += Weight_of_Cores[i];
    rest += Weight_of_Cores[10];
    printf("rest: %f\n", rest);
    return 0;
}