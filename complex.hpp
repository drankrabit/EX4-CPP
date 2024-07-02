// ************************
// 326538022
// itay.alexandrov@gmail.com
// ************************
#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include <iostream>
#include <sstream>
#include <string>

class Complex {
private:
    double real;
    double imag;

public:
    Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}

    std::string to_string() const {
        std::ostringstream oss;
        oss << "(" << real << ", " << imag << ")";
        return oss.str();
    }

    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << "(" << c.real << ", " << c.imag << ")";
        return os;
    }

    bool operator>(const Complex& other) const {
        return real > other.real || (real == other.real && imag > other.imag);
    }
};

#endif // COMPLEX_HPP
