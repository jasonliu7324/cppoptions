//  Source file for Exact pricing method class
//
//
//
//

#include "ExactPrice.hpp"
#include "Option.hpp"

namespace Jason::Finance
{
    // Base and copy constructors
    ExactPrice::ExactPrice() : PricingMethod() {};
    ExactPrice::ExactPrice(const ExactPrice& source) : PricingMethod(source) {};

    // Assignment operator
    ExactPrice& ExactPrice::operator = (const ExactPrice& source)
    {
        if (this == &source)
        {
            return *this;
        }

        PricingMethod::operator = (source);

        return *this;
    }

    // Destructor
    ExactPrice::~ExactPrice() {};

    // Name
    std::string ExactPrice::name() const
    {
        return "Exact Price";
    }

    // isAvailable
    bool ExactPrice::isAvailable(const Option& opt) const
    {
        return opt.hasClosedForm();
    }

    // Exact pricer
    std::optional<double> ExactPrice::price(const Option& opt) const
    {
        if (!isAvailable(opt))
        {
            return std::nullopt;
        }

        // Uses the black scholes pricing formula
        return opt.price();
    }

}