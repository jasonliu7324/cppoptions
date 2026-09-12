//  Header file for European Call class
//  Derived from EuropeanOption
//
//
//

#ifndef EUROPEANCALLOPTION_HPP
#define EUROPEANCALLOPTION_HPP

#include "EuropeanOption.hpp"

namespace Jason
{
    namespace Finance
    {
        class EuropeanCallOption : public EuropeanOption
        {
            public:
                EuropeanCallOption();                                   // Default Constructor
                EuropeanCallOption(const double new_S,                  // Specific constructor
                                   const double new_K,
                                   const double new_R,
                                   const double new_sig, 
                                   const double new_b,
                                   const double new_T);
                EuropeanCallOption(const EuropeanCallOption& source);   // Copy Constructor

                ~EuropeanCallOption();                                  // Default Destructor

                EuropeanCallOption& operator = (const EuropeanCallOption& source);      // Assignment operator

                double price() const;   // Call pricer

                double delta() const;               // Delta of call option
                double deltaApprox(double h);       // Delta via 3-point order approximation
        };
    }   // namespace Finance
}   // namespace Jason

#endif // EUROPEANCALLOPTION_HPP