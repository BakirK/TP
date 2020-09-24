/* TP, 2017/2018, Tutorijal 4, Zadatak 5 */
#include <iostream>
#include <vector>

template <typename someType>
bool isInside (someType element, std::vector<someType> duplikati) {
    for (int i = 0; i < duplikati.size(); i++) {
        if (duplikati.at(i) == element) {
            return true;
        }
    }
    return false;
}

template <typename someType>
std::vector<someType> Presjek( std::vector<someType> v1, std::vector<someType> v2 ) {
    std::vector<someType> temp;
    for (int i = 0; i < v1.size(); i++) {
        for (int j = 0; j < v2.size(); j++) {
            if (v1.at(i) == v2.at(j)) {
                if ( isInside (v1.at(i), temp) ) {
                    continue;
                }
                temp.push_back(v1.at(i));
            }
        }
    }
    return temp;
}


int main ()
{
    std::cout << "Test za realne brojeve..." << std::endl;
    int n1;
    std::cout << "Unesite broj elemenata prvog vektora: ";
    std::cin >> n1;
    int i (0);
    std::vector<double> d1;
    std::cin.ignore(1000, '\n');
    std::cout << "Unesite elemente prvog vektora: ";
    while (i < n1) {
        double temp;
        std::cin >> temp;
        d1.push_back(temp);
        i++;
    }
    
    std::cout << "Unesite broj elemenata drugog vektora: ";
    int n2;
    std::cin >> n2;
    i = 0;
    std::vector<double> d2;
    std::cin.ignore(1000, '\n');
    std::cout << "Unesite elemente drugog vektora: ";
    while (i < n2) {
        double temp;
        std::cin >> temp;
        d2.push_back(temp);
        i++;
    }
    std::vector<double> d3 = Presjek(d1, d2);
    std::cout << "Zajednicki elementi su: ";
    for (int i = 0; i < d3.size(); i++) {
        if (i == d3.size() - 1) {
            std::cout << d3.at(i) << "\n";
        }
        else {
            std::cout << d3.at(i) << " ";
        }
    }
    
    std::cout << std::endl << "Test za stringove..." << std::endl;
    
    n1 = 0;
    std::cout << "Unesite broj elemenata prvog vektora: ";
    std::cin >> n1;
    std::vector<std::string> s1;
    std::cin.ignore(1000, '\n');
    std::cout << "Unesite elemente prvog vektora (ENTER nakon svakog unosa): ";
    i = 0;
    while (i < n1) {
        std::string temp;
        std::getline(std::cin, temp);
        s1.push_back(temp);
        i++;
    }
    
    std::cout << "Unesite broj elemenata drugog vektora: ";
    n2 = 0;
    std::cin >> n2;
    std::vector<std::string> s2;
    std::cin.ignore(1000, '\n');
    std::cout << "Unesite elemente drugog vektora (ENTER nakon svakog unosa): ";
    i = 0;
    /*
    for (int i = 0; i < n2; i++) {
        std::string temp;
        std::getline(std::cin, temp);
        s2.push_back(temp);
    }*/
    
    
    while (i < n2) {
        std::string temp;
        std::getline(std::cin, temp);
        s2.push_back(temp);
        i++;
    }
    std::vector<std::string> s3 = Presjek(s1, s2);
    std::cout << "Zajednicki elementi su:";
    for (int i = 0; i < s3.size(); i++) {
        std::cout << std::endl << s3.at(i) ;
    }
    
	return 0;
}