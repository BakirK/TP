#include <iostream>
#include <vector>
#include <stdexcept>
#include <iomanip>
#include <cmath>
#include <limits>

typedef std::vector<std::vector<int>> matrica;

int NajvecaSirina (std::vector<std::vector<int>> matrica) {
	if (matrica.size() == 0) {
		return 0;
	} else if (matrica.at(0).size() == 0) {
		return 0;
	}
	long long int max (0);
	for (int i = 0; i < matrica.size(); i++) {
    	for (int j = 0; j < matrica.at(i).size(); j++) {
    	    if (std::abs(static_cast<long long int>(matrica.at(i).at(j))) > max) {
    	        max = std::abs(matrica.at(i).at(j));    
    	    }
    	}
	}
	int sirina (0);
	while(max != 0) {
		sirina++;
		max /= 10;
	}
	
	for (int i = 0; i < matrica.size(); i++) {
    	for (int j = 0; j < matrica.at(i).size(); j++) {
    	    int sirinaTemp = 0;
    	    unsigned int temp = std::abs(matrica.at(i).at(j));
    	    while (temp != 0) {
    	        sirinaTemp++;
    	        temp /= 10;
    	    }
    	    if (sirinaTemp == sirina && matrica.at(i).at(j) < 0) {
    	        sirina++;
    	        break;
    	    }
    	}
	}
	return sirina;
}




matrica KroneckerovProizvod (matrica m1, matrica m2) {
	try {
		int sirinaM1  (m1.at(0).size());
		bool parametriM1 (true);
		/*
		if (sirina == 0) {
			sirina1 = true;
		}*/
		for (int i = 1; i < m1.size(); i++) {
			if (sirinaM1 != m1.at(i).size()) {
				parametriM1 = false;
				break;
			}
		}
		
		int sirinaM2 (m2.at(0).size());
		bool parametriM2 (true);
		for (int i = 1; i < m2.size(); i++) {
			if (sirinaM2 != m2.at(i).size()) {
				parametriM2 = false;
				break;
			}
		}
		
		if (!parametriM1 && parametriM2) {
			throw std::domain_error ("Prvi parametar nema formu matrice");
		}
		else if (parametriM1 && !parametriM2) {
			throw std::domain_error ("Drugi parametar nema formu matrice");

		} 
		else if (!parametriM1 && !parametriM2) {
			throw std::domain_error ("Parametri nemaju formu matrice");
		}
		
		
		matrica m3 ( m1.size() * m2.size() );
		for (int i = 0; i < m3.size(); i++) {
		    m3.at(i).resize( m1.at(0).size() * m2.at(0).size() );
		}
		
		for (int i = 0; i < m1.size(); i++) {
			for (int j = 0; j < m1.at(0).size(); j++) {
				int startRow = i * m2.size();
				int startColumn = j * m2.at(0).size();
	    	    for (int k = 0; k < m2.size(); k++) {
	    			for (int n = 0; n < m2.at(0).size(); n++) {
	    	    		m3.at(startRow + k).at(startColumn + n) = m1.at(i).at(j) * m2.at(k).at(n);
	    			}
	    		}
	    	}
		}
		return m3;
	}
	catch (std::domain_error belaj) {
		std::cout << belaj.what() << std::endl;
		matrica m3;
		return m3;
	}
	catch (...) {
		matrica m3;
		return m3;
	}
}

int main ()
{
		//unos prve
		int m1, n1;
	    while (true) {
	        std::cout << "Unesite dimenzije prve matrice: ";
	        std::cin >> m1 >> n1;
	        if (n1 <= 0 || m1 <= 0) {
	            std::cout << "Broj elemenata mora biti veci od 0!" << std::endl;
	            return 0;
	        }
	        break;
	    }
	    std::cout << "\nUnesite elemente prve matrice: ";
	    matrica matrix1 (m1);
	    for (int i = 0; i < m1; i++) {
	    	for (int j = 0; j < n1; j++) {
	    		int temp;
	    		std::cin >> temp;
	        	matrix1.at(i).push_back(temp);
	    	}
		}
		
	    //unos druge
		int m2, n2;
	    while (true) {
	        std::cout << "\nUnesite dimenzije druge matrice: ";
	        std::cin >> m2 >> n2;
	        if (n2 <= 0 || m2 <= 0) {
	            std::cout << "Broj elemenata mora biti veci od 0!" << std::endl;
	            return 0;
	        }
	        break;
	    }
	    std::cout << "\nUnesite elemente druge matrice: ";
	    matrica matrix2(m2);
	    
	    for (int i = 0; i < m2; i++) {
	    	for (int j = 0; j < n2; j++) {
	    		int temp;
	    		std::cin >> temp;
	        	matrix2.at(i).push_back(temp);
	    	}
		}
	    
	    std::cout << std::endl;
	    matrica proizvod = KroneckerovProizvod(matrix1, matrix2);
	    int sirina = NajvecaSirina(proizvod) + 1;
		std::cout << "\nNjihov Kroneckerov proizvod glasi: \n";

		for (int i = 0; i < proizvod.size(); i++) {
			for (int j = 0; j < proizvod.at(0).size(); j++) {
				std::cout << std::setw(sirina) << std::right << proizvod.at(i).at(j);
			}	
			std::cout << std::endl;
		}
	return 0;
}