#ifndef _PCHELEXP_H_INCLUDED_
#define _PCHELEXP_H_INCLUDED_

#include <vector>
#include <map>
#include <cmath>

namespace MatrixExp
{

using namespace boost::numeric;
using namespace std;

class PchelExp
{
    ublas::matrix<double> a;
    vector<ublas::matrix<double> > powers;
    vector<double> norms;

    typedef std::map<std::pair<unsigned int, unsigned int>, double> pair_map;

    typedef std::map<unsigned int, double> atom_map;

    pair_map q_cache;
    atom_map p_cache;

    // получить следющую степень матри
    ublas::matrix<double> nextPower(const ublas::matrix<double>& prev,
                                     const ublas::matrix<double>& a) const
    {
        return ublas::prod(prev,a);
    }

public:

    PchelExp(ublas::matrix<double> m)
        : a(m), powers(a.size1() + 1), norms(a.size1() + 1)
    {    
       powers[0] = ublas::identity_matrix<double>(a.size1(), a.size2());
       norms[0]  = ublas::norm_1(powers[0]);
       powers[1] = a;
       norms[1]  = ublas::norm_1(powers[1]);

       for(size_t i = 2; i < powers.size(); ++i)
       {
           powers[i] = nextPower(powers[i-1], a);
           norms[i]  = ublas::norm_1(powers[i]);
       }
    }


    ublas::matrix<double> exp(const double t, const double eps)
    {
        ublas::matrix<double> result = ublas::zero_matrix<double>(a.size1(), a.size2());

        int n = a.size1();

        for(int k = 0; k < n; ++k)
        {
//            cout << "k=" << k << endl;
            double temp = 0;
            double r = 0;
            int m = 0;

            double t_k = (pow(t, k) / factorial(k));

            do
            {
//                cout << "m=" << m << endl;
                double r1 = q(m, n - k);
                double r2 = factorial(m + n);

                r = r1 / r2;

                temp += r;
                m++;

            } while (fabs(r) > eps);

            result += powers[k] * (t_k + temp);
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
        return result;
    }

    double p(const unsigned int k) 
    {
        
        atom_map::const_iterator i = p_cache.find(k);

        if(i != p_cache.end())
        {
            return i->second;
        }
 
        if(k == 1)
        {
            double result = trace(a);
            p_cache[k] = result;
            return result;
        }
        
        double result = s(k);

        for(unsigned int i = 1; i <= (k-1); ++i)
        {
            double tmp = p(i) * s(k-i);
            result -= tmp;
        }

        result /= k;

        p_cache[k] = result;
 
        return result;
    }

    double q(const unsigned int m, const unsigned int k) 
    {

        pair_map::const_iterator i = q_cache.find(make_pair(m, k));

        if(i != q_cache.end())
        {
            return i->second;
        }

        if(k == a.size1() + 1)
        {
            q_cache[make_pair(m,k)] = 0;
            return 0;
        }

        if(m == 0)
        {
            double result = p(k);

            q_cache[make_pair(m,k)] = result;
            return result;
        }

        double result = (p(k) * q(m-1, 1)) + q(m-1, k+1);

        q_cache[make_pair(m,k)] = result;
        return result;
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
