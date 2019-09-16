#ifndef CARDSERIALIZATION_H
#define CARDSERIALIZATION_H

#include "Card.h"

#include <vector>
#include <unistd.h>

class CardSerialization
{
private:

public:
    static bool writeObject(int fd, const std::vector<_Carte>& input, const char& flag, const std::string& mesaj);
    static bool writeAction(int fd, const char& flag);
    static std::vector<Carte> readObject(int fd);
    static char readAction(int fd);
};

#endif