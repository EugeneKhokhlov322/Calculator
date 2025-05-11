#include <iostream>
#include <memory>
using namespace std;

class MathOperation {
protected:
    static int totalOperations;
public:
    virtual ~MathOperation() = default;
    virtual double compute(double a, double b) = 0;

    static int getTotalOperations() {
        return totalOperations;
    }
};
int MathOperation::totalOperations = 0;

class BinaryOperation : public MathOperation {
public:
    double execute(double a, double b) {
        totalOperations++;
        return compute(a, b);
    }
};

class Addition : public BinaryOperation {
public:
    double compute(double a, double b) override {
        return a + b;
    }
};

int main() {
    unique_ptr<MathOperation> op = make_unique<Addition>();
    cout << "10 + 5 = " << static_cast<BinaryOperation*>(op.get())->execute(10, 5) << endl;
    cout << "Total operations: " << MathOperation::getTotalOperations() << endl;
    return 0;
}