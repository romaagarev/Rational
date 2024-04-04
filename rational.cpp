#include <sstream>
#include "rational.h"

int64_t Multiply(int a, int b) {
    return static_cast<int64_t>(a) * b;
}

int64_t GetLeft(Rational lhs, Rational rhs) {
    return Multiply(lhs.GetNumerator(), rhs.GetDenominator());
}

int64_t GetRight(Rational lhs, Rational rhs) {
    return Multiply(lhs.GetDenominator(), rhs.GetNumerator());
}

Rational::Rational() : numer_(0), denom_(1){};

Rational::Rational(int value) : numer_(value), denom_(1){};  // NOLINT

Rational::Rational(int numer, int denom) {
    Set(numer, denom);
};

int Rational::GetNumerator() const {
    return numer_;
}

int Rational::GetDenominator() const {
    return denom_;
}

void Rational::SetNumerator(int value) {
    Set(value, denom_);
}

void Rational::SetDenominator(int value) {
    Set(numer_, value);
}

void Rational::Set(int64_t numer, int64_t denom) {
    if (denom == 0) {
        throw RationalDivisionByZero{};
    }
    int64_t divider = std::gcd(numer, denom);
    if (denom < 0) {
        numer_ = -static_cast<int>(numer / divider);
        denom_ = -static_cast<int>(denom / divider);
    } else {
        numer_ = static_cast<int>(numer / divider);
        denom_ = static_cast<int>(denom / divider);
    }
}

Rational operator+(const Rational& ratio) {
    Rational result(ratio.GetNumerator(), ratio.GetDenominator());
    return result;
};

Rational operator-(const Rational& ratio) {
    Rational result(-ratio.GetNumerator(), ratio.GetDenominator());
    return result;
};

Rational& operator+=(Rational& lhs, const Rational& rhs) {
    lhs.Set(Multiply(lhs.GetNumerator(), rhs.GetDenominator()) + Multiply(lhs.GetDenominator(), rhs.GetNumerator()),
            Multiply(lhs.GetDenominator(), rhs.GetDenominator()));
    return lhs;
};

Rational& operator-=(Rational& lhs, const Rational& rhs) {
    lhs += -rhs;
    return lhs;
};

Rational& operator*=(Rational& lhs, const Rational& rhs) {
    lhs.Set(Multiply(lhs.GetNumerator(), rhs.GetNumerator()), Multiply(lhs.GetDenominator(), rhs.GetDenominator()));
    return lhs;
};

Rational& operator/=(Rational& lhs, const Rational& rhs) {
    if (rhs.GetNumerator() == 0) {
        throw RationalDivisionByZero{};
    }
    Rational divider(rhs.GetDenominator(), rhs.GetNumerator());
    if (rhs.GetNumerator() < 0) {
        divider.SetNumerator(-divider.GetNumerator());
        divider.SetDenominator(-divider.GetDenominator());
    }
    lhs *= divider;
    return lhs;
};

Rational operator+(const Rational& lhs, const Rational& rhs) {
    Rational result = lhs;
    result += rhs;
    return result;
};

Rational operator-(const Rational& lhs, const Rational& rhs) {
    Rational result = lhs;
    result -= rhs;
    return result;
};

Rational operator*(const Rational& lhs, const Rational& rhs) {
    Rational result = lhs;
    result *= rhs;
    return result;
};

Rational operator/(const Rational& lhs, const Rational& rhs) {
    Rational result = lhs;
    result /= rhs;
    return result;
};

Rational& operator++(Rational& ratio) {
    ratio.SetNumerator(ratio.GetNumerator() + ratio.GetDenominator());
    return ratio;
};

Rational& operator--(Rational& ratio) {
    ratio.SetNumerator(ratio.GetNumerator() - ratio.GetDenominator());
    return ratio;
};

Rational operator++(Rational& ratio, int) {
    return ++ratio - 1;
};

Rational operator--(Rational& ratio, int) {
    return --ratio + 1;
};

bool operator<(const Rational& lhs, const Rational& rhs) {
    return (GetLeft(lhs, rhs) < GetRight(lhs, rhs));
};

bool operator>(const Rational& lhs, const Rational& rhs) {
    return (GetLeft(lhs, rhs) > GetRight(lhs, rhs));
};

bool operator<=(const Rational& lhs, const Rational& rhs) {
    return (GetLeft(lhs, rhs) <= GetRight(lhs, rhs));
};

bool operator>=(const Rational& lhs, const Rational& rhs) {
    return (GetLeft(lhs, rhs) >= GetRight(lhs, rhs));
};

bool operator==(const Rational& lhs, const Rational& rhs) {
    return (GetLeft(lhs, rhs) == GetRight(lhs, rhs));
};

bool operator!=(const Rational& lhs, const Rational& rhs) {
    return (GetLeft(lhs, rhs) != GetRight(lhs, rhs));
};

std::istream& operator>>(std::istream& is, Rational& ratio) {
    std::string input;
    is >> input;
    std::stringstream number;
    number << input;
    int64_t numer = 0;
    int64_t denom = 1;
    char separator = ' ';
    number >> numer;
    number >> separator;
    number >> denom;
    ratio.Set(numer, denom);
    return is;
}

std::ostream& operator<<(std::ostream& os, const Rational& ratio) {
    if (ratio.GetDenominator() == 1 || ratio.GetNumerator() == 0) {
        return os << ratio.GetNumerator();
    }
    return os << ratio.GetNumerator() << '/' << ratio.GetDenominator();
};
