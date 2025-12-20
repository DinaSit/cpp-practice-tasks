#ifndef POLISH_NOTATION_HPP
#define POLISH_NOTATION_HPP

#include <string_view>
#include <stdexcept>
#include <string>

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

int CalculatePolishNotation(std::string_view input);

#endif  // POLISH_NOTATION_HPP
