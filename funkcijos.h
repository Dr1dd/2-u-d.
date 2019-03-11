#ifndef FUNKCIJOS_H
#define FUNKCIJOS_H
#include <list>
#include <deque>
struct Studentai{
	std::string fname, lname;
	double egzGal;
	double mediana;
	std::vector<double> ND;
};
     
Studentai Informacija();
void Spausdinti(std::vector<Studentai> Studentai, std::string tipas, int studSkaic);
void Spausdinti(std::vector<Studentai> Studentai);
void SpausdintiList(std::list<Studentai> &StudentuInfo);
void SpausdintiDeque(std::deque<Studentai> &StudentuInfo);
double Mediana(Studentai Stud, int n, int p);
std::string Tikrinti(std::string tekstas);
double TikrintiSkaicius(std::string tekstas);
void Skaitymas(std::vector<Studentai> &StudentuInfo, std::string pav);
void SkaitymasList(std::list<Studentai> &StudentuInfo, std::string pav);
void SkaitymasDeque(std::deque<Studentai> &StudentuInfo, std::string pav);
bool Lyginimas(const Studentai &a, const Studentai &b);
bool fileExists(const std::string& filename);
void Generuoti(int n);
void Generuoti(std::vector<Studentai> StudentuInfo, int n);
void Generuoti(std::list<Studentai> &StudentuInfo, int n);
void Generuoti(std::deque<Studentai> StudentuInfo, int n);
void FailuIrasymas(std::vector<Studentai> StudentuInfo, int n);
void FailuIrasymas(std::list<Studentai> &StudentuInfo, int n);
void FailuIrasymas(std::deque<Studentai> StudentuInfo, int n);
void VectorRusiavimas1strat(std::vector<Studentai> StudentuInfo, int n);
void ListRusiavimas1strat(std::list<Studentai> &StudentuInfo, int n);
void DequeRusiavimas1strat(std::deque<Studentai> StudentuInfo, int n);
void VectorRusiavimas2strat(std::vector<Studentai> StudentuInfo, int n);
void ListRusiavimas2strat(std::list<Studentai> &StudentuInfo, int n);
void DequeRusiavimas2strat(std::deque<Studentai> StudentuInfo, int n);
void vector();
void list();
void deque();
bool maziau(const Studentai &i);
#endif
