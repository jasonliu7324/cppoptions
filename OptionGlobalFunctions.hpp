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
#include <string>                                // For labels
#include <stdexcept>                             // For invalid_argument


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
                                              double (OptionType::*quantity)() const = &OptionType::price)
        {
            std::vector<double> price;      // price vector that we return

            // Capture original
            double original = (option.*getter)();

            // Iterate through elements of the mesh, which differe for underlying ParamType
            for (auto it = mesh.begin(); it != mesh.end(); ++it)
            {
                // Update option with new ParamType at each increment
                (option.*setter)(*it);

                // Compute the quantity at each step
                // Done with the function pointer passed through
                price.push_back((option.*quantity)());      
            }

            // Reset to original 
            (option.*setter)(original);
            return price;
        }

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
                                                       double (OptionType::*quantity)() const = &OptionType::price)
        {
            // Label size must match number of meshes
            if (labels.size() != meshes.size())
                throw std::invalid_argument("Number of labels must match length of meshes");

            // Matrix to be returned
            std::vector<std::vector<double> > mat;

            // Iterate through the size of labels
            for (int i = 0; i < labels.size(); ++i)
            {
                const std::string& label = labels[i];           // Set the current parameter we iterate over
                const std::vector<double> row = meshes[i];      // Set parameter mesh

                // Compare the labels and call appropriate QuantityOverParam function
                if (label == "S")
                    mat.push_back(QuantityOverParam(option, row, &OptionType::setS, &OptionType::getS, quantity));
                else if (label == "K")  
                    mat.push_back(QuantityOverParam(option, row, &OptionType::setK, &OptionType::getK, quantity));
                else if (label == "r")
                    mat.push_back(QuantityOverParam(option, row, &OptionType::setR, &OptionType::getR, quantity));
                else if (label == "sig")
                    mat.push_back(QuantityOverParam(option, row, &OptionType::setSig, &OptionType::getSig, quantity));
                else if (label == "b")
                    mat.push_back(QuantityOverParam(option, row, &OptionType::setB, &OptionType::getB, quantity));
                else
                    // if label unknown, throw error
                    throw std::invalid_argument("Unknown label" + label);
            }

            return mat;
        }


        // Specialized OptionMatrix for EuropeanOptions
        // Used for European Option specific functions (greeks and iterating over T)
        // Updated to be template function to handle greeks (quick reason: EuropeanOption pointer does not
        // automatically convert to a derived class pointer)
        template <typename OptionType>
        std::vector<std::vector<double> > EuropeanOptionMatrix(OptionType& option,
                                                               const std::vector<std::string>& labels,
                                                               const std::vector<std::vector<double> >& meshes,
                                                               double (OptionType::*quantity)() const = &OptionType::price)
        {
            // Label size must match number of meshes
            if (labels.size() != meshes.size())
                throw std::invalid_argument("Number of labels must match length of meshes");
            
            // Matrix to be returned
            std::vector<std::vector<double> > mat;

            // Iterate through size of labels
            for (int i = 0; i < labels.size(); ++i)
            {
                const std::string& label = labels[i];           // Set current parameter we iterate over
                const std::vector<double> row = meshes[i];      // Set parameter mesh

                // Compare the labels and call appropriate function
                if (label == "T")
                    mat.push_back(QuantityOverParam(option, row, &EuropeanOption::setT, &EuropeanOption::getT, quantity));
                else
                    // Instead of rewriting, ew may reuse the previous function
                    // {label}, {row} is list initialization syntax for vector that contains 
                    // a "label" and "row" temporarily
                    // Call .front() pulls the first element of the matrix out (whcih is a vector)
                    mat.push_back((OptionMatrix(option, {label}, {row}, quantity)).front());
            }

            return mat;
        }


        // priceMatrix utility function to print
        void printMatrix(const std::vector<std::string>& labels, 
                         const std::vector<std::vector<double> >& priceMatrix);
        


    }   // namespace Finance
}   // namespace Jason


#endif // OPTIONGLOBALFUNCTION_HPP