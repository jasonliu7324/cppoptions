//  Source file for American Put options
//
//  
//
//

//  10/5 : Implementation

#include "AmericanPutOption.hpp"
#include "Option.hpp"

namespace Jason::Finance
{
    AmericanPutOption::AmericanPutOption() : AmericanOption() {};
    AmericanPutOption::AmericanPutOption(const double new_S,                      
                                         const double new_K,
                                         const double new_r,
                                         const double new_sig,
                                         const double new_b,
                                         const double new_T) : AmericanOption(new_S, new_K, new_r, new_sig, new_b, new_T) {};
    
    AmericanPutOption::AmericanPutOption(const AmericanPutOption& source) : AmericanOption(source) {};
    AmericanPutOption::~AmericanPutOption() {};

    AmericanPutOption& AmericanPutOption::operator = (const AmericanPutOption& source)
    {
        if (this == &source)
        {
            return *this;
        }

        AmericanOption::operator = (source);

        return *this;
    }

    // double AmericanPutOption::PayOff(double S) const

}   // namespace Jason::Finance