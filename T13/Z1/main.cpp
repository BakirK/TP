#include <iostream>
#include <stdexcept>
#include <cmath>
#include <vector>
#include <memory>
#include <cctype>

class Lik
{
public:
	virtual void IspisiSpecificnosti() const = 0;
	virtual double DajObim() const = 0;
	virtual double DajPovrsinu() const = 0;
	void Ispisi() const
	{
		IspisiSpecificnosti();
		std::cout << "Obim: " << DajObim() << " Povrsina: " << DajPovrsinu() << std::endl;
	}
	virtual ~Lik() {};
};

class Krug: public Lik
{
	double r;
	static constexpr double PI = 3.141592653589793;
public:
	Krug(double r)
	{
		if (r <= 0) {
			throw std::domain_error("Neispravni parametri");
		} else {
			this->r = r;
		}
	}
	void IspisiSpecificnosti() const override
	{
		std::cout << "Krug poluprecnika " << r << std::endl;
	}
	double DajObim() const override
	{
		return 2 * PI * r;
	}
	double DajPovrsinu() const override
	{
		return r * r * PI;
	}

};

class Pravougaonik: public Lik
{
	double a, b;
public:
	Pravougaonik (double a, double b)
	{
		if (a <= 0 || b <= 0) {
			throw std::domain_error("Neispravni parametri");
		} else {
			this->a = a;
			this->b = b;
		}
	}
	void IspisiSpecificnosti() const override
	{
		std::cout << "Pravougaonik sa stranicama duzine " << a << " i " << b << std::endl;
	}
	double DajObim() const override
	{
		return (2*a + 2*b);
	}
	double DajPovrsinu() const override
	{
		return (a * b);
	}

};

class Trougao: public Lik
{
	double a, b, c;
public:
	Trougao(double a, double b, double c)
	{
		if ( a == b && b == c && c == a && a > 0 && b > 0 && c > 0) {
			this->a = a;
			this->b = b;
			this->c = c;
		} else {
			if (a+b <=c || a+c <= b || b + c <= a || a <=0 || b <=0 || c <= 0) {
				throw std::domain_error("Neispravni parametri");
			} else {
				this->a = a;
				this->b = b;
				this->c = c;
			}
		}
	}
	void IspisiSpecificnosti() const override
	{
		std::cout << "Trougao sa stranicama duzine " << a << ", " << b << " i " << c << std::endl;
	}
	double DajObim() const override
	{
		return a + b + c;
	}
	double DajPovrsinu() const override
	{
		double s = DajObim() / 2;
		return std::sqrt(s * (s - a) * (s - b) * (s - c));
	}

};

int main ()
{
	std::cout << "Koliko zelite likova: ";
	int n;
	std::cin >> n;
	std::vector<std::shared_ptr<Lik>> v(0);
	int i(0);
	while (i < n) {
		std::cout << "Lik " << i + 1 << ": ";
		char l;
		std::cin >> l;
		switch(l) {
		case 'K': {
			double r;
			std::cin >> r;
			if (!std::cin) {
				std::cout << "Pogresni podaci, ponovite unos!" << std::endl;
				std::cin.clear();
				std::cin.ignore(1000, '\n');
				i--;
			} else {
				if (std::cin.peek() != '\n') {
					std::cout << "Pogresni podaci, ponovite unos!" << std::endl;
					std::cin.ignore(1000, '\n');
					i--;
				} else {
					try {
						v.push_back(std::make_shared<Krug>(r));
					} catch( std::domain_error e) {
						//std::cout << e.what();
						std::cin.ignore(1000, '\n');
						std::cout << "Pogresni podaci, ponovite unos!" << std::endl;
						i--;
					}
				}
			}
			break;
		}
		case 'P': {
			if (isalpha(std::cin.peek())) {
				std::cout << "Pogresni podaci, ponovite unos!" << std::endl;
				std::cin.ignore(1000, '\n');
				i--;
			} else {
				double a, b;
				std::cin >> a;
				if (std::cin.peek() != ',') {
					std::cout << "Pogresni podaci, ponovite unos!" << std::endl;
					std::cin.ignore(1000, '\n');
					i--;
				} else {
					std::cin.get();
					if (isalpha(std::cin.peek())) {
						std::cout << "Pogresni podaci, ponovite unos!" << std::endl;
						std::cin.ignore(1000, '\n');
						i--;
					} else {
						std::cin >> b;
						try {
							v.push_back(std::make_shared<Pravougaonik>(a, b));
						} catch( std::domain_error e) {
							//std::cout << e.what();
							std::cin.ignore(1000, '\n');
							std::cout << "Pogresni podaci, ponovite unos!" << std::endl;
							i--;
						}
					}
				}
			}

			break;
		}
		case 'T': {
			double a, b, c;
			std::cin >> a;
			if (!std::cin) {
				std::cout << "Pogresni podaci, ponovite unos!" << std::endl;
				std::cin.clear();
				std::cin.ignore(1000, '\n');
				i--;
			} else {
				if (std::cin.peek() != ',') {
					std::cout << "Pogresni podaci, ponovite unos!" << std::endl;
					std::cin.ignore(1000, '\n');
					i--;
				} else {
					std::cin.get();
					std::cin >> b;
					if (!std::cin) {
						std::cout << "Pogresni podaci, ponovite unos!" << std::endl;
						std::cin.clear();
						std::cin.ignore(1000, '\n');
						i--;
					} else {
						if (std::cin.peek() != ',') {
							std::cout << "Pogresni podaci, ponovite unos!" << std::endl;
							std::cin.ignore(1000, '\n');
							i--;
						} else {
							std::cin.get();
							std::cin >> c;
							if (!std::cin) {
								std::cout << "Pogresni podaci, ponovite unos!" << std::endl;
								std::cin.clear();
								std::cin.ignore(1000, '\n');
								i--;
							} else {
								try {
									v.push_back(std::make_shared<Trougao>(a, b, c));
								} catch( std::domain_error e) {
									//std::cout << e.what();
									std::cin.ignore(1000, '\n');
									std::cout << "Pogresni podaci, ponovite unos!" << std::endl;
									i--;
								}
							}
						}
					}
				}
			}
			break;
		}
		default: {
			std::cout << "Pogresni podaci, ponovite unos!" << std::endl;
			std::cin.ignore(1000, '\n');
			i--;
			break;
		}
		}
		i++;
	}
	std::cout << std::endl;
	auto it(v.begin());
	while(it != v.end()) {
		(*it)->Ispisi();
		it++;
	}
	return 0;
}
