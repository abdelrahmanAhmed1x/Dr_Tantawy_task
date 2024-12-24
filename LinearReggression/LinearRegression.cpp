//
// Created by abo-k on 12/24/2024.
//

#include "LinearRegression.h"
#include "LinearRegression.h"
#include <iostream>
#include <numeric>

LinearRegression::LinearRegression() : slope(0.0), intercept(0.0) {}

void LinearRegression::addDataPoint(double x, double y) {
    x_data.push_back(x);
    y_data.push_back(y);
}

void LinearRegression::calculateParameters() {
    if (x_data.size() < 2) {
        slope = 0.0;
        intercept = 0.0;
        return;
    }

    size_t n = x_data.size();
    double sum_x = std::accumulate(x_data.begin(), x_data.end(), 0.0);
    double sum_y = std::accumulate(y_data.begin(), y_data.end(), 0.0);
    double sum_xy = 0.0;
    double sum_x_squared = 0.0;

    for (size_t i = 0; i < n; ++i) {
        sum_xy += x_data[i] * y_data[i];
        sum_x_squared += x_data[i] * x_data[i];
    }

    double x_mean = sum_x / n;
    double y_mean = sum_y / n;

    slope = (sum_xy - n * x_mean * y_mean) / (sum_x_squared - n * x_mean * x_mean);
    intercept = y_mean - slope * x_mean;
}

void LinearRegression::fit() {
    calculateParameters();
}

double LinearRegression::predict(double x) const {
    return slope * x + intercept;
}

void LinearRegression::displayEquation() const {
    std::cout << "Linear Regression Equation: y = " << slope << " * x + " << intercept << std::endl;
}

void LinearRegression::clearData() {
    x_data.clear();
    y_data.clear();
    slope = 0.0;
    intercept = 0.0;
}
