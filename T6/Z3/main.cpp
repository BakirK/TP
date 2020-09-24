#include <iostream>
#include <vector>
#include <type_traits>
#include <stdexcept>
#include <cmath>


//maznuto sa predavanja
template <typename TipElemenata>
void UnistiMatricu(TipElemenata **mat, int br_redova) {
	if(!mat) return;
	for(int i = 0; i < br_redova; i++) delete[] mat[i];
	delete[] mat;
}

template <typename TipElemenata>
TipElemenata **StvoriMatricu(int br_redova) {
	TipElemenata **mat = new TipElemenata*[br_redova]{};
	try {
		for(int i = 0; i < br_redova; i++)
		 mat[i] = new TipElemenata[(2 * i) + 1];
	}
	catch(...) {
		UnistiMatricu(mat, br_redova);
		throw;
	}
	 return mat;
}





int **KreirajTrougao (int n) {
	int **niz = nullptr;
	if (n <= 0) {
			throw std::domain_error("Broj redova mora biti pozitivan");
		}
	try {
		/*
		niz = new int*[n]{};
		for (int i = 0; i < n; i++) {
			niz[i] = new int*[(2 * i) + 1];
		}*/
		niz = StvoriMatricu<int>(n);
		for (int i = 0; i < n; i++) {
			int brojac = -1 * (i+1);
			for (int j = 0; j < (i * 2) + 1; j++) {
				niz[i][j] = std::abs(brojac);
				brojac++;
				if (brojac == 0) {
					brojac+=2;
				}
			}
			
		}
		return niz;
	}
	catch (std::domain_error a) {
		throw std::domain_error("Broj redova mora biti pozitivan");
	}
	catch (std::bad_alloc a) {
		UnistiMatricu(niz, n);
		niz = nullptr;
		throw std::bad_alloc();
	}
	catch (...) {
		UnistiMatricu(niz, n);
		niz = nullptr;
		throw std::bad_alloc();
	}
	return niz;
}



int main ()
{
	std::cout << "Koliko zelite redova: ";
	int n;
	std::cin >> n;
	int **niz = nullptr;
	try{
		niz = KreirajTrougao(n);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < (i * 2) + 1; j++) {
				std::cout << niz[i][j] << " ";
			}
			std::cout << std::endl;
		}
		UnistiMatricu(niz, n);
	}
	catch (std::domain_error a) {
		UnistiMatricu(niz, n);
		niz = nullptr;
		std::cout << "Izuzetak: " << a.what() << std::endl;
	}
	catch (std::bad_alloc a) {
		UnistiMatricu(niz, n);
		std::cout << "Izuzetak: Nedovoljno memorije!" << std::endl;
		niz = nullptr;
	}
	catch (...) {
		UnistiMatricu(niz, n);
		niz = nullptr;
		std::cout << "Izuzetak: Nedovoljno memorije!" << std::endl;
	}
	return 0;
}