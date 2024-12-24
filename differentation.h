#ifndef DIFFERENTATION_H
#define DIFFERENTATION_H
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <limits>
#include <stack>
#include <map>
#include <cmath>
#include <algorithm>
#include <memory>

class Fraction {
private:
    long long numerator;
    long long denominator;

    void simplify() {
        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
        long long gcd = std::__gcd(std::abs(numerator), denominator);
        numerator /= gcd;
        denominator /= gcd;
    }

public:
    Fraction(long long n = 0, long long d = 1) : numerator(n), denominator(d) {
        if (denominator == 0) throw std::runtime_error("Division by zero");
        simplify();
    }

    static Fraction fromString(const std::string& str) {
        size_t pos = str.find('/');
        if (pos == std::string::npos) {
            return Fraction(std::stoll(str));
        }
        return Fraction(std::stoll(str.substr(0, pos)),
                       std::stoll(str.substr(pos + 1)));
    }

    Fraction operator+(const Fraction& other) const {
        return Fraction(numerator * other.denominator + other.numerator * denominator,
                       denominator * other.denominator);
    }

    Fraction operator-(const Fraction& other) const {
        return Fraction(numerator * other.denominator - other.numerator * denominator,
                       denominator * other.denominator);
    }

    Fraction operator*(const Fraction& other) const {
        return Fraction(numerator * other.numerator,
                       denominator * other.denominator);
    }

    Fraction operator/(const Fraction& other) const {
        if (other.numerator == 0) throw std::runtime_error("Division by zero");
        return Fraction(numerator * other.denominator,
                       denominator * other.numerator);
    }

    double toDouble() const {
        return static_cast<double>(numerator) / denominator;
    }

    std::string toString() const {
        if (denominator == 1) return std::to_string(numerator);
        return std::to_string(numerator) + "/" + std::to_string(denominator);
    }
};
class Term {
public:
    virtual ~Term() = default;
    virtual std::shared_ptr<Term> clone() const = 0;
    virtual std::shared_ptr<Term> derivative() const = 0;
    virtual std::shared_ptr<Term> integrate() const = 0;
    virtual double evaluate(double x) const = 0;
    virtual std::string toString() const = 0;
};
class PolynomialTerm : public Term {
    Fraction coefficient;
    int power;

public:
    PolynomialTerm(const Fraction& coeff, int pow)
        : coefficient(coeff), power(pow) {}

    std::shared_ptr<Term> clone() const override {
        return std::make_shared<PolynomialTerm>(*this);
    }

    std::shared_ptr<Term> derivative() const override {
        if (power == 0) return std::make_shared<PolynomialTerm>(Fraction(0), 0);
        return std::make_shared<PolynomialTerm>(
            coefficient * Fraction(power), power - 1);
    }

    std::shared_ptr<Term> integrate() const override {
        return std::make_shared<PolynomialTerm>(
            coefficient / Fraction(power + 1), power + 1);
    }

    double evaluate(double x) const override {
        return coefficient.toDouble() * std::pow(x, power);
    }

    std::string toString() const override {
        std::string result;
        std::string coeffStr = coefficient.toString();
        if (coeffStr != "1" || power == 0) {
            result += coeffStr;
            if (power > 0 && coeffStr != "1") result += "*";
        }
        if (power > 0) {
            result += "x";
            if (power > 1) {
                result += "^" + std::to_string(power);
            }
        }
        return result;
    }
};
class Expression {
    std::vector<std::shared_ptr<Term>> terms;

public:
    void addTerm(std::shared_ptr<Term> term) {
        terms.push_back(term);
    }

    Expression derivative() const {
        Expression result;
        for (const auto& term : terms) {
            result.addTerm(term->derivative());
        }
        return result;
    }

    Expression integrate() const {
        Expression result;
        for (const auto& term : terms) {
            result.addTerm(term->integrate());
        }
        return result;
    }

    double evaluate(double x) const {
        double result = 0.0;
        for (const auto& term : terms) {
            result += term->evaluate(x);
        }
        return result;
    }
    std::string toString() const {
        if (terms.empty()) return "0";
        std::string result;
        bool first = true;
        for (const auto& term : terms) {
            if (!first) {
                std::string termStr = term->toString();
                if (termStr[0] != '-') {
                    result += " + ";
                } else {
                    result += " ";
                }
            }
            result += term->toString();
            first = false;
        }
        return result;
    }
};
class ExpressionParser {
public:
    static Expression parseSimple(const std::string& input) {
        Expression expr;
        std::istringstream iss(input);
        double coeff;
        char x, caret;
        int power;

        while (iss >> coeff) {
            if (iss.peek() == 'x') {
                iss >> x;
                if (iss.peek() == '^') {
                    iss >> caret >> power;
                } else {
                    power = 1;
                }
            } else {
                power = 0;
            }
            expr.addTerm(std::make_shared<PolynomialTerm>(Fraction(coeff), power));

            if (iss.peek() == '+' || iss.peek() == '-') {
                iss.get();
                if (iss.peek() == ' ') iss.get();
            }
        }
        return expr;
    }
};

class menu {
public:
    void main_menu() {
        std::string input;
        Expression expr;
        int choice;

        while (true) {
            std::cout << "\n=== Polynomial Calculator ===\n";
            std::cout << "1. Enter polynomial\n";
            std::cout << "2. Calculate derivative\n";
            std::cout << "3. Calculate integral\n";
            std::cout << "4. Exit\n";
            std::cout << "Enter choice: ";

            std::cin >> choice;
            std::cin.ignore();

            switch (choice) {
                case 1: {
                    std::cout << "Enter polynomial (e.g., 2x^2 + 3x + 1): ";
                    std::getline(std::cin, input);
                    try {
                        expr = ExpressionParser::parseSimple(input);
                        std::cout << "Parsed polynomial: " << expr.toString() << "\n";
                    } catch (const std::exception& e) {
                        std::cout << "Error: " << e.what() << "\n";
                    }
                    break;
                }
                case 2: {
                    try {
                        Expression deriv = expr.derivative();
                        std::cout << "Derivative: " << deriv.toString() << "\n";
                    } catch (const std::exception& e) {
                        std::cout << "Error: " << e.what() << "\n";
                    }
                    break;
                }
                case 3: {
                    try {
                        Expression integ = expr.integrate();
                        std::cout << "Integral: " << integ.toString() << " + C\n";
                    } catch (const std::exception& e) {
                        std::cout << "Error: " << e.what() << "\n";
                    }
                    break;
                }
                case 4:
                    std::cout << "Goodbye!\n";
                return ;
                default:
                    std::cout << "Invalid choice\n";
            }
        }
    }

};

#endif //DIFFERENTATION_H