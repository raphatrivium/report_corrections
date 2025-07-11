#include <iostream>
#include <vector>
#include <cmath>



int rel4_efeito_fotoeletricoV2() {

    double e = 1.60218e-19; // C

    // As definições de x,y e a odem mudar de acordo com a fórmula.
    int DefFlag = -1;
    // 0  x=V  , y=nu/e,  a=h   
    // 1  x=eV , y=nu  ,  a=h
    // 2  x=V  , y=nu  ,  a=h/e

    // std::vector<double> x = {5.19e14, 5.49e14, 6.88e14, 7.41e14, 8.22e14};
    // std::vector<double> y = {0.619, 0.761, 1.377, 1.503, 1.842 };


    // Agatha, Samuel e Thayna
    DefFlag = 2;
    std::vector<double> x = {5.19e14, 5.49e14, 6.88e14, 7.41e14, 8.22e14};
    std::vector<double> y = {0.718,0.785,1.347,1.507,1.783};
    
    


    int n = x.size();

    std::cout << "------------- Medidas Computadas --------------------------: " << std::endl;
    std::cout << "nu(frequency) X: ";
    for (int i = 0; i < n; ++i) {
        std::cout  << x[i] << "  ";
    }
    std::cout << "[Hz] [1/s]" << std::endl;
    std::cout << "V             Y: ";
    for (int i = 0; i < n; ++i) {
        std::cout <<  y[i] << "  " ;
    }
    std::cout << "[Volts] [J/C]\n" << std::endl;

    std::cout << "------------- Medidas a serem usadas --------------------------: " << std::endl;

    if ( DefFlag == 0){
        std::cout << "nu/e          X: ";
        for (int i = 0; i < n; ++i) {
            std::cout  << x[i]/e << "  " ;
            x[i] = x[i]/e; // Update the vector value (nu/e)
        }
        std::cout << "[C-1.s-1]" << std::endl;
        std::cout << "V             Y: ";
        for (int i = 0; i < n; ++i) {
            std::cout <<  y[i] << "  " ;
        }
        std::cout << "[Volts] [J/C]\n" << std::endl;
    }
    else if ( DefFlag == 1)
    {
        std::cout << "nu(frequency)  X: ";
        for (int i = 0; i < n; ++i) {
            std::cout  << x[i] << "  ";
        }
        std::cout << "[Hz] [1/s]" << std::endl;
        
        std::cout << "eV             Y: ";
        for (int i = 0; i < n; ++i) {
            std::cout <<  y[i]*e << "  " ; 
            y[i] = y[i]*e;  // Update the vector value (V*e)
        }
        std::cout << "[C.Volts] [J]" << std::endl;
    }
    else if ( DefFlag == 2)
    {
        std::cout << "----------------------------" << std::endl;
        std::cout << "Coefienciente angular a=h/e"  << std::endl;
        std::cout << "----------------------------" << std::endl;
    }
    
    std::cout << "----------------------------------------: " << std::endl;

    double meanX = 0;
    double meanY = 0;
    double meanXY = 0;
    double meanX2 = 0;
    double meanY2 = 0;

    // Compute sums
    for (int i = 0; i < n; ++i) {
        meanX += x[i]/n;
        meanY += y[i]/n;
        meanXY += (x[i]*y[i])/n;
        meanX2 += pow(x[i],2)/n;
        meanY2 += pow(y[i],2)/n;
    }

    std::cout << "média aritmética X : " << meanX << std::endl;
    std::cout << "média aritmética Y : " << meanY << std::endl;
    std::cout << "média do produto XY: " << meanXY << std::endl;
    std::cout << "média quadrática X : " << meanX2 << std::endl;
    std::cout << "média quadrática Y : " << meanY2 << std::endl;
    std::cout << "----------------------------------------: " << std::endl;

    double sigmaX = pow( meanX2-pow(meanX,2) ,0.5); 
    double sigmaY = pow( meanY2-pow(meanY,2) ,0.5);
    double sigmaX2 = pow( sigmaX ,2); 
    double sigmaY2 = pow( sigmaY ,2);
    double sigmaXY = meanXY - meanX*meanY;  

    std::cout << "Desvio Padrão (Sigma) X: " << sigmaX << std::endl;
    std::cout << "Desvio Padrão (Sigma) Y: " << sigmaY << std::endl;
    std::cout << "Variância X (SigmaX)²  : " << sigmaX2 << std::endl;
    std::cout << "Variância Y (SigmaY)²  : " << sigmaY2 << std::endl;
    std::cout << "Covariância (SigmaXY)  : " << sigmaXY << std::endl;

    std::cout << "----------------------------------------: " << std::endl;

    double r = sigmaXY/(sigmaX*sigmaY);
    double a = sigmaXY/sigmaX2;
    double b = meanY-a*meanX;

    std::cout << "Coeficiente Pearson 'r': " << r << std::endl;
    std::cout << "Coeficiente angular 'a': " << a << std::endl;
    std::cout << "Coeficiente linear  'b': " << b << std::endl;

    std::cout << "----------------------------------------: " << std::endl;

    double epsilonY = 0;
    for (int i = 0; i < n; ++i) {
        epsilonY += pow(y[i]-(a*x[i]+b),2);
    }
    epsilonY = pow(epsilonY/(n-2),0.5);

    std::cout << "Erro de cada medida (EpsilonY): " << epsilonY << std::endl;

    std::cout << "----------------------------------------: " << std::endl;

    double sigmaA = (1/sigmaX)*(epsilonY/pow(n,0.5));
    double sigmaB = sigmaA*pow(meanX2,0.5);

    std::cout << "Erro de 'a' (sigma a): " << sigmaA << std::endl;
    std::cout << "Erro de 'b' (sigma b): " << sigmaB << std::endl;

    std::cout << "----------------------------------------: " << std::endl;
    std::cout << "RESULTADO FINAL: \n" << std::endl;

    double jToEv = 6.242e18; // Scale factor "J" to "eV"

    if ( DefFlag == 0){
        double h = a;
        double sigmaH = sigmaA;

        std::cout << "h   = " <<  h << " +- " << sigmaH << " J.s" << std::endl;
        std::cout << "phi = " <<  b << " +- " << sigmaB << " Volts\n" << std::endl;

        std::cout << "or applying scale factor " << jToEv << " ('J' to 'eV' )\n" << std::endl;

        std::cout << "h   = " <<  h*jToEv  << " +- " << sigmaH*jToEv << " eV.s" << std::endl;
        std::cout << "phi = " <<  b*jToEv << " +- " << sigmaB*jToEv << " Volts" << std::endl;
        
    }
    else if ( DefFlag == 1)
    {
        double h = a;
        double sigmaH = sigmaA;
        std::cout << "h = " <<  h << " +- " << sigmaA << " J.s" << std::endl;
        std::cout << "phi = " <<  b << " +- " << sigmaB << " J\n" << std::endl;
    }
    else if ( DefFlag == 2)
    {
        std::cout << "a = " <<  a << " +- " << sigmaA << " J.s / C  [V.s]" << std::endl;
        std::cout << "b = " <<  b << " +- " << sigmaB << " V" << std::endl;

        std::cout << " Multilicando pela carga do eletron 'e':" << std::endl;

        double h = a*e;
        double sigmaH = sigmaA*e;

        std::cout << "h = " <<  h << " +- " << sigmaH << " J.s" << std::endl;

    }



    std::cout << "----------------------------------------: " << std::endl;

    return 0; 

}