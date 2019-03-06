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
                    Generuoti(std::round(pow(10, z)));
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

