//  Header file for exact pricing method
//
//  Derived from Pricing method base class
//
//

#ifndef EXACTPRICE_HPP
#define EXACTPRICE_HPP

#include "Option.hpp"
#include "PricingMethod.hpp"
#include <string>
#include <optional>

namespace Jason::Finance
{
    class ExactPrice : public PricingMethod
    {
        private:
            ///////////////////////////////////////////////////////////////////////////////////////////////

        public: 
            ExactPrice();                                                       // Default constructor
            ExactPrice(const ExactPrice& source);                               // Copy constructor
            ExactPrice& operator = (const ExactPrice& source);                  // Assignment operator
            ~ExactPrice() override;

            std::string name() const override;                                  // Returns name of pricing method
            std::optional<double> price(const Option& opt) const override;      // Returns price of pricing method
            bool isAvailable(const Option& opt) const override;                 // Returns if pricing method is available

    };


}    // namespace Jason::Finance


#endif  // EXACTPRICE_HPP