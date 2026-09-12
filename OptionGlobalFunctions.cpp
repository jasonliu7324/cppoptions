//  Source file for Options global function
//
//
//
//

#ifndef OPTIONGLOBALFUNCTIONS_CPP
#define OPTIONGLOBALFUNCTIONS_CPP

#include "OptionGlobalFunctions.hpp"
#include <stdexcept>
#include <vector>
#include <iostream>

namespace Jason
{
    namespace Finance
    {
        ////////////////////////////////////////// NORMAL CDF/PDF //////////////////////////////////////////
        // Normal cdf
        double N(double x)
        {
            boost::math::normal_distribution<> mySDNormal(0.0, 1.0);    // Standard Normal
            return cdf(mySDNormal, x);                                  // Returns CDF
        }

        // Normal pdf
        double n(double x)
        {
            boost::math::normal_distribution<> mySDNormal(0.0, 1.0);    // Standard normal
            return pdf(mySDNormal, x);                                  // Returns PDF
        }

        ////////////////////////////////////////// Put-Call Parity /////////////////////////////////////////
        double PutfromCall(const EuropeanCallOption& call)
        {
            // P = C + Ke^{-rT} - S
            return call.price() + call.getK() * std::exp(-1.0 * call.getR() * call.getT()) - call.getS();
        }

        double CallfromPut(const EuropeanPutOption& put)
        {
            // C = P + S - Ke^{-rT}
            return put.price() + put.getS() - put.getK() * std::exp(-1.0 * put.getR() * put.getT());
        }

        bool ParityCheck(const EuropeanCallOption& call, const EuropeanPutOption& put, double tol)
        {
            // Same asset check, need S, K, r, T to all be the same, otherwise throw error
            if (call.getS() != put.getS() || call.getK() != put.getK() || call.getR() != put.getR() || call.getT() != put.getT())
                {
                    throw std::invalid_argument("S, K, r, T must all be the same for both assets");
                }
            
            // Two sides of put call parity equation
            double lhs = call.price() + call.getK() * std::exp(-1.0 * call.getR() * call.getT());
            double rhs = put.price() + put.getS();

            return std::abs(lhs - rhs) < tol;   
        }

        ////////////////////////////////////// Sensitivity Analysis //////////////////////////////////////

        // Simple mesh generator with step size h
        std::vector<double> mesh(double start, double end, double h)
        {   
            std::vector<double> m;  // Mesh that we return

            // Total number of steps to take based on h (rounding to prevent errors)
            int steps = static_cast<int>(std::round((end - start) / h));

            // Increment each step
            for (int i = 0; i <= steps; ++i)
            {
                m.push_back(start + i * h);
            }

            return m;
        }

        // Simple sensitivity output based on varying S
        std::vector<double> PriceOverS(Option& option, const std::vector<double>& mesh)
        {
            std::vector<double> price;      // Price vector that we return

            // Capture original
            double original = option.getS();

            // Iterate through elements of mesh, which are different underlying S
            for (auto it = mesh.begin(); it != mesh.end(); ++it)
            {
                // Update option with new S at each increment
                option.setS(*it);

                // Price option at each increment
                price.push_back(option.price());
            }

            // Reset to original
            option.setS(original);

            return price;
        }

        // Generalized sensitivity output based on varying parameter
        // To set parameter, pass appropriate setter and getter (latter necessary for resetting to original
        // For example, if we vary over S, pass &Option::setS, for T, we pass &EuropeanOption::setT since T exists only there.
        // In this updated version, we must also pass through the quantity we wish to compute
        // By default, it is the price, but if we want a greek instead, then pass &EuropeanOption::delta for instance.
        template<typename OptionType, typename ParamType>
        std::vector<double> QuantityOverParam(OptionType& option,
                                              const std::vector<double>& mesh,
                                              void (ParamType::*setter)(double),
                                              double (ParamType::*getter)() const,
                                              double (OptionType::*quantity)() const)
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

        // General sensitivity matrix for general option type
        template <typename OptionType>
        std::vector<std::vector<double> > OptionMatrix(OptionType& option, 
                                                       const std::vector<std::string>& labels, 
                                                       const std::vector<std::vector<double> >& meshes, 
                                                       double (OptionType::*quantity)() const)
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

        // Sensitivity matrix but for European options
        template <typename OptionType>
        std::vector<std::vector<double> > EuropeanOptionMatrix(OptionType& option,
                                                               const std::vector<std::string>& labels,  
                                                               const std::vector<std::vector<double> >& meshes,
                                                               double (OptionType::*quantity)() const)
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

        // priceMatrix printer
        void printMatrix(const std::vector<std::string>& labels, 
                         const std::vector<std::vector<double> >& OptionMatrix)
        {
            // Iterate through matrix
            for (int i = 0; i < OptionMatrix.size(); ++i)
            {
                // Print row label
                std::cout << labels[i] << ": ";

                // Iterate through row using range base for loop
                for (double v : OptionMatrix[i])
                    std::cout << v << " ";
                std::cout << "\n";
            }
        }
        
    }   // namespace Finance
}   // namespace Jason

#endif // OPTIONGLOBALFUNCTIONS_CPP

/*

    // Some retired code that has been since updated


    // Generalized sensitivty output based on varying parameter
    // To set the parameter, pass appropriate setter & getter functions (getter necessary to restore original)
    // For example, for S, we pass &Option::setS, for T, we pass &EuropeanOption::setT
    template <typename OptionType, typename ParamType>
    std::vector<double> PriceOverParam(OptionType& option,
                                        const std::vector<double>& mesh,
                                        void (ParamType::*setter)(double),
                                        double (ParamType::*getter)() const)
    {
        std::vector<double> price;      // Price vector that we return

        // Capture original
        double original = (option.*getter)();

        // Iterate through elements of the mesh, which are different for underlying ParamType  
        for (auto it = mesh.begin(); it != mesh.end(); ++it)
        {
            // Update option with new ParamType at each increment
            (option.*setter)(*it);

            // Price option at each increment
            price.push_back(option.price());
        }

        // Reset to original 
        (option.*setter)(original);

        return price;
    }

    // General Matrix Pricer
    // Note: Label must be in order "S", "K", "r", "sig", "b"!!!!! and "T" if using Euro version
    std::vector<std::vector<double> > OptionMatrix(Option& option,
                                                    const std::vector<std::string>& labels,
                                                    const std::vector<std::vector<double> >& meshes)
    {
        // Label length must match mesh length
        if (labels.size() != meshes.size())
            throw std::invalid_argument("Number of labels must match number of meshes");

        // Matrix to be returned
        std::vector<std::vector<double> > price;

        for (int i = 0; i < labels.size(); ++i)
        {
            const std::string& label = labels[i];           // Set the current parameter we iterate over
            const std::vector<double> row = meshes[i];      // Set parameter mesh

            // Compare the labels and call appropriate PriceOverParam function
            if (label == "S")
                price.push_back(PriceOverParam(option, row, &Option::setS, &Option::getS));
            else if (label == "K")
                price.push_back(PriceOverParam(option, row, &Option::setK, &Option::getK));
            else if (label == "r")
                price.push_back(PriceOverParam(option, row, &Option::setR, &Option::getR));
            else if (label == "sig")
                price.push_back(PriceOverParam(option, row, &Option::setSig, &Option::getSig));
            else if (label == "b")
                price.push_back(PriceOverParam(option, row, &Option::setB, &Option::getB));
            else
                // If label unknown, stop and throw error
                throw std::invalid_argument("Unknown label: " + label);
        }

        return price;
    }

    // European Matrix Pricer
    std::vector<std::vector<double> > EuropeanOptionMatrix(EuropeanOption& option, 
                                                            const std::vector<std::string>& labels,
                                                            const std::vector<std::vector<double> >& meshes)
    {
        // Label length must match mesh length
        if (labels.size() != meshes.size())
            throw std::invalid_argument("Number of labels must match number of meshes");
        
        // Matrix to be returned
        std::vector<std::vector<double> > price;

        for (int i = 0; i < labels.size(); ++i)
        {
            const std::string& label = labels[i];           // Set the current parameter we iterate over
            const std::vector<double> row = meshes[i];      // Set parameter mesh 

            // Same logic as the previous function
            if (label == "T")
                price.push_back(PriceOverParam(option, row, &EuropeanOption::setT, &EuropeanOption::getT));
            else
                // Instead of rewriting, ew may reuse the previous function
                // {label}, {row} is list initialization syntax for vector that contains 
                // a "label" and "row" temporarily
                // Call .front() pulls the first element of the matrix out (whcih is a vector)
                price.push_back((OptionMatrix(option, {label}, {row})).front());
        }

        return price;
    }

*/