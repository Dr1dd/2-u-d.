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
#include <deque>
#include "funkcijos.h"

void deque(){
	std::string pradinis;
	std::string generate;
	std::cout << "Pasirinkta deque konteineriai" << std::endl;
    std::cout << "Skaitymas is failo ar ivestis? (1 = Skaitymas, 0=Ivestis)" << std::endl;
    std::cin >> pradinis;
    std::deque<Studentai> StudentuInfo;
    std::vector<Studentai> Studentai;
    while (pradinis != "1" && pradinis != "0") {
        std::cout << "Ivestis neteisinga, bandykite dar karta ivesdami 1 ar 0" << std::endl;
        std::cin >> pradinis;
    }
    if (pradinis == "1") {
        std::cout << "Ar norite generuoti tekstinius failus? (taip ar ne)" << std::endl;
        std::cin >> generate;
        while (generate != "taip" && generate != "ne") {
            std::cout << "Ivestis neteisinga, bandykite dar karta ivesdami taip arba ne" << std::endl;
            std::cin >> generate;
        }
        if (generate == "taip") {
            if (fileExists("10.txt") && fileExists("10neislaike.txt")) {
            		auto start = std::chrono::high_resolution_clock::now();
                std::string pav;
                std::cout << "Failai jau egzistuoja" << std::endl;
                std::cout << "Pradedami skaitymai is failu" << std::endl;
                for (int i = 1; i <= 5; i++) {
                    std::stringstream ss;
                    ss << std::round(pow(10, i));
                    std::string pav = ss.str() + ".txt";
                    std::cout << pav << std::endl;
                    SkaitymasDeque(StudentuInfo, pav);
                }
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end - start;
        std::cout << "Failu skaitymo laikas: " << diff.count() << " s." << std::endl;
            } else {
            		auto start1 = std::chrono::high_resolution_clock::now();
                for (int z = 1; z <= 5; z++) {
                    Generuoti(StudentuInfo, std::round(pow(10, z)));
                }
        auto end1 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff1 = end1 - start1;
        std::cout << "Failu generavimo laikas: " << diff1.count() << " s." << std::endl;
            }
        }
        if (generate == "ne") {
        	auto start2 = std::chrono::high_resolution_clock::now();
            SkaitymasDeque(StudentuInfo, "kursiokai.txt");
            SpausdintiDeque(StudentuInfo);
         auto end2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff2 = end2 - start2;
        std::cout << "Programos laikas: " << diff2.count() << " s." << std::endl;
        }
    } else {
        int studSkaic;
        bool valid = true;
        std::string tekstas;
        std::cout << "Iveskite studentu skaiciu" << std::endl;
        std::cin.sync();
        while (valid) {
            valid = false;
            try {
                studSkaic = TikrintiSkaicius(tekstas);
            }
            catch (const std::out_of_range &e) {
                std::cout << "Sis skaicius yra per didelis, bandykite dar karta" << std::endl;
                valid = true;

            }
        }
        Studentai.reserve(studSkaic);

        for (int i = 0; i < studSkaic; i++) Studentai.push_back(Informacija());

        std::string tipas;
        std::cout << "Pasirinkite kokio rezultato norite - Vid ar Med" << std::endl;
        std::cin >> tipas;

        while (tipas != "Vid" && tipas != "Med") {
            std::cout << "Ivestis neteisinga, bandykite dar karta" << std::endl;
            std::cin >> tipas;
        }
        Spausdinti(Studentai, tipas, studSkaic);
    }
}
void SkaitymasDeque(std::deque<Studentai> &StudentuInfo, std::string pav){
	std::string a;
	std::string b;
	int skaicius = 0;
	int elSkaic = 0;
	int ndSkaic;
	double egz;
	int p = 0;
	Studentai Stud;
	double vidurkis;
	double galutinis;
	double mediana;
	int suma = 0;
	
	std::ifstream fd;
	fd.open(pav);
	if (!fd.is_open())
    {
       std::cout <<"Nepavyko atidaryti failo" << std::endl;
    }
    else{
	while(std::getline(fd, a)) skaicius++;
	fd.clear();
	fd.seekg(0, std::ios::beg);
	while(!fd.eof()){
		fd >> a;
		elSkaic++;
		if(a == "Egzaminas") break;
	}
	ndSkaic = elSkaic - 3;
	for(int i = 0; i < skaicius-1; i++){
		for(int j = 0; j < elSkaic; j++){
			fd >> b;
			if(j == 0) Stud.lname = b;
			if(j == 1) Stud.fname = b;
			if(j == elSkaic-1) egz = std::stoi(b);
			if(j>1 && j < elSkaic-1) {
			Stud.ND.push_back(std::stoi(b));	
			}
		}
	vidurkis = (double)suma/ndSkaic;
	galutinis = 0.4 * vidurkis + 0.6*egz;
	Stud.egzGal = galutinis;
	mediana = Mediana(Stud, ndSkaic, p);
	Stud.mediana = 0.4 * mediana + 0.6*egz;
	StudentuInfo.push_back(Stud);
	Stud.ND.clear();
}
	fd.close();
}
}

void SpausdintiDeque(std::deque <Studentai> &StudentuInfo){
	std::sort(StudentuInfo.begin(), StudentuInfo.end(), Lyginimas);
	int studSkaic = 0;
	for(int z=0; z<StudentuInfo.size(); z++){
	studSkaic++;
	}
	int ilg;
	int ilgiausiasV = 0;
	int ilgiausiaP = 0;
	for(int i = 0; i < studSkaic; i++) {	
    if(StudentuInfo[i].fname.size() > ilgiausiasV) ilgiausiasV = StudentuInfo[i].fname.size();
    if(StudentuInfo[i].lname.size() > ilgiausiaP) ilgiausiaP = StudentuInfo[i].lname.size();
}
	std::cout <<std::left <<std::setw(7+ilgiausiaP)<<"Pavarde" <<std::left << std::setw(7+ilgiausiasV) << "Vardas" <<std::left << std::setw(19) <<"Galutinis (Vid.)" <<std::left << std::setw(19) <<"Galutinis (Med.)" <<std::endl;
	std::cout <<std::setfill('-') << std::setw(14+ilgiausiaP+ilgiausiasV+38) << "-"<< std::endl;
	std::cout << std::setfill(' ');
	for(int nuo = 0; nuo < studSkaic; nuo++){
		std::cout <<std::left <<std::setw(7+ilgiausiaP)<< StudentuInfo[nuo].lname << std::left << std::setw(7+ilgiausiasV)  << StudentuInfo[nuo].fname <<std::left << std::setw(19) << std::setprecision(2) <<std::fixed << StudentuInfo[nuo].egzGal << std::setw(19) << std::setprecision(2) <<std::fixed << StudentuInfo[nuo].mediana<< std::endl;
	}
}
void Generuoti(std::deque<Studentai> StudentuInfo, int n){
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 gen(seed);
	std::uniform_int_distribution<std::mt19937::result_type> genSK (1, 10);
	StudentuInfo.clear();
	std::string lname;
	std::string fname;
	Studentai Stud;
	double suma = 0;
	int egzrez;
	int pazymys;
	double vidurkis;
	double galutinis;
	for(int i = 0; i <= n; i++){
			suma = 0;
			lname = "Pavarde";
			lname+= std::to_string(i);
			Stud.lname = lname;
			fname = "Vardas";
			fname+= std::to_string(i);
			Stud.fname = fname;
			Stud.ND.reserve(35);
			for(int j = 0; j <= 30; j++){
					pazymys = genSK(gen);
					Stud.ND.push_back(pazymys);
					suma += pazymys;
			}
			egzrez = Stud.ND[30];
		vidurkis = suma /100;
		galutinis = 0.4*vidurkis + 0.6*egzrez;
		Stud.egzGal = galutinis;
		StudentuInfo.push_back(Stud);
		Stud.ND.clear();
	}
	FailuIrasymas(StudentuInfo, n);
}
void FailuIrasymas(std::deque<Studentai> StudentuInfo, int n){
		std::stringstream ss;
	ss << n;
	std::string pav= ss.str() + ".txt";
	std::ofstream fr(pav);
	std::string N1;
	for(int i = 0; i <= n; i++){
		if(i == 0){
			fr << std::left<< std::setw(14) << "Pavarde" << std::left << std::setw(14) << "Vardas";
			for(int y = 1; y <=31; y++) {
			N1 = "N";
			N1+= std::to_string(y);
			if(y != 31) fr << std::left << std::setw(7) << N1;
				else fr << std::left << std::setw(13) << "Egzaminas" << std::endl;
			}
		}
		else{
			fr <<std::left << std::setw(14) << StudentuInfo[i].lname << std::left << std::setw(14) <<StudentuInfo[i].fname;
			for(int j = 0; j <= 30; j++){
				if(j != 30) fr << std::left << std::setw(7) << StudentuInfo[i].ND[j];
				else fr << std::left << std::setw(13) << StudentuInfo[i].ND[j] << std::endl;
				}
			}
		}
		int strat;
		std::cout << "Pasirinkite rusiavimo strategija: 1- pirma, 2 - antra" << std::endl;
		std::cin >> strat;
		while(strat != 1 && strat != 2){
			std::cout << "Ivestis neteisinga, bandykite is naujo irasydami arba 1 arba 2" << std::endl;
			std::cin >> strat;
		}
		if(strat == 1){
		auto start = std::chrono::high_resolution_clock::now();
     	DequeRusiavimas1strat(StudentuInfo, n);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end - start;
        std::cout << n << " Studentu rusiavimo laikas: " << diff.count() << " s." << std::endl;	
		}
		else {
		auto start1 = std::chrono::high_resolution_clock::now();
     	DequeRusiavimas2strat(StudentuInfo, n);
        auto end1 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff1 = end1 - start1;
        std::cout << n << " Studentu rusiavimo laikas: " << diff1.count() << " s." << std::endl;		
		}
 fr.close();

}
void DequeRusiavimas1strat(std::deque<Studentai> StudentuInfo, int n){
	std::stringstream ss;
	ss << n;
	std::string pav1= ss.str() +"islaike.txt";
	std::string pav2= ss.str()+ "neislaike.txt";
	std::deque<Studentai> neislaike;
	std::deque<Studentai> islaike;
	std::ofstream fr1(pav1);
	std::ofstream fr2(pav2);
		for(int i = 0; i <= n; i++){
		if(i == 0){
			fr1 << std::right << std::setw(23) << "Islaike" << std::endl; 
			fr1 << std::left << std::setw(13) << "Pavarde" << std::left  << std::setw(13) << "Vardas" << std::left << std::setw(7) << "Galutinis balas" << std::endl;
			fr1 <<std::endl;
		    fr2 << std::right << std::setw(23) << "Neislaike" << std::endl; 
		    fr2 << std::left << std::setw(13) << "Pavarde" << std::left  << std::setw(13) << "Vardas" << std::left << std::setw(7) << "Galutinis balas" << std::endl;
			fr2 <<std::endl;
		}
		else{
		if(StudentuInfo[i].egzGal >= 5)	islaike.push_back(StudentuInfo[i]);
		if(StudentuInfo[i].egzGal < 5) neislaike.push_back(StudentuInfo[i]);
	}
	}
	int dydis1 = islaike.size();
	int dydis2 = neislaike.size();
	for(int j = 0; j< dydis1; j++){
		fr1 << std::left << std::setw(13) << islaike[j].lname << std::left << std::setw(13) << islaike[j].fname << std::left << std::setw(7) << islaike[j].egzGal << std::endl;
	}
		for(int j1 = 0; j1< dydis2; j1++){
		fr2 << std::left << std::setw(13) << neislaike[j1].lname << std::left << std::setw(13) << neislaike[j1].fname << std::left << std::setw(7) << neislaike[j1].egzGal << std::endl;
	}
	fr1.close();
	fr2.close();
}
void DequeRusiavimas2strat(std::deque<Studentai> StudentuInfo, int n){
	std::stringstream ss;
	ss << n;
	std::string pav1= ss.str() +"islaike.txt";
	std::string pav2= ss.str()+ "neislaike.txt";
	std::deque<Studentai> neislaike;
	std::ofstream fr1(pav1);
	std::ofstream fr2(pav2);
			fr1 << std::right << std::setw(23) << "Islaike" << std::endl; 
			fr1 << std::left << std::setw(13) << "Pavarde" << std::left  << std::setw(13) << "Vardas" << std::left << std::setw(7) << "Galutinis balas" << std::endl;
			fr1 <<std::endl;
		    fr2 << std::right << std::setw(23) << "Neislaike" << std::endl; 
		    fr2 << std::left << std::setw(13) << "Pavarde" << std::left  << std::setw(13) << "Vardas" << std::left << std::setw(7) << "Galutinis balas" << std::endl;
			fr2 <<std::endl;

	 StudentuInfo.erase(StudentuInfo.begin());
std::deque<Studentai>::iterator it =StudentuInfo.begin();
while(it != StudentuInfo.end()){
		if(it->egzGal < 5){
			if(it->fname == "") break;
			 neislaike.push_back(*it);
}

it++;
	}
	std::deque<Studentai>::iterator it1 =StudentuInfo.begin();
	while(it1 !=StudentuInfo.end()){
		if(it1->egzGal <5){
			if(it1->fname == "") break;
		    it1 = StudentuInfo.erase(it1);
		}	
		else it1++;
}
	
	StudentuInfo.shrink_to_fit();
	neislaike.shrink_to_fit();
	int dydis1 = StudentuInfo.size();
	int dydis2 = neislaike.size();
	for(int j = 0; j< dydis1; j++){
		fr1 << std::left << std::setw(13) << StudentuInfo[j].lname << std::left << std::setw(13) << StudentuInfo[j].fname << std::left << std::setw(7) << StudentuInfo[j].egzGal << std::endl;
	}
		for(int j1 = 0; j1< dydis2; j1++){
		fr2 << std::left << std::setw(13) << neislaike[j1].lname << std::left << std::setw(13) << neislaike[j1].fname << std::left << std::setw(7) << neislaike[j1].egzGal << std::endl;
	}
	fr1.close();
	fr2.close();
}



