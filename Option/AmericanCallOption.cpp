//  Source file for American Call Options
//
//  10/5 : Implemented
//
//

#include "AmericanCallOption.hpp"
#include "Option.hpp"


namespace Jason::Finance
{
    AmericanCallOption::AmericanCallOption() : AmericanOption() {};
    AmericanCallOption::AmericanCallOption(const double new_S,                      
                                           const double new_K,
                                           const double new_r,
                                           const double new_sig,
                                           const double new_b,
                                           const double new_T) : AmericanOption(new_S, new_K, new_r, new_sig, new_b, new_T) {};
    
    AmericanCallOption::AmericanCallOption(const AmericanCallOption& source) : AmericanOption(source) {};
    AmericanCallOption::~AmericanCallOption() {};

    AmericanCallOption& AmericanCallOption::operator = (const AmericanCallOption& source)
    {
        if (this == &source)
        {
            return *this;
        }

        AmericanOption::operator = (source);

        return *this;
    }

    // double AmericanCallOption::PayOff(double S) const

}   // namespace Jason::Finance
