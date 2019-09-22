#ifndef CARDSERIALIZATION_H
#define CARDSERIALIZATION_H

#include "Card.h"
#include "Player.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>

#include <string.h>
#include <vector>
#include <memory>

class CardSerialization
{
private:
    int listenFd = 0;
    int port;
    std::vector<int> fdClientRecv;
    std::vector<int> fdClientResp;
    static std::shared_ptr< CardSerialization> instance;

    CardSerialization(int port);
    bool writeObject(int fd, const std::vector<_Carte>& input, const char& flag, const std::string& mesaj = "");

public:
    static std::shared_ptr< CardSerialization> getInstance(const int port);

    unsigned int getNoClienti() {return fdClientRecv.size();}

    bool writeClient(const int index, Player& jucator);
    void writeAllClients(const std::vector<_Carte>& input, const char& flag, const std::string& mesaj = "");
    bool writeClientAction(const int index, const char& flag);
    void writeAllClientsAction(const char& flag);
    char readClientAction(const int index);

    void destroy();
    void closeCommunication(const int index);
};

#endif