//  Header file containing declarations for global functions used for options
//
//  Includes:
//  - Normal cdf and pdf
//  - put-call parity
//  - mesh generator
//  - Price/Greek sensitivity analysis

#ifndef OPTIONGLOBALFUNCTIONS_HPP
#define OPTIONGLOBALFUNCTIONS_HPP

#include <cmath>
#include <boost/math/distributions/normal.hpp>  // For normal distribution
#include "EuropeanCallOption.hpp"               // For Call options
#include "EuropeanPutOption.hpp"                // For Put options
#include <vector>                               // For vectors


namespace Jason
{
    namespace Finance
    {
        ////////////////////////////////////////// NORMAL CDF/PDF //////////////////////////////////////////
        double N(double x);     // Returns CDF
        double n(double x);     // Returns PDF

        ////////////////////////////////////////// Put-Call Parity /////////////////////////////////////////
        double PutfromCall(const EuropeanCallOption& call);     // Computes put price from call
        double CallfromPut(const EuropeanPutOption& put);       // Computes call price from put

        // Returns True/False if put/call prices satisfies parity based on tolerance (default 1e-4)
        bool ParityCheck(const EuropeanCallOption& call, const EuropeanPutOption& put, double tol = 1e-4);

        ///////////////////////////////////////// Sensitivity Analysis /////////////////////////////////////
        std::vector<double> mesh(double start, double end, double h);       // Computes mesh

        // Computes S given a mesh (for part c specifically)
        std::vector<double> PriceOverS(Option& option, const std::vector<double>& mesh);         
        
        // Updated version of PriceOverParam
        // Updated to be QuantityOverParam to accomdate the greeks
        // Pass option, mesh, setter, getter, and also desired quantity to be computed (default to price)
        // Note: to use greeks, one must pass &EuropeanOption::greek() since greeks live in EuropeanOption class
        template <typename OptionType, typename ParamType>
        std::vector<double> QuantityOverParam(OptionType& option,
                                              const std::vector<double>& mesh,
                                              void (ParamType::*setter)(double), 
                                              double (ParamType::*getter)() const,
                                              double (OptionType::*quantity)() const = &OptionType::price);

        // Matrix version of QuantityOverParam
        // General version that handles parameters S, K, r, sig, b
        // Updated to output greeks as well as price, which is the default option
        // Updated to be template to handle reuse from other option types (eg EuropeanOptionMatrix)
        // Inputs: Option (American, or even European if not iterating over T)
        //         Labels to vary over (ex: {"S", "K", "r"}) 
        //         Meshes per label to iterate over (this is where matrix inputs)
        //         Pass through quantity to be computed for price pass &Option::greek() (defaults to price)

        // optionMatrix will work for European Options when NOT using Euro Option specific features (greeks or iterate over T)
        template <typename OptionType>
        std::vector<std::vector<double> > OptionMatrix(OptionType& option,
                                                       const std::vector<std::string>& labels,
                                                       const std::vector<std::vector<double> >& meshes,
                                                       double (OptionType::*quantity)() const = &OptionType::price);


        // Specialized OptionMatrix for EuropeanOptions
        // Used for European Option specific functions (greeks and iterating over T)
        // Updated to be template function to handle greeks (quick reason: EuropeanOption pointer does not
        // automatically convert to a derived class pointer)
        template <typename OptionType>
        std::vector<std::vector<double> > EuropeanOptionMatrix(OptionType& option,
                                                               const std::vector<std::string>& labels,
                                                               const std::vector<std::vector<double> >& meshes,
                                                               double (OptionType::*quantity)() const = &OptionType::price);


        // priceMatrix utility function to print
        void printMatrix(const std::vector<std::string>& labels, 
                         const std::vector<std::vector<double> >& priceMatrix);
        


    }   // namespace Finance
}   // namespace Jason


#endif // OPTIONGLOBALFUNCTION_HPP


/*

    // Some retired code that has been since updated 

    // General version of PriceOver(Param)
    template <typename OptionType, typename ParamType>
    std::vector<double> PriceOverParam(OptionType& option, 
                                        const std::vector<double>& mesh,
                                        void (ParamType::*setter)(double),
                                        double (ParamType::*getter)() const);

    // Matrix version of PriceOver
    // General Version that handles parameters S, K, r, sig, b
    // Inputs: Option (Any general option)
    //         Labels ({"S", "K", "r"}) to vary over
    //         Meshs per label to iterate over
    std::vector<std::vector<double> > priceMatrix(Option& option, 
                                                    const std::vector<std::string>& labels,
                                                    const std::vector<std::vector<double> >& meshes);

    // EuropeanOptions version that handles parameters S, K, r, sig, b, and T
    // Inputs: same as above
    std::vector<std::vector<double> > priceMatrixEuropean(EuropeanOption& option, 
                                            const std::vector<std::string>& labels,
                                            const std::vector<std::vector<double> >& meshes);

*/