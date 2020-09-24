#include <iostream>
#include <algorithm>

std::string IzvrniBezRazmaka(std::string recenica) {
	std::string temp;
	std::remove_copy(recenica.rbegin(), recenica.rend(), std::inserter(temp, temp.begin()), ' ');
	return temp;
}


int main ()
{
	return 0;
}