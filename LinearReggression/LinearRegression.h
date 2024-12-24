//
// Created by abo-k on 12/24/2024.
//

#ifndef LINEARREGRESSION_LINEARREGRESSION_H
#define LINEARREGRESSION_LINEARREGRESSION_H


#include <vector>
#include <string>

class LinearRegression {
private:
    double slope;
    double intercept;
    std::vector<double> x_data;
    std::vector<double> y_data;

    void calculateParameters();

public:
    LinearRegression();

    void addDataPoint(double x, double y);
    void fit();
    double predict(double x) const;
    void displayEquation() const;
    void clearData();
};


#endif //LINEARREGRESSION_LINEARREGRESSION_H
