// Source file for American Perpetual put option
//
//
//
//

#include "AmericanPerpetualPutOption.hpp"
#include "Option.hpp"
#include <cmath>
#include <algorithm>

namespace Jason
{
    namespace Finance
    {
        // Default constructor
        AmericanPerpetualPutOption::AmericanPerpetualPutOption() : Option()
        {
        }

        // Specific Constructor
        AmericanPerpetualPutOption::AmericanPerpetualPutOption(const double new_S,
                                                               const double new_K, 
                                                               const double new_r,
                                                               const double new_sig,
                                                               const double new_b) : Option(new_S, new_K, new_r, new_sig, new_b)
        {
        }

        // Copy constructor
        AmericanPerpetualPutOption::AmericanPerpetualPutOption(const AmericanPerpetualPutOption& source) : Option(source)
        {
        }

        // Default destructor
        AmericanPerpetualPutOption::~AmericanPerpetualPutOption()
        {
        }

        // Assignment operator
        AmericanPerpetualPutOption& AmericanPerpetualPutOption::operator = (const AmericanPerpetualPutOption& source)
        {
            // Self copy check
            if (this == &source)
            {
                return *this;
            }

            // Call base class assignment operator
            Option::operator = (source);

            return *this;
        }

        // y2 = 1/2 - b/sig^2 - sqrt((b/sig^2 - 1/2)^2 + 2r/sig^2)
        double AmericanPerpetualPutOption::y2() const
        {
            return (1.0/2.0) - getB()/(getSig() * getSig()) - 
                   std::sqrt(std::pow(((getB()/(getSig() * getSig())) - (1.0/2.0)), 2) + (2 * getR()) / (getSig() * getSig()));
        }

        // P = K/(1 - y2) ((y2-1)/y2* S/K)^y2
        double AmericanPerpetualPutOption::price() const
        {
            return getK()/(1 - y2()) * std::pow(((y2() - 1)/y2() * (getS()/getK())) ,y2());
        }

        // PayOff implementation
        double AmericanPerpetualPutOption::PayOff() const
        {
            return std::max(getK() - getS(), 0.0);
        }
        double AmericanPerpetualPutOption::PayOff(double S) const
        {
            return std::max(getK() - S, 0.0);
        }

    }   // namespace Finance
}   // namespace Jason