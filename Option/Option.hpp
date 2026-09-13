// Header file for Options Abstract base class
//
// Holds S, K, r, sig, b
// 
//

#ifndef OPTION_HPP
#define OPTION_HPP

namespace Jason
{
    // New namespace "Finance" to avoid name collisions
    namespace Finance
    {
        class Option
        {
            private:
                double S;       // Underlying asset price
                double K;       // Strike price 
                double r;       // Risk-free IR
                double sig;     // Volatility
                double b;       // Cost of carry

            public:
                Option();                           // Default Constructor

                Option(const double new_S,          // Specific Constructor
                       const double new_K, 
                       const double new_r, 
                       const double new_sig, 
                       const double new_b);       

                Option(const Option& source);       // Copy Constructor
                virtual ~Option();                  // Default Destructor

                // Setters and Getters for member data
                // Inlined here for simplicity

                // S, K, Sig implemented in source for parameter check
                void setS(double new_S);
                void setK(double new_K);
                void setR(double new_r) {r = new_r;}
                void setSig(double new_sig);
                void setB(double new_b) {b = new_b;}

                double getS() const {return S;}
                double getK() const {return K;}
                double getR() const {return r;}
                double getSig() const {return sig;}
                double getB() const {return b;}

                Option& operator = (const Option& source);      // Assignment Operator 

                // PVMF price function
                // Will vary depending on derived class
                // E.g. EuroPutOption will have different Price() vs EuroCallOption
                virtual double price() const = 0;       // Polymorphic price function 
                virtual double PayOff() const = 0;      // Polymorphic payoff function
        };
    }   // namespace Finance
}   // namespace Jason

#endif  // OPTION_HPP

