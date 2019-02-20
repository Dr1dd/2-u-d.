#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <fstream>
#include "funkcijos.h"


Studentai Informacija(){
	std::string vardas, pavarde;
	int n =0;
	double galutinis;
	double vidurkis;
	int studSkaic;
	int p = 0;
	int laikina = 1;
	int laik = 0;
	int ilgis;
	int egzam = 0;
	double egzaminas = 0;
	double mediana = 0;
	
	int suma = 0;
	bool valid;
	Studentai Stud;
	bool raides = true;
	bool skaiciai = false;
	std::string tekstas;
	std::string ivestis;
	std::cout <<"Iveskite varda" << std::endl;
	std::cin.sync();
	Stud.fname = Tikrinti(tekstas);
	std::cout <<"Iveskite pavarde" << std::endl;
	std::cin.sync();
    Stud.lname = Tikrinti(tekstas);
	bool gen = false;
	std::string generuoti;
	int randomSkaic;
	std::cout <<"Iveskite kiek namu darbu buvo atlikta (Bet koks simbolis isskyrus skaicius = galesite baigti kai irasysite - 0)" << std::endl;
	 std::cin.sync();
	 std::getline(std::cin, ivestis);
	 std::stringstream s(ivestis);
    if(s >> n){
    	std::cout<<"Ar norite skaicius generuoti?(egz ir n.d.) Pasirinkimai: (Taip arba Ne)" << std::endl;
    	std::cin>> generuoti;
    	while(generuoti!= "Taip" && generuoti !="Ne" && generuoti!= "taip" && generuoti !="ne"){
		std::cout<<"Ivestis neteisinga, bandykite dar karta: (Iveskite Taip arba Ne)" << std::endl;
		std::cin >> generuoti;
   }
    	if(generuoti == "Taip"){
    	 gen = true;
    	for(int i =1;i <=n; i++){
    		randomSkaic = 1+rand()%10;
    	 Stud.ND.push_back(randomSkaic);
    	 suma = suma + randomSkaic;
    }
		}
		else{
			for(int i =1;i <=n; i++){
		std::cout <<"Iveskite nr " << i << " namu darbo rezultata (1-10)" << std::endl;
		std::cin.sync();
		laik = TikrintiSkaicius(tekstas);
		if(laik >10 || laik <0){
		  std::cout <<"Jus ivedete neimanoma rezultata, bandykite dar karta" << std::endl;
		  i= i-1;
		}
		else {
			Stud.ND.push_back(laik);
			suma = suma + laik;	
		}
        }
    }
    }
    else{
        while(laikina != 0){
			std::cout <<"Iveskite nr " << p+1 << " namu darbo rezultata (1-10) (0 = ivedimas baigiamas)" << std::endl;
			laikina = TikrintiSkaicius(tekstas);
			if(laikina >10 || laikina <0){
		  		std::cout <<"Jus ivedete neimanoma rezultata, bandykite dar karta" << std::endl;
		}
			else {
				if(laikina == 0) break;
				p++;
				Stud.ND.push_back(laikina);
				suma = suma + laikina;
			}
		}
	}
	int egzas = 0;
	if(gen == true){
		egzas = 1+rand()%10;
	if(p>0)vidurkis = (double)suma/p;
	else vidurkis = (double)suma/n;
	galutinis = 0.4 * vidurkis + 0.6*egzas;
	Stud.egzGal = galutinis;
	mediana = Mediana(Stud, n, p);
	Stud.mediana = 0.4 * mediana + 0.6*egzas;
	}
	else{
	std::cout <<"Iveskite egzamino rezultata" << std::endl;
	std::cin.sync();
	egzam = TikrintiSkaicius(tekstas); 
	if(egzam > 10 || egzam <1){
		while(egzam >10 || egzam < 1){
			std::cout <<"Jus ivedete neimanoma rezultata, bandykite dar karta" << std::endl;
			std::cout <<"Iveskite egzamino rezultata" << std::endl;
			std::cin >> egzam;
		}
	}
	else egzaminas = egzam;
	if(p>0)vidurkis = (double)suma/p;
	else vidurkis = (double)suma/n;
	galutinis = 0.4 * vidurkis + 0.6*egzaminas;
	Stud.egzGal = galutinis;
	mediana = Mediana(Stud, n, p);
	Stud.mediana = 0.4 * mediana + 0.6*egzaminas;
}

return Stud;
}

double Mediana(Studentai Stud, int n, int p){
	double mediana;
	int f = 0;

	std::sort(Stud.ND.begin(), Stud.ND.end());

	if(n!=0){
		if(n % 2 == 0) mediana = (Stud.ND[n/2-1] + Stud.ND[n/2]) / 2;
		else {
			if(n == 1) mediana = 1;
			else mediana = Stud.ND[n/2];
		}
	}
	else{
	if(p % 2 == 0)mediana = (Stud.ND[p/2-1] + Stud.ND[p/2]) / 2;
	 else {
	 	if(p == 1) mediana == 1;
	 	else mediana = Stud.ND[p/2];
	 }
}

return mediana;
}


