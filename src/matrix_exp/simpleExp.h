#ifndef _SIMPLEEXP_H_INCLUDED_
#define _SIMPLEEXP_H_INCLUDED_

namespace MatrixExp{
using namespace boost::numeric;

class SimpleExp
{
private:

    double epsilon;
    double t;

    // Получить следующий факториал
    double nextFactor(double prev, double current) const
    {
        return prev*current;
    }

    // получить следющую степень матри
    ublas::matrix<double> nextPower(const ublas::matrix<double>& prev,
                                     const ublas::matrix<double>& a) const
    {
        return ublas::prod(prev,a);
    }


public:

    SimpleExp()
    {
        epsilon = 0.001;
        t = 1;
    }

    SimpleExp(const double _t, const double eps)
        : epsilon(eps), t(_t)
    {
    }

    ublas::matrix<double> operator()(const ublas::matrix<double>& _a) const
    {
        size_t n = _a.size1(), m = _a.size2();

        ublas::identity_matrix<double> id(n, m);

        ublas::matrix<double> a(n,m), result(n,m), temp(n,m), step(n,m);

        a = _a * t;

        result = id + a;
        temp = a;

        double factor = 1;

        int i = 2;
        bool finished = false;
        while(!finished)
        {
            factor = nextFactor(factor, i);
            temp = nextPower(temp, a);
            step = ((1. / factor) * temp);
            result += step;
            i++;

            finished = ublas::norm_1(step) < epsilon;
        }

        //std::cout << "It took " << i << " steps." << std::endl;

        return result;
    }

};

}

#endif //_SIMPLEEXP_H_INCLUDED_
