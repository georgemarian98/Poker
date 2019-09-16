#pragma once
#include <time.h>
#include <stdlib.h> 
#include <iostream>
#include <vector>
#include <memory>

struct Carte{
	char no;
	char simbol;

	Carte(): no(0), simbol(0){ };
	Carte(char no, char simbol) : no(no), simbol(simbol) { };

	friend std::ostream& operator<< (std::ostream& out, const Carte& carte)
	{
		(carte.no == 'D') ? out << 10 : out << carte.no;
		out  << carte.simbol;

		return out;
	};

	bool operator== (const Carte& carte) const
	{
		return (this->no == carte.no && this->simbol == carte.simbol);
	}
};

#define _Carte std::shared_ptr<Carte>

class Card
{
private:
	static const char numar[13];
	static const char simbol[4];
	static std::vector<_Carte> foo;

private:
	static bool gasit(const Carte& carte);

public:
	static _Carte generareCarte( );
	static int compareToNumber(const Carte& carte1,const Carte& carte2);
	static int compareToSymbol(const Carte& carte1,const Carte& carte2);
	static int getIndex(const Carte& carte);
	static int getIndexSimbol(const Carte& carte);
	static int reset( );
};

