#include "mediant.hpp"

/** Thanks to Stackoverflow **/

inline Fraction double_to_frac(double number, long max_den)
{

    double atof();
    int atoi();
    void exit();

    long m[2][2];
    double x, startx;
    long maxden;
    long ai;

    /* read command line arguments */

    startx = x = number;
    maxden = max_den;

    /* initialize matrix */
    m[0][0] = m[1][1] = 1;
    m[0][1] = m[1][0] = 0;

    /* loop finding terms until denom gets too big */
    while (m[1][0] * (ai = (long)x) + m[1][1] <= maxden)
    {
        long t;
        t = m[0][0] * ai + m[0][1];
        m[0][1] = m[0][0];
        m[0][0] = t;
        t = m[1][0] * ai + m[1][1];
        m[1][1] = m[1][0];
        m[1][0] = t;
        if (x == (double)ai)
            break; // AF: division by zero
        x = 1 / (x - (double)ai);
        if (x > (double)0x7FFFFFFF)
            break; // AF: representation failure
    }

    return Fraction(m[0][0], m[1][0]);

    /* now remaining x is between 0 and 1/ai */
    /* approx as either 0 or 1/m where m is max that will fit in maxden */
    /* first try zero */
    /**
    printf("%ld/%ld, error = %e\n", m[0][0], m[1][0],
           startx - ((double)m[0][0] / (double)m[1][0]));
           **/

    /* now try other possibility */
    /**
    ai = (maxden - m[1][1]) / m[1][0];
    m[0][0] = m[0][0] * ai + m[0][1];
    m[1][0] = m[1][0] * ai + m[1][1];
    printf("%ld/%ld, error = %e\n", m[0][0], m[1][0],
           startx - ((double)m[0][0] / (double)m[1][0]));
           **/
}

inline double calc_double_mediant(double a, double b, long max_den)
{
    Fraction f_a = double_to_frac(a, max_den);
    Fraction f_b = double_to_frac(b, max_den);
    return ((f_a.z + f_b.z) / (f_a.n + f_b.n));
}

complex_type calc_complex_mediant(complex_type a, complex_type b, long max_den)
{
    return complex_type(calc_double_mediant(a.real(), b.real(), max_den),
                        calc_double_mediant(a.imag(), b.imag(), max_den));
}