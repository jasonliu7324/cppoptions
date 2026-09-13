//  Header file for American Perpetual Call Option
//
//  Derived from Option Abstract base class
//
//

#ifndef AMERICANPERPETUALCALLOPTION_HPP
#define AMERICANPERPETUALCALLOPTION_HPP

#include "Option.hpp"

namespace Jason
{
    namespace Finance
    {
        class AmericanPerpetualCallOption : public Option
        {
            private:
                double y1() const;      // Term used in pricing formula

            public:
                AmericanPerpetualCallOption();                                                  // Default constructor
                AmericanPerpetualCallOption(const double new_S,                                 // Specific constructor
                                            const double new_K,
                                            const double new_r,
                                            const double new_sig,
                                            const double new_b);
                AmericanPerpetualCallOption(const AmericanPerpetualCallOption& source);         // Copy constructor

                ~AmericanPerpetualCallOption();                                                 // Default destructor

                // Assignment operator
                AmericanPerpetualCallOption& operator = (const AmericanPerpetualCallOption& source);

                // Call pricer
                double price() const;
                double PayOff() const;              // Returns payoff
                double PayOff(double S) const;      // Returns payoff given asset price S

        };
    }   // namespace Finance
}   // namespace Jason

#endif // AMERICANPERPETUALCALLOPTION_HPP