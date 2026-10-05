//  Header file for American call options
//
//  Derived from AmericanOptions
//
//

//  10/5 : Implementation

#ifndef AMERICANCALLOPTION_HPP
#define AMERICANCALLOPTION_HPP

#include "Option.hpp"
#include "AmericanOption.hpp"

namespace Jason::Finance
{
    class AmericanCallOption : public AmericanOption
    {
        public:
            AmericanCallOption();                                       // Default Constructor
            AmericanCallOption(const double new_S,                      // Specific constructor
                               const double new_K,
                               const double new_r,
                               const double new_sig,
                               const double new_b,
                               const double new_T);
            AmericanCallOption(const AmericanCallOption& source);       // Copy constructor

            ~AmericanCallOption();      // Default destructor

            AmericanCallOption& operator = (const AmericanCallOption& source);      // Assignment operator

            // double PayOff(double S) const override;     // Computes Call Payoff given asset price
    };
}

#endif  // AMERICANCALLOPTION_HPP