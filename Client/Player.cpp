#include "Player.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>


Player::Player()
{
    //////////////////////////// Partea de Server /////////////////////
    struct sockaddr_in serv_addr;

    if ((sockFdRecv = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("Receive socket");
        exit(-1);
    }

    if ((sockFdResp = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("Response socket");
        exit(-1);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons( port );
    serv_addr.sin_addr.s_addr = inet_addr( ip );

    //descriptorul de primire date
    if (connect(sockFdRecv, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
        perror("Connect received socket");
        exit(-1);
    }
    
    //descriptorul de trimitere date
    if (connect(sockFdResp, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
        perror("Connect response socket");
        exit(-1);
    }    
}

void Player::run()
{
    bool run = true;
    std::vector<Carte> CartiMasa;

    while ( run ){
        //flag pentru datele ce urmeaza sa fie trimise
        const unsigned char flag = CardSerialization::readAction(sockFdRecv);
        
        std::system("clear");
        run = checkResponse(flag, CartiMasa);

        afisare(CartiMasa);
        afisare(m_cartiMana);

        writeAction(run);
    }
}

bool Player::checkResponse(char response, std::vector<Carte>& cartiMasa)
{
    switch (response)
    {
        //sunt trimise cartile de pe masa
        case 1:
        {
            std::vector<Carte> aux = CardSerialization::readObject(sockFdRecv);
            cartiMasa.insert(cartiMasa.end(), aux.begin(), aux.end());
            input = true;
        }
            break;

        // sunt trimise cartiile din mana jucatorului
        case 2:
            m_cartiMana = CardSerialization::readObject(sockFdRecv);
            break;

        // sunt trimise datele referitoare la cine a castigat si sunt procesate datele
        case 3:
        {
            bool castigat = false;

            char str[100];
            int dim = -1;
            read(sockFdRecv, &dim , sizeof(dim));
            read(sockFdRecv, str , dim);

            std::vector<Carte> cartiCastigatoare = CardSerialization::readObject(sockFdRecv);

            //Verificam daca cartiile castigatoare trimise sunt cele din mana jucatorului
            for(Carte castigatori : cartiCastigatoare){
                for(Carte cartiPlayer : m_cartiMana){
                    if( castigatori == cartiPlayer){
                        castigat = true;
                        break;
                    }
                }
            }

            str[dim] = 0;

            if ( castigat ){
                std::cout << "Ai castigat!\nAi avut: " << str << std::endl;;
            } else {
                std::cout << "Ai pierdut!\nCastigatorul o avut: " << str << " ";
                afisare(cartiCastigatoare);
            }
        }

        //iesire din joc
        default:
            return false;
            break;
    }

    return true;
}

void Player::writeAction(bool action)
{
    if ( action == false ){
        return;
    }
    
    std::cout << std::endl;
    std::cout << "1) Check\n";
    std::cout << "2) Fold\n";
    std::cout << "3) Call\n";
    std::cout << "4) Raise\n";


    if(input){
        unsigned char aux = -1; 

        while( true ){
            aux = CardSerialization::readAction(sockFdRecv);
            if(aux == 4)
                break;
            
            std::cout << "Ce alegi: ";

            //Arunca ce era in bufferul de input a terminalului
            tcflush(STDIN_FILENO, TCIFLUSH);
        
            int resp;
            std::cin >> resp;
            CardSerialization::writeAction(sockFdResp, resp);
        }
    }
}

void Player::afisare(const std::vector<Carte>& carti)
{    
    for(Carte aux : carti){
        std::cout <<  aux << " " ;
    }
    std::cout << std::endl;
}

Player::~Player()
{
    //cleaning
    close(sockFdResp);
    close(sockFdRecv);
}
