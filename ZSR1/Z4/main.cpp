#include <string>
#include <typeinfo>

#ifdef __GNUG__

    #include <cxxabi.h>
    #include <cstdlib>
    #include <memory>

    template< typename T > std::string type_name()
    {
        int status ;
        std::unique_ptr< char[], decltype(&std::free) > buffer(
            __cxxabiv1::__cxa_demangle( typeid(T).name(), nullptr, 0, &status ), &std::free ) ;
        return status==0 ? buffer.get() : "__cxa_demangle error" ;
    }

#else // !defined __GNUG__

    template< typename T > std::string type_name() { return typeid(T).name() ; }

#endif //__GNUG__

template< typename T > std::string type_name( const T& ) { return type_name<T>() ; }


#define print_type_name(var) ( std::cout << #var << " is of type " << type_name(var) << "\n\n" )

template<class T> class App{
    public:
        T var;
        App(T arg) :var(arg){}

};

class Test{};

#include <iostream>
#include <vector>
#include <cstring>


template <typename NekiTip>
 auto F(NekiTip t) -> decltype(&t) {
 return new NekiTip(t);
 }
 
 
int main ()
{
   auto x = F("333");



    std::cout << *x << std::endl;
    print_type_name(x);
	return 0;
}