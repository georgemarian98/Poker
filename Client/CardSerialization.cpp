#include "CardSerialization.h"

bool CardSerialization::writeObject(int fd, const std::vector<Carte>& input)
{
    const unsigned char count = input.size();

    if(write(fd,&count, sizeof(char)) < 0){
        perror("Scriere dimensiune vector");
        return false;
    }

    for(Carte carte : input){
        if(write(fd, &(carte.no), sizeof(carte.no)) < 0){
            perror("Scriere numar");
            return false;
        }

        if(write(fd, carte.simbol.c_str() , 3) < 0){
            perror("Scriere simbol");
            return false;
        }
    }

    return true;
}

bool CardSerialization::writeAction(int fd, const char input)
{
    if(write(fd, &input , sizeof(input)) < 0){
        perror("Scriere actiune");
        return false;
    }
    return true;
}

std::vector<Carte> CardSerialization::readObject(int fd)
{
    std::vector<Carte> output;
    unsigned char count = 0;

    if( read(fd, &count, sizeof(char)) < 0 ){
        perror("Citire dimensiune");
        return output;
    }

    output.reserve(count);

    for (int i = 0; i < count; i++){
        char nr = 0;
        char sir[4];

        if(read(fd, &nr, sizeof(nr) ) < 0){
            perror("Citire numar");
            return output;
        }
        
        if(read(fd, sir , 3) < 0){
            perror("Citire simbol");
            return output;
        }

        sir[3] = 0;
        output.push_back(Carte(nr,sir));
    }
    
    return output;
}

unsigned char CardSerialization::readAction(int fd)
{
    unsigned char action = -1;
    if(read(fd, &action, sizeof(action) ) < 0){
            perror("Citire actiune");
            return action;
    }
    return action;
}