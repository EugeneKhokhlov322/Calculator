#include <iostream>

using namespace std;

class Operation {
public:
    virtual double execute(double a, double b) = 0;
};

class Addition : public Operation {
public:
    double execute(double a, double b) override {
        return a + b;
    }
};

class Subtraction : public Operation {
public:
    double execute(double a, double b) override {
        return a - b;
    }
};

class Multiplication : public Operation {
public:
    double execute(double a, double b) override {
        return a * b;
    }
};

class Division : public Operation {
public:
    double execute(double a, double b) override {
        if (b == 0) {
            throw invalid_argument("Error: division by zero!");
        }
        return a / b;
    }
};

class Calculator {
private:
    Operation* operation;

public:
    void setOperation(Operation* op) {
        operation = op;
    }

    double calculate(double a, double b) {
        return operation->execute(a, b);
    }
};

class Power : public Operation {
public:
    double execute(double a, double b) override {
        return pow(a, b);
    }
};

int main() {
    Calculator calc;
    Addition add;
    Subtraction sub;
    Multiplication mul;
    Division div;
    Power pow;

    double a = 10;
    double b = 5;

    calc.setOperation(&add);
    cout << "Addition: " << calc.calculate(a, b) << endl;

    calc.setOperation(&sub);
    cout << "Subtraction: " << calc.calculate(a, b) << endl;

    calc.setOperation(&mul);
    cout << "Multiplication: " << calc.calculate(a, b) << endl;

    calc.setOperation(&div);
    cout << "Division: " << calc.calculate(a, b) << endl;

    calc.setOperation(&pow);
    cout << "Power: " << calc.calculate(a, b) << endl;

    return 0;
}