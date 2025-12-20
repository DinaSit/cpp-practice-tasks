#ifndef CALCULATOR_TOKENIZE_HPP
#define CALCULATOR_TOKENIZE_HPP

#include <string_view>
#include <string>
#include <vector>
#include <variant>
#include <stdexcept>

struct UnknownSymbolError : public std::runtime_error {
  char symbol;
  
  explicit UnknownSymbolError(char s) : std::runtime_error(std::string("Unknown symbol: ") + s), symbol(s) {}
};

struct UnknownWordError : public std::runtime_error {
  std::string_view word;

  explicit UnknownWordError(std::string_view w) : std::runtime_error("Unknown word: " + std::string(w)), word(w) {}
};

struct PlusToken {};  // +

inline bool operator==(PlusToken, PlusToken) {
  return true;
}

struct MinusToken {}; // -

inline bool operator==(MinusToken, MinusToken) {
  return true;
}

struct MultiplyToken {}; // *

inline bool operator==(MultiplyToken, MultiplyToken) {
  return true;
}

struct ResidualToken {}; // %

inline bool operator==(ResidualToken, ResidualToken) {
  return true;
}

struct DivideToken {}; // /

inline bool operator==(DivideToken, DivideToken) {
  return true;
}

struct OpeningBracketToken {};  // (

inline bool operator==(OpeningBracketToken, OpeningBracketToken) {
  return true;
}

struct ClosingBracketToken {}; // )

inline bool operator==(ClosingBracketToken, ClosingBracketToken) {
  return true;
}

struct SqrToken {};  // sqr

inline bool operator==(SqrToken, SqrToken) {
  return true;
}

struct MaxToken {}; // max

inline bool operator==(MaxToken, MaxToken) {
  return true;
}

struct MinToken {};  // min

inline bool operator==(MinToken, MinToken) {
  return true;
}

struct AbsToken {};  // abs

inline bool operator==(AbsToken, AbsToken) {
  return true;
}

struct NumberToken {  // произвольное число
  int value;
};

inline bool operator==(NumberToken lhs, NumberToken rhs) {
  return lhs.value == rhs.value;
}

struct UnknownToken { // abracadabra
  std::string value;
};

inline bool operator==(UnknownToken lhs, UnknownToken rhs) {
  return lhs.value == rhs.value;
}

// псевдоним типов
using Token = std::variant<PlusToken, MinusToken, MultiplyToken, ResidualToken, DivideToken, OpeningBracketToken, ClosingBracketToken, SqrToken, MaxToken, MinToken, AbsToken, NumberToken, UnknownToken>;

std::vector<Token> Tokenize(std::string_view input);

#endif  // CALCULATOR_TOKENIZE_HPP
