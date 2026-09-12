//  Source file for EuropeanPutOption
//
//
//
//

#include "EuropeanPutOption.hpp"
#include "OptionGlobalFunctions.hpp"    // Has specialized math functions for computation

#include <cmath>    // Necessary math functions
#include <iostream>

namespace Jason
{
    namespace Finance
    {
        // Default Constructor
        EuropeanPutOption::EuropeanPutOption() : EuropeanOption()
        {
        }

        // Specific constructor
        EuropeanPutOption::EuropeanPutOption(const double new_S,
                                             const double new_K,
                                             const double new_r,
                                             const double new_sig,
                                             const double new_b,
                                             const double new_T) : EuropeanOption(new_S, new_K, new_r, new_sig, new_b, new_T)
        {
        }

        // Copy Constructor
        EuropeanPutOption::EuropeanPutOption(const EuropeanPutOption& source) : EuropeanOption(source)
        {
        }

        // Default destructor 
        EuropeanPutOption::~EuropeanPutOption()
        {
        }

        // Assignment Operator
        EuropeanPutOption& EuropeanPutOption::operator = (const EuropeanPutOption& source)
        {
            // Self check
            if (this == &source)
            {
                return *this;
            }

            // Call base class assignment oeprator
            EuropeanOption::operator = (source);

            return *this;
        }

        // Put pricer
        double EuropeanPutOption::price() const
        {
            // BSM solution for P
            // For stock options have b = r
            return (getK() * std::exp(-1.0 * getR() * getT()) * N(-1.0 * d2()) - getS() 
                   * std::exp((getB() - getR())* getT()) * N(-1.0 * d1()));
        }

        // Put delta
        double EuropeanPutOption::delta() const
        {
            // e^{(b-r)T} (N(d1) - 1)
            return std::exp((getB() - getR()) * getT()) * (N(d1()) - 1);
        }

        // 3-point order approximation of delta
        double EuropeanPutOption::deltaApprox(double h)
        {
            double V_plus, V_minus, diff;       // V(S+h), V(S-h), V(S+h) - V(S-h)
            double S_original = getS();         // Capture original 

            setS(S_original + h);
            V_plus = price();           // V(S+h)

            setS(S_original - h);
            V_minus = price();          // V(S-h)

            setS(S_original);           // Restore original

            // Guard here: if diff is too small (near 0) then h is too small to be resolved
            // reliably in double precision
            // No throw here since we want to see "discarded" values
            diff = V_plus - V_minus;

            if (std::abs(diff) < 1e-14 * std::abs(V_plus))
            {
                std::cout << "Warning: h = " << h << " may be too small and" 
                          << "V(S+h) - V(S-h) is likely lost to round off. \n";
            }

            return diff / (2 * h);
        }

    }   // namespace Finance
}   // namespace Jason