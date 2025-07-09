#include <iostream>
#include <vector>
#include <cmath>






// Least Squares Fitting: y = ax + b
void leastSquaresFit(const std::vector<double>& x, const std::vector<double>& y, 
                     double& a, double& b) {
    if (x.size() != y.size() || x.empty()) {
        std::cerr << "Error: Invalid input data!" << std::endl;
        return;
    }

    double sumX = 0.0, sumY = 0.0, sumXY = 0.0, sumX2 = 0.0;
    int n = x.size();

    // Compute sums
    for (int i = 0; i < n; ++i) {
        sumX += x[i];
        sumY += y[i];
        sumXY += x[i] * y[i];
        sumX2 += x[i] * x[i];
    }

    // Calculate coefficients (a = slope, b = intercept)
    double denominator = n * sumX2 - sumX * sumX;
    if (std::abs(denominator) < 1e-10) {
        std::cerr << "Error: Singular matrix (vertical line)." << std::endl;
        return;
    }

    a = (n * sumXY - sumX * sumY) / denominator;
    b = (sumY * sumX2 - sumX * sumXY) / denominator;
}

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
    
    std::cout << "Angular Coefficient: " << a << std::endl;

    return a;
}



int rel4_efeito_fotoeletrico() {
    // Example data points (x, y)
    // std::vector<double> x = {1.0, 2.0, 3.0, 4.0, 5.0};
    // std::vector<double> y = {1.1, 1.9, 3.2, 4.0, 5.1};

    // std::vector<double> x = {5.19, 5.49, 6.88, 7.41, 8.22};
    // std::vector<double> y = {0.718,0.785,1.347,1.507,1.783};

    std::vector<double> x = {3.24, 3.43, 4.29, 4.62, 5.13};
    std::vector<double> y = {0.649, 0.810, 1.458, 1.530, 1.958};

    double sigmaXY = covariance(x,y);
    double sigmaX = standardDeviation(x);

    double a = angularCoefficient(sigmaXY, sigmaX);

    // double a, b;
    // leastSquaresFit(x, y, a, b);

    // std::cout << "Fitted line: y = " << a << "x + " << b << std::endl;
    return 0;
}