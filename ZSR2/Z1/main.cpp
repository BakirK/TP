#include <iostream>
#include <vector>

int main ()
{
	std::vector<int> v(5);
	std::vector<int>::iterator it (v.begin());

  typedef std::iterator_traits<decltype(it)> it_traits;
  
  it_traits::difference_type test1;
  it_traits::value_type var = 20; std::cout << var << std::endl;
  it_traits::pointer pointer;
  //it_traits::reference reference;
  it_traits::iterator_category iterator_category;
 
  if (typeid(it_traits::iterator_category)==typeid(std::random_access_iterator_tag))
    std::cout << "it_traits::iterator_category is a random-access iterator" << std::endl;;
    std::cout << "--end";
	return 0;
}
