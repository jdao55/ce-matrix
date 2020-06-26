#include "matrix.hpp"

#include "operator.hpp"
int main()
{
    ce::ctmatrix<int, 3, 3> test{ 0, 1, 2, 3, 4, 5, 6, 7, 8 };
    ce::ctmatrix<int, 3, 3> test2{ 0, 1, 2, 3, 4, 5, 6, 7, 8 };
    return test2(0, 1);
}
