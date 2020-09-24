#include <iostream>
#include <type_traits>
#include <vector>
#include <deque>

//maznuto sa predavanja
template <typename TipElemenata>
void UnistiMatricu(TipElemenata **mat, int br_redova) {
	if(!mat) return;
	delete[] mat[0];
	delete[] mat;
}

/*
TipElemenata **mat = new TipElemenata*[br_redova]{};
	try {
		mat[0] = new int[br_redova * br_redova];
		for(int i = 1; i < br_redova; i++)
		 mat[i] = mat[i - 1] + ((2 * i - 1));
*/

template <typename TipElemenata>						
auto KreirajDinamickuKopiju2D (TipElemenata struktura) -> typename std::remove_reference<decltype(struktura.at(0).at(0))>::type** {
	//int broj = struktura.size();
	auto temp = struktura.at(0);
	int brojElemenata (0);
	int nizTemp[100];
	int total (0);
	for(int i = 0; i < struktura.size(); i++) {
		//brojElemenata += struktura.at(i).size();
		brojElemenata++;
		total += struktura.at(i).size();
		nizTemp[i] = struktura.at(i).size();
	}
	
	//typename std::remove_reference<decltype(struktura.at(0).at(0))>::type **kopija = nullptr;
	typename std::remove_reference<decltype(struktura.at(0).at(0))>::type **kopija = new typename std::remove_reference<decltype(struktura.at(0).at(0))>::type* [struktura.size()]{};
	
	try{
		kopija[0] = new  typename std::remove_reference<decltype(struktura.at(0).at(0))>::type[total];
		 
		
		for(int i = 1; i < struktura.size(); i++) {
			//kopija[i] = new typename std::remove_reference<decltype(struktura.at(i).at(0))>::type [struktura.at(i).size()];
			//std::cout <<  struktura.at(0).size()<< std::endl;
			kopija[i] = kopija[i - 1] + nizTemp[i - 1];
		}
		
		int brojac (0);
		for(int i = 0; i < struktura.size(); i++) {
			//kopija[i] = new typename std::remove_reference<decltype(struktura.at(i).at(0))>::type [struktura.at(i).size()];
			//std::cout <<  struktura.at(0).size()<< std::endl;
			for(int j = 0; j < struktura.at(i).size(); j++) {
				kopija[0][brojac] = struktura.at(i).at(j);
				brojac++;
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
	
	/*
	try {
   std::vector<std::vector<std::string>> m {{"Ja"}, { "opet", "testiram"}, {"program","na","stringove"}};
    auto m1(KreirajDinamickuKopiju2D(m));
    for(int i = 0; i < 3; i++) {
      for(int j = 0; j <=i; j++) std::cout << m1[i][j] << " ";
      std::cout << std::endl;
    }
    delete[] m1[0];
    delete[] m1;
  }
  catch(std::bad_alloc) {
    std::cout << "Nedovoljno memorije!";
  }*/
	return 0;
}