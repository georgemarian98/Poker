#ifndef POKER_H
#define POKER_H

#include<vector>
#include <map>
#include <set>

#include "Player.h"
#include "CardSerialization.h"
#include "ComboHand.h"

enum Date{
	CartiMasa = 1,
	CartiPlayer, Castigat, Exit
};

enum State {
	Check = 1,
	Fold, Call, Raise
};

class Poker
{
private:
    //Server
    const int port = 5000;
    std::shared_ptr< CardSerialization> m_server;

    //Poker
    std::vector<Player> m_jucatori;
    std::vector<_Carte> m_cartiAratate;
    const int cartiExtrase[3] = {3, 1, 1};

	std::vector<Combo*> combinatiiPosibile;

private:
	void check( );
    void bids();
    bool handleInput(char input, int index);

    bool checkPlayers();
    void resetCheck();

public:
    Poker();
    ~Poker();

	void run( );
};


#endif