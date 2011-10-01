#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

#include <fstream>
#include <unistd.h>

#include "simpleExp.h"

int main ()
{
    using namespace boost::numeric::ublas;

    matrix<double> a (4, 4);

    for (unsigned i = 0; i < a.size1(); ++ i)
        for (unsigned j = 0; j < a.size2(); ++ j)
            a(i, j) = 3;


    MatrixExp::SimpleExp se(0.0001);

    matrix<double> result = se(a);

//    std::cout << nextPower(a, a) << std::endl;
    std::cout << result << std::endl;
    std::cout << norm_inf(result) << std::endl;

//    sleep(20);
}
