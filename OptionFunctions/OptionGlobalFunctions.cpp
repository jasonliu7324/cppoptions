//  Source file for Options global function
//
//
//
//

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