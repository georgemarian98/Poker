#pragma once
#include "Card.h"

#include <vector>
#include <set>

class Player
{
private:
	_Carte carti[2];
	int buget;

public:
	Player( );

	std::vector<_Carte> getCarti( ) { return {carti[0],carti[1]}; };
	   
	friend std::ostream& operator<< (std::ostream& out, const Player& jucator)
	{
		out << *jucator.carti[0] << " " << *jucator.carti[1];

		return out;
	};
};

