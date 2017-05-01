#include <iostream>
#include <cstring>
#include <cmath>
//FINISHED
class Igrachka 
{
public:
	virtual float getVolumen() const = 0;
	virtual float getMasa() const = 0;
	virtual inline ~Igrachka() {}
};

class Forma 
{
protected:
	char boja[100];
	int gustina;
public:
	// да се имплементираат потребните методи
	Forma()
	{
		for (unsigned short i = 0; i < 100; ++i)
			boja[i] = '\0';
		gustina = 0;
	}
	Forma(const char* _boja, const int _gustina) :gustina(_gustina)
	{
		//strcpy(boja, _boja);
		strcpy_s(boja, strlen(_boja), _boja);
	}
	virtual ~Forma() {}
};

class Topka :public Igrachka, public Forma
{
protected:
	unsigned radius;
public:
	Topka(const char* _boja, const int _gustina, const unsigned _radius) :
		Forma(_boja, _gustina),
		radius(_radius) {}
	
	inline float getMasa() const { return this-> getVolumen()*gustina; }
	inline float getVolumen() const { return 4 / (float)3 * (3.14 * pow(radius, 3)); }
	~Topka() { Igrachka::~Igrachka(); Forma::~Forma(); }
};

class Kocka :public Igrachka, public Forma
{
protected:
	unsigned visina;
	unsigned shirina;
	unsigned dlabocina;
public:
	Kocka(const char* _boja,const unsigned _gustina, const unsigned _visina, 
		const unsigned _shirina, const unsigned _dlabocina) :
		Forma(_boja, _gustina),
		visina(_visina), shirina(_shirina), dlabocina(_dlabocina) {}

	inline float getMasa() const { return this-> getVolumen()*gustina; }
	inline float getVolumen() const { return visina*shirina*dlabocina; }
	~Kocka() { Igrachka::~Igrachka(); Forma::~Forma(); }
};

int main() 
{
	//vnesi informacii za kupche
	Igrachka** kupche;
	char boja[100];
	unsigned gustina;
	unsigned radius;
	unsigned visina;
	unsigned shirina;
	unsigned dlabocina;
	unsigned short par;
	unsigned short igracki;

	std::cin >> igracki;
	kupche = new Igrachka*[igracki];

	for (unsigned short i = 0; i < igracki; ++i)
	{
		std::cin >> par;
		if (par == 1)
		{
			std::cin >> boja >> gustina >> radius;
			kupche[i] = new Topka(boja, gustina, radius);
		}
		else if (par == 2)
		{
			std::cin >> boja >> gustina >> visina >> shirina >> dlabocina;
			kupche[i] = new Kocka(boja, gustina, visina, shirina, dlabocina);
		}
		else std::cerr << "Gresen vlez\n";
	}
	//vnesi informacii za igrachkata na Petra
	std::cin >> boja >> gustina >> visina >> shirina >> dlabocina;
	Kocka* Petra;
	Petra = new Kocka(boja, gustina, visina, shirina, dlabocina);

	//baranje 1
	float masa = 0.0;
	for (unsigned short i = 0; i < igracki; ++i)
		masa += kupche[i]->getMasa();
	if (masa > Petra->getMasa())
		std::cout << "DA\n";
	else std::cout << "NE\n";

	//baranje 2
	Igrachka* volumen;
	volumen = kupche[0];
	for (unsigned short i = 0; i < igracki; ++i)
		if (kupche[i]->getVolumen() > volumen->getVolumen())
			volumen = kupche[i];
	float razlika = 0.0;
	razlika = volumen->getVolumen() - Petra->getVolumen();
	std::cout << "Razlikata e:" << fabs(razlika);

	delete Petra;
	delete[] kupche;
	delete volumen;
	return 0;
}
