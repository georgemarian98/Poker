#include "CardSerialization.h"
/*
    1 - Carti puse pe masa
    2 - Carti playeri
    3 - Castigatori
    4 - Exit
*/

std::shared_ptr<CardSerialization> CardSerialization::m_instance = NULL;

CardSerialization::CardSerialization(int port) : port(port)
{
    //////////////////// Partea de server ////////////////////
    struct sockaddr_in serv_addr;

    listenFd = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(port);

    if (bind(listenFd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
        perror("bind");
        exit(-1);
    }

    if (listen(listenFd, 10) == -1){
        perror("Failed to listen\n");
        exit(-1);
    }

    while( true ){
    	std::cout << "Asteptam clienti!\n";

		//Response - trimite date 
        int connfdResp = accept(listenFd, (struct sockaddr *)NULL, NULL);
        if (connfdResp < 0){
            perror("accept response");
            exit(-1);
        }

		//Receive primeste date
        int connfdRecv = accept(listenFd, (struct sockaddr *)NULL, NULL);
		if (connfdRecv < 0){
            perror("accept receive");
            exit(-1);
        }

        fdClientResp.push_back(connfdResp);
        fdClientRecv.push_back(connfdRecv);

		int nr = fdClientResp.size();
        std::cout << "Nr jucatori: " << nr << std::endl;

		if(nr >= 2){
			std::cout << "Incepem jocul? [Y/N]\n";

			tcflush(STDIN_FILENO, TCIFLUSH);
			char raspuns;
			std::cin >> raspuns;

			if(raspuns == 'Y' || raspuns == 'y')
				break;
		}

    }
}

std::shared_ptr< CardSerialization> CardSerialization::getInstance(const int port)
{
    if( m_instance == NULL){
        m_instance = std::shared_ptr< CardSerialization>(new CardSerialization(port));
    }

    return m_instance;
}

void CardSerialization::destroy() 
{
    close(listenFd);

    for (unsigned int i = 0, n = fdClientResp.size(); i < n; i++){
        close( fdClientResp[i] );
        close( fdClientRecv[i] );
    }

	fdClientRecv.clear();
	fdClientResp.clear();

}

bool CardSerialization::writeClients(const int index, Player& jucator) 
{
    writeObject(fdClientResp[index], jucator.getCarti() , 2);

    unsigned int buget = jucator.getBuget();
    if(write(fdClientResp[index], &buget, sizeof(buget)) < 0){
        perror("Scriere buget");
        return false;
    }

    return true;
}

void CardSerialization::writeClients(const std::vector<_Carte>& input, const char& flag, const std::string& mesaj)
{
    for(const int& fd : fdClientResp){
        writeObject(fd, input ,flag , mesaj);
    }
}

bool CardSerialization::writeClients(const int index, const char& flag)
{
    if(write(fdClientResp[index], &flag, sizeof(flag)) < 0){
        perror("Scriere actiune");
        return false;
    }

    return true;
}

void CardSerialization::writeClients(const char& flag)
{
    for(unsigned int i = 0,n = fdClientResp.size(); i < n; i++){
        writeClients(i, flag);
    }
}

void CardSerialization::closeCommunication(const int index) 
{
    close(fdClientRecv[index]);
    close(fdClientResp[index]);

    fdClientResp.erase( fdClientResp.begin() + index);
	fdClientRecv.erase( fdClientRecv.begin() + index);
}

char CardSerialization::readClientAction(const int index)
{
    char output = -1;
    if(read(fdClientRecv[ index ], &output, sizeof(output) ) < 0){
        perror("Citire actiune");
        return 0;
    }

    return output;
}

///////////////////////////////////////////Serialization //////////////////////////////////

bool CardSerialization::writeObject(int fd, const std::vector<_Carte>& input, const char& flag, const std::string& mesaj)
{
    const unsigned char count = input.size();

    if(write(fd, &flag, sizeof(char)) < 0){
        perror("Scriere flag");
        return false;
    }

    //Cand trimite datele castigatorului trimite si un string cu ce combinatie o avut
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
