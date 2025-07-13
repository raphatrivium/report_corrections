#include <iostream>
#include <vector>
#include <cmath>


void mmq(const std::vector<double>& x, 
         const std::vector<double>& y,
         double& meanX,
         double& meanY,
         double& meanXY,
         double& meanX2,
         double& meanY2,
         double& sigmaX,
         double& sigmaY,
         double& sigmaX2,
         double& sigmaY2,
         double& sigmaXY,
         double& r,
         double& a,
         double& b,
         double& epsilonY,
         double& sigmaA,
         double& sigmaB)
{

    int n = x.size();

    // Compute sums
    for (int i = 0; i < n; ++i) {
        meanX += x[i]/n;
        meanY += y[i]/n;
        meanXY += (x[i]*y[i])/n;
        meanX2 += pow(x[i],2)/n;
        meanY2 += pow(y[i],2)/n;
    }

    sigmaX = pow( meanX2-pow(meanX,2) ,0.5); 
    sigmaY = pow( meanY2-pow(meanY,2) ,0.5);
    sigmaX2 = pow( sigmaX ,2); 
    sigmaY2 = pow( sigmaY ,2);
    sigmaXY = meanXY - meanX*meanY;  

    r = sigmaXY/(sigmaX*sigmaY);
    a = sigmaXY/sigmaX2;
    b = meanY-a*meanX;

    epsilonY = 0;
    for (int i = 0; i < n; ++i) {
        epsilonY += pow(y[i]-(a*x[i]+b),2);
    }
    epsilonY = pow(epsilonY/(n-2),0.5);

    sigmaA = (1/sigmaX)*(epsilonY/pow(n,0.5));
    sigmaB = sigmaA*pow(meanX2,0.5);
}
