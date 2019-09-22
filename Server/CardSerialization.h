#ifndef CARDSERIALIZATION_H
#define CARDSERIALIZATION_H

#include "Card.h"
#include "Player.h"

#include <vector>
#include <memory>
#include <unistd.h>

class CardSerialization
{
private:
    int listenFd = 0;
    int port;
    std::vector<int> fdClientRecv;
    std::vector<int> fdClientResp;
    static std::shared_ptr< CardSerialization> instance;

    CardSerialization(int port) {std::cout << "insta si aici?\n";};

public:
    static bool writeObject(int fd, const std::vector<_Carte>& input, const char& flag, const std::string& mesaj);
    static bool writeObject(int fd, Player& jucator);
    static bool writeAction(int fd, const char& flag);
    static std::vector<Carte> readObject(int fd);
    static char readAction(int fd);

    static std::shared_ptr< CardSerialization> getInstance(const int port);
};

#endif