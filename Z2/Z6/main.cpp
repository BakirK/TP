/* TP, 2018/2019
*/
#include <iostream>
#include <vector>
#include <cctype>
#include <string>
#include <algorithm>

//custom to upperfunction
void toUpperSting (std::string &a, std::string &b) {
    for (int i(0); i < a.size(); i++) {
        if (a.at(i) >= 'a' && a.at(i) <= 'z') {
            a.at(i) -= 'A';
        }
    }
    for (int i(0); i < b.size(); i++) {
        if (b.at(i) >= 'a' && b.at(i) <= 'z') {
            b.at(i) -= 'A';
        }
    }
}


bool KriterijSortiranja (std::string a, std::string b) {
    if (a.size() > b.size()) {
        return false;
    }
    else if (a.size() < b.size()) {
        return true;
    }
    auto aTemp = a;
    auto bTemp = b;
    toUpperSting(aTemp, bTemp);
    std::cout << aTemp << " " << bTemp<< std::endl;
    
    return (aTemp < bTemp);
}


void SortirajPoDuzini (std::string *p, int broj_elemenata) {
    auto kraj = p;
    int i (0);
    while(i < broj_elemenata) {
        kraj++;
        i++;
    }
    std::sort(p, kraj, KriterijSortiranja);
 }

bool PretraziBinarno (std::string *p, int broj_elemenata, std::string word){
    auto temp = p + broj_elemenata;
    return std::binary_search(p, temp, word, KriterijSortiranja);
}

int main ()
{
    std::cout << "Unesite broj rijeci: ";
    int n;
    std::cin >> n;
    std::string *rijeci = nullptr;
    //std::cin.ignore(1000, '\n');
    std::cout << "Unesite rijeci: ";
    try {
        rijeci = new std::string[n];
        for (int i(0); i < n; i++) {
            std::string temp;
            std::cin >> temp;
            //std::getline(std::cin, temp);
            rijeci[i] = temp;
        }
        SortirajPoDuzini(rijeci, n);
        std::cout << "Sortirane rijeci: ";   
        for (int i = 0; i < n; i++) {
            if (i == n - 1) {
                std::cout << rijeci[i];
            }
            else {
                std::cout << rijeci[i] << " ";
            }
            
        }
        //std::cin.ignore(1000, '\n');
        std::cout << std::endl << "Unesite rijec za pretragu: ";   
        std::string word;
        std::cin >> word;
        if (PretraziBinarno(rijeci, n, word)) {
            std::cout << "Rijec '" << word << "' se nalazi u nizu." << std::endl;
        }
        else {
            std::cout << "Rijec '" << word << "' se ne nalazi u nizu." << std::endl;
        }
        delete[] rijeci;
    }
    catch (std::bad_alloc a) {
        std::cout << a.what() << std::endl;
        delete [] rijeci;
    }
	return 0;
}