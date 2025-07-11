#include <iostream>
#include <vector>
#include <cmath>


double covariance(const std::vector<double>& x, 
                const std::vector<double>& y) 
{
    double meanX = 0;
    double meanY = 0;
    double sigmaXY = 0;
    int n = x.size();

    // Compute sums
    for (int i = 0; i < n; ++i) {
        meanX += x[i]/n;
        meanY += y[i]/n;
    }
     
    std::cout << "mean X: " << meanX << std::endl;
    std::cout << "mean Y: " << meanY << std::endl;

    for (int i = 0; i < n; ++i) {
        // sigmaXY += (y[i]-meanY)*(x[i]-meanX) ;
        sigmaXY += (x[i]- meanX)*(y[i]- meanY);
        std::cout << "Xi: " << x[i] << " | (Xi-meanX): " << x[i]- meanX << " | Yi: " << y[i] << " | (Yi-meanY): " << y[i]- meanY << " | (Xi-meanX)(Yi-meanY): " << (x[i]- meanX)*(y[i]- meanY) << std::endl;
    }
    std::cout << "SUM (Xi-meanX)(Yi-meanY): " << sigmaXY << std::endl;

    sigmaXY = sigmaXY/(n-1);

    std::cout << "Covariance sigmaXY: " << sigmaXY << std::endl;

    return sigmaXY;
}

double standardDeviation(const std::vector<double>& x) 
{
    double meanX = 0;
    double sigmaX = 0;
    int n = x.size();

    // Compute sums
    for (int i = 0; i < n; ++i) {
        meanX += x[i]/n;
    }

    for (int i = 0; i < n; ++i) {
        sigmaX += pow((x[i]-meanX),2) ;
    }
    std::cout << "SUM (Xi-meanX)^2: " << sigmaX << std::endl;
    sigmaX = sigmaX/(n-1);
    sigmaX = pow(sigmaX,0.5);

    std::cout << "Standard Deviation: " << sigmaX << std::endl;

    return sigmaX;
}

double angularCoefficient(double sigmaXY, double sigmaX) 
{
    double a = 0;
    
    a = sigmaXY/pow(sigmaX,2);
    
    std::cout << "Angular Coefficient: " << a << "  J.s" <<  std::endl;

    return a;
}



int rel4_efeito_fotoeletrico() {
    
    double electronCharge =1.60218e-19;

    // Anderson e Pedro
    // std::vector<double> x = {5.19E+14,5.49E+14,6.88E+14,7.41E+14,8.22E+14};
    // std::vector<double> y = {0.649, 0.810, 1.458, 1.530, 1.958};

    // Agatha, Samuel e Thayna
    // std::vector<double> x = {5.19E+14,5.49E+14,6.88E+14,7.41E+14,8.22E+14};
    // std::vector<double> y = {0.718,0.785,1.347,1.507,1.783};

    // Jiayi, Sara e Vitor
    // std::vector<double> x = {5.19E+14,5.49E+14,6.88E+14,7.41E+14,8.22E+14};
    // std::vector<double> y = {0.619, 0.761, 1.377, 1.503, 1.842 };

    // Carlos e Nathalia
    std::vector<double> x = {5.19E+14,5.49E+14,6.88E+14,7.41E+14,8.22E+14};
    std::vector<double> y = {0.495, 0.574, 1.336, 0.733, 0.906 };
    // std::vector<double> y = {0,537,0,638,1,345,0,785,0,934 }; // Primeira medidad deles




    int n = x.size();


    std::cout << "------------- DATA --------------------------: " << std::endl;
    std::cout << "nu(frequency)  : ";
    for (int i = 0; i < n; ++i) {
        std::cout  << x[i] << "  ";
    }
    std::cout << "[Hz]" << std::endl;
    std::cout << "nu/e          X: ";
    for (int i = 0; i < n; ++i) {
        std::cout  << x[i]/electronCharge << "  " ;
        x[i] = x[i]/electronCharge; // Update the vector value (nu/e)
    }
    std::cout << "[C-1.s-1 ]" << std::endl;
    std::cout << "V             Y: ";
    for (int i = 0; i < n; ++i) {
        std::cout <<  y[i] << "  " ;
    }
    std::cout << "[Volts]" << std::endl;
    std::cout << "----------------------------------------: " << std::endl;


    double sigmaXY = covariance(x,y);
    double sigmaX = standardDeviation(x);

    double a = angularCoefficient(sigmaXY, sigmaX);

    double meanX = 0;
    double meanY = 0;
    for (int i = 0; i < n; ++i) {
        meanX += x[i]/n;
        meanY += y[i]/n;
    }

    // -------------------------------------------------
    //  epsilonY
    // -------------------------------------------------

    double b = meanY - a*meanX;
    std::cout << "b: " <<  b  << " Volts" << std::endl;
    std::cout << "----------------------------------------: " << std::endl;
    // double a, b;
    // leastSquaresFit(x, y, a, b);

    double epsilonY = 0; // 
    for (int i = 0; i < n; ++i) {
        epsilonY += pow( (y[i]-(a*x[i]+b) ) ,2);
        std::cout << "y[i]: " << y[i] << " | prevision: " <<  (a*x[i]+b) << " | resíduo: " << y[i]-(a*x[i]+b) << std::endl;
    }
    epsilonY = epsilonY/(n-2);
    epsilonY = pow(epsilonY,0.5);

    std::cout << "epsilonY: " <<  epsilonY  << std::endl;
    std::cout << "----------------------------------------: " << std::endl;

    // -------------------------------------------------
    //  SIGMA a and SIGMA b
    // -------------------------------------------------
    double sigmaA = epsilonY/(sigmaX*pow(n,0.5)); // 
    std::cout << "sigmaA: " <<  sigmaA  << std::endl;
    std::cout << "----------------------------------------: " << std::endl;

    double meanX2 = 0;
    for (int i = 0; i < n; ++i) {
        meanX2 += pow(x[i],2)/n;
        // std::cout << "meanX2: " <<  meanX2  << std::endl;
    }
    std::cout << "meanX2: " <<  meanX2  << std::endl;
    std::cout << "----------------------------------------: " << std::endl;

    double sigmaB = sigmaA*pow(meanX2,0.5);

    std::cout << "sigmaB: " <<  sigmaB  << std::endl;
    std::cout << "----------------------------------------: " << std::endl;

    double jToEv = 6.242e18; // Scale factor "J" to "eV"
    double h =  a*jToEv; // "eV.s"
    double sigmaH =  sigmaA*jToEv; // "eV.s"

    std::cout << "h   = " <<  a << " +- " << sigmaA << " J.s" << std::endl;
    std::cout << "or (applying scalefactor " << jToEv << " ""J"" to ""eV"" )" << std::endl;
    // std::cout << "h   = " <<  a*jToEv << " +- " << sigmaA*jToEv << " eV.s\n" << std::endl;
    std::cout << "h   = " <<  h  << " +- " << sigmaH << " eV.s\n" << std::endl;


    std::cout << "phi = " <<  b << " +- " << sigmaB << " Volts" << std::endl;
    std::cout << "----------------------------------------: " << std::endl;

    // -------------------------------------------------
    //  epsilon (erro relativo)
    // -------------------------------------------------
    double hRef = 4.135e-15; // eV.s   Planck Constant

    double epsilon = sigmaH/abs(h);
    std::cout << "epsilon (erro relativo)= " <<  epsilon << " | " << epsilon*100 << " %" << std::endl;
    std::cout << "----------------------------------------: " << std::endl;


    // double epsilon = abs(h-hRef)/hRef;
    // std::cout << "epsilon = " <<  epsilon << " | " << epsilon*100 << " %" << std::endl;

    // -------------------------------------------------
    //  Compatibilidade
    // -------------------------------------------------

    double compatibility = abs(h-hRef)/(sigmaH);
    std::string strDis = "";
    if (compatibility < 2.){
        strDis = " < 2";
    }
    else{
        strDis = " > 2";
    }
    std::cout << "compatibility (z)= " <<  compatibility << strDis << std::endl;
    std::cout << "----------------------------------------: " << std::endl;


    // -------------------------------------------------
    //  discrepancy
    // -------------------------------------------------
    double discrepancy = abs(h-hRef)/(2*sigmaH);
    if (discrepancy < 1.){
        strDis = " < 1";
    }
    else{
        strDis = " > 1";
    }
    std::cout << "discrepancy = " << discrepancy << strDis << std::endl;
    std::cout << "----------------------------------------: " << std::endl;



    // std::cout << "Fitted line: y = " << a << "x + " << b << std::endl;
    return 0;
}