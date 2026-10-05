//  Source file for American Option
//
//  10/5: Implementation
//
//

#include "Option.hpp"
#include "AmericanOption.hpp"

namespace Jason::Finance
{
    AmericanOption::AmericanOption() : Option(), T(0) {};
    AmericanOption::AmericanOption(const double new_S,                      
                                   const double new_K,
                                   const double new_r,
                                   const double new_sig,
                                   const double new_b,
                                   const double new_T) : Option(new_S, new_K, new_r, new_sig, new_b), T(new_T) {};
    AmericanOption::AmericanOption(const AmericanOption& source) : Option(source), T(source.T) {};

    AmericanOption::~AmericanOption() {};

    AmericanOption& AmericanOption::operator = (const AmericanOption& source)
    {
        if (this == &source)
        {
            return *this;
        }

        Option::operator = (source);
        T = source.T;

        return *this;
    }

}   //  namespace Jason::Finance
