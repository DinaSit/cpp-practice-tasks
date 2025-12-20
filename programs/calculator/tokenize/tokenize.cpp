#include "tokenize.hpp"
#include <cctype>
#include <unordered_map>
#include <algorithm>
#include <limits>

const static std::unordered_map<char, Token> kSpecialSymbols {
  {'+', PlusToken{}}, {'-', MinusToken{}}, {'*', MultiplyToken{}}, {'/', DivideToken{}}, {'%', ResidualToken{}},
  {'(', OpeningBracketToken{}}, {')', ClosingBracketToken{}}
};
const static std::unordered_map<std::string_view, Token> kSpecialNames {
  {"abs", AbsToken{}}, {"min", MinToken{}}, {"max", MaxToken{}}, {"sqr", SqrToken{}}
};

template <class Predicate>
std::string_view GetConsecutive(std::string_view str, size_t pos, Predicate pred) {
  auto begin = str.begin() + pos;
  auto end = std::find_if_not(begin, str.end(), pred);
  return str.substr(pos, end - begin);
}

static bool IsDigit(char symbol) {
  return '0' <= symbol && symbol <= '9';
}

static bool IsAlpha(char symbol) {
  return std::isalpha(static_cast<unsigned char>(symbol));
}

static bool IsSpace(char symbol) {
  return std::isspace(static_cast<unsigned char>(symbol));
}

static int ToNumber(std::string_view word) {
  int value = 0;
  for (char c : word) {
    value = value * 10 + (c - '0');
  }
  return value;
}

std::vector<Token> Tokenize(const std::string_view input) {
  std::vector<Token> tokens;
  size_t pos = 0;

  while (pos < input.size()) {
    if (IsSpace(input[pos])) {
      ++pos;
    } else if (IsDigit(input[pos])) {
      const auto word = GetConsecutive(input, pos, IsDigit);
      tokens.emplace_back(NumberToken{ToNumber(word)});
      pos += word.size();
    } else if (IsAlpha(input[pos])) {
      const auto word = GetConsecutive(input, pos, IsAlpha);
      if (kSpecialNames.contains(word)) {
        tokens.emplace_back(kSpecialNames.at(word));
      } else {
        tokens.emplace_back(UnknownToken{std::string(word)});
      }
        pos += word.size();
    } else if (kSpecialSymbols.contains(input[pos])) {
      tokens.emplace_back(kSpecialSymbols.at(input[pos]));
      ++pos;
    } else {
      tokens.emplace_back(UnknownToken{std::string(1, input[pos])});
      ++pos;
    }
  }
  return tokens;
}
