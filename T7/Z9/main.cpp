#include <iostream>
#include <functional>

std::function<double(double)> plus2(double x) {
	return [x](double y) -> double {
		return x+y;
	};
}

std::function<std::function<double(double)>(double)> plus3(double x) {
	return [x](double y) -> std::function<double(double)> {
		return [x, y] (double z) -> double {
			return x + y + z;
		};
	};
}

int main ()
{
	return 0;
}