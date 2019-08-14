#include <iostream>
#include <sstream>
#include <omp.h>

using namespace std;

void sum(char *output, const long unsigned int d, const long unsigned int n)
{
    long unsigned int digits[d + 11];
    long unsigned int interValues[d + 11];

    #pragma omp parallel
    {
        #pragma omp for schedule(dynamic)
        for (long unsigned int digit = 0; digit < d + 11; ++digit)
        {
            digits[digit] = 0;
            interValues[digit] = 0;
        }
    }

#pragma omp parallel firstprivate(interValues)
    {
#pragma omp for schedule(dynamic, 2)
        for (long unsigned int i = 1; i <= n; ++i)
        {
            long unsigned int remainder = 1;

            for (long unsigned int digit = 0; digit < d + 11 && remainder; ++digit)
            {
                long unsigned int div = remainder / i;

                interValues[digit] += div;

                remainder = remainder % i * 10;
                // digits[digit] += div;
            }
        }

#pragma omp critical
        {
            for (long unsigned int k = 0; k < d + 11; ++k)
            {
                digits[k] += interValues[k];
            }
        }

        
    }
    for (long unsigned int i = d + 11 - 1; i > 0; --i)
    {
        digits[i - 1] += digits[i] / 10;
        digits[i] %= 10;
    }
    if (digits[d + 1] >= 5)
    {
        ++digits[d];
    }
    for (long unsigned int i = d; i > 0; --i)
    {
        digits[i - 1] += digits[i] / 10;
        digits[i] %= 10;
    }
    stringstream stringstreamA;
    stringstreamA << digits[0] << ".";
    for (long unsigned int i = 1; i <= d; ++i)
    {
        stringstreamA << digits[i];
    }
    stringstreamA << '\0';
    string stringA = stringstreamA.str();
    stringA.copy(output, stringA.size());
}

int main()
{

    long unsigned int d, n;

    cin >> d >> n;

    char output[d + 10]; // extra precision due to possible error

    sum(output, d, n);

    cout << output << endl;

    return 0;
}
