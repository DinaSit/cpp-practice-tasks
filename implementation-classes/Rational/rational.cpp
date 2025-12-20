#include "rational.hpp"

void Rational::Normalize() {
    if (den_ == 0) {
        throw RationalDivisionByZero{};
    }
    if (num_ == 0) {
        den_ = 1;
        return;
    }
    // знак переносим в числитель
    if (den_ < 0) {
        den_ = -den_;
        num_ = -num_;
    }
    int g = std::gcd(num_, den_);
    if (g > 1) {
        num_ /= g;
        den_ /= g;
    }
}

// Конструкторы
Rational::Rational() : num_(0), den_(1) {}

Rational::Rational(int value) : num_(value), den_(1) {} // NOLINT

Rational::Rational(int num, int den) : num_(num), den_(den) {
    Normalize();
}

// Методы
int Rational::GetNumerator() const { return num_; }
int Rational::GetDenominator() const { return den_; }

void Rational::SetNumerator(int num) {
    num_ = num;
    Normalize();
}
void Rational::SetDenominator(int den) {
    den_ = den;
    Normalize();
}

// Унарные
Rational Rational::operator+() const { return *this; }
Rational Rational::operator-() const { return { -num_, den_ }; }

// Присваивающие
Rational& Rational::operator+=(const Rational& rhs) {
    num_ = static_cast<int>(num_ * rhs.den_ + den_ * rhs.num_);
    den_ = static_cast<int>(den_ * rhs.den_);
    Normalize();
    return *this;
}

Rational& Rational::operator-=(const Rational& rhs) {
    num_ = static_cast<int>(num_ * rhs.den_ - den_ * rhs.num_);
    den_ = static_cast<int>(den_ * rhs.den_);
    Normalize();
    return *this;
}

Rational& Rational::operator*=(const Rational& rhs) {
    num_ = static_cast<int>(num_ * rhs.num_);
    den_ = static_cast<int>(den_ * rhs.den_);
    Normalize();
    return *this;
}

Rational& Rational::operator/=(const Rational& rhs) {
    if (rhs.num_ == 0) {
        throw RationalDivisionByZero{};
    }
    num_ = static_cast<int>(num_ * rhs.den_);
    den_ = static_cast<int>(den_ * rhs.num_);
    Normalize();
    return *this;
}

// Инкремент/декремент
Rational& Rational::operator++() { // ++x
    num_ += den_;
    Normalize();
    return *this;
}
Rational Rational::operator++(int) { // x++
    Rational tmp = *this;
    ++(*this);
    return tmp;
}

Rational& Rational::operator--() { // --x
    num_ -= den_;
    Normalize();
    return *this;
}
Rational Rational::operator--(int) { // x--
    Rational tmp = *this;
    --(*this);
    return tmp;
}

// Сравнения
bool operator==(const Rational& a, const Rational& b) {
    return a.GetNumerator() == b.GetNumerator() && a.GetDenominator() == b.GetDenominator();
}

bool operator!=(const Rational& a, const Rational& b) { return !(a == b); }

bool operator<(const Rational& a, const Rational& b) {
    // a/b < c/d  <=>  ad < bc (знаменатели > 0)
    return static_cast<int64_t>(a.GetNumerator()) * b.GetDenominator()
         < static_cast<int64_t>(b.GetNumerator()) * a.GetDenominator();
}

bool operator>(const Rational& a, const Rational& b)  { return b < a; }

bool operator<=(const Rational& a, const Rational& b) { return !(b < a); }

bool operator>=(const Rational& a, const Rational& b) { return !(a < b); }

// Вывод
std::ostream& operator<<(std::ostream& out, const Rational& r) {
    if (r.GetDenominator() == 1) {
        return out << r.GetNumerator();
    }
    return out << r.GetNumerator() << '/' << r.GetDenominator();
}

// Ввод (допускаем "p/q" или "p")
std::istream& operator>>(std::istream& in, Rational& r) {
    int p = 0;
    if (!(in >> p)) { return in; }

    in >> std::ws;
    if (in.peek() == '/') {
        in.get();
        int q = 0;
        if (!(in >> q)) { return in; }
        r = Rational(p, q);
    } else {
        r = Rational(p);
    }
    return in;
}
