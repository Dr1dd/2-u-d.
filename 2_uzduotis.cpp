#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <cmath>
#include "funkcijos.h"

int main(){
	srand(time(NULL));
	std::string pradinis;
	std::string generate;
	std::vector<Studentai> StudentuInfo;
	std::cout << "Skaitymas is failo ar ivestis? (1 = Skaitymas, 0=Ivestis)" << std::endl;
	std::cin >> pradinis;
		while(pradinis != "1" && pradinis !="0"){
			std::cout <<"Ivestis neteisinga, bandykite dar karta ivesdami 1 ar 0" << std::endl;
			std::cin >> pradinis;
		}
	if(pradinis == "1"){
		std::cout <<"Ar norite generuoti tekstinius failus? (taip ar ne)" << std::endl;
		std::cin >> generate;
		while(generate != "taip" && generate!="ne"){
			std::cout<<"Ivestis neteisinga, bandykite dar karta ivesdami taip arba ne" << std::endl;
			std::cin >> generate;
		}
		if(generate == "taip"){
			for(int z = 1;z <= 5; z++){
				Generuoti(std::round(pow(10, z)));
			}
		}
		if(generate == "ne"){
			Skaitymas(StudentuInfo);
			Spausdinti(StudentuInfo);		
		}
		}
	else{
	int studSkaic;
	bool valid = true;
	std::string tekstas;
	std::cout <<"Iveskite studentu skaiciu" << std::endl;
	std::cin.sync();
	while(valid){
		valid = false;
	try{
		studSkaic = TikrintiSkaicius(tekstas);		
	}
	catch(const std::out_of_range& e){
		std::cout<< "Sis skaicius yra per didelis, bandykite dar karta" <<std::endl;
		valid = true;
		
	}
}
	StudentuInfo.reserve(studSkaic);
	for(int i = 0 ; i< studSkaic; i++) StudentuInfo.push_back(Informacija());
	
	
	std::string tipas;
	std::cout <<"Pasirinkite kokio rezultato norite - Vid ar Med" << std::endl;
	std::cin >> tipas;
	
	while(tipas!= "Vid" && tipas !="Med"){
		std::cout<<"Ivestis neteisinga, bandykite dar karta" << std::endl;
		std::cin >> tipas;
}
	Spausdinti(StudentuInfo, tipas, studSkaic);
}
	return 0;
}


