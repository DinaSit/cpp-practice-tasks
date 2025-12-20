#include "parser.hpp"
// 1. Выражение = Сумма/разность нескольких (>=1) слагаемых (может быть и одного)
// 2. Слагаемое = Произведение/частное нескольких (>= 1) множителей (может быть и одного)
// 3. Множитель = Число или унарная операция или выражение в скобках 
// +, -, *, /, % и константы

std::unique_ptr<IExpression> ParseExpression(const std::vector<Token>& tokens, size_t& pos) {
  auto expression = ParseAddendum(tokens, pos);
  while (pos < tokens.size()) {
    const auto& token = tokens[pos];
    if (std::holds_alternative<PlusToken>(token)) {  // +
      ++pos;
      auto addendum = ParseAddendum(tokens, pos);
      expression = std::make_unique<Sum>(std::move(expression), std::move(addendum));
    } else if (std::holds_alternative<MinusToken>(token)) {  // -
      ++pos;
      auto deductible = ParseAddendum(tokens, pos);
      expression = std::make_unique<Subtract>(std::move(expression), std::move(deductible));
    } else if (std::holds_alternative<UnknownToken>(token)) {
      throw UnknownSymbolError(std::get<UnknownToken>(token).value);
    } else {
      break;
    }
  }
  return expression;
}

std::unique_ptr<IExpression> ParseAddendum(const std::vector<Token>& tokens, size_t& pos) {
  auto expression = ParseFactor(tokens, pos);
  while (pos < tokens.size()) {
    const auto& token = tokens[pos];
    if (std::holds_alternative<MultiplyToken>(token)) {  // *
      ++pos;
      auto multiplier = ParseFactor(tokens, pos);
      expression = std::make_unique<Multiply>(std::move(expression), std::move(multiplier));
    } else if (std::holds_alternative<DivideToken>(token)) {  // /
      ++pos;
      auto divider = ParseFactor(tokens, pos);
      expression = std::make_unique<Divide>(std::move(expression), std::move(divider));
    } else if (std::holds_alternative<ResidualToken>(token)) {  // %
      ++pos;
      auto residue = ParseFactor(tokens, pos);
      expression = std::make_unique<Residual>(std::move(expression), std::move(residue));
    } else if (std::holds_alternative<UnknownToken>(token)) {
      throw UnknownSymbolError(std::get<UnknownToken>(token).value);
    } else {
      break;
    }
  }
  return expression;
}

std::unique_ptr<IExpression> ParseFactor(const std::vector<Token>& tokens, size_t& pos) {
  if (pos >= tokens.size()) {
    throw WrongExpressionError("not enough operands");
  }
  const auto& token = tokens[pos];
  ++pos;
  if (std::holds_alternative<NumberToken>(token)) {  // const
    return std::make_unique<Constant>(std::get<NumberToken>(token).value);
  }
  if (std::holds_alternative<MinusToken>(token)) {  // unary -
    auto arg = ParseFactor(tokens, pos);
    return std::make_unique<Minus>(std::move(arg));
  }
  if (std::holds_alternative<PlusToken>(token)) {  // unary +
    auto arg = ParseFactor(tokens, pos);
    return std::make_unique<Plus>(std::move(arg));
  }
  if (std::holds_alternative<OpeningBracketToken>(token)) {  // ()
    auto sub_expression = ParseExpression(tokens, pos);
    if (pos >= tokens.size() || !std::holds_alternative<ClosingBracketToken>(tokens[pos])) {
      throw WrongExpressionError("no matching ) for (");
    }
    ++pos;
    return sub_expression;
  }
  if (std::holds_alternative<UnknownToken>(token)) {
    throw UnknownSymbolError(std::get<UnknownToken>(token).value);
  }
  throw WrongExpressionError("unexpected token"); // встретили что-то неожиданное (нр внезапный знак деления)
}

std::unique_ptr<IExpression> ParseTerm(const std::vector<Token>& tokens, size_t& pos) {
  return ParseAddendum(tokens, pos);
}

std::unique_ptr<IExpression> ParseMultiplier(const std::vector<Token>& tokens, size_t& pos) {
  return ParseFactor(tokens, pos);
}
