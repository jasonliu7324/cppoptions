//  Header file for MonteCarlo pricing method
//
//  Derived from PricingMethod
//  
//  9/29: Added current_mesh, pathSim, SD and SE member and methods
//  9/30: Added SD, SE member data and methods
//  10/1: Added sample_path member data

#ifndef MONTECARLO_HPP
#define MONTECARLO_HPP

#include "PricingMethod.hpp"
#include "Option.hpp"
#include "EuropeanOption.hpp"
#include <optional>
#include <vector>
#include <string>

namespace Jason::Finance
{
    class MonteCarlo : public PricingMethod
    {
        private: 
            long NSIM;                                                                  // Number of simulations
            long NT;                                                                    // Number of time steps
            mutable std::optional<std::vector<double> > payoffs;                        // Encodes the most recent payoffs
            mutable std::optional<std::vector<std::vector<double>>> sample_path;        // Encodes the first 100 paths of a simulation for visualization
            mutable std::optional<double> current_sd;                                   // Encodes the most recent standard deviation   
            mutable std::optional<double> current_se;                                   // Encodes the most recent standard error

        public:
            MonteCarlo();                                               // Default constructor
            MonteCarlo(double NSIM, double NT);                         // Specific construcotr
            MonteCarlo(const MonteCarlo& source);                       // Copy constructor
            MonteCarlo& operator = (const MonteCarlo& source);          // Assignment operator
            ~MonteCarlo() override;                                     // Default destructor

            std::string name() const override;                                      // Name
            std::optional<double> price(const Option& opt) const override;          // Pricer function
            bool isAvailable(const Option& opt) const override;                     // Checks availability

            void pathSim(const Option& opt) const;
            double standDev(const Option& opt) const;
            double standErr(const Option& opt) const;

            // Getters and setters inlined
            double getNSIM() const {return NSIM;};
            double getNT() const {return NT;};
            double getSD() const {return current_sd.value();};
            double getSE() const {return current_se.value();};
            const std::vector<double>& getMesh() const {return payoffs.value();};
            const std::vector<std::vector<double>>& getSamplePath() const {return sample_path.value();};
            void setNSIM(double val) {NSIM = val;};
            void setNT(double val) {NT = val;};
             
    };

}   // namespace Jason::Finance

#endif // MONTECARLO_HPP