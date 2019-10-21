#ifndef CARD_H
#define CARD_H

#include <time.h>
#include <stdlib.h> 
#include <iostream>
#include <vector>
#include <memory>
#include <string.h>

struct Carte{
	char no;
	std::string simbol;

	Carte(): no('X'),simbol("X"){ };
	Carte(const char no,const  std::string simbol) : no(no), simbol(simbol) {};

	friend std::ostream& operator<< (std::ostream& out, const Carte& carte){
		(carte.no == 'D') ? out << 10 : out << carte.no;
		out  << carte.simbol;

		return out;
	};

	bool operator== (const Carte& carte) const{
		return (this->no == carte.no && carte.simbol == this->simbol);
	}
};

typedef std::shared_ptr<Carte> _Carte;

class Card
{
private:
	static const char numar[13];
	static const std::string simbol[4];
	static std::vector<_Carte> carti;

private:
	static bool gasit(const Carte& carte);

public:
	static _Carte generareCarte( );
	static int compareToNumber(const _Carte& carte1,const _Carte& carte2);
	static int compareToSymbol(const _Carte& carte1,const _Carte& carte2);
	static int getIndex(const _Carte& carte);
	static int getIndexSimbol(const _Carte& carte);
	static void reset( );
};

#endif
