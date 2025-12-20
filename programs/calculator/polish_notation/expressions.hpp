#ifndef EXPRESSIONS_HPP
#define EXPRESSIONS_HPP

#include <memory>

class IExpression {
public:
  virtual int Calculate() const = 0;
  virtual ~IExpression() = default;
};

class Constant : public IExpression {
  int value_;

public:
  explicit Constant(int value) : value_(value) {
  }

  int Calculate() const override {
    return value_;
  }
};

class IUnaryOperation : public IExpression {
  std::unique_ptr<IExpression> operand_;

public:
  explicit IUnaryOperation(std::unique_ptr<IExpression> operand) : operand_(std::move(operand)) {
  }

  int Calculate() const override {
    return Operation(operand_->Calculate());
  }

  virtual int Operation(int value) const = 0;
};

class Plus : public IUnaryOperation {  // +a
public:
  int Operation(int value) const override {
    return +value;
  }

  using IUnaryOperation::IUnaryOperation;
};

class Minus : public IUnaryOperation {  // -a
public:
  int Operation(int value) const override {
    return -value;
  }

  using IUnaryOperation::IUnaryOperation;
};

class AbsoluteValue : public IUnaryOperation {  // |a|
public:
  int Operation(int value) const override {
    return value < 0 ? -value : value;
  }

  using IUnaryOperation::IUnaryOperation;
};

class Square : public IUnaryOperation {  // a**2
public:
  int Operation(int value) const override {
    return value * value;
  }

  using IUnaryOperation::IUnaryOperation;
};

class IBinaryOperation : public IExpression {
  std::unique_ptr<IExpression> left_;
  std::unique_ptr<IExpression> right_;

public:
  explicit IBinaryOperation(std::unique_ptr<IExpression> left, std::unique_ptr<IExpression> right) : left_(std::move(left)), right_(std::move(right)) {
  }

  int Calculate() const override {
    return Operation(left_->Calculate(), right_->Calculate());
  }

  virtual int Operation(int left, int right) const = 0;
};

class Sum : public IBinaryOperation {  // a + b
public:
  int Operation(int left, int right) const override {
    return left + right;
  }

  using IBinaryOperation::IBinaryOperation;
};

class Subtract : public IBinaryOperation {  // a - b
public:
  int Operation(int left, int right) const override {
    return left - right;
  }

  using IBinaryOperation::IBinaryOperation;
};

class Multiply : public IBinaryOperation {  // a * b
public:
  int Operation(int left, int right) const override {
    return left * right;
  }

  using IBinaryOperation::IBinaryOperation;
};

class Divide : public IBinaryOperation {  // a / b
public:
  int Operation(int left, int right) const override {
    return left / right;
  }

  using IBinaryOperation::IBinaryOperation;
};

class Residual : public IBinaryOperation {  // a % b
public:
  int Operation(int left, int right) const override {
    return left % right;
  }

  using IBinaryOperation::IBinaryOperation;
};

class Minimum : public IBinaryOperation {  // min(a, b)
public:
  int Operation(int left, int right) const override {
    return left < right ? left : right;
  }

  using IBinaryOperation::IBinaryOperation;
};

class Maximum : public IBinaryOperation {  // max(a, b)
public:
  int Operation(int left, int right) const override {
    return left > right ? left : right;
  }

  using IBinaryOperation::IBinaryOperation;
};

#endif  // EXPRESSIONS_HPP
