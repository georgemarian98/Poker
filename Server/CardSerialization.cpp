#include "CardSerialization.h"
/*
    1 - Carti puse pe masa
    2 - Carti playeri
    3 - Castigatori
    4 - Exit
*/

bool CardSerialization::writeObject(int fd, const std::vector<_Carte>& input, const char& flag, const std::string& mesaj)
{
    const unsigned char count = input.size();

    if(write(fd, &flag, sizeof(char)) < 0){
        perror("Scriere flag");
        return false;
    }

    if( flag == 3){
        const unsigned int dim = mesaj.size();

        if( write(fd, &dim , sizeof(dim)) < 0){
            perror("Scriere dim string");
            return false;
        }

        if( write(fd, mesaj.c_str() , dim) < 0){
            perror("Scriere string");
            return false;
        }
    }

    if(flag == 4){
        return true;
    }

    if(write(fd,&count, sizeof(char)) < 0){
        perror("Scriere dimensiune vector");
        return false;
    }

    for(_Carte carte : input){
        if(write(fd, &(carte->no), sizeof(carte->no)) < 0){
            perror("Scriere numar");
            return false;
        }

        if(write(fd, carte->simbol.c_str() , 3) < 0){
            perror("Scriere simbol");
            return false;
        }
    }

    return true;
}

bool CardSerialization::writeObject(int fd,Player& jucator)
{
    CardSerialization::writeObject(fd, jucator.getCarti() , 2 , "");

    unsigned int buget = jucator.getBuget();
    if(write(fd, &buget, sizeof(buget)) < 0){
        perror("Scriere buget");
        return false;
    }

    return true;
}

bool CardSerialization::writeAction(int fd, const char& flag)
{
    if(write(fd, &flag, sizeof(char)) < 0){
        perror("Scriere flag");
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

    for (int i = 0; i < count; i++)
    {
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

char CardSerialization::readAction(int fd)
{
    char output = -1;
    if(read(fd, &output, sizeof(output) ) < 0){
        perror("Citire actiune");
        return 0;
    }

    return output;
}