#include <iostream>
#include <cmath>
#include <utility>
#include <typeindex>


class Kompleksni
{
	double re, im;
public:

	double getRe() const
	{
		return re;
	}

	double getIm() const
	{
		return im;
	}

	Kompleksni(double re = 0, double im = 0) : re(re), im(im) {}
	friend Kompleksni operator +(const Kompleksni &a)
	{
		return a;
	}
	friend Kompleksni operator -(const Kompleksni &a)
	{
		return {-a.re, -a.im};
	}
	friend Kompleksni operator +(const Kompleksni &a, const Kompleksni &b)
	{
		return {a.re + b.re, a.im + b.im};
	}
	friend Kompleksni operator -(const Kompleksni &a, const Kompleksni &b)
	{
		return Kompleksni(a.re - b.re, a.im - b.im);
	}
	friend Kompleksni operator *(const Kompleksni &a, const Kompleksni &b)
	{
		return {a.re * b.re - a.im * b.im, a.re * b.im + a.im * b.re};
	}
	friend Kompleksni operator /(const Kompleksni &a, const Kompleksni &b)
	{
		double pomocna = b.re * b.re + b.im * b.im;
		return {(a.re * b.re + a.im * b.im) / pomocna,
		        (a.im * b.re - a.re * b.im) / pomocna};
	}
	friend bool operator ==(const Kompleksni &a, const Kompleksni &b)
	{
		return a.re == b.re && a.im == b.im;
	}
	friend bool operator !=(const Kompleksni &a, const Kompleksni &b)
	{
		return !(a == b);
	}
	friend Kompleksni &operator +=(Kompleksni &a, const Kompleksni &b)
	{
		a.re += b.re;
		a.im += b.im;
		return a;
	}
	friend Kompleksni &operator -=(Kompleksni &a, const Kompleksni &b)
	{
		a.re -= b.re;
		a.im -= b.im;
		return a;
	}
	friend Kompleksni &operator *=(Kompleksni &a, const Kompleksni &b)
	{
		double pomocna = a.re * b.im + a.im * b.re;
		a.re = a.re * b.re - a.im * b.im;
		a.im = pomocna;
		return a;
	}


	friend Kompleksni &operator /=(Kompleksni &a, const Kompleksni &b)
	{
		double pom1 = a.im * b.re - a.re * b.im, pom2 = b.re * b.re + b.im * b.im;
		a.re = (a.re * b.re + a.im * b.im) / pom2;
		a.im = pom1 / pom2;
		return a;
	}
	friend std::ostream &operator <<(std::ostream &tok, const Kompleksni &a);

	friend std::istream &operator >>(std::istream &tok, Kompleksni &a);
	friend double real(const Kompleksni &a)
	{
		return a.re;
	}
	friend double imag(const Kompleksni &a)
	{
		return a.im;
	}
	friend double abs(const Kompleksni &a);
	friend double arg(const Kompleksni &a);
	friend Kompleksni conj(const Kompleksni &a)
	{
		return {a.re, -a.im};
	}
	friend Kompleksni sqrt(const Kompleksni &a);
};

std::istream &operator >>(std::istream &tok, Kompleksni &a)
{
	char znak;
	tok >> std::ws; // "Progutaj" razmake...
	if(tok.peek() != '(') {
		tok >> a.re;
		a.im = 0;
	} else {
		tok >> znak >> a.re >> znak;
		if(znak != ',') tok.setstate(std::ios::failbit);
		tok >> a.im >> znak;
		if(znak != ')') tok.setstate(std::ios::failbit);
	}
	return tok;
}

std::ostream &operator <<(std::ostream &tok, const Kompleksni &a)
{
	bool sign = true;
	if (a.re == 0) {
		sign = false;

	} else {
		tok << std::noshowpos << a.re;
	}


	if (a.im > 1 || a.im < -1) {
		if (sign) {
			tok <<	std::showpos << a.im << "i";
		} else {
			tok << std::noshowpos << a.im << "i";
		}
	} else if (a.im == 0) {
		if (!sign) {
			tok << 0;
		}
	} else if (a.im == -1) {
		tok << "-i";
	} else if (a.im == 1) {
		if (sign) {
			tok << "+i";
		} else {
			tok <<"i";
		}
	}
	return tok;
}




double abs(const Kompleksni &a)
{
	return std::sqrt(a.re * a.re + a.im * a.im);
}

double arg(const Kompleksni &a)
{
	return std::atan2(a.im, a.re);
}

namespace aaa
{
	double abs(const Kompleksni &a)
	{
		return std::sqrt(a.getRe() * a.getRe() + a.getIm() * a.getIm());
	}
}


namespace std
{
	double arg(const Kompleksni &a)
	{
		return std::atan2(a.getIm(), a.getRe());
	}

}


Kompleksni sqrt(const Kompleksni &a)
{
	double rho = std::sqrt(aaa::abs(a));
	double phi = std::arg(a) / 2;
	return {rho * std::cos(phi), rho * std::sin(phi)};
}


int main ()
{
	std::cout  << Kompleksni(2, 1) << " " << Kompleksni(2, 5) << " " << Kompleksni(2, -1) << " "
	           << Kompleksni(2, -5) << " " << Kompleksni(-1, 1) << " " << Kompleksni(-1, 3) << " "
	           << Kompleksni(-1, -1) << " " << Kompleksni(-1, -5) << std::endl;

	return 0;
}
