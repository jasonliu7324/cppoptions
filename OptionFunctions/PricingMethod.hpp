//  Header file for Pricing Method abstract base class
//
//  Pricing methods are derived from 
//
//

// Abstract pricing class that will derive into Exact Price, MonteCarlo, and FDM

#ifndef PRICINGMETHOD_HPP
#define PRICINGMETHOD_HPP

#include "Option.hpp"
#include <string>   
#include <optional>      // Needed for std::optional

namespace Jason::Finance
{
    class PricingMethod
    {
        private:
            ///////////////////////////////////////////////////////////////////////////////////////////////

        public:
            PricingMethod();                                            // Default constructor
            PricingMethod(const PricingMethod& source);                 // Copy constructor
            PricingMethod& operator = (const PricingMethod& source);    // Assignment operator
            virtual ~PricingMethod();

            // Virtual functions    
            virtual std::string name() const = 0;                                      // Returns name of the method
            virtual std::optional<double> price(const Option& opt) const = 0;          // Returns price of option based on method
            virtual bool isAvailable(const Option& opt) const = 0;                     // Returns if Method can be called on given option
    };
}   // End Namespace Jason::Finance

#endif // PRICINGMETHOD_HPP