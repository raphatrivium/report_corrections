


#include "mmq.h"

int efeitoFotoeletrico() {
    
    // As definições de x,y e a odem mudar de acordo com a fórmula.
    int DefFlag = -1;
    // 0  x=V  , y=nu/e,  a=h   
    // 1  x=eV , y=nu  ,  a=h
    // 2  x=V  , y=nu  ,  a=h/e

    // Anderson e Pedro
    // DefFlag = 2;
    // std::vector<double> x = {5.19E+14,5.49E+14,6.88E+14,7.41E+14,8.22E+14};
    // std::vector<double> y = {0.649, 0.810, 1.458, 1.530, 1.958};

    // Agatha, Samuel e Thayna
    DefFlag = 2;
    std::vector<double> x = {5.19e14, 5.49e14, 6.88e14, 7.41e14, 8.22e14};
    std::vector<double> y = {0.718,0.785,1.347,1.507,1.783};

    // Jiayi, Sara e Vitor
    // std::vector<double> x = {5.19E+14,5.49E+14,6.88E+14,7.41E+14,8.22E+14};
    // std::vector<double> y = {0.619, 0.761, 1.377, 1.503, 1.842 };

    // Carlos e Nathalia
    // std::vector<double> x = {5.19E+14,5.49E+14,6.88E+14,7.41E+14,8.22E+14};
    // std::vector<double> y = {0.495, 0.574, 1.336, 0.733, 0.906 };
    // std::vector<double> y = {0,537,0,638,1,345,0,785,0,934 }; // Primeira medidad deles



    double e = 1.60218e-19; // [C]   Carga do eletron
    int n = x.size();

    double meanX = 0;
    double meanY = 0;
    double meanXY = 0;
    double meanX2 = 0;
    double meanY2 = 0;
    double sigmaX = 0;
    double sigmaY = 0;
    double sigmaX2 = 0;
    double sigmaY2 = 0;
    double sigmaXY = 0;
    double r = 0;
    double a = 0;
    double b = 0;
    double epsilonY = 0;
    double sigmaA = 0;
    double sigmaB = 0;

    std::cout << "------------- Medidas Coletadas --------------------------: " << std::endl;
    std::cout << "nu(frequency) X: ";
    for (int i = 0; i < n; ++i) {
        std::cout  << x[i] << "  ";
    }
    std::cout << "[Hz] ou [1/s]" << std::endl;
    std::cout << "V             Y: ";
    for (int i = 0; i < n; ++i) {
        std::cout <<  y[i] << "  " ;
    }
    std::cout << "[Volts] ou [J/C]\n" << std::endl;

    std::cout << "------------- Medidas a serem usadas --------------------------: " << std::endl;

    if ( DefFlag == 0){
        std::cout << "V = h x (nu) + phi\n" << std::endl;
        std::cout << "y = V\nx = nu/e\na = h\nb= phi\n " << std::endl;
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
        std::cout << "eV = (h)x(nu) + (e)x(phi)" << std::endl;
        std::cout << "y = eV\nx = nu\na = h\nb = e x phi\n" << std::endl;
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
    {   std::cout << "V = (h/e) x (nu) + phi" << std::endl;
        std::cout << "y = V\nx = nu\na = h/e\nb = phi\n" << std::endl;
        std::cout << "nu(frequency) X: ";
        for (int i = 0; i < n; ++i) {
            std::cout  << x[i] << "  ";
        }
        std::cout << "[Hz] ou [1/s]" << std::endl;
        std::cout << "V             Y: ";
        for (int i = 0; i < n; ++i) {
            std::cout <<  y[i] << "  " ;
        }
        std::cout << "[Volts] ou [J/C]\n" << std::endl;
    }

    // Método do Mínimos Quadrados
    mmq(x, y, meanX, meanY, meanXY, meanX2, meanY2,
        sigmaX, sigmaY, sigmaX2, sigmaY2, sigmaXY,
        r, a, b, epsilonY, sigmaA, sigmaB);
    
    std::cout << "----------------------------------------: " << std::endl;
    std::cout << "média aritmética X : " << meanX << std::endl;
    std::cout << "média aritmética Y : " << meanY << std::endl;
    std::cout << "média do produto XY: " << meanXY << std::endl;
    std::cout << "média quadrática X : " << meanX2 << std::endl;
    std::cout << "média quadrática Y : " << meanY2 << std::endl;
    std::cout << "----------------------------------------: " << std::endl;
    std::cout << "Desvio Padrão (Sigma) X: " << sigmaX << std::endl;
    std::cout << "Desvio Padrão (Sigma) Y: " << sigmaY << std::endl;
    std::cout << "Variância X (SigmaX)²  : " << sigmaX2 << std::endl;
    std::cout << "Variância Y (SigmaY)²  : " << sigmaY2 << std::endl;
    std::cout << "Covariância (SigmaXY)  : " << sigmaXY << std::endl;
    std::cout << "----------------------------------------: " << std::endl;
    std::cout << "Coeficiente Pearson 'r': " << r << std::endl;
    std::cout << "Coeficiente angular 'a': " << a << std::endl;
    std::cout << "Coeficiente linear  'b': " << b << std::endl;
    std::cout << "----------------------------------------: " << std::endl;
    std::cout << "Erro de cada medida (EpsilonY): " << epsilonY << std::endl;
    std::cout << "----------------------------------------: " << std::endl;
    std::cout << "Erro de 'a' (sigma a): " << sigmaA << std::endl;
    std::cout << "Erro de 'b' (sigma b): " << sigmaB << std::endl;
    std::cout << "----------------------------------------: " << std::endl;
    std::cout << "RESULTADO FINAL: \n" << std::endl;

    double jToEv = 6.242e18; // Scale factor "J" to "eV"
    double h = 0;
    double sigmaH = 0;

    if ( DefFlag == 0){
        h = a;
        sigmaH = sigmaA;

        std::cout << "h   = " <<  h << " +- " << sigmaH << " J.s" << std::endl;
        std::cout << "phi = " <<  b << " +- " << sigmaB << " Volts\n" << std::endl;

        std::cout << "or applying scale factor " << jToEv << " ('J' to 'eV' )\n" << std::endl;

        std::cout << "h   = " <<  h*jToEv  << " +- " << sigmaH*jToEv << " [eV.s]" << std::endl;
        std::cout << "phi = " <<  b*jToEv << " +- " << sigmaB*jToEv << " [Volts]" << std::endl;
        
    }
    else if ( DefFlag == 1)
    {
        h = a;
        sigmaH = sigmaA;
        std::cout << "h   = " <<  h << " +- " << sigmaA << " [J.s]" << std::endl;
        std::cout << "phi = " <<  b << " +- " << sigmaB << " [J]\n" << std::endl;
    }
    else if ( DefFlag == 2)
    {
        std::cout << "a (h/e)= " <<  a << " +- " << sigmaA << " [J.s/C]  [V.s]" << std::endl;
        std::cout << "b (phi)= " <<  b << " +- " << sigmaB << " [V]\n" << std::endl;

        std::cout << " Multiplicando pela carga do eletron 'e':\n" << std::endl;

        h = a*e;
        sigmaH = sigmaA*e;

        std::cout << "h = " <<  h << " +- " << sigmaH << " [J.s]" << std::endl;
        std::cout << "phi = " <<  b << " +- " << sigmaB << " [V]" << std::endl;

    }
    std::cout << "----------------------------------------: " << std::endl;
    double relErr = (sigmaH*100)/h;
    std::cout << "Erro Relativo  (sigmaH/h)x100: "<< relErr << " %" <<std::endl;
    std::cout << "----------------------------------------: " << std::endl;

    return 0;
}