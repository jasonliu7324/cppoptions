//  Source file for European options class
//
//
//
//

#include "OptionGlobalFunctions.hpp"
#include "EuropeanOption.hpp"
#include <stdexcept>
#include <cmath>    // Necessary for math functions
#include <iostream>


namespace Jason
{
    namespace Finance
    {
        // Default Constructor, Sets time to 0
        EuropeanOption::EuropeanOption() : Option(), T(0)
        {
        }

        // Specific Constructor
        EuropeanOption::EuropeanOption(const double new_S,
                                       const double new_K,
                                       const double new_r,
                                       const double new_sig,
                                       const double new_b,
                                       const double new_T) : Option(new_S, new_K, new_r, new_sig, new_b)
        {
            setT(new_T);
        }

        // Copy Constructor
        EuropeanOption::EuropeanOption(const EuropeanOption& source) : Option(source), T(source.T)
        {
        }

        // Default Destructor
        EuropeanOption::~EuropeanOption()
        {
        }

        // Setter for T
        void EuropeanOption::setT(double new_T)
        {
            // Parameter validation
            if (new_T <= 0)
                throw std::invalid_argument("Time must be greater than 0");
            
            T = new_T;
        }

        // Assignment operator
        EuropeanOption& EuropeanOption::operator = (const EuropeanOption& source)
        {
            // Self Copy check
            if (this == &source)
            {
                return *this;
            }

            // Calls base class assignment operator
            Option::operator = (source);

            T = source.T;

            return *this;
        }

        // d1
        double EuropeanOption::d1() const
        {
            // Formula for d1
            return (std::log(getS() / getK()) + (getB() + (getSig() * getSig() / 2.0)) * getT()) / (getSig() * std::sqrt(getT()));
        }

        // d2
        double EuropeanOption::d2() const
        {
            // Formula for d2 via calling d1()
            return (d1() - getSig() * std::sqrt(getT()));
        }

        // Gamma
        double EuropeanOption::gamma() const
        {
            // (n(d1) e^{(b-r)T}) / (S \sigma \sqrt(T))
            return (n(d1()) * std::exp((getB() - getR()) * getT())) / (getS() * getSig() * std::sqrt(getT()));
        }

        // 3-point oder approximation of Gamma
        double EuropeanOption::gammaApprox(double h)
        {
            double V_plus, V_minus, num;          // V(S+h) and V(S-h), V(S+h) - 2V(S) + V(S-h)
            double S_original = getS();           // Capture original

            setS(S_original + h);
            V_plus = price();       // V(S+h)

            setS(S_original - h);
            V_minus = price();      // V(S-h)

            setS(S_original);       // Restore original

            // Guard here: if diff is too small (near 0) then h is too small to be resolved
            // reliably in double precision
            // No throw here since we want to see "discarded" values
            num = V_plus - (2 * price()) + V_minus;

            if (std::abs(num) < 1e-14 * std::abs(V_plus))
            {
                std::cout << "Warning: h = " << h << " may be too small and" 
                          << "V(S+h) - 2V(S) + V(S-h) is likely lost to round off. \n";
            }

            return (num) / (h * h);
        }

        bool EuropeanOption::hasClosedForm() const
        {
            return true;
        }

        bool EuropeanOption::isPerpetual() const
        {
            return false;
        }

        
    }   // namespace Finance
}   // namespace Jason