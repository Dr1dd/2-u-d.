#ifndef FUNKCIJOS_H
#define FUNKCIJOS_H

struct Studentai{
	std::string fname, lname;
	double egzGal;
	double mediana;
	std::vector<int> ND;
};
     
Studentai Informacija();
void Spausdinti(std::vector<Studentai> Studentai, std::string tipas, int studSkaic);
void Spausdinti(std::vector<Studentai> Studentai);
double Mediana(Studentai Stud, int n, int p);
std::string Tikrinti(std::string tekstas);
double TikrintiSkaicius(std::string tekstas);
void Skaitymas(std::vector<Studentai> &StudentuInfo, std::string pav);
bool Lyginimas(const Studentai &a, const Studentai &b);
bool fileExists(const std::string& filename);
void Generuoti(int n);

#endif
