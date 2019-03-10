#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <cmath>
#include <random>
#include <chrono>
#include <list>
#include "funkcijos.h"

int main(){
	int tipas;
	std::cout << "Ar norite naudoti vectorius, list'us ar deque's? Pasirinkite atitinkamai (0- vector, 1 - list, 2 - deque)" << std::endl;
	std::cin >> tipas;
	while(tipas != 0 && tipas!= 1 && tipas != 2){
	    std::cout << "Ivestis neteisinga, bandykite dar karta su 0, 1, 2" << std::endl;
	    std::cin>> tipas;
	}
	if(tipas == 0) vector();
	if(tipas == 1) list();
	if(tipas == 2) deque();

	return 0;
}


