#pragma once 

class Complex {
 public:
    Complex() = default;
    Complex(double re_, double im_ = 0.0);

    double GetRe() const;
    double GetIm() const;

    Complex operator+();
    Complex operator-();

    Complex& operator+=(const Complex& b);
    Complex& operator-=(const Complex& b);
    Complex& operator*=(const Complex& b);

 private:
    double re = 0.0;
    double im = 0.0;
};

Complex operator+(const Complex& a, const Complex& b);
Complex operator-(const Complex& a, const Complex& b);
Complex operator*(const Complex& a, const Complex& b);

bool operator==(const Complex& a, const Complex& b);
bool operator!=(const Complex& a, const Complex& b);
