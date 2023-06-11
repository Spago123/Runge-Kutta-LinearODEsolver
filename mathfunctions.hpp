#ifndef MATHFUNCTION_H
#define MATHFUNCTION_H

#include <string>
#include <vector>
#include <regex>
#include <cmath>

std::vector<std::string> extractTerms(const std::string& equation) {
    std::vector<std::string> terms;
    std::regex termRegex("[-+]?\\d*\\.?\\d*[a-zA-Z]+\\(\\d*[a-zA-Z]+\\)|[-+]?\\d*\\.?\\d*[a-zA-Z]+|[-+]?\\d+\\.?\\d*");

    std::sregex_iterator iter(equation.begin(), equation.end(), termRegex);
    std::sregex_iterator end;

    while (iter != end) {
        terms.push_back((*iter).str());
        ++iter;
    }

    return terms;
}

class Function {
public:
    virtual double evaluate(double x) const = 0;
};



class Polynomial : public Function {
private:
    double coefficient_;

public:
    Polynomial(double coefficient) : coefficient_(coefficient) {}

    double evaluate(double x) const override {
        return coefficient_ * x;
    }
};

class TrigonometricFunction : public Function {
protected:
    double amplitude_;
    double frequency_;

public:
    TrigonometricFunction(double amplitude, double frequency)
        : amplitude_(amplitude), frequency_(frequency) {}
};

class SineFunction : public TrigonometricFunction {
public:
    SineFunction(double amplitude, double frequency)
        : TrigonometricFunction(amplitude, frequency) {}

    double evaluate(double x) const override {
        return amplitude_ * std::sin(frequency_ * x);
    }
};

class CosineFunction : public TrigonometricFunction {
public:
    CosineFunction(double amplitude, double frequency)
        : TrigonometricFunction(amplitude, frequency) {}

    double evaluate(double x) const override {
        return amplitude_ * std::cos(frequency_ * x);
    }
};

class ConstantFunction : public Function {
private:
    double constant_;

public:
    ConstantFunction(double constant) : constant_(constant) {}

    double evaluate(double x) const override {
        return constant_;
    }
};

std::vector<Function*> convertToFunctions(const std::vector<std::string>& terms) {
    std::vector<Function*> functions;

    for (const auto& term : terms) {
        std::regex polyRegex("([-+]?\\d*\\.?\\d*)[a-zA-Z]+");
        std::regex trigRegex("([-+]?\\d*\\.?\\d*)\\w+\\((\\d*\\.?\\d*)[a-zA-Z]+\\)");
        std::regex constantRegex("([-+]?\\d*\\.?\\d*)");

        std::smatch match;
        if (std::regex_match(term, match, polyRegex)) {
            double coefficient = std::stod(match[1]);
            functions.push_back(new Polynomial(coefficient));
        }
        else if (std::regex_match(term, match, trigRegex)) {
            double amplitude = std::stod(match[1]);
            double frequency = std::stod(match[2]);
            if (term.find("sin") != std::string::npos)
                functions.push_back(new SineFunction(amplitude, frequency));
            else if (term.find("cos") != std::string::npos)
                functions.push_back(new CosineFunction(amplitude, frequency));
        }
        else if (std::regex_match(term, match, constantRegex)) {
            double constant = std::stod(match[1]);
            functions.push_back(new ConstantFunction(constant));
        }
    }

    return functions;
}

#endif