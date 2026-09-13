//  Source file for EuropeanCallOption
//
//
//
//

#include "EuropeanCallOption.hpp"
#include "OptionGlobalFunctions.hpp"    // Has specialized math functions for computation

#include <cmath>           // Necessary for math functions
#include <iostream>
#include <algorithm>       // Necessary for max

namespace Jason
{
    namespace Finance
    {
        // Default Constructor
        EuropeanCallOption::EuropeanCallOption() : EuropeanOption()
        {
        }

        // Specific constructor
        EuropeanCallOption::EuropeanCallOption(const double new_S,
                                               const double new_K,
                                               const double new_r,
                                               const double new_sig,
                                               const double new_b,
                                               const double new_T) : EuropeanOption(new_S, new_K, new_r, new_sig, new_b, new_T)
        {
        }

        // Copy Constructor
        EuropeanCallOption::EuropeanCallOption(const EuropeanCallOption& source) : EuropeanOption(source)
        {
        }

        // Default Destructor
        EuropeanCallOption::~EuropeanCallOption()
        {
        }

        // Assignment Operator
        EuropeanCallOption& EuropeanCallOption::operator = (const EuropeanCallOption& source)
        {
            // Self check
            if (this == &source)
            {
                return *this;
            }

            // Call base class assignment operator
            EuropeanOption::operator = (source);

            return *this;
        }

        // Call pricer
        double EuropeanCallOption::price() const
        {
            // BSM solution for C 
            // For stock options we have b = r
            return (getS() * std::exp((getB() - getR()) * getT()) * N(d1()) - getK() 
                    * std::exp(-1.0 * getR() * getT()) * N(d2()));
        }

        // Call delta
        double EuropeanCallOption::delta() const
        {
            // e^{(b-r)T} N(d1)
            return std::exp((getB() - getR()) * getT()) * N(d1());
        }

        // 3-point order approximation of delta
        double EuropeanCallOption::deltaApprox(double h)
        {
            double V_plus, V_minus, diff;         // V(S+h) and V(s-h), V(S+h) - V(S-h)
            double S_original = getS();           // Capture original

            setS(S_original + h);
            V_plus = price();       // V(S+h)

            setS(S_original - h);
            V_minus = price();      // V(S-h)

            setS(S_original);       // Restore original

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

        // PayOff implementation
        double EuropeanCallOption::PayOff() const
        {
            return std::max(getS() - getK(), 0.0);
        }
        double EuropeanCallOption::PayOff(double S) const
        {
            return std::max(S - getK(), 0.0);
        }

    }   // namespace Finance
}   // namespace Jason