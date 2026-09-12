// Source file for abstract base class
//
// 
//
//

#include "Option.hpp"
#include <stdexcept>    // Necessary for invalid_argument

namespace Jason
{
    namespace Finance
    {   
        // Default Constructor, sets all values to 0 
        Option::Option() : S(0), K(0), r(0), sig(0), b(0)
        {
        }
        
        // Specific Constructor
        Option::Option(const double new_S,
                       const double new_K,
                       const double new_r,
                       const double new_sig,
                       const double new_b)
        {
            setS(new_S);
            setK(new_K);
            setR(new_r);
            setSig(new_sig);
            setB(new_b);
        }

        // Copy Constructor
        Option::Option(const Option& source) : S(source.S), K(source.K), r(source.r), sig(source.sig), b(source.b)
        {
        }

        // Default Destructor
        Option::~Option()
        {
        }

        // Asset price setter
        void Option::setS(double new_S)
        {
            // Parameter validation
            if (new_S <= 0.0)
                throw std::invalid_argument("S must be greater than 0");
            
            S = new_S;
        }

        // Strike setter
        void Option::setK(double new_K)
        {
            // Parameter validation
            if (new_K <= 0.0)
                throw std::invalid_argument("K must be greater than 0");
            
            K = new_K;
        }
        
        // Volatility setter
        void Option::setSig(double new_sig)
        {
            // Parameter validation
            if (new_sig <= 0.0)
                throw std::invalid_argument("Volatility must be greater than 0");
            
            sig = new_sig;
        }


        // Assignment operator
        Option& Option::operator = (const Option& source)
        {
            // Same check
            if (this == &source)
            {
                return *this;
            }
            
            // Set new parameters
            S = source.S;
            K = source.K;
            r = source.r;
            sig = source.sig;
            b = source.b;

            return *this;
        }
    }   // namespace Finance
}   // namespace Jason