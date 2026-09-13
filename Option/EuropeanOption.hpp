//  Header file for base European option class
//
//  Derived from Option Abstract base class
//
//  Adds T (time to expiry), d1(), and d2(), two parameters for price function

#ifndef EUROPEANOPTION_HPP
#define EUROPEANOPTION_HPP

#include "Option.hpp"

namespace Jason
{
    namespace Finance
    {
        class EuropeanOption : public Option
        {
            private:
                double T;   // Time to expiry

            // Protected because only derived classes require it; not for public
            protected:
                double d1() const;
                double d2() const;

            public:
                EuropeanOption();                                   // Default constructor
                EuropeanOption(const double new_S,                  // Specific constructor
                               const double new_K,
                               const double new_r,
                               const double new_sig,
                               const double new_b,
                               const double new_T);
                EuropeanOption(const EuropeanOption& source);       // Copy constructor
                    
                virtual ~EuropeanOption();                          // Default Destructor

                double getT() const {return T;}                     // Getter for T
                void setT(double new_T);                            // Setter for T

                EuropeanOption& operator = (const EuropeanOption& source);      // Assignment operator

                virtual double delta() const = 0;           
                virtual double deltaApprox(double h) = 0;
                
                double gamma() const;                 // Gamma of option (same for both call and put) 
                double gammaApprox(double h);         // Gamma via 3-point order approximation

                bool hasClosedForm() const; 
                bool isPerpetual() const;
        };
    }   // namespace Finance
}   // namespace Jason

#endif // EUROPEANOPTION_HPP