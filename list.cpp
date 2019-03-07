#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <cmath>
#include <chrono>
#include <list>
#include "funkcijos.h"

void list(){
    std::string pradinis;
    std::string generate;
    std::cout << "Pasirinkta list konteineriai" << std::endl;
    std::cout << "Skaitymas is failo ar ivestis? (1 = Skaitymas, 0=Ivestis)" << std::endl;
    std::cin >> pradinis;
    std::list <Studentai> StudentuInfo;
    std::vector <Studentai> Studentai;
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
                    SkaitymasList(StudentuInfo, pav);
                }
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end - start;
        std::cout << "Skaitymo laikas: " << diff.count() << " s." << std::endl;
            } else {
                for (int z = 1; z <= 5; z++) {
                    Generuoti(StudentuInfo, std::round(pow(10, z)));
                StudentuInfo.clear();
				}
            }

        }
        if (generate == "ne") {
        	auto start1 = std::chrono::high_resolution_clock::now();
            SkaitymasList(StudentuInfo, "kursiokai.txt");
            SpausdintiList(StudentuInfo);
             auto end1 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff1 = end1 - start1;
        std::cout << "Skaitymo ir Spausdinimo i ekrana laikas (su listais): " << diff1.count() << " s." << std::endl;
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

void SpausdintiList(std::list <Studentai> &StudentuInfo){
	StudentuInfo.sort(Lyginimas);
	int ilg;
	int ilgiausiasV = 0;
	int ilgiausiaP = 0;
	for(std::list<Studentai>::iterator it= StudentuInfo.begin(); it != StudentuInfo.end(); it++) {	
    if(it->fname.size() > ilgiausiasV) ilgiausiasV = it->fname.size();
    if(it->lname.size() > ilgiausiaP) ilgiausiaP = it->lname.size();
}
	std::cout <<std::left <<std::setw(7+ilgiausiaP)<<"Pavarde" <<std::left << std::setw(7+ilgiausiasV) << "Vardas" <<std::left << std::setw(19) <<"Galutinis (Vid.)" <<std::left << std::setw(19) <<"Galutinis (Med.)" <<std::endl;
	std::cout <<std::setfill('-') << std::setw(14+ilgiausiaP+ilgiausiasV+38) << "-"<< std::endl;
	std::cout << std::setfill(' ');
	for(std::list<Studentai>::iterator it1= StudentuInfo.begin(); it1 != StudentuInfo.end(); it1++){
		std::cout <<std::left <<std::setw(7+ilgiausiaP)<< it1->lname << std::left << std::setw(7+ilgiausiasV)  << it1->fname <<std::left << std::setw(19) << std::setprecision(2) <<std::fixed << it1->egzGal << std::setw(19) << std::setprecision(2) <<std::fixed << it1->mediana<< std::endl;
	}

}

void SkaitymasList(std::list<Studentai> &StudentuInfo, std::string pav){
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
void Generuoti(std::list<Studentai> &StudentuInfo, int n){
	StudentuInfo.clear();
	std::string lname;
	std::string fname;
	Studentai Stud;
	double suma = 0;
	int egzrez;
	int pazymys;
	double vidurkis;
	double galutinis;
	for(int i = 1; i <= n; i++){
			suma = 0;
			lname = "Pavarde";
			lname+= std::to_string(i);
			Stud.lname = lname;
			fname = "Vardas";
			fname+= std::to_string(i);
			Stud.fname = fname;
			Stud.ND.reserve(35);
			for(int j = 0; j <= 30; j++){
					pazymys = 1+rand()%10;
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
void FailuIrasymas(std::list<Studentai> &StudentuInfo, int n){
		std::stringstream ss;
	ss << n;
	std::string pav= ss.str() + ".txt";
	std::ofstream fr(pav);
	std::string N1;
	std::list<Studentai>::iterator it;
	int  i = 0;
	for(it = StudentuInfo.begin(); it != StudentuInfo.end(); it++){
		if(i == 0){
			fr << std::left<< std::setw(14) << "Pavarde" << std::left << std::setw(14) << "Vardas";
			for(int y = 1; y <=31; y++) {
			N1 = "N";
			N1+= std::to_string(y);
			if(y != 31) fr << std::left << std::setw(7) << N1;
				else fr << std::left << std::setw(13) << "Egzaminas" << std::endl;
			}
			i++;
		}
			fr <<std::left << std::setw(14) << it->lname << std::left << std::setw(14) <<it->fname;
			for(int j = 0; j <= 30; j++){
				if(j != 30) fr << std::left << std::setw(7) << it->ND[j];
				else fr << std::left << std::setw(13) << it->ND[j] << std::endl;
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
     	ListRusiavimas1strat(StudentuInfo, n);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end - start;
        std::cout << n << " Studentu rusiavimo laikas: " << diff.count() << " s." << std::endl;	
		}
		else {
		auto start1 = std::chrono::high_resolution_clock::now();
     	ListRusiavimas2strat(StudentuInfo, n);
        auto end1 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff1 = end1 - start1;
        std::cout << n << " Studentu rusiavimo laikas: " << diff1.count() << " s." << std::endl;		
		}
 fr.close();

}
void ListRusiavimas1strat(std::list<Studentai> &StudentuInfo, int n){
	std::stringstream ss;
	ss << n;
	std::string pav1= ss.str() +"islaike.txt";
	std::string pav2= ss.str()+ "neislaike.txt";
	std::list<Studentai> neislaike;
	std::list<Studentai> islaike;
	std::ofstream fr1(pav1);
	std::ofstream fr2(pav2);
	int i = 0;
		for(std::list<Studentai>::iterator it = StudentuInfo.begin(); it != StudentuInfo.end(); it++){
		if(i == 0){
			fr1 << std::right << std::setw(23) << "Islaike" << std::endl; 
			fr1 << std::left << std::setw(13) << "Pavarde" << std::left  << std::setw(13) << "Vardas" << std::left << std::setw(7) << "Galutinis balas" << std::endl;
			fr1 <<std::endl;
		    fr2 << std::right << std::setw(23) << "Neislaike" << std::endl; 
		    fr2 << std::left << std::setw(13) << "Pavarde" << std::left  << std::setw(13) << "Vardas" << std::left << std::setw(7) << "Galutinis balas" << std::endl;
			fr2 <<std::endl;
		i++;
		}
		if(it->egzGal >= 5)	islaike.push_back(*it);
		if(it->egzGal < 5) neislaike.push_back(*it);
	}
	int dydis1 = islaike.size();
	int dydis2 = neislaike.size();
	for(std::list<Studentai>::iterator it1 = islaike.begin(); it1 != islaike.end(); ++it1){
		fr1 << std::left << std::setw(13) << it1->lname << std::left << std::setw(13) << it1->fname << std::left << std::setw(7) << it1->egzGal << std::endl;
	}
		for(std::list<Studentai>::iterator it2 = neislaike.begin(); it2 != neislaike.end(); ++it2){
		fr2 << std::left << std::setw(13) << it2->lname << std::left << std::setw(13) << it2->fname << std::left << std::setw(7) << it2->egzGal << std::endl;
	}
	fr1.close();
	fr2.close();
}
void ListRusiavimas2strat(std::list<Studentai> &StudentuInfo, int n){
	std::stringstream ss;
	ss << n;
	std::string pav1= ss.str() +"islaike.txt";
	std::string pav2= ss.str()+ "neislaike.txt";
	std::list<Studentai> neislaike;
	std::ofstream fr1(pav1);
	std::ofstream fr2(pav2);
			fr1 << std::right << std::setw(23) << "Islaike" << std::endl; 
			fr1 << std::left << std::setw(13) << "Pavarde" << std::left  << std::setw(13) << "Vardas" << std::left << std::setw(7) << "Galutinis balas" << std::endl;
			fr1 <<std::endl;
		    fr2 << std::right << std::setw(23) << "Neislaike" << std::endl; 
		    fr2 << std::left << std::setw(13) << "Pavarde" << std::left  << std::setw(13) << "Vardas" << std::left << std::setw(7) << "Galutinis balas" << std::endl;
			fr2 <<std::endl;
std::list<Studentai>::iterator it =StudentuInfo.begin();
while(it != StudentuInfo.end()){
		if(it->egzGal < 5){
			if(it->fname == "") break;
			 neislaike.push_back(*it);
}

it++;
	}
	std::list<Studentai>::iterator it1 =StudentuInfo.begin();
	while(it1 !=StudentuInfo.end()){
		if(it1->egzGal <5){
			if(it1->fname == "") break;
		    it1 = StudentuInfo.erase(it1);
		}	
		else it1++;
}
	for(std::list<Studentai>::iterator it1 = StudentuInfo.begin(); it1 !=StudentuInfo.end(); it1++){
		fr1 << std::left << std::setw(13) << it1->lname << std::left << std::setw(13) << it1->fname << std::left << std::setw(7) << it1->egzGal << std::endl;
	}
		for(std::list<Studentai>::iterator it2 = neislaike.begin(); it2 != neislaike.end(); it2++){
		fr2 << std::left << std::setw(13) << it2->lname << std::left << std::setw(13) << it2->fname << std::left << std::setw(7) << it2->egzGal << std::endl;
	}
	fr1.close();
	fr2.close();
}



