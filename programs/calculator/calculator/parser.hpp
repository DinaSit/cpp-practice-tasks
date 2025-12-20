#ifndef PARSER_HPP
#define PARSER_HPP

#include "expressions.hpp"
#include "tokenize.hpp"

class UnknownSymbolError : public std::runtime_error {
public:
  explicit UnknownSymbolError(const std::string& symbol)
      : std::runtime_error("UnknownSymbolError: unknown symbol \"" + symbol + "\"") {
  }
};

class WrongExpressionError : public std::runtime_error {
public:
  explicit WrongExpressionError(const std::string& message)
      : std::runtime_error("WrongExpressionError: " + message) {
  }
};

std::unique_ptr<IExpression> ParseExpression(const std::vector<Token>& tokens, size_t& pos);
std::unique_ptr<IExpression> ParseAddendum(const std::vector<Token>& tokens, size_t& pos);
std::unique_ptr<IExpression> ParseFactor(const std::vector<Token>& tokens, size_t& pos);

std::unique_ptr<IExpression> ParseTerm(const std::vector<Token>& tokens, size_t& pos);
std::unique_ptr<IExpression> ParseMultiplier(const std::vector<Token>& tokens, size_t& pos);

#endif  // PARSER_HPP
