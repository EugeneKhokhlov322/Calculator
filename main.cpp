#include <iostream>
#include <memory>
#include <stdexcept>
using namespace std;

class Operation {
public:
    virtual ~Operation() = default;
    virtual double execute(double a, double b) {
        validate(a, b);
        return compute(a, b);
    }

protected:
    virtual double compute(double a, double b) = 0;
    virtual void validate(double a, double b) {}
};

class Addition : public Operation {
protected:
    double compute(double a, double b) override {
        return a + b;
    }
};

class Division : public Operation {
protected:
    double compute(double a, double b) override {
        return a / b;
    }

    void validate(double a, double b) override {
        if (b == 0) throw invalid_argument("Division by zero");
    }
};

class OperationFactory {
public:
    static unique_ptr<Operation> create(char op) {
        switch (op) {
        case '+': return make_unique<Addition>();
        case '/': return make_unique<Division>();
        default: throw invalid_argument("Unknown operation");
        }
    }
};

int main() {
    auto op = OperationFactory::create('+');
    cout << "10 + 5 = " << op->execute(10, 5) << endl;

    op = OperationFactory::create('/');
    try {
        cout << "10 / 2 = " << op->execute(10, 2) << endl;
        cout << "10 / 0 = " << op->execute(10, 0) << endl;
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
    return 0;
}