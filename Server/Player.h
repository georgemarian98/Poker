#ifndef PLAYER_H
#define PLAYER_H

#include "Card.h"
#include <vector>

class Player
{
private:
	_Carte carti[2];
	int buget;
	bool check = false;

public:
	Player( );

	std::vector<_Carte> getCarti( ) { return {carti[0],carti[1]}; };
	   
	friend std::ostream& operator<< (std::ostream& out, const Player& jucator){
		out << *jucator.carti[0] << " " << *jucator.carti[1];
		return out;
	};
};

#endif