#include <iostream>
#include <iomanip>
#include <cstring>
#include <stdexcept>
#include <new>
#include <iomanip>
#include <sstream>

template <typename TipEl>
class Matrica
{
	int br_redova, br_kolona;
	TipEl **elementi;
	char ime_matrice;
	static TipEl **AlocirajMemoriju(int br_redova, int br_kolona);
	static void DealocirajMemoriju(TipEl **elementi, int br_redova);
	void KopirajElemente(TipEl **elementi);
public:
	Matrica(int br_redova, int br_kolona, char ime = 0);
	Matrica(const Matrica &m);
	Matrica(Matrica &&m);
	~Matrica()
	{
		DealocirajMemoriju(elementi, br_redova);
	}
	Matrica &operator =(const Matrica &m);
	Matrica &operator =(Matrica &&m);

	template <typename TipE2>
	friend std::ostream &operator<<(std::ostream &stream, Matrica<TipE2> m);

	template <typename TipE2>
	friend std::istream &operator>>(std::istream &stream, Matrica<TipE2> &m);
//sabiranje 2 matrice
	template <typename TipE2>
	friend Matrica<TipE2> operator+(const Matrica<TipE2> &m1, const Matrica<TipE2> &m2);

	template <typename TipE2>
	friend Matrica<TipE2> &operator+=(Matrica<TipE2> &m1, const Matrica<TipE2> &m2);
//oduzimanje 2 matrice
	template <typename TipE2>
	friend Matrica<TipE2> operator-(const Matrica<TipE2> &m1, const Matrica<TipE2> &m2);

	template <typename TipE2>
	friend Matrica<TipE2> &operator-=(Matrica<TipE2> &m1, const Matrica<TipE2> &m2);
//mnozenje dvije matrice
	template <typename TipE2>
	friend Matrica<TipE2> operator*(const Matrica<TipE2> &m1, const Matrica<TipE2> &m2);

	template <typename TipE2>
	friend Matrica<TipE2> &operator*=(Matrica<TipE2> &m1, const Matrica<TipE2> &m2);

//mnozenje sa skalarom
	template <typename TipElemenata, typename TipE2>
	friend Matrica<TipElemenata> operator*(const Matrica<TipElemenata> &m1, TipE2 skalar);

	template <typename TipE1, typename TipE2>
	friend Matrica<TipE2> operator*(TipE1 skalar, const Matrica<TipE2> &m1);

	template <typename TipElemenata, typename TipE2>
	friend Matrica<TipElemenata> &operator*=(Matrica<TipElemenata> &m1, TipE2 skalar);
//indeksiranje sa provjerom
	TipEl &operator()(int i, int j)
	{
		if (i > br_redova || j > br_kolona || i <= 0 || j <= 0) {
			throw std::range_error("Neispravan indeks");
		}
		return elementi[i - 1][j - 1];
	}

	TipEl operator()(int i, int j) const
	{
		if (i > br_redova || j > br_kolona || i <= 0 || j <= 0) {
			throw std::range_error("Neispravan indeks");
		}
		return elementi[i - 1][j - 1];
	}
//indeksiranje bez provjere
	TipEl *&operator[](int i) const
	{
		return elementi[i];
	}

	operator std::string() const
	{
		std::string final = "";
		final += "{";
		for (int i = 0; i < br_redova; i++) {
			std::string red = "";
			red += "{";
			for (int j = 0; j < br_kolona; j++) {
				if (j == br_kolona - 1 ) {
					red += std::to_string(int(elementi[i][j]));
				} else {
					red += std::to_string(int(elementi[i][j]));
					red += ",";
				}
			}
			if (i == br_redova - 1 ) {
				red += "}";
			} else {
				red += "}";
				red += ",";
			}
			final += red;
		}
		final += "}";
		return final;
	}
};

template <typename TipEl>
TipEl ** Matrica<TipEl>::AlocirajMemoriju(int br_redova, int br_kolona)
{
	TipEl **elementi = new TipEl*[br_redova] {};
	try {
		for(int i = 0; i < br_redova; i++) elementi[i] = new TipEl[br_kolona] {};
	} catch(...) {
		DealocirajMemoriju(elementi, br_redova);
		throw;
	}
	return elementi;
}

template <typename TipEl>
void Matrica<TipEl>::DealocirajMemoriju(TipEl **elementi, int br_redova)
{
	for(int i = 0; i < br_redova; i++) delete[] elementi[i];
	delete[] elementi;
}

template <typename TipEl>
Matrica<TipEl>::Matrica(int br_redova, int br_kolona, char ime) :
	br_redova(br_redova), br_kolona(br_kolona), ime_matrice(ime),
	elementi(AlocirajMemoriju(br_redova, br_kolona)) {}

template <typename TipEl>
void Matrica<TipEl>::KopirajElemente(TipEl **elementi)
{
	for(int i = 0; i < br_redova; i++)
		for(int j = 0; j < br_kolona; j++)
			Matrica::elementi[i][j] = elementi[i][j];
}

template <typename TipEl>
Matrica<TipEl>::Matrica(const Matrica<TipEl> &m) : br_redova(m.br_redova),
	br_kolona(m.br_kolona), ime_matrice(m.ime_matrice),
	elementi(AlocirajMemoriju(m.br_redova, m.br_kolona))
{
	KopirajElemente(m.elementi);
}

template <typename TipEl>
Matrica<TipEl>::Matrica(Matrica<TipEl> &&m) : br_redova(m.br_redova),
	br_kolona(m.br_kolona), elementi(m.elementi), ime_matrice(m.ime_matrice)
{
	m.br_redova = 0;
	m.elementi = nullptr;
}

template <typename TipEl>
Matrica<TipEl> &Matrica<TipEl>::operator =(const Matrica<TipEl> &m)
{
	if(br_redova < m.br_redova || br_kolona < m.br_kolona) {
		TipEl **novi_prostor = AlocirajMemoriju(m.br_redova, m.br_kolona);
		DealocirajMemoriju(elementi, br_redova);
		elementi = novi_prostor;
	} else if(br_redova > m.br_redova)
		for(int i = m.br_redova; i < br_redova; i++) delete elementi[i];
	br_redova = m.br_redova;
	br_kolona = m.br_kolona;
	ime_matrice = m.ime_matrice;
	KopirajElemente(m.elementi);
	return *this;
}

template <typename TipEl>
Matrica<TipEl> &Matrica<TipEl>::operator =(Matrica<TipEl> &&m)
{
	std::swap(br_redova, m.br_redova);
	std::swap(br_kolona, m.br_kolona);
	std::swap(ime_matrice, m.ime_matrice);
	std::swap(elementi, m.elementi);
	return *this;
}


template <typename TipEl>
std::ostream &operator<<(std::ostream &stream, const Matrica<TipEl> m)
{
	int width = stream.width();
	for(int i = 0; i < m.br_redova; i++) {
		for(int j = 0; j < m.br_kolona; j++)
			std::cout << std::setw(width) << m.elementi[i][j];
		std::cout << std::endl;
	}
	return stream;
}

template <typename TipEl>
std::istream &operator>>(std::istream &stream, Matrica<TipEl> &m)
{
	for(int i = 0; i < m.br_redova; i++) {
		for(int j = 0; j < m.br_kolona; j++) {
			std::cout << m.ime_matrice << "(" << i + 1 << "," << j + 1 << ") = ";
			stream >> m.elementi[i][j];
		}
	}
	return stream;
}

template <typename TipE2>
Matrica<TipE2> operator+(const Matrica<TipE2> &m1, const Matrica<TipE2> &m2)
{
	if(m1.br_redova != m2.br_redova || m1.br_kolona != m2.br_kolona) {
		throw std::domain_error("Matrice nemaju jednake dimenzije!");
	}

	Matrica<TipE2> m3(m1.br_redova, m1.br_kolona);
	for(int i = 0; i < m1.br_redova; i++)
		for(int j = 0; j < m1.br_kolona; j++)
			m3.elementi[i][j] = m1.elementi[i][j] + m2.elementi[i][j];
	return m3;
}


template <typename TipE2>
Matrica<TipE2> operator-(const Matrica<TipE2> &m1, const Matrica<TipE2> &m2)
{
	if(m1.br_redova != m2.br_redova || m1.br_kolona != m2.br_kolona) {
		throw std::domain_error("Matrice nemaju jednake dimenzije!");
	}

	Matrica<TipE2> m3(m1.br_redova, m2.br_kolona);
	for(int i = 0; i < m1.br_redova; i++)
		for(int j = 0; j < m1.br_kolona; j++)
			m3.elementi[i][j] = m1.elementi[i][j] - m2.elementi[i][j];
	return m3;
}

template <typename TipE2>
Matrica<TipE2> &operator+=(Matrica<TipE2> &m1, const Matrica<TipE2> &m2)
{
	return m1 = m1 + m2;
}


template <typename TipE2>
Matrica<TipE2> &operator-=(Matrica<TipE2> &m1, const Matrica<TipE2> &m2)
{
	return m1 = m1 - m2;
}


template <typename TipElemenata>
Matrica<TipElemenata> operator*(const Matrica<TipElemenata> &m1, const Matrica<TipElemenata> &m2)
{
	if (m2.br_redova != m1.br_kolona ) {
		throw std::domain_error ("Matrice nisu saglasne za mnozenje");
	}
	Matrica<TipElemenata> c(m1.br_redova, m2.br_kolona, 'C');
	for (int i(0); i < c.br_redova; i++) {
		for (int j(0); j < c.br_kolona; j++) {
			c.elementi[i][j] = 0;
			for (int k(0); k < m1.br_kolona; k++) {
				TipElemenata temp = m1.elementi[i][k] * m2.elementi[k][j];
				c.elementi[i][j] += temp;
			}
		}
	}
	return c;
}

template <typename TipE2>
Matrica<TipE2> &operator*=(Matrica<TipE2> &m1, const Matrica<TipE2> &m2)
{
	return m1 = m1 * m2;
}


template <typename TipElemenata, typename TipE2>
Matrica<TipElemenata> operator*(const Matrica<TipElemenata> &m1, TipE2 skalar)
{
	Matrica<TipElemenata> c(m1.br_redova, m1.br_kolona, 'C');
	for (int i(0); i < m1.br_redova; i++) {
		for (int j(0); j < m1.br_kolona; j++) {
			c.elementi[i][j] = m1.elementi[i][j] * skalar;
		}
	}
	return c;
}


template <typename TipE1, typename TipE2>
Matrica<TipE2> operator*(TipE1 skalar, const Matrica<TipE2> &m1)
{
	return operator *(m1, skalar);
}

template <typename TipElemenata, typename TipE2>
Matrica<TipElemenata> &operator*=(Matrica<TipElemenata> &m1, TipE2 skalar)
{
	return m1 = m1 * skalar;
}


int main()
{
	int m,n;
	std::cout << "Unesi broj redova i kolona za matrice:\n";
	std::cin >> m >> n;
	try {
		Matrica<double> a(m, n, 'A'), b(m, n, 'B');
		std::cout << "Unesi matricu A:\n";
		std::cin >> a;
		std::cout << "Unesi matricu B:\n";
		std::cin >> b;
		const Matrica<double>c(a);
		for(int i = 0; i < 2; i++) {
			for(int j = 0; j < 2; j++)
				std::cout << c(i+1,j+1) << " ";
			std::cout << std::endl;
		}
		std::cout << "---------------" << std::endl;
		for(int i = 0; i < 2; i++) {
			for(int j = 0; j < 2; j++)
				std::cout << c[i][j] << " ";
			std::cout << std::endl;
		}
		std::cout << std::setw(5) << a << std::setw(5) << b;
	} catch(std::bad_alloc) {
		std::cout << "Nema dovoljno memorije!\n";
	} catch(std::domain_error e) {
		std::cout << e.what();
	} catch(std::range_error e) {
		std::cout << e.what();
	}

	return 0;
}
