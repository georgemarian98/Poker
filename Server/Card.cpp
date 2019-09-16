#include "Card.h"

/*
	2660  WHITE HEART SUIT
	2663  WHITE DIAMOND SUIT
	2665  WHITE SPADE SUIT
	2666  WHITE CLUB SUIT
*/

const char Card::numar[13] = {'2', '3', '4', '5', '6', '7', '8', '9', 'D', 'J', 'Q', 'K', 'A'};
const std::string Card::simbol[4] = {"\u2660", "\u2663", "\u2665", "\u2666"};
std::vector<_Carte> Card::carti;

_Carte Card::generareCarte( )
{
	while(true){
		int indexSimbol = rand( ) % 4;
		int indexNo = rand( ) % 13;

		if(gasit( Carte(numar[indexNo], simbol[indexSimbol]) ) == false){
			carti.push_back( std::make_shared<Carte>(numar[indexNo], simbol[indexSimbol]) );
			break;
		}
	}

	return carti.back( );
}

bool Card::gasit(const Carte& carte)
{
	for(auto cauta : carti){
		if(*cauta == carte)
			return true;
	}
	return false;
}

int Card::compareToNumber(const _Carte& carte1,const _Carte& carte2)
{
	if(carte1->no == carte2->no){
		return 0;
	}
	else if(carte1->no > carte2->no){
		return 1;
	}
	else if(carte1->no < carte2->no){
		return -1;
	}
	 
	return -2;
}

int Card::compareToSymbol(const _Carte& carte1,const _Carte& carte2)
{
	if(carte1->simbol == carte2->simbol){
		return 0;
	}
	else if(carte1->simbol > carte2->simbol){
		return 1;
	}
	else if(carte1->simbol < carte2->simbol){
		return -1;
	}

	return -2;
}

int Card::getIndex(const _Carte& carte)
{
	for(int i = 0; i < 13; i++){
		if(numar[i] == carte->no)
			return i;
	}
	return -1;
}

int Card::getIndexSimbol(const _Carte& carte)
{
	for(int i = 0; i < 4; i++){
		if( simbol[i] == carte->simbol )
			return i;
	}
	return 0;
}

void Card::reset( )
{
	carti.clear( );
}

