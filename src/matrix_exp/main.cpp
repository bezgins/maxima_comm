#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

#include <fstream>

#include "simpleExp.h"
#include "pchelExp.h"

int main ()
{
    using namespace boost::numeric::ublas;

    matrix<double> a (10, 10);

    for (unsigned i = 0; i < a.size1(); ++ i)
        for (unsigned j = 0; j < a.size2(); ++ j)
            a(i, j) = 0.1 * ((double)j/ 4.0);


    MatrixExp::SimpleExp se(0.000001);

    matrix<double> result = se(a);

    std::cout << result << std::endl;
    std::cout << norm_inf(result) << std::endl;


    MatrixExp::PchelExp pe(a);

    matrix<double> result1 = pe.exp(1, 0.0000001); 

    std::cout << result1 << std::endl;

    std::cout << result - result1 << std::endl;


    return 0;
}
