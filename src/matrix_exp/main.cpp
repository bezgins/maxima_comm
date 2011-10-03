#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

#include <fstream>

#include "simpleExp.h"
#include "pchelExp.h"

int main ()
{
    using namespace boost::numeric::ublas;

    matrix<double> a (3, 3);

    for (unsigned i = 0; i < a.size1(); ++ i)
        for (unsigned j = 0; j < a.size2(); ++ j)
            a(i, j) = 3;


    MatrixExp::SimpleExp se(0.0001);

    matrix<double> result = se(a);

    std::cout << result << std::endl;
    std::cout << norm_inf(result) << std::endl;


    MatrixExp::PchelExp pe(a);

    std::cout << pe.exp(1, 0.0001) << std::endl;


    return 0;
}
