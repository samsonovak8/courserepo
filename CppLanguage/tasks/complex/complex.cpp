#include"complex.hpp"
#include<cmath>
#include<iostream>

Complex::Complex(double re_, double im_) : re(re_), im(im_) {}

double Complex::GetRe() const {
    return re;
}

double Complex::GetIm() const {
    return im;
}

Complex Complex::operator+() {
    Complex complex;
    complex.re = re;
    complex.im = im;
    return complex;
}

Complex Complex::operator-() {
    Complex complex;
    complex.re = -re;
    complex.im = -im;
    return complex;
}

Complex& Complex::operator+=(const Complex& b) {
    re += b.re;
    im += b.im;
    return *this;
}

Complex& Complex::operator-=(const Complex& b) {
    re -= b.re;
    im -= b.im;
    return *this;
}

Complex& Complex::operator*=(const Complex& b) {
    Complex tmp;
    tmp.re = re * b.re - im * b.im;
    tmp.im = re * b.im + im * b.re;
    re = tmp.re;
    im = tmp.im;
    return *this;
}

Complex operator+(const Complex& a, const Complex& b) {
    Complex tmp = a;
    tmp += b;
    return tmp;
}

Complex operator-(const Complex& a, const Complex& b) {
    Complex tmp = a;
    tmp -= b;
    return tmp;
}

Complex operator*(const Complex& a, const Complex& b) {
    Complex tmp = a;
    tmp *= b;
    return tmp;
}

bool operator==(const Complex& a, const Complex& b) {
    return (a.GetRe() == b.GetRe() && a.GetIm() == b.GetIm());
}

bool operator!=(const Complex& a, const Complex& b) {
    return (a.GetRe() != b.GetRe() || a.GetIm() != b.GetIm());
}

template<typename T>
T Abs(const T& obj) {
    return obj > 0 ? obj : -obj;
}

double Abs(const Complex& a) {
    return sqrt(a.GetRe() * a.GetRe() + a.GetIm() * a.GetIm());
}
