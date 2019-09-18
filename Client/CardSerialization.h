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

    template<typename T>
    static T readAction(int fd);
};

template<typename T>
T CardSerialization::readAction(int fd)
{
    T action = -1;
    if(read(fd, &action, sizeof(action) ) < 0){
            perror("Citire actiune");
            return action;
    }
    return action;
}

#endif