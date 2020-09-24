#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <new>
#include <vector>

template <typename TipElemenata>
struct Matrica {
    int br_redova, br_kolona;
    TipElemenata **elementi = nullptr; // VEOMA BITNA INICIJALIZACIJA!
};


template <typename TipElemenata>
void UnistiMatricu(Matrica<TipElemenata> &mat)
{
    if(!mat.elementi) return;
    for(int i = 0; i < mat.br_redova; i++) delete[] mat.elementi[i];
    delete[] mat.elementi;
    mat.elementi = nullptr;
}


template <typename TipElemenata>
Matrica<TipElemenata> StvoriMatricu(int br_redova, int br_kolona)
{
    Matrica<TipElemenata> mat;
    mat.br_redova = br_redova;
    mat.br_kolona = br_kolona;
    mat.elementi = new TipElemenata*[br_redova] {};
    try {
        for(int i = 0; i < br_redova; i++) {
            mat.elementi[i] = new TipElemenata[br_kolona];
            for (int j(0); j < br_kolona; j++) {
                mat.elementi[i][j] = 0;
            }
        }
    } catch(...) {
        UnistiMatricu(mat);
        throw;
    }
    return mat;
}

template <typename TipElemenata>
Matrica<TipElemenata> StvoriJedinicnuMatricu(int br_redova, int br_kolona)
{
    Matrica<TipElemenata> mat;
    mat.br_redova = br_redova;
    mat.br_kolona = br_kolona;
    mat.elementi = new TipElemenata*[br_redova] {};
    try {
        for(int i = 0; i < br_redova; i++) {
            mat.elementi[i] = new TipElemenata[br_kolona];
            for (int j(0); j < br_kolona; j++) {
                if (i == j) {
                    mat.elementi[i][j] = 1;
                } else {
                    mat.elementi[i][j] = 0;
                }
            }
        }

    } catch(...) {
        UnistiMatricu(mat);
        throw;
    }
    return mat;
}


template <typename TipElemenata>
void UnesiMatricu(char ime_matrice, Matrica<TipElemenata> &mat)
{
    for(int i = 0; i < mat.br_redova; i++)
        for(int j = 0; j < mat.br_kolona; j++) {
            std::cout << ime_matrice
                      << "(" << i + 1 << "," << j + 1 << ") = ";
            std::cin >> mat.elementi[i][j];
        }
}


template <typename TipElemenata>
void IspisiMatricu(Matrica<TipElemenata> &mat, int sirina_ispisa, int preciznost = 6, bool treba_brisati = false)
{
    for(int i = 0; i < mat.br_redova; i++) {
        for(int j = 0; j < mat.br_kolona; j++) {
            std::cout << std::setw(sirina_ispisa) << std::setprecision(preciznost) << mat.elementi[i][j];
        }
        std::cout << std::endl;
    }
    if (treba_brisati) {
        UnistiMatricu(mat);
    }
}


template <typename TipElemenata>
void ZbirMatrica(Matrica<TipElemenata> &A, const Matrica<TipElemenata> &B)
{
    if(A.br_redova != B.br_redova || A.br_kolona != B.br_kolona)
        throw std::domain_error("Matrice nemaju jednake dimenzije!");
    for(int i = 0; i < A.br_redova; i++)
        for(int j = 0; j < A.br_kolona; j++)
            A.elementi[i][j] = A.elementi[i][j] + B.elementi[i][j];
}



template <typename TipElemenata, typename TipElemenata2>
void PomnoziSaSkalarom(Matrica<TipElemenata> &mat, TipElemenata2 skalar)
{
    for(int i = 0; i < mat.br_redova; i++) {
        for(int j = 0; j < mat.br_kolona; j++) {
            mat.elementi[i][j] *= skalar;
        }
    }
}


template <typename TipElemenata>
Matrica<TipElemenata> ProduktMatrica (const Matrica<TipElemenata> &a, const Matrica<TipElemenata> &b)
{
    if (b.br_redova != a.br_kolona ) {
        throw std::domain_error ("Matrice nisu saglasne za mnozenje");
    }
    Matrica<TipElemenata> c;
    try {
        c = StvoriMatricu<TipElemenata>(a.br_redova, b.br_kolona);
    } catch (std::bad_alloc) {
        UnistiMatricu(c);
        std::cout << "Problem sa memorijom u produktu matrice.";
    }


    for (int i(0); i < c.br_redova; i++) {
        for (int j(0); j < c.br_kolona; j++) {
            c.elementi[i][j] = 0;
            for (int k(0); k < a.br_kolona; k++) {
                TipElemenata temp = a.elementi[i][k] * b.elementi[k][j];
                c.elementi[i][j] += temp;
            }
        }
    }
    return c;
}


template <typename TipElemenata>
void KopirajMatricu(Matrica<TipElemenata> &a, const Matrica<TipElemenata> &b)
{
    for (int i(0); i < b.br_redova; i++) {
        for (int j(0); j < b.br_kolona; j++) {
            TipElemenata temp = b.elementi[i][j];
            a.elementi[i][j] = temp;
        }
    }
}


template <typename TipElemenata>
Matrica<TipElemenata> MatricniPolinom(const Matrica<TipElemenata> &a, std::vector<double> polinom)
{
    int i (0);
    if (a.br_kolona != a.br_redova) {
        throw std::domain_error ("Matrica mora biti kvadratna");
    }
    Matrica<TipElemenata> povratna;
    bool brisi(true);
    try {
        povratna = StvoriMatricu<TipElemenata>(a.br_redova, a.br_kolona);
    } catch (std::bad_alloc) {
        UnistiMatricu(povratna);
        std::cout << "Problemi sa memorijom u MatricniPolinom";
    }
    Matrica<TipElemenata> prethodniStepenMatrice;
    while (i < polinom.size()) {
        if (brisi) {
            brisi = false;
            UnistiMatricu<TipElemenata>(povratna);
        }
        
        if (!i) {
            try {
                povratna = StvoriJedinicnuMatricu<TipElemenata>(a.br_redova, a.br_kolona);
                PomnoziSaSkalarom(povratna, polinom.at(i));

                prethodniStepenMatrice = StvoriMatricu<TipElemenata>(a.br_redova, a.br_kolona);
                KopirajMatricu(prethodniStepenMatrice, a);
            } catch (std::bad_alloc) {
                UnistiMatricu(povratna);
                std::cout << "Problemi sa memorijom u MatricniPolinom";
            }
            /*std::cout << " jedinicna:" << std::endl;
            IspisiMatricu(povratna, 3);*/
        }

        else if (i == 1) {
            Matrica<TipElemenata> temp;
            try {
                temp = StvoriMatricu<TipElemenata>(a.br_redova, a.br_kolona);
                KopirajMatricu(temp, a);
                PomnoziSaSkalarom<TipElemenata>(temp, polinom.at(i));
                ZbirMatrica(povratna, temp);
                /*std::cout << " prvi stepen:" << std::endl;
                IspisiMatricu(temp, 3);*/
            } catch(std::bad_alloc) {
                UnistiMatricu(temp);
                std::cout << "Problemi sa memorijom u MatricniPolinom";
            }
            UnistiMatricu(temp);

        }

        else {
            Matrica<TipElemenata> temp (ProduktMatrica(prethodniStepenMatrice, a));
            KopirajMatricu(prethodniStepenMatrice, temp);
            /*std::cout << i << "-ti stepen:" << std::endl;
            IspisiMatricu(prethodniStepenMatrice, 3);*/
            PomnoziSaSkalarom(temp, polinom.at(i));
            ZbirMatrica(povratna, temp);
            UnistiMatricu(temp);
        }
        i++;
    }
    UnistiMatricu(prethodniStepenMatrice);
    return povratna;
}


int main()
{
    
    Matrica<double> a, b, c;
    int m;
    std::cout << "Unesite dimenziju kvadratne matrice: ";
    std::cin >> m;
    try {
        a = StvoriMatricu<double>(m, m);
        std::cout << "Unesite elemente matrice A: \n";
        UnesiMatricu('A', a);
    } catch(std::bad_alloc) {
        std::cout << "Nema dovoljno memorije!";
        return 0;
    }
    //IspisiMatricu<double>(a, 3);
    std::cout << "Unesite red polinoma: ";
    int red;
    std::cin >> red;
    std::cout << "Unesite koeficijente polinoma: ";
    std::vector<double> polinom;
    int i(0);
    while (i <= red) {
        double temp;
        std::cin >> temp;
        polinom.push_back(temp);
        i++;
    }
    Matrica<double> rezultat (MatricniPolinom<double>(a, polinom));
    IspisiMatricu<double>(rezultat, 10, 2, true);
    UnistiMatricu(a);
    UnistiMatricu(rezultat);
    return 0;
}
