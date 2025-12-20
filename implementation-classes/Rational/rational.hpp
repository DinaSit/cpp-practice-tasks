#ifndef RATIONAL_HPP
#define RATIONAL_HPP

#include <iostream>
#include <numeric> // std::gcd
#include <fstream>
#include <stdexcept>

class RationalDivisionByZero : public std::runtime_error {
 public:
  RationalDivisionByZero() : std::runtime_error("RationalDivisionByZero") {
  }
};

class Rational {
public:
    // Конструктор по умолчанию, который инициализирует число нулем;
    Rational();

    // Неявный конструктор преобразования от целых чисел // NOLINT
    Rational(int value); // NOLINT

    // Конструктор от двух целых чисел (числитель и знаменатель)
    // При этом не гарантируется, что числа взаимно простые и ненулевые
    Rational(int num, int den);

    // Методы, возвращающие числитель и знаменатель соответственно
    int GetNumerator() const;
    int GetDenominator() const;

    // Методы, устанавливающие числитель и знаменатель в требуемые значения
    void SetNumerator(int num);
    void SetDenominator(int den);

    // Унарные операторы
    Rational operator+() const;
    Rational operator-() const;

    // Присваивающие арифметические операторы
    Rational& operator+=(const Rational& rhs);
    Rational& operator-=(const Rational& rhs);
    Rational& operator*=(const Rational& rhs);
    Rational& operator/=(const Rational& rhs);

    // Инкремент/декремент
    Rational& operator++();   // ++x
    Rational  operator++(int); // x++
    Rational& operator--();   // --x
    Rational  operator--(int); // x--

private:
    int num_; // числитель
    int den_; // знаменатель

    void Normalize(); // делает знаменатель положительным и сокращает дробь
};

template <typename L, typename R>
Rational operator+(const L& lhs, const R& rhs) {
    return Rational(lhs) += Rational(rhs);
}

template <typename L, typename R>
Rational operator-(const L& lhs, const R& rhs) {
    return Rational(lhs) -= Rational(rhs);
}

template <typename L, typename R>
Rational operator*(const L& lhs, const R& rhs) {
    return Rational(lhs) *= Rational(rhs);
}

template <typename L, typename R>
Rational operator/(const L& lhs, const R& rhs) {
    return Rational(lhs) /= Rational(rhs);
}

// Сравнения
bool operator==(const Rational& a, const Rational& b);
bool operator!=(const Rational& a, const Rational& b);
bool operator<(const Rational& a, const Rational& b);
bool operator>(const Rational& a, const Rational& b);
bool operator<=(const Rational& a, const Rational& b);
bool operator>=(const Rational& a, const Rational& b);

// Ввод / вывод
std::ostream& operator<<(std::ostream& out, const Rational& r);
std::istream& operator>>(std::istream& in, Rational& r);

#endif
