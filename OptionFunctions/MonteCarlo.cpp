//  Source file for MonteCarlo pricing class
//
//
//
//

#include "MonteCarlo.hpp"
#include "PricingMethod.hpp"
#include "Option.hpp"

#include <string>
#include <optional>


namespace Jason::Finance
{
    // Constructor implementations
    MonteCarlo::MonteCarlo() : PricingMethod() , NSIM(0), NT(0) {};
    MonteCarlo::MonteCarlo(double NSIM, double NT) : PricingMethod(), NSIM(NSIM), NT(NT) {};
    MonteCarlo::MonteCarlo(const MonteCarlo& source) : PricingMethod(source), NSIM(source.NSIM), NT(source.NT) {};

    // Assignment oeprator
    MonteCarlo& MonteCarlo::operator = (const MonteCarlo& source)
    {
        if (this == &source)
        {
            return *this;
        }

        PricingMethod::operator = (source);
        NSIM = source.NSIM;
        NT = source.NT;

        return *this;

    }

    // Destructor
    MonteCarlo::~MonteCarlo() {};

    // Name
    std::string MonteCarlo::name() const
    {
        return "Monte Carlo";
    }

    // isAvailable
    bool MonteCarlo::isAvailable(const Option& opt) const
    {
        if (!opt.isPerpetual())
        {
            return true;
        }
    }


    // Pricer
    std::optional<double> MonteCarlo::price() const
    {
        if (!isAvailable)
        {
            return std::nullopt;
        }
    }






}   // namespace Jason::Finance