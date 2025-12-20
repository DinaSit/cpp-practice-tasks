#include "calculator.hpp"

std::unique_ptr<IExpression> InfixNotation(const std::vector<Token>& tokens) {
  size_t pos = 0;
  auto expression = ParseExpression(tokens, pos);
  if (pos != tokens.size()) {
    if (pos < tokens.size() && std::holds_alternative<ClosingBracketToken>(tokens[pos])) {
      throw WrongExpressionError("no matching ( for )");
    }
    throw WrongExpressionError("extra tokens after expression");
  }
  return expression;
}

int CalculateExpression(std::string_view input) {
  const auto tokens = Tokenize(input);  // токенизируем пользовательский ввод
  const auto expression = InfixNotation(tokens);
  return expression->Calculate();
}
