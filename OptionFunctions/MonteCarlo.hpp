//  Header file for MonteCarlo pricing method
//
//  Derived from PricingMethod
//
//

#ifndef MONTECARLO_HPP
#define MONTECARLO_HPP

#include "PricingMethod.hpp"
#include "Option.hpp"
#include <optional>
#include <string>

namespace Jason::Finance
{
    class MonteCarlo : public PricingMethod
    {
        private: 
            long NSIM;          // Number of simulations
            long NT;            // Number of time steps

        public:
            MonteCarlo();                                               // Default constructor
            MonteCarlo(double NSIM, double NT);                         // Specific construcotr
            MonteCarlo(const MonteCarlo& source);                       // Copy constructor
            MonteCarlo& operator = (const MonteCarlo& source);          // Assignment operator
            ~MonteCarlo();                                              // Default destructor

            std::string name() const;
            std::optional<double> price() const;
            bool isAvailable(const Option& opt) const;
    };


}   // namespace Jason::Finance

#endif // MONTECARLO_HPP