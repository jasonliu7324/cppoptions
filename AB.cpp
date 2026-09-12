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
#include "OptionGlobalFunctions.cpp"

#include <iostream>
#include <vector>

using namespace Jason::Finance;

int main()
{
    EuropeanPutOption FinalPutOption(102, 122, 0.045, 0.43, 0.0, 1.65);
    std::cout << "Put Price: " << FinalPutOption.price() << std::endl;
    std::cout << "Put Delta: " << FinalPutOption.delta() << std::endl;
    std::cout << "Put Gamma: " << FinalPutOption.gamma() << std::endl;
    /*
    //////////////////////////////////////////// SECTION A1 ////////////////////////////////////////////
    ////////////////////// A //////////////////////
    EuropeanCallOption Batch1c(60.0, 65.0, 0.08, 0.30, 0.08, 0.25);
    std::cout << "Call Price Batch1: " << Batch1c.price() << std::endl;
    EuropeanCallOption Batch2c(100.0, 100.0, 0.0, 0.2, 0.0, 1.0);
    std::cout << "Call Price Batch2: " << Batch2c.price() << std::endl;
    EuropeanCallOption Batch3c(5.0, 10.0, 0.12, 0.5, 0.12, 1.0);
    std::cout << "Call Price Batch3: " << Batch3c.price() << std::endl;
    EuropeanCallOption Batch4c(100.0, 100.0, 0.08, 0.3, 0.08, 30.0);
    std::cout << "Call Price Batch4: " << Batch4c.price() << std::endl;

    std::cout << "//////////////////////////////////////////////////////////////////" << std::endl;

    EuropeanPutOption Batch1p(60.0, 65.0, 0.08, 0.30, 0.08, 0.25);
    std::cout << "Put Price Batch1: " << Batch1p.price() << std::endl;
    EuropeanPutOption Batch2p(100.0, 100.0, 0.0, 0.2, 0.0, 1.0);
    std::cout << "Put Price Batch2: " << Batch2p.price() << std::endl;
    EuropeanPutOption Batch3p(5.0, 10.0, 0.12, 0.5, 0.12, 1.0);
    std::cout << "Put Price Batch3: " << Batch3p.price() << std::endl;
    EuropeanPutOption Batch4p(100.0, 100.0, 0.08, 0.3, 0.08, 30.0);
    std::cout << "Put Price Batch4: " << Batch4p.price() << std::endl;

    std::cout << "//////////////////////////////////////////////////////////////////" << std::endl;

    ////////////////////// B //////////////////////

    // Testing put-call parity

    std::cout << "Put from Call Batch1: " << PutfromCall(Batch1c) << std::endl;
    std::cout << "Put from Call Batch2: " << PutfromCall(Batch2c) << std::endl;
    std::cout << "Put from Call Batch3: " << PutfromCall(Batch3c) << std::endl;
    std::cout << "Put from Call Batch4: " << PutfromCall(Batch4c) << std::endl;

    std::cout << "//////////////////////////////////////////////////////////////////" << std::endl;

    std::cout << "Call from Put Batch1: " << CallfromPut(Batch1p) << std::endl;
    std::cout << "Call from Put Batch2: " << CallfromPut(Batch2p) << std::endl;
    std::cout << "Call from Put Batch3: " << CallfromPut(Batch3p) << std::endl;
    std::cout << "Call from Put Batch4: " << CallfromPut(Batch4p) << std::endl;

    std::cout << "//////////////////////////////////////////////////////////////////" << std::endl;

    // 0 False, 1 True
    
    std::cout << "Batch1 satisfies parity: " << ParityCheck(Batch1c, Batch1p) << std::endl;
    std::cout << "Batch2 satisfies parity: " << ParityCheck(Batch2c, Batch2p) << std::endl;
    std::cout << "Batch3 satisfies parity: " << ParityCheck(Batch3c, Batch3p) << std::endl;
    std::cout << "Batch4 satisfies parity: " << ParityCheck(Batch4c, Batch4p) << std::endl;

    std::cout << "//////////////////////////////////////////////////////////////////" << std::endl;

    ////////////////////// C //////////////////////

    std::vector<double> SMesh = mesh(50, 70, 1);                 // S = 50, 51, ..., 70
    std::vector<double> priceS1 = PriceOverS(Batch1c, SMesh);    // Price over S
    
    // Quick check
    for (double v : priceS1)
    {
        std::cout << v << " ";
    }

    std::cout << "\n";
    std::cout << "//////////////////////////////////////////////////////////////////" << std::endl;


    ////////////////////// D //////////////////////
    std::vector<double> TMesh = mesh(0.5, 2.5, 0.1);        // T = 0.5, 0.6, ..., 2.5
    std::vector<double> KMesh = mesh(60, 80, 1);            // K = 60, 61, ..., 80
    std::vector<double> SigMesh = mesh(0.3, 0.5, 0.01);     // sig = 0.30, 0.31, ..., 0.50

    // Combine meshes into matrix
    std::vector<std::vector<double> > meshes1{SMesh, KMesh, SigMesh, TMesh};    
    
    // Labels vector
    std::vector<std::string> labels1{"S", "K", "sig", "T"};   

    std::vector<std::vector<double> > priceOverSKsigT = EuropeanOptionMatrix(Batch1c, labels1, meshes1);
    printMatrix(labels1, priceOverSKsigT);

    //////////////////////////////////////////// SECTION A2 ////////////////////////////////////////////
    ////////////////////// A //////////////////////
    EuropeanCallOption Batch5c(105.0, 100.0, 0.1, 0.36, 0.0, 0.5);
    EuropeanPutOption Batch5p(105.0, 100.0, 0.1, 0.36, 0.0, 0.5);

    std::cout << "Delta call Batch5c: " << Batch5c.delta() << std::endl;
    std::cout << "Delta put Batch5p: " << Batch5p.delta() << std::endl;
    std::cout << "Gamma call Batch5c: " << Batch5c.gamma() << std::endl;        // Should be same as put
    std::cout << "Gamma put Batch5p: " << Batch5p.gamma() << std::endl;

    std::cout << "//////////////////////////////////////////////////////////////////" << std::endl;

    ////////////////////// B //////////////////////
    std::vector<double> SMesh2 = mesh(95, 115, 1);
    std::vector<double> deltaS = QuantityOverParam(Batch5c, SMesh2, &Option::setS, 
                                                   &Option::getS, &EuropeanCallOption::delta);

    for (double v : deltaS)
    {
        std::cout << v << " ";
    }

    std::cout << "\n";
    std::cout << "//////////////////////////////////////////////////////////////////" << std::endl;

    ////////////////////// C //////////////////////
    
    // In this first test case we compute the delta for Batch5c
    std::vector<std::string> labels2{"S", "K", "sig", "T"};
    std::vector<std::vector<double> > meshes2{SMesh2, KMesh, SigMesh, TMesh};

    // EuropeanOptionMatrix for delta
    std::vector<std::vector<double> > deltaOverSKsigT = EuropeanOptionMatrix(Batch5c, labels2, meshes2, 
                                                                             &EuropeanCallOption::delta);

    printMatrix(labels2, deltaOverSKsigT);

    std::cout << "//////////////////////////////////////////////////////////////////" << std::endl;

    // EuropeanOptionMatrix for gamma
    std::vector<std::vector<double> > gammaOverSKsigT = EuropeanOptionMatrix<EuropeanOption>(Batch5c, labels2, meshes2, 
                                                                             &EuropeanOption::gamma);

    /*
    
        We have to force deduction to euro option above since gamma lives in eurooption but template deduces 
        the option to be the derived class member, EuroCallOption

        main problem here: member pointer to functions dont convert the same way references do

        // Note: because pointer-to-member types don't convert between base and 
        // derived classes, quantity's declaring class must exactly match OptionType:
        //   - price()  -> declared on Option, works via &Option::price or &Leaf::price
        //   - delta()  -> declared per-leaf -> pass &EuropeanCallOption::delta / &EuropeanPutOption::delta,
        //                 letting OptionType deduce naturally from the object
        //   - gamma()  -> declared only on EuropeanOption -> pass &EuropeanOption::gamma
        //                 with an explicit EuropeanOptionMatrix<EuropeanOption>(...) to pin OptionType

    */
    
    /*
    printMatrix(labels2, gammaOverSKsigT);

    std::cout << "//////////////////////////////////////////////////////////////////" << std::endl;


    ////////////////////// D //////////////////////

    // Tesing approximations for Gamma and Delta
    // Observing h^2 convergence
    std::vector<double> hValues = {1.0, 0.5, 0.25, 0.125, 0.0625, 0.03125, 0.015625};                 

    // Delta approximations
    for (double h : hValues)
    {
        std::cout << Batch5c.deltaApprox(h) << " ";
    }

    std::cout << "\n";

    std::cout << "//////////////////////////////////////////////////////////////////" << std::endl;

    // Gamma approximations
    for (double h : hValues)
    {
        std::cout << Batch5c.gammaApprox(h) << " ";
    }

    // For O(h^2) we observe that err(h)/err(h/2) = 4 approximately

    std::cout << "\n";
    std::cout << "//////////////////////////////////////////////////////////////////" << std::endl;

    //////////////////////////////////////////// SECTION B2 ////////////////////////////////////////////
    ////////////////////// B //////////////////////

    AmericanPerpetualCallOption Batch6c(110.0, 100.0, 0.1, 0.1, 0.02);
    AmericanPerpetualPutOption Batch6p(110.0, 100.0, 0.1, 0.1, 0.02);

    // American put and call prices for new data
    std::cout << "Call price Batch6: " << Batch6c.price() << std::endl;
    std::cout << "Put price Batch6: " << Batch6p.price() << std::endl;

    std::cout << "//////////////////////////////////////////////////////////////////" << std::endl;

    ////////////////////// C //////////////////////
    std::vector<double> SMesh3 = mesh(100, 120, 1);          // S = 100, 101, ..., 120
    std::vector<double> Batch6cOverS = PriceOverS(Batch6c, SMesh3);
    std::vector<double> Batch6pOverS = PriceOverS(Batch6p, SMesh3);

    for (double v : Batch6cOverS)
    {
        std::cout << v << " ";
    }

    std::cout << "\n";

    for (double v : Batch6pOverS)
    {
        std::cout << v << " ";
    }

    std::cout << "\n";
    std::cout << "//////////////////////////////////////////////////////////////////" << std::endl;

    ////////////////////// D //////////////////////

    // Matrix pricer
    // Note that OptionMatrix works with perpetual American options
    std::vector<std::string> labels3{"S", "K", "sig"};
    std::vector<std::vector<double> > meshes3{SMesh3, KMesh, SigMesh};

    std::vector<std::vector<double> > Batch6cPriceOverSKSig = OptionMatrix(Batch6c, labels3, meshes3);

    printMatrix(labels3, Batch6cPriceOverSKSig);

    */
}