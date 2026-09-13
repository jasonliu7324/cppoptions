//  Source file for PricingMethod abstract base class
//
//  
//
//

#include "PricingMethod.hpp"

namespace Jason::Finance
{   
    PricingMethod::PricingMethod() {};
    PricingMethod::PricingMethod(const PricingMethod& source) {};

    PricingMethod& PricingMethod::operator = (const PricingMethod& source)
    {
        if (this == &source)
        {
            return *this;
        }
        
        return *this;
    }

    PricingMethod::~PricingMethod() {};
}   // namespace Jason::Finance