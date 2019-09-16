#pragma once
#include <vector>
#include <map>
#include "Card.h"
#include "Player.h"
#include "ComboHand.h"



class Poker
{
private:
	std::vector<Player> jucatori;
	std::vector<_Carte> cartiAratate;
	const int cartiPuse[3] = {3, 1, 1};

	std::vector<Combo*> combinatiiPosibile;
private:
	void afisare( );
	void check( );
public:
	Poker(int noJucatori = 1);
	~Poker( );
	void run( );
};

