#ifndef _PCHELEXP_H_INCLUDED_
#define _PCHELEXP_H_INCLUDED_

#include <vector>
#include <cmath>

namespace MatrixExp
{

using namespace boost::numeric;
using namespace std;

class PchelExp
{
    ublas::matrix<double> a;
    vector<ublas::matrix<double> > powers;

    // получить следющую степень матри
    ublas::matrix<double> nextPower(const ublas::matrix<double>& prev,
                                     const ublas::matrix<double>& a) const
    {
        return ublas::prod(prev,a);
    }

public:

    PchelExp(ublas::matrix<double> m)
        : a(m), powers(a.size1() + 1)
    {    
       powers[0] = ublas::identity_matrix<double>(a.size1(), a.size2());
       powers[1] = a;

       for(size_t i = 2; i < powers.size(); ++i)
           powers[i] = nextPower(powers[i-1], a);
    }


    ublas::matrix<double> exp(const double t, const double eps) const
    {
        ublas::matrix<double> result = ublas::zero_matrix<double>(a.size1(), a.size2());

        //cout << result << endl;

        int n = a.size1();

        for(int k = 0; k < n; ++k)
        {
            cout << "k=" << k << endl;
            double temp = 0;
            double r = 0;
            int m = 0;

            do
            {
                cout << "m=" << m << endl;
                double r1 = q(m, n - k);
                double r2 = factorial(m + n);

//                cout << "R(" << m << "," << k << ")= " <<  r1 << " / " << r2 << endl;

                r = r1 / r2;

                //cout << r << endl;

                temp += r;
                m++;
            } while (fabs(r) > eps);

//            cout << "temp = " << temp << endl;

            temp = (pow(t, k) / factorial(k)) + temp;

//            cout << "temp = " << temp << endl;

            result += powers[k] * temp;
        }

        return result;
    }

private:
    double trace(const ublas::matrix<double> a) const
    {
        double result = 0;

        for(size_t i = 0; i < a.size1(); ++i)
        {
            result += a(i,i);
        }

        return result;
    }

    double s(const unsigned int k) const
    {
        double result = trace(powers[k]);
//        cout << "s(" << k << ") = " << result << endl;
        return result;
    }

    double p(const unsigned int k) const 
    {
        if(k == 1)
            return trace(a);
        
        double result = s(k);

        for(unsigned int i = 1; i <= (k-1); ++i)
        {
            //TODO: Add memoization here.
            double tmp = p(i) * s(k-i);
            result -= tmp;
        }

        result /= k;

//        cout << "P(" << k << ") = " << result << endl;

        return result / k;
    }

    double q(const unsigned int m, const unsigned int k) const 
    {

//        cout << "q(" << m << "," << k << ")" << endl;

        if(k == a.size1() + 1)
        {
//            cout << "returning 0" << endl;
            return 0;
        }

        if(m == 0)
        {
//            cout << "returning p(k)" << endl;
            return p(k);
        }

        return (p(k) * q(m-1, 1)) + q(m-1, k+1);
    }

    double factorial(const unsigned int n) const
    {
        double result = 1;

        for (unsigned int i = 2; i <= n; ++i)
            result *= i;

        return result;
    }
};

}

#endif //_PCHELEXP_H_INCLUDED_
