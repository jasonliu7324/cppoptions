//  Header file for European Put class
//  Derived from European Option
//
//
//

#ifndef EUROPEANPUTOPTION_HPP
#define EUROPEANPUTOPTION_HPP

#include "EuropeanOption.hpp"

namespace Jason
{
    namespace Finance
    {
        class EuropeanPutOption: public EuropeanOption
        {
            public:
                EuropeanPutOption();                                    // Default constructor
                EuropeanPutOption(const double new_S,                   // Specific constructor
                                  const double new_K,
                                  const double new_R,
                                  const double new_sig,
                                  const double new_b,
                                  const double new_T);
                EuropeanPutOption(const EuropeanPutOption& source);     // Copy constructor

                ~EuropeanPutOption();                                   // Default Destructor

                EuropeanPutOption& operator = (const EuropeanPutOption& source);        // Assignment operator

                double price() const;   // Put pricer

                double delta() const;               // Delta of put option
                double deltaApprox(double h);       // Delta via 3-point order approximation
        };
    }   // namespace Finance
}   // namespace Jason

#endif // EUROPEANPUTOPTION_HPP