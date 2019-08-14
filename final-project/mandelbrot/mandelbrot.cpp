#include <complex>
#include <iostream>

using namespace std;

int main()
{
    int max_row, max_column, max_n;
    cin >> max_row;
    cin >> max_column;
    cin >> max_n;

    char **mat = (char **)malloc(sizeof(char *) * max_row);

    for (int i = 0; i < max_row; i++)
        mat[i] = (char *)malloc(sizeof(char) * max_column);

#pragma omp parallel
    {
#pragma omp for collapse(2) schedule(dynamic)
        for (int r = 0; r < max_row; ++r)
        {
            for (int c = 0; c < max_column; ++c)
            {
                complex<float> number_c;

                complex<float> z;
                number_c = decltype(z)((float)c * 2 / max_column - 1.5, (float)r * 2 / max_row - 1);

                int iterations = 0;
                while (abs(z) < 2 && ++iterations < max_n)
                    //decltype(z) is yeading the type of the variable z to the resulf of the following example
                    z = pow(z, 2.0f) + number_c;

                mat[r][c] = (iterations == max_n ? '#' : '.'); //n = max if we 'blew' up, hence, whether this will be a . or #
            }
        }
    }

    for (int r = 0; r < max_row; ++r)
    {
        for (int c = 0; c < max_column; ++c)
            std::cout << mat[r][c];
        cout << '\n';
    }

    free(mat);
}
