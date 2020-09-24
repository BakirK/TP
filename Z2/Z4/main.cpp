/* TP, 2018/2019
*/
#include <iostream>
#include <stdexcept>
#include <algorithm>


template <typename TipElemenata>
void UnistiFragmentiranuMatricu(TipElemenata **mat, int br_redova) {
	if(!mat) return;
	for(int i = 0; i < br_redova; i++) delete[] mat[i];
	delete[] mat;
	mat = nullptr;
}

template <typename TipElemenata>
void UnistiKontinualnuMatricu(TipElemenata **mat, int br_redova) {
	if(!mat) return;
	delete[] mat[0];
	delete[] mat;
}

long long int StirlingBrojFunction(long long int n, long long int k) {
    if (k > n){
        return 0;
    } 
    else if (k == n) {
        return 1;
    }
    else if (k == 0 && n == 0) {
        return 1;
    }
    else if (k == 0) {
        return 0;
    }
    else {
        return StirlingBrojFunction(n - 1, k - 1) + k * StirlingBrojFunction(n - 1, k);
    }
}

long long int** StirlingoviBrojeviV1 (long long int n) {
    if (n <= 0) {
        throw std::domain_error("Parametar ne smije biti negativan");
    }
    else if (n >= 23) {
        throw std::range_error("Parametar prevelik za raspoloživu memoriju");
    }
    
    
    long long int **matrica = nullptr;
    try{
        matrica = new long long int* [n + 1]{};
        for (long long int i (0); i <= n; i++ ) {
            matrica[i] = new long long int[i + 1];
        }
        
        for (long long int i (0); i <= n; i++ ) {
            for (long long int j (0); j <= i; j++) {
                matrica[i][j] = StirlingBrojFunction(i, j);
            }
        }
    }
    catch(std::bad_alloc) {
        UnistiFragmentiranuMatricu(matrica, n + 1);
        throw std::bad_alloc();
    }
    catch(std::domain_error error) {
        UnistiFragmentiranuMatricu(matrica, n + 1);
        throw std::domain_error(error.what());
    }
    catch(std::range_error) {
        UnistiFragmentiranuMatricu(matrica, n + 1);
        throw std::range_error("Parametar prevelik za raspoloživu memoriju");
    }
    
    catch(...) {
        UnistiFragmentiranuMatricu(matrica, n + 1);
        throw std::range_error("Parametar prevelik za raspoloživu memoriju");
        
    }
    return matrica;
}


int duzina (int a) {
    if (a == 1) {
        return 1;
    }
    if (a == 2) {
        return 3;
    }
    int suma (0);
    int brojac (1);
    for (int i(0); i < a; i++) {
        suma += brojac;
        brojac++;
    }
    return suma;
}

long long int** StirlingoviBrojeviV2 (long long int n) {
    if (n <= 0) {
        throw std::domain_error("Parametar ne smije biti negativan");
    }
    else if (n >= 23) {
        throw std::range_error("Parametar prevelik za raspoloživu memoriju");
    }
    int sum (0);
    for (int i (0); i <= n; i++) {
        sum += i + 1;
    }
    long long int **matrica = nullptr;
    try{
        matrica = new long long int* [n + 1]{};
        matrica[0] = new long long int[sum];
        int brojac (0);
        for (long long int i (1); i <= n; i++ ) {
            int temp = duzina(i);
            matrica[i] = matrica[0] + temp;
            brojac++;
        }
        int index (0);
        for (long long int i (0); i <= n; i++ ) {
            for (long long int j (0); j <= i; j++) {
                long long int temp = StirlingBrojFunction(i, j);
                matrica[i][j] = temp;
                index++;
            }
        }
        return matrica;
    }
    catch(std::bad_alloc) {
        UnistiFragmentiranuMatricu(matrica, n + 1);
        throw std::bad_alloc();
    }
    catch(std::domain_error error) {
        UnistiKontinualnuMatricu(matrica, n + 1);
        throw std::domain_error(error.what());
    }
    catch(std::range_error) {
        UnistiKontinualnuMatricu(matrica, n + 1);
        throw std::range_error("Parametar prevelik za raspoloživu memoriju");
    }
    
    catch(...) {
        UnistiKontinualnuMatricu(matrica, n + 1);
        throw std::range_error("Parametar prevelik za raspoloživu memoriju");
    }
    return matrica;
}

int main ()
{
    
    long long int n;
    std::cin >> n;
    //std::cout << std::endl;
    long long int **matrica = nullptr;
    
    try {
        matrica = StirlingoviBrojeviV1(n);
        for (long long int i (0); i <= n; i++ ) {
            for (long long int j (0); j <= i; j++) {
                std::cout << matrica[i][j] << " ";
            }
            std::cout << std::endl;
        }
        UnistiFragmentiranuMatricu(matrica, n + 1);
    }
    catch(std::domain_error error) {
        UnistiFragmentiranuMatricu(matrica, n + 1);
        std::cout << "Izuzetak: " << error.what() << std::endl;
    }
    catch(std::range_error error) {
        UnistiFragmentiranuMatricu(matrica, n + 1);
        std::cout << error.what() << std::endl;
    }
    catch(std::bad_alloc) {
        UnistiFragmentiranuMatricu(matrica, n + 1);
        std::cout << "Nedovoljno memorije" << std::endl;
    }
    catch(...) {
        UnistiFragmentiranuMatricu(matrica, n + 1);
        std::cout << "Nepoznata greska" << std::endl;
        
    }
    
    long long int **matricaKontinualna = nullptr;
    std::cout << std::endl;
    try {
        matricaKontinualna = StirlingoviBrojeviV2(n);
        int index (0);
        //ispisujem tu matricu
        for (int i (0); i <= n; i++ ) {
            for (int j (0); j <= i; j++) {
                //std::cout << matricaKontinualna[0][index] << " ";
                std::cout << matricaKontinualna[i][j] << " ";
                index++;
            }
            std::cout << std::endl;
        }
        UnistiKontinualnuMatricu(matricaKontinualna, n+1);
    }
    catch(std::domain_error error) {
        UnistiKontinualnuMatricu(matricaKontinualna, n+1);
        std::cout << "Izuzetak: " << error.what() << std::endl;
    }
    catch(std::range_error error) {
        UnistiFragmentiranuMatricu(matrica, n + 1);
        std::cout << error.what() << std::endl;
    }
    catch(std::bad_alloc) {
        UnistiKontinualnuMatricu(matricaKontinualna, n+1);
        std::cout << "Nedovoljno memorije" << std::endl;
    }
    catch(...) {
        UnistiKontinualnuMatricu(matricaKontinualna, n+1);
        std::cout << "Nepoznata greska" << std::endl;
    }
	return 0;
}