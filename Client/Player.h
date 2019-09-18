#ifndef PLAYER_H
#define PLAYER_H

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

#include "Card.h"
#include "CardSerialization.h"

class Player
{
private:
    int sockFdRecv = 0;
    int sockFdResp = 0;
    const int port = 5000;
    const char ip[10] = "127.0.0.1";

    bool input = false;
    std::vector<Carte> m_cartiMana;
    unsigned int buget = 0;

private:
    bool checkResponse(char response, std::vector<Carte>& cartiMasa);
    void writeAction(bool action);
    void afisare(const std::vector<Carte>& carti);
public:
    Player();
    ~Player();

    void run();
};


#endif