#include "polish_notation.hpp"
#include "tokenize.hpp"
#include "expressions.hpp"

std::unique_ptr<IExpression> Parse(const std::vector<Token>& tokens, size_t& pos);

template <class UnaryOperation>
std::unique_ptr<IExpression> MakeUnary(const std::vector<Token>& tokens, size_t& pos) {
  auto op = Parse(tokens, pos);
  return std::make_unique<UnaryOperation>(std::move(op));
}

template <class BinaryOperation>
std::unique_ptr<IExpression> MakeBinary(const std::vector<Token>& tokens, size_t& pos) {
  auto left_op = Parse(tokens, pos);
  auto right_op = Parse(tokens, pos);
  return std::make_unique<BinaryOperation>(std::move(left_op), std::move(right_op));
}

std::unique_ptr<IExpression> Parse(const std::vector<Token>& tokens, size_t& pos) {
  if (pos >= tokens.size()) {
    throw WrongExpressionError("not enough operands");
  }

  const auto& token = tokens[pos];

  if (std::holds_alternative<ClosingBracketToken>(token)) {
    throw WrongExpressionError("no matching ( for )");
  }
  if (std::holds_alternative<UnknownToken>(token)) {
    throw UnknownSymbolError(std::get<UnknownToken>(token).value);
  }

  ++pos;
  if (std::holds_alternative<OpeningBracketToken>(token)) {  // ()
    auto sub_expression = Parse(tokens, pos);
    if (pos >= tokens.size() || !std::holds_alternative<ClosingBracketToken>(tokens[pos])) {
      throw WrongExpressionError("no matching ) for (");
    }
    ++pos;
    return sub_expression;
  }
  if (std::holds_alternative<NumberToken>(token)) {  // Number
    auto value = std::get<NumberToken>(token).value;
    return std::make_unique<Constant>(value);
  }

  if (std::holds_alternative<AbsToken>(token)) {  // |..| -> AbsoluteValue
    return MakeUnary<AbsoluteValue>(tokens, pos);
  }
  if (std::holds_alternative<SqrToken>(token)) {  // a^2 -> Square
    return MakeUnary<Square>(tokens, pos);
  }

  if (std::holds_alternative<PlusToken>(token)) {  // + -> Plus / Sum
    auto left_op = Parse(tokens, pos);
    if (pos == tokens.size() || std::holds_alternative<ClosingBracketToken>(tokens[pos])) {
      return std::make_unique<Plus>(std::move(left_op));
    }
    auto right_op = Parse(tokens, pos);
    return std::make_unique<Sum>(std::move(left_op), std::move(right_op));
  }
  if (std::holds_alternative<MinusToken>(token)) { // - -> Minus / Subtract
    auto left_op = Parse(tokens, pos);
    if (pos == tokens.size() || std::holds_alternative<ClosingBracketToken>(tokens[pos])) {
      return std::make_unique<Minus>(std::move(left_op));
    }
    auto right_op = Parse(tokens, pos);
    return std::make_unique<Subtract>(std::move(left_op), std::move(right_op));
  }

  if (std::holds_alternative<MultiplyToken>(token)) {  // * -> Multiply
    return MakeBinary<Multiply>(tokens, pos);
  }
  if (std::holds_alternative<DivideToken>(token)) {  // / -> Divide
    return MakeBinary<Divide>(tokens, pos);
  }
  if (std::holds_alternative<ResidualToken>(token)) {  // % -> Residual
    return MakeBinary<Residual>(tokens, pos);
  }
  if (std::holds_alternative<MinToken>(token)) {  // Min(a, b) -> Minimum
    return MakeBinary<Minimum>(tokens, pos);
  }
  if (std::holds_alternative<MaxToken>(token)) {  // Max(a, b) -> Maximum
    return MakeBinary<Maximum>(tokens, pos);
  }
  throw WrongExpressionError("unknown token in expression");
}

std::unique_ptr<IExpression> ParsePolishNotation(const std::vector<Token>& tokens) {  // возвращаем указатель на верхний узел дерева выражения
  size_t pos = 0;
  auto expression = Parse(tokens, pos);  // рекурсивное вычисление лев и прав оп
  if (pos < tokens.size()) {
    throw WrongExpressionError("too many operands");
  }
  return expression;
}

int CalculatePolishNotation(std::string_view input) {
  const auto tokens = Tokenize(input);  // токенизируем пользовательский ввод
  const auto expression = ParsePolishNotation(tokens);  // парсим / строим дерево разбора выражения
  return expression->Calculate();  // вычисляем дерево разбора выражения
}
