#include <iostream>
#include <tuple>

typedef std::tuple<double, double, double> Vektor3d;


void UnesiVektor(Vektor3d &v)
{
    std::cout << "X = ";
    std::cin >> std::get<0>(v);
    std::cout << "Y = ";
    std::cin >> std::get<1>(v);
    std::cout << "Z = ";
    std::cin >> std::get<2>(v);
}


Vektor3d ZbirVektora(const Vektor3d &v1, const Vektor3d &v2)
{
    double xV1, yV1, zV1;
    std::tie(xV1, yV1, zV1) = v1;
    double xV2, yV2, zV2;
    std::tie(xV2, yV2, zV2) = v2;
    //return {std::get<0>(v1) + std::get<0>(v2), std::get<1>(v1) + std::get<1>(v2), std::get<2>(v1) + std::get<2>(v2)};
    return {xV1 + xV2, yV1 + yV2, zV1 + zV2};
}


Vektor3d VektorskiProizvod(const Vektor3d &v1, const Vektor3d &v2)
{
    double xV1, yV1, zV1;
    std::tie(xV1, yV1, zV1) = v1;
    double xV2, yV2, zV2;
    std::tie(xV2, yV2, zV2) = v2;
    /* {std::get<1>(v1) * std::get<2>(v2) - std::get<2>(v1) * std::get<1>(v2), std::get<2>(v1) * std::get<0>(v2) - std::get<0>(v1) * std::get<2>(v2),
            xV1 * std::get<1>(v2) - std::get<1>(v1) * std::get<0>(v2)};*/
    return {yV1 * zV2 - zV1 * yV2, zV1 * xV2 - xV1 * zV2,
            xV1 * yV2 - yV1 * xV2};
    
}


void IspisiVektor(const Vektor3d &v)
{
    double x, y, z;
    std::tie(x, y, z) = v;
    //std::cout << "{" << std::get<0>(v) << "," << std::get<1>(v) << "," << std::get<2>(v) << "}";
    std::cout << "{" << x << "," << y << "," << z << "}";
}


int main()
{
    Vektor3d a, b;
    std::cout << "Unesi prvi vektor:\n";
    UnesiVektor(a);
    std::cout << "Unesi drugi vektor:\n";
    UnesiVektor(b);
    std::cout << "Suma ova dva vektora je: ";
    IspisiVektor(ZbirVektora(a, b));
    std::cout << std::endl << "Njihov vektorski prozivod je: ";
    IspisiVektor(VektorskiProizvod(a, b));
    return 0;
}
