#ifndef CARDSERIALIZATION_H
#define CARDSERIALIZATION_H

#include "Card.h"

#include <vector>
#include <unistd.h>

class CardSerialization
{
public:
    static bool writeObject(int fd, const std::vector<Carte>& input);
    static bool writeAction(int fd, const char input);
    static std::vector<Carte> readObject(int fd);
    static unsigned char readAction(int fd);
};

#endif