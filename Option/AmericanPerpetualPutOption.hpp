// Header file for American perpetual put option
//
// Derived from Option Abstract base class
//
//

#ifndef AMERICANPERPETUALPUTOPTION_HPP
#define AMERICANPERPETUALPUTOPTION_HPP

#include "Option.hpp"

namespace Jason
{
    namespace Finance
    {
        class AmericanPerpetualPutOption : public Option
        {
            private:
                double y2() const;      // Term used in pricing formula

            public:
                AmericanPerpetualPutOption();                                               // Default constructor
                AmericanPerpetualPutOption(const double new_S,                              // Specific constructor
                                           const double new_K,
                                           const double new_r,
                                           const double new_sig,
                                           const double new_b);
                AmericanPerpetualPutOption(const AmericanPerpetualPutOption& source);       // Copy constructor
                        
                ~AmericanPerpetualPutOption();                                              // Default destructor

                // Assignment operator
                AmericanPerpetualPutOption& operator = (const AmericanPerpetualPutOption& source);

                // Put pricer
                double price() const;
                double PayOff() const;              // returns payoff of perpetual put
                double PayOff(double S) const;      // returns payoff of perpetual put given asset price

                bool hasClosedForm() const; 
                bool isPerpetual() const;
        };
    }   // namespace Finance
}   // namespace Jason

#endif // AMERICANPERPETUALPUTOPTION_HPP
