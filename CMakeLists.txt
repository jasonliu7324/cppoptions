cmake_minimum_required(VERSION 3.15)
project(OptionsPricingLibrary LANGUAGES CXX)
cmake_policy(SET CMP0167 NEW)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost REQUIRED)

add_executable(options_pricing

    maintest.cpp

    OptionFunctions/OptionGlobalFunctions.cpp
    OptionFunctions/MonteCarlo.cpp
    OptionFunctions/PricingMethod.cpp
    OptionFunctions/ExactPrice.cpp

    Option/Option.cpp
    Option/EuropeanOption.cpp
    Option/EuropeanCallOption.cpp
    Option/EuropeanPutOption.cpp
    Option/AmericanOption.cpp
    Option/AmericanPerpetualCallOption.cpp
    Option/AmericanPerpetualPutOption.cpp
    Option/AmericanCallOption.cpp
    Option/AmericanPutOption.cpp

)

target_include_directories(options_pricing PRIVATE ${Boost_INCLUDE_DIRS} Option OptionFunctions)

add_executable(testing

    maintest2.cpp

    OptionFunctions/OptionGlobalFunctions.cpp
    OptionFunctions/MonteCarlo.cpp
    OptionFunctions/PricingMethod.cpp
    OptionFunctions/ExactPrice.cpp

    Option/Option.cpp
    Option/EuropeanOption.cpp
    Option/EuropeanCallOption.cpp
    Option/EuropeanPutOption.cpp
    Option/AmericanOption.cpp
    Option/AmericanPerpetualCallOption.cpp
    Option/AmericanPerpetualPutOption.cpp
    Option/AmericanCallOption.cpp
    Option/AmericanPutOption.cpp
)

target_include_directories(testing PRIVATE ${Boost_INCLUDE_DIRS} Option OptionFunctions)