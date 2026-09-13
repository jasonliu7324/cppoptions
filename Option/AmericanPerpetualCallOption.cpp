// Source file for American perp call options
//
//
//
//

#include "AmericanPerpetualCallOption.hpp"
#include "Option.hpp"
#include <cmath>
#include <algorithm>

namespace Jason
{
    namespace Finance
    {
        // Default constructor
        AmericanPerpetualCallOption::AmericanPerpetualCallOption() : Option()
        {
        }

        // Specific Constructor
        AmericanPerpetualCallOption::AmericanPerpetualCallOption(const double new_S,
                                                                 const double new_K,
                                                                 const double new_r,
                                                                 const double new_sig,
                                                                 const double new_b) : Option(new_S, new_K, new_r, new_sig, new_b)
        {
        }

        // Copy Constructor
        AmericanPerpetualCallOption::AmericanPerpetualCallOption(const AmericanPerpetualCallOption& source) : Option(source)
        {
        }

        // Default destructor
        AmericanPerpetualCallOption::~AmericanPerpetualCallOption()
        {
        }

        // Assignment operator
        AmericanPerpetualCallOption& AmericanPerpetualCallOption::operator = (const AmericanPerpetualCallOption& source)
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

        // y1 = 1/2 - b/sig^2 + sqrt((b/sig^2 - 1/2)^2 + 2r/sig^2)
        double AmericanPerpetualCallOption::y1() const
        {
            return (1.0/2.0) - getB()/(getSig() * getSig()) + 
                   std::sqrt(std::pow(((getB()/(getSig() * getSig())) - (1.0/2.0)), 2) + (2 * getR()) / (getSig() * getSig()));
        }

        // C = K/(y1 - 1) ((y1-1)/y1* S/K)^y1
        double AmericanPerpetualCallOption::price() const
        {
            return getK()/(y1() - 1) * std::pow(((y1() - 1)/y1() * (getS()/getK())) ,y1());
        }

        // Payoff implementation
        double AmericanPerpetualCallOption::PayOff() const
        {
            return std::max(getS() - getK(), 0.0);
        }
        double AmericanPerpetualCallOption::PayOff(double S) const
        {
            return std::max(S - getK(), 0.0);
        }
        

    }   // namespace Finance
}   // namespace Finance