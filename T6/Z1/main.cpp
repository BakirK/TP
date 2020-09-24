//TP 2017/2018: ZSR 1, Zadatak 1
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <limits>


template <typename someType>
someType *GenerirajStepeneDvojke (int n) {
    if (n <= 0 ) {
        throw std::domain_error("Broj elemenata mora biti pozitivan");
    }
    
    someType *p (nullptr);
    someType *first;
    bool ex (false);
    try {
        someType pom = 1;
        p = new someType[n];
        int stepen (0);
        first = p;
        for (int i (0); i < n; i++) {   
            *first = pom;
            
            if (*first < 1 || (*first > ((std::numeric_limits<someType>::max()) / 2) && i != n - 1)) {
                throw std::overflow_error("overflow");
            }
            else {
                first++;
                stepen++;
                pom*=2;
            }
        }
    }
    catch(std::domain_error) {
        if (!ex) {
            ex = true;
            delete[] p;
            first = nullptr;
            p = nullptr;
        }
        throw std::domain_error("Broj elemenata mora biti pozitivan");
    }
    catch (std::overflow_error) {
        if (!ex) {
            ex = true;
            delete[] p;
            first = nullptr;
            p = nullptr;
        }
        throw std::overflow_error("Prekoracen dozvoljeni opseg");
    }
    catch(std::runtime_error) {
        if (!ex) {
            ex = true;
            delete[] p;
            first = nullptr;
            p = nullptr;
        }
        throw std::runtime_error("Alokacija nije uspjela");
    }
    catch (...) {
        if (!ex) {
            ex = true;
            delete[] p;
            first = nullptr;
            p = nullptr;
        }
    }
    return p;
}

int main ()
{
    std::cout << "Koliko zelite elemenata: ";
    int n;
    std::cin >> n;
    unsigned long long int *p = nullptr;
    try {
        
        p = GenerirajStepeneDvojke<unsigned long long int>(n);
        unsigned long long int *temp = p;
        for (int i (0); i < n; i++) {
            std::cout << *temp << " ";
            temp++;
        }
        delete[] p;
    }
    catch (std::overflow_error overFlowError) {
        std::cout << "Izuzetak: " << overFlowError.what() << std::endl;
        delete[] p;
    }
    catch(std::runtime_error runtimeError) {
        std::cout << "Izuzetak: "  << runtimeError.what() << std::endl;
        delete[] p;
    }
    catch (std::domain_error domainError) {
        std::cout << "Izuzetak: "  << domainError.what() << std::endl;
        delete[] p;
    }
    catch (...) {
        std::cout << "Nepoznati izuzetak: "  << std::endl;
        delete[] p;
    }
	return 0;
}