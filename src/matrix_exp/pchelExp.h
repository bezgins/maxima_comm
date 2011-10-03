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
        : powers(a.size1() + 1), a(m)
    {    
       powers[0] = ublas::identity_matrix<double>(a.size1(), a.size2());
       powers[1] = a;

       for(size_t i = 2; i < powers.size(); ++i)
           powers[i] = nextPower(powers[i-1], a);
    }


    ublas::matrix<double> exp(const double t, const double eps) const
    {
        ublas::matrix<double> result(a.size1(), a.size2());

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
                r = (q(m, n-k)) / (factorial(m+n));
                temp += r;
                ++m;
            } while (r > eps);

            temp = (pow(t, k) / factorial(k)) + temp;

            result += powers[k] * temp;
        }
    }

private:
    double trace(const ublas::matrix<double> a) const
    {
        double result = 0;

        for(int i = 0; i < a.size1(); ++i)
        {
            result += a(i,i);
        }

        return result;
    }

    double s(const unsigned int k) const
    {
        return trace(powers[k]);
    }

    double p(const unsigned int k) const 
    {
        if(k == 1)
            return trace(a);
        
        double result = s(k);

        for(int i = 1; i <= (k-1); ++i)
        {
            //TODO: Add memoization here.
            double tmp = p(i) * s(k-i);
            result -= tmp;
        }

        return result / k;
    }

    double q(const unsigned int m, const unsigned int k) const 
    {

        cout << "q(" << m << "," << k << ")" << endl;

        if(k == a.size1() + 1)
        {
            cout << "returning 0" << endl;
            return 0;
        }

        if(m == 0)
        {
            cout << "returning p(k)" << endl;
            return p(k);
        }

        return (p(k) * q(m-1, 1)) + q(m-1, k+1);
    }

    double factorial(const unsigned int n) const
    {
        double result = 1;

        for (int i = 2; i <= n; ++i)
            result *= i;

        return result;
    }
};

}

#endif //_PCHELEXP_H_INCLUDED_
