//  Source file for MonteCarlo pricing class
//
//
// 
//  9/29: Implemented pathSim
//  9/30: Implemented price/SD/SE as well as member data for SD/SE
//  10/1: Implemented sample_path member data and getter as well as sample_path_temp in pathSim


#include "MonteCarlo.hpp"
#include "PricingMethod.hpp"
#include "Option.hpp"
#include "Range.hpp"

#include <string>
#include <optional>
#include <boost/random/lagged_fibonacci.hpp>
#include <boost/random/normal_distribution.hpp>
#include <random>
#include <cmath>
#include <numeric>
#include <utility>


namespace Jason::Finance
{
    // Constructor implementations
    MonteCarlo::MonteCarlo() : PricingMethod() , NSIM(0), NT(0), payoffs(std::nullopt), current_sd(std::nullopt), current_se(std::nullopt), sample_path(std::nullopt) {};
    MonteCarlo::MonteCarlo(double NSIM, double NT) : PricingMethod(), NSIM(NSIM), NT(NT), payoffs(std::nullopt), current_sd(std::nullopt), current_se(std::nullopt), sample_path(std::nullopt) {};
    MonteCarlo::MonteCarlo(const MonteCarlo& source) : PricingMethod(source), NSIM(source.NSIM), NT(source.NT), payoffs(std::nullopt), current_sd(std::nullopt), current_se(std::nullopt), sample_path(std::nullopt) {};

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
        payoffs = std::nullopt;
        current_sd = std::nullopt;
        current_se = std::nullopt;
        sample_path = std::nullopt;

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
    std::optional<double> MonteCarlo::price(const Option& opt) const
    {
        if (!isAvailable(opt))
        {
            return std::nullopt;
        }

        // Call pathSim
        this -> pathSim(opt);
        std::vector<double>& payoff = payoffs.value();
        
        // Sum the payoffs
        double sum = std::accumulate(payoff.begin(), payoff.end(), 0.0);

        // Average then discount
        return (sum / double(NSIM)) * exp(-opt.getR() * opt.getT());
    }

    // Simulates a path when price() is called
    void MonteCarlo::pathSim(const Option& opt) const
    {       
        // Randomness for GBM term
        boost::random::lagged_fibonacci607 rng(std::random_device{}());
        boost::random::normal_distribution<double> normal(0.0, 1.0);

        // Sample path for visualization
        std::vector<std::vector<double>> sample_path_temp;
        std::vector<double> path_temp;
        sample_path_temp.reserve(100);
        path_temp.reserve(NT);

        // Payoff vector to be returned
        std::vector<double> result;
        result.reserve(NSIM);

        // Create range and mesh in that range
        Range<double> range(0.0, opt.getT());
        std::vector<double> x = range.mesh(NT);

        // Time step
        double k = opt.getT() / double(NT);
        double sqrk = sqrt(k);

        double dW, VNew, VOld;      // dW is GBM, VNew is X_n+1, VOld is X_n

        // Main loop
        for (long i = 0; i < NSIM; ++i)
        {
            VOld = opt.getS();

            // Clear and add new path to path_temp
            path_temp.clear();

            if (i < 100)
            {
                path_temp.push_back(VOld);
            }
            for (unsigned long index = 1; index < x.size(); ++ index)
            {
                dW = normal(rng);

                // Explicit Euler
                VNew = VOld + (k * (opt.getR() * VOld))
                            + (sqrk * opt.getSig() * VOld * dW);

                VOld = VNew;

                // Add each new value to the path_temp vector
                if (i < 100)
                {
                    path_temp.push_back(VNew);
                }
            }

            // Add the path_temp to the sample_path_temp vector
            if (i < 100)
            {
                sample_path_temp.push_back(path_temp);
            }

            result.push_back(opt.PayOff(VNew));
        }

        sample_path = std::move(sample_path_temp);
        payoffs = std::move(result);
    }

    double MonteCarlo::standDev(const Option& opt) const
    {   
        const std::vector<double>& payoff = payoffs.value();

        double M = payoff.size();
        double sum = std::accumulate(payoff.begin(), payoff.end(), 0.0);
        double square_sum = std::inner_product(payoff.begin(), payoff.end(), payoff.begin(),  0.0);

        double sd = sqrt(((square_sum) - (1 / M) * (sum * sum)) / (M - 1)) * exp(-opt.getR() * opt.getT());
        current_sd = sd;
        return sd;
    }

    double MonteCarlo::standErr(const Option& opt) const
    {
        if (current_sd == std::nullopt)
        {
            this -> standDev(opt);
        }
        else
        {
            current_sd = this -> standDev(opt);
        }
        const std::vector<double>& payoff = payoffs.value();
        double M = payoff.size();

        double se = current_sd.value() / sqrt(M);
        current_se = se;

        return se;
    }


}   // namespace Jason::Finance