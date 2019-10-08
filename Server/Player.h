#ifndef PLAYER_H
#define PLAYER_H

#include "Card.h"
#include <vector>

class Player
{
private:
	_Carte carti[2];
	unsigned int buget;
	bool check = false;

public:
	Player( );

	std::vector<_Carte> getCarti( ) { return {carti[0],carti[1]}; };

	void setCheck(bool _check) { this->check = _check;};
	const bool getCheck() const { return check;};
	const unsigned int& getBuget() const { return buget;};
	   
	friend std::ostream& operator<< (std::ostream& out, const Player& jucator){
		out << *jucator.carti[0] << " " << *jucator.carti[1];
		return out;
	};

};

#endif