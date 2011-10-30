#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

#include <fstream>

#include <stdlib.h>
#include <time.h>

#include "simpleExp.h"
#include "pchelExp.h"


//////////////////////
//
// Time measurement routines
//
/////////////////////

#include <sys/time.h>

struct timeval tv1,tv2,dtv;
struct timezone tz;

void time_start()
{
    gettimeofday(&tv1, &tz);
}

long time_stop()
{
    gettimeofday(&tv2, &tz);

    dtv.tv_sec= tv2.tv_sec -tv1.tv_sec;
    dtv.tv_usec=tv2.tv_usec-tv1.tv_usec;

    if(dtv.tv_usec<0)
    {
        dtv.tv_sec--;
        dtv.tv_usec+=1000000;
    }

    return dtv.tv_sec*1000+dtv.tv_usec/1000;
}

//////////////////////
//
// main code
//
/////////////////////

void test(int size)
{
    using namespace boost::numeric::ublas;

//    std::cout << size << "\t";

    matrix<double> a (size, size);

    for (unsigned i = 0; i < a.size1(); ++ i)
        for (unsigned j = 0; j < a.size2(); ++ j)
            a(i, j) = (rand() % 100) * 0.01;


    MatrixExp::SimpleExp se(1, 0.00001);

    time_start();
    matrix<double> result = se(a);

    long elapsed = time_stop();
    std::cout <<  elapsed << "\t";

    time_start();
    MatrixExp::PchelExp pe(a);
    long constr = time_stop();

    time_start();
    matrix<double> result1 = pe.exp(1, 0.00001);
    elapsed = time_stop();
    std::cout << elapsed + constr << "\t";


//    std::cout << norm_1(result) << std::endl;
//    std::cout << norm_1(result1) << std::endl;
    std::cout << norm_1(result - result1)/norm_1(result) << std::endl;
}

int main ()
{
    srand(time(NULL));

    for(int i = 2; i < 100; i++)
    {
        test(i);
    }

    return 0;
}
