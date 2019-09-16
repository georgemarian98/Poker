#include "Card.h"

const char Card::numar[13] = {'2', '3', '4', '5', '6', '7', '8', '9', 'D', 'J', 'Q', 'K', 'A'};
const char Card::simbol[4] = {3, 4, 5, 6};
std::vector<_Carte> Card::foo;

_Carte Card::generareCarte( )
{
	while(true){
		int indexSimbol = rand( ) % 4;
		int indexNo = rand( ) % 13;

		if(gasit(Carte(numar[indexNo], simbol[indexSimbol])) == false){
			foo.push_back( std::make_shared<Carte>(numar[indexNo], simbol[indexSimbol]) );
			break;
		}
	}

	return foo.back( );
}

int Card::compareToNumber(const Carte& carte1,const Carte& carte2)
{
	if(carte1.no == carte2.no){
		return 0;
	}
	else if(carte1.no > carte2.no){
		return 1;
	}
	else if(carte1.no < carte2.no){
		return -1;
	}
	 
}

int Card::compareToSymbol(const Carte& carte1,const Carte& carte2)
{
	if(carte1.simbol == carte2.simbol){
		return 0;
	}
	else if(carte1.simbol > carte2.simbol){
		return 1;
	}
	else if(carte1.simbol < carte2.simbol){
		return -1;
	}
}


bool Card::gasit(const Carte& carte)
{
	for(auto cauta : foo){
		if(*cauta == carte)
			return true;
	}
	return false;
}

int Card::getIndex(const Carte& carte)
{
	for(int i = 0; i < 13; i++){
		if(numar[i] == carte.no)
			return i;
	}
	return -1;
}

int Card::getIndexSimbol(const Carte& carte)
{
	for(int i = 0; i < 4; i++){
		if(simbol[i] == carte.simbol)
			return i;
	}
	return 0;
}

int Card::reset( )
{
	foo.clear( );
	return 0;
}

