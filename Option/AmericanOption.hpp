//  Header file for American Option
//
//  Derived from Option
//
//  Essentially same structure as European class
//  
//  10/5: Implementation

#ifndef AMERICANOPTION_HPP
#define AMERICANOPTION_HPP

#include "Option.hpp"

namespace Jason::Finance
{
    class AmericanOption : public Option
    {
        private:
            double T;   // Time to expiry

        public:
            AmericanOption();                                       // Default constructor
            AmericanOption(const double new_S,                      // Specific constructor
                           const double new_K,
                           const double new_r,
                           const double new_sig,
                           const double new_b,
                           const double new_T);
            AmericanOption(const AmericanOption& source);           // Copy constructor

            virtual ~AmericanOption();                              // Default destructor

            double getT() const override {return T;};               // Getter for T
            void setT(double new_T) override {T = new_T;};          // Setter for T

            AmericanOption& operator = (const AmericanOption& source);      // Assignment operator

            bool hasClosedForm() const {return true;};
            bool isPerpetual() const {return false;};
    };

}   // namespace Jason::Finance

#endif // AMERICANOPTION_HPP

