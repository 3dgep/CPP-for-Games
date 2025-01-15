#include <iostream>

int main()
{
    int values[5]{1, 2};

    for (int i = 0; i < std::size(values); ++i)
    {
        std::cout << "values[" << i << "]: " << values[i] << std::endl;
    }

    int* pvalues = new int[10]{0, 1, 2};

    for (int i = 0; i < 10; ++i)
    {
        std::cout << "pvalues[" << i << "]: " << pvalues[i] << std::endl;
    }

    int values2d[][3]
    {
        {0, 1, 2},
        {3, 4, 5},
        {6, 7, 8},
        {9, 10, 11}
    };

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            int idx = i * 3 + j;
            std::cout << "values2d[" << i << "][" << j << "]: " << values2d[i][j] << " idx: " << idx << std::endl;
        }
    }

    int* pvalues2d = &values2d[0][0];

    for (int i = 0; i < 12; ++i)
    {
        std::cout << "pvalues2d[" << i << "]: " << *(pvalues2d++) << std::endl;
    }

    delete[] pvalues;

    return 0;
}