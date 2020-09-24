#include <iostream>
#include <type_traits>
#include <vector>
#include <deque>

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


template <typename TipElemenata>						
auto KreirajDinamickuKopiju2D (TipElemenata struktura) -> typename std::remove_reference<decltype(struktura.at(0).at(0))>::type** {
	int broj = struktura.size();
	auto temp = struktura.at(0);
	typename std::remove_reference<decltype(struktura.at(0).at(0))>::type **kopija = nullptr;
	try{
		kopija = new  typename std::remove_reference<decltype(struktura.at(0).at(0))>::type* [broj];
		
		for(int i = 0; i < struktura.size(); i++) {
			kopija[i] = new typename std::remove_reference<decltype(struktura.at(i).at(0))>::type [struktura.at(i).size()];
			//std::cout <<  struktura.at(0).size()<< std::endl;
			for(int j = 0; j < struktura.at(i).size(); j++) {
				kopija[i][j] = struktura.at(i).at(j);
			} 
		}
		return kopija;
	}
	catch(std::bad_alloc ){
		UnistiMatricu(kopija, struktura.size());
		kopija = nullptr;
		throw std::bad_alloc();
	} 
	catch (...) {
		UnistiMatricu(kopija, struktura.size());
		kopija = nullptr;
		throw;
	}
	return kopija;
}




int main ()
{
	std::cout << "Unesite broj redova kvadratne matrice: ";
	int n;
	std::cin >> n;
	int **niz = nullptr;
	try{
	std::vector<std::deque<int> > matrica (n);
	std::cout << "Unesite elemente matrice: ";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int broj;
			std::cin >> broj;
			matrica.at(i).push_back(broj);
		}
	}
	
		niz = KreirajDinamickuKopiju2D(matrica);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
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
		std::cout << "Nedovoljno memorije" << std::endl;
		niz = nullptr;
	}
	catch (...) {
		UnistiMatricu(niz, n);
		niz = nullptr;
		std::cout << "Nedovoljno memorije" << std::endl;
	}
	return 0;
}