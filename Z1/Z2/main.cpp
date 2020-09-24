#include <iostream>
#include <vector>
#include <stdexcept>
#include <iomanip>
#include <cmath>
#include <limits>
#include <complex>

typedef std::vector<std::vector<int>> matrica;

std::complex<double> VrhMatrice (matrica m, int x, int y) {
	try {
		int sirina (m.at(0).size());
		bool parametri (true);
		for (int i = 1; i < m.size(); i++) {
			if (sirina != m.at(i).size()) {
				parametri = false;
				break;
			}
		}
		if (x > m.size() - 1 || y > (m.at(0).size())-1) {
			throw std::range_error ("Nekorektna pocetna pozicija");
		}
		if (!parametri) {
			throw std::domain_error ("Nekorektna matrica");
		}
		if (m.size() == 0 || m.at(0).size()==0) {
			throw std::domain_error ("Nekorektna matrica");
		}
		int rowCurrent (x);
		int columnCurrent (y);
		int width = m.at(0).size();
		int height = m.size();
		int max = m.at(x).at(y);
		
			bool changed (false);
			//samo jedan red
			if (height == 1) {
				while (true) {
					changed = false;
					if (width == 1) {
						std::complex<double> dramela (rowCurrent, columnCurrent);
						return dramela;
					}
					if (columnCurrent == 0) {
						if (m.at(0).at(1) > max) {
							max = m.at(0).at(1);
							columnCurrent = 1;
							changed = true;
						}
						if (!changed) {
							break;
						}
					}
					else if (columnCurrent == width -1) {
						if (m.at(0).at(width - 1) > max) {
							max = m.at(0).at(width - 1);
							columnCurrent = width - 1;
							changed = true;
						}
						if (!changed) {
							break;
						}
					}
					else {
						int tempColumn = columnCurrent;
						if (m.at(0).at(tempColumn + 1) > max) {
							max = m.at(0).at(tempColumn + 1);
							columnCurrent += 1;
							changed = true;
						}
						if (m.at(0).at(tempColumn - 1) > max ) {
							max = m.at(0).at(tempColumn - 1);
							columnCurrent -= 1;
							changed = true;
						}
						if (!changed) {
							break;
						}
					}
				}
				std::complex<double> dramela (rowCurrent, columnCurrent);
				return dramela;
			}
			
			//samo jedna kolona
			if (width == 1) {
				while (true) {
					changed = false;
					if (rowCurrent == 0) {
						if (m.at(1).at(0) > max) {
							max = m.at(1).at(0);
							rowCurrent = 1;
							changed = true;
						}
						if (!changed) {
							break;
						}
					}
					else if (rowCurrent == height - 1) {
						if (m.at(height - 2).at(0) > max) {
							max = m.at(height - 2).at(0);
							rowCurrent = height - 2;
							changed = true;
						}
						if (!changed) {
							break;
						}
					}
					else {
						int tempRow = rowCurrent;
						if (m.at(tempRow - 1).at(0) > max) {
							max = m.at(tempRow - 1).at(0);
							rowCurrent -= 1;
							changed = true;
						}
						if (m.at(tempRow + 1).at(0) > max) {
							max = m.at(tempRow + 1).at(0);
							rowCurrent += 1;
							changed = true;
						}
						if (!changed) {
							break;
						}
					}
				}
				std::complex<double> dramela (rowCurrent, columnCurrent);
				return dramela;
			}

		while (true) {	
			changed = false;
			 if (rowCurrent == 0) {
				//gornji lijevi cosak
				if (columnCurrent == 0) {
					if ( m.at(0).at(1) > max ) {
						max = m.at(0).at(1);
						rowCurrent = 0;
						columnCurrent = 1;
						changed = true;
					}
					for (int j = 1; j >= 0; j--) {
							if ( m.at(1).at(j) > max) {
								max = m.at(1).at(j);
								rowCurrent = 1;
								columnCurrent = j;
								changed = true;
							}
					}
					if (!changed) {
						break;
					}
				}
				//gornji desni cosak
				else if (columnCurrent == width - 1) {
					for (int j = width - 1; j >= width - 2; j--) {
							if ( m.at(1).at(j) > max) {
								max = m.at(1).at(j);
								rowCurrent = 1;
								columnCurrent = j;
								changed = true;
							}
					}
					if ( m.at(0).at(width - 2) > max ) {
						max = m.at(0).at(width - 2);
						rowCurrent = 0;
						columnCurrent = width - 2;
						changed = true;
					}
					if (!changed) {
						break;
					}
				} 
				//gornji zid
				else {
					int tempColumn = columnCurrent;
					if ( m.at(0).at(tempColumn + 1) > max ) {
						max = m.at(0).at(tempColumn + 1);
						rowCurrent = 0;
						columnCurrent = tempColumn + 1;
						changed = true;
					}
					for (int j = tempColumn + 1; j >= tempColumn - 1; j--) {
							if ( m.at(1).at(j) > max) {
								max = m.at(1).at(j);
								rowCurrent = 1;
								columnCurrent = j;
								changed = true;
							}
					}
					if ( m.at(0).at(tempColumn - 1) > max ) {
						max = m.at(0).at(tempColumn - 1);
						rowCurrent = 0;
						columnCurrent = tempColumn - 1;
						changed = true;
					}
					if (!changed) {
						break;
					}
				}
			}
			else if (rowCurrent == height - 1) {
				//lijevi donji cosak
				if (columnCurrent == 0) {
					for (int j = 0; j <= 1; j++) {
						if ( m.at(height - 2).at(j) > max) {
							max = m.at(height - 2).at(j);
							rowCurrent = height - 2;
							columnCurrent = j;
							changed = true;							
						}
					}
					if ( m.at(height - 1).at(1) > max ) {
						max = m.at(rowCurrent).at(1);
						rowCurrent = rowCurrent;
						columnCurrent = 1;
						changed = true;
					}
					if (!changed) {
						break;
					}
				}
				//desni donji cosak
				else if (columnCurrent == width - 1) {
					if ( m.at(height - 2).at(width - 1) > max ) {
						max = m.at(height - 2).at(width - 1);
						rowCurrent = height - 2;
						columnCurrent = width - 1;
						changed = true;
					}
					for (int j = height - 1; j >= height - 2; j--) {
						if ( m.at(j).at(width - 2) > max) {
							max = m.at(j).at(width - 2);
							rowCurrent = j;
							columnCurrent = width - 2;
							changed = true;
						}
					}
					if (!changed) {
						break;
					}
				} 
				//donji zid
				else {
					int tempRow = rowCurrent;
					int tempColumn = columnCurrent;
					for (int i = height - 2; i < height; i++) {
						for (int j = tempColumn - 1; j <= tempColumn; j++) {
							if ( m.at(i).at(j) > max) {
								max = m.at(i).at(j);
								rowCurrent = i;
								columnCurrent = j;
								changed = true;
							}
						}
					}
					for (int i = tempRow; i >= tempRow - 1; i--) {
						if ( m.at(i).at(tempColumn) > max) {
							max = m.at(i).at(tempColumn);
							rowCurrent = i;
							columnCurrent = tempColumn;
							changed = true;
						}
					}
					if (!changed) {
						break;
					}
				}
			}

			else {
				//lijevi zid
				if (columnCurrent == 0) {
					int tempRow = rowCurrent;
					int tempColumn = columnCurrent;
					for (int j = tempColumn; j <= tempColumn + 1; j++) {
						if ( m.at(tempRow - 1).at(j) > max) {
							max = m.at(tempRow - 1).at(j);
							rowCurrent = tempRow - 1;
							columnCurrent = j;
							changed = true;
						}
					}
					if ( m.at(tempRow).at(tempColumn + 1) > max) {
						max = m.at(tempRow).at(tempColumn + 1);
						rowCurrent = tempRow;
						columnCurrent = tempColumn + 1;
						changed = true;
					}
					for (int j = tempColumn + 1; j  >= tempColumn; j--) {
						if ( m.at(tempRow + 1).at(j) > max) {
							max = m.at(tempRow + 1).at(j);
							rowCurrent = tempRow + 1;
							columnCurrent = j;
							changed = true;
						}
					}
					if (!changed) {
						break;
					}
				}
				//desni zid
				else if (columnCurrent == width - 1) {
					int tempRow = rowCurrent;
					int tempColumn = columnCurrent;
					if ( m.at(tempRow - 1).at(tempColumn) > max) {
						max = m.at(tempRow - 1).at(tempColumn);
						rowCurrent = tempRow - 1;
						columnCurrent = tempColumn;
						changed = true;
					}
					if ( m.at(tempRow + 1).at(tempColumn) > max) {
						max = m.at(tempRow + 1).at(tempColumn);
						rowCurrent = tempRow + 1;
						columnCurrent = tempColumn;
						changed = true;
					}
					for (int i = tempRow + 1; i >= tempRow - 1; i--) {
						if ( m.at(i).at(tempColumn - 1) > max) {
							max = m.at(i).at(tempColumn - 1);
							rowCurrent = i;
							columnCurrent = tempColumn - 1;
							changed = true;
						}
					}
					if (!changed) {
						break;
					}
				} 
				//centar matrice
				else {
					int tempRow = rowCurrent;
					int tempColumn = columnCurrent;
					for (int j = tempColumn; j <= tempColumn + 1; j++) {
						if ( m.at(tempRow - 1).at(j) > max) {
							max = m.at(tempRow - 1).at(j);
							rowCurrent = tempRow - 1;
							columnCurrent = j;
							changed = true;
						}
					}
					if ( m.at(tempRow).at(tempColumn + 1) > max) {
						max = m.at(tempRow).at(tempColumn + 1);
						rowCurrent = tempRow;
						columnCurrent = tempColumn + 1;
						changed = true;
					}
					for (int j = tempColumn + 1; j >= tempColumn - 1; j--) {
						if ( m.at(tempRow + 1).at(j) > max) {
							max = m.at(tempRow + 1).at(j);
							rowCurrent = tempRow + 1;
							columnCurrent = j;
							changed = true;
						}
					}
					for (int i = tempRow ; i >= tempRow - 1; i--) {
						if ( m.at(i).at(tempColumn - 1) > max) {
							max = m.at(i).at(tempColumn - 1);
							rowCurrent = i;
							columnCurrent = tempColumn - 1;
							changed = true;
						}
					}
					if (!changed) {
						break;
					}
				}
			}
		}
		std::complex<double> dramela (rowCurrent, columnCurrent);
		return dramela;
	}
	catch (std::domain_error belaj) {
		throw std::domain_error ("Nekorektna matrica");
	}
	catch (std::range_error belaj) {
		throw std::range_error ("Nekorektna pocetna pozicija");
	}
	catch (...) {
		throw std::domain_error ("Nekorektna matrica");
	}
	std::complex<double> c;
	return c;
}

int main ()
{
	try{
		int m, n;
	    while (true) {
	        std::cout << "Unesite broj redova i kolona matrice:";
	        std::cin >> m >> n;
	        if (m <= 0 || n <= 0) {
	            std::cout << "Broj elemenata mora biti veci od 0!" << std::endl;
	            return 0;
	        }
	        break;
	    }
	    std::cout << "\nUnesite elemente matrice:";
	    matrica matrix (m);
	    for (int i = 0; i < m; i++) {
	    	for (int j = 0; j < n; j++) {
	    		int temp;
	    		std::cin >> temp;
	        	matrix.at(i).push_back(temp);
	    	}
		}
		std::cout << "\nUnesite poziciju odakle zapocinje pretraga:";
		int x, y;
		std::cin >> x >> y;
	    std::complex<double> pozicija (VrhMatrice(matrix, x, y));
		std::cout << "\nNadjen je vrh matrice na poziciji " << pozicija.real() << " " << pozicija.imag();
		std::cout << "\nNjegova vrijednost je " << matrix.at(pozicija.real()).at(pozicija.imag());
	}
	catch (std::domain_error belaj) {
		std::cout<< "\nGreska: " << belaj.what();
		
	}
	catch (std::range_error belaj) {
		std::cout<< "\nGreska: " << belaj.what();
	}
	catch (...) {
		std::cout<< "\nGreska!";
	}
	return 0;
}