//  Main C++ file to run the functionatilities of One-Factor Plain Euro Option classes 
//
//  A general idea of the design philosopy for the Euro options (more in docs):
//  OptionsABC is abstract base class -> EuroBase -> EuroCall/EuroPut
//  

/*
    Compile copy paste
    g++ AB.cpp EuropeanCallOption.cpp EuropeanOption.cpp EuropeanPutOption.cpp Option.cpp AmericanPerpetualCallOption.cpp AmericanPerpetualPutOption.cpp -o main
*/

// Option functionality
#include "Option.hpp"
#include "EuropeanOption.hpp"
#include "EuropeanCallOption.hpp"
#include "EuropeanPutOption.hpp"
#include "AmericanPerpetualCallOption.hpp"
#include "AmericanPerpetualPutOption.hpp"
#include "OptionGlobalFunctions.hpp"
#include "PricingMethod.hpp"
#include "ExactPrice.hpp"
#include "MonteCarlo.hpp"
#include "UtilityFunctions.hpp"

#include <iostream>
#include <vector>

using namespace Jason::Finance;

int main()
{
    EuropeanCallOption call1(65.0, 60, 0.08, 0.3, 0.08, 1);
    ExactPrice exact; 
    MonteCarlo mc1(500000, 300);

    std::cout << *exact.price(call1) << std::endl;
    std::cout << *mc1.price(call1) << std::endl;
    std::vector<std::vector<double>> sample_path = mc1.getSamplePath();
    std::cout << sample_path.size() << std::endl;
    std::cout << sample_path[0].size() << std::endl;
    std::cout << sample_path[1].size() << std::endl;
    std::cout << sample_path[50].size() << std::endl;


    return 0;
}