//  Header file for American Put options
//
//  Derived from AmericanOptions
//
//

//  10/5 : Implementation

#ifndef AMERICANPUTOPTION_HPP
#define AMERICANPUTOPTION_HPP

#include "Option.hpp"
#include "AmericanOption.hpp"

namespace Jason::Finance
{
    class AmericanPutOption : public AmericanOption
    {
        public:
            AmericanPutOption();                                       // Default Constructor
            AmericanPutOption(const double new_S,                      // Specific constructor
                              const double new_K,
                              const double new_r,
                              const double new_sig,
                              const double new_b,
                              const double new_T);
            AmericanPutOption(const AmericanPutOption& source);       // Copy constructor

            ~AmericanPutOption();      // Default destructor

            AmericanPutOption& operator = (const AmericanPutOption& source);      // Assignment operator

            // double PayOff(double S) const override;     // Computes Call Payoff given asset price
    };
}   // namespace Jason::Finance

#endif  // AMERICANPUTOPTION_HPP