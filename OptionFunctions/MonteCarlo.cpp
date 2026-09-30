//  Source file for MonteCarlo pricing class
//
//
// 
//  9/29: Implemented pathSim
//  9/30: Implemented price/SD/SE
//  To do: improve SD/SE (maybe update with private member data so no need for multiple calls)

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


namespace Jason::Finance
{
    // Constructor implementations
    MonteCarlo::MonteCarlo() : PricingMethod() , NSIM(0), NT(0), current_mesh(std::nullopt) {};
    MonteCarlo::MonteCarlo(double NSIM, double NT) : PricingMethod(), NSIM(NSIM), NT(NT), current_mesh(std::nullopt) {};
    MonteCarlo::MonteCarlo(const MonteCarlo& source) : PricingMethod(source), NSIM(source.NSIM), NT(source.NT), current_mesh(std::nullopt) {};

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
        current_mesh = std::nullopt;

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
        if (!isAvailable)
        {
            return std::nullopt;
        }

        // Call pathSim
        this -> pathSim(opt);
        std::vector<double>& payoffs = current_mesh.value();
        
        // Sum the payoffs
        double sum = std::accumulate(payoffs.begin(), payoffs.end(), 0.0);

        // Average then discount
        return (sum / double(NSIM)) * exp(-opt.getR() * opt.getT());
    }

    // Simulates a path when price() is called
    void MonteCarlo::pathSim(const Option& opt) const
    {       
        // Randomness for GBM term
        boost::random::lagged_fibonacci607 rng(std::random_device{}());
        boost::random::normal_distribution<double> normal(0.0, 1.0);


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
            for (unsigned long index = 1; index < x.size(); ++ index)
            {
                dW = normal(rng);

                // Explicit Euler
                VNew = VOld + (k * (opt.getR() * VOld))
                            + (sqrk * opt.getSig() * VOld * dW);

                VOld = VNew;
            }

            result.push_back(opt.PayOff(VNew));
        }

        current_mesh = std::move(result);
    }

    double MonteCarlo::standDev(const Option& opt) const
    {   
        std::vector<double>& payoffs = current_mesh.value();

        double M = payoffs.size();
        double sum = std::accumulate(payoffs.begin(), payoffs.end(), 0.0);
        double square_sum = std::inner_product(payoffs.begin(), payoffs.end(), payoffs.begin(),  0.0);

        return (sqrt((square_sum) - (1 / M) * (sum * sum)) / (M - 1) * exp(-opt.getR() * opt.getT()));

    }

    double MonteCarlo::standErr(const Option& opt) const
    {
        double sd = this -> standDev(opt);
        double M = current_mesh.value().size();

        return sd / sqrt(M);
    }

}   // namespace Jason::Finance