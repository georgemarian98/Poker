#ifndef POKER_H
#define POKER_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <pthread.h>

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
    int listenFd = 0;
    const int port = 5000;
    std::vector<int> fdClientRecv;
    std::vector<int> fdClientResp;

    //Poker
    std::vector<Player> m_jucatori;
    std::vector<_Carte> m_cartiAratate;
    const int cartiExtrase[3] = {3, 1, 1};

	std::vector<Combo*> combinatiiPosibile;

private:
	void check( );
    void bids();
    void trimiteDate( const std::vector<_Carte>& cartiPuse,const Date& status,const std::string& mesaj);
    bool handleInput(char input, int index);

public:
    Poker();
    ~Poker();

	void run( );
};


#endif