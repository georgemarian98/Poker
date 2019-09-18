#include "Poker.h"
#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>


Poker::Poker()
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
		std::system("clear");
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

    //////////////////// Partea de joc ////////////////////

    int noJucatori = fdClientResp.size();
    m_jucatori.reserve(noJucatori);

	//Trimiterea cartiilor din mana catre jucatori 
	for(int i = 0; i < noJucatori; i++){
		m_jucatori.push_back(Player( ));
        CardSerialization::writeObject(fdClientResp[i], m_jucatori.back().getCarti(), Date::CartiPlayer , "");
	}

    std::weak_ptr<Carte> carteArsa = Card::generareCarte( );

    combinatiiPosibile.push_back(new Combo( ));
	combinatiiPosibile.push_back(new OnePair( ));
	combinatiiPosibile.push_back(new TwoPair( ));
	combinatiiPosibile.push_back(new ThreeOfAKind( ));
	combinatiiPosibile.push_back(new Straight( ));
	combinatiiPosibile.push_back(new Flush( ));
	combinatiiPosibile.push_back(new FullHouse( ));
	combinatiiPosibile.push_back(new FourOfTheKind( ));
	combinatiiPosibile.push_back(new StraightFlush( ));
	combinatiiPosibile.push_back(new RoyalFlush( ));
}


Poker::~Poker()
{
	//cleaning
    for (int i = 0, n = fdClientResp.size(); i < n; i++){
        close( fdClientResp[i] );
        close( fdClientRecv[i] );
    }

    close(listenFd);

    for(auto combinatii : combinatiiPosibile){
		delete combinatii;
	}
	
	Card::reset( );

	fdClientRecv.clear();
	fdClientResp.clear();
	m_jucatori.clear();
	m_cartiAratate.clear();
	combinatiiPosibile.clear( );
}

void Poker::check( )
{
	struct Mesaj{
		float priority;
		std::string mesaj;
	};
	struct Greater{
		//crescator
		bool operator()(const Mesaj& Left,const Mesaj& Right) const
		{
			return (Left.priority > Right.priority);
		}
	};

	//hash map sortat
	std::map<Mesaj, std::vector<Player>,Greater> castigatori;
	
	for(auto jucator : m_jucatori){
		std::set<Combo*, Comparable> combinatii;
		
		for(auto combinatie : combinatiiPosibile){
			//daca are combinatia o punem in set
			if(combinatie->check(m_cartiAratate, jucator.getCarti( )) == true){
				combinatii.insert(combinatie);
			}
		}
		//cea mai buna combinatie a jucatorului
		Combo* aux = *combinatii.begin( );

		castigatori[ {aux->priority( ), aux->mesaj()} ].push_back(jucator);
	}

	//cea mai buna mana
    std::string mesaj = castigatori.begin( )->first.mesaj;
	std::vector<_Carte> cartiCastigatoare;
	cartiCastigatoare.reserve( 2 * castigatori.begin( )->second.size() );

	//punem cartiile jucatoriilor castigatori impreuna sa le trimitem odata
	for(auto castigator : castigatori.begin( )->second){
		std::vector<_Carte> aux = castigator.getCarti();
		cartiCastigatoare.insert(cartiCastigatoare.end(), aux.begin(), aux.end());
	}

	//trimitem datele
    for(int fd : fdClientResp){
        CardSerialization::writeObject(fd, cartiCastigatoare , Date::Castigat , mesaj);
    }
}

void Poker::run( )
{
	for(int i = 0; i < 3; i++){
		std::vector<_Carte> cartiPuse;
		cartiPuse.reserve(cartiExtrase[i]);

        //extragere carti
		for(int index = 0; index < cartiExtrase[i]; index++){
			cartiPuse.push_back(Card::generareCarte( ));
		}

		//ardem cartea
		std::weak_ptr<Carte> carteArsa = Card::generareCarte( );

		//trimiterea cartilor extrase catre clienti
        trimiteDate( cartiPuse, Date::CartiMasa, "");
        m_cartiAratate.insert(m_cartiAratate.end(), cartiPuse.begin(), cartiPuse.end());

		//user input
		bids();
	}
	//desemnare castigator
	check( );
}

void Poker::trimiteDate(const std::vector<_Carte>& cartiPuse,const Date& status,const std::string& mesaj  )
{
    for(int fd : fdClientResp){
        CardSerialization::writeObject(fd , cartiPuse, status , mesaj);
    }
}

void Poker::bids()
{
	// for(int i = 0, n = fdClientResp.size(); i < n; i++){
	// // 	char resp = 1;
	// // 	CardSerialization::writeAction(fdClientResp[i], resp);

	// 	//daca o dat fold decrementam i ca sa nu sarim peste un jucator
	// 	if( handleInput( CardSerialization::readAction(fdClientRecv[i]), i) == true && i != n -1){
	// 		i--;
	// 		n--;
	// 	}
	// }
	

	unsigned int index = 0;
	unsigned int n = fdClientRecv.size();
	bool run = true;

	while( run ){
		char resp = 1;
		CardSerialization::writeAction(fdClientResp[ index ], resp);

		//daca o dat fold decrementam i ca sa nu sarim peste un jucator
		if( handleInput( CardSerialization::readAction(fdClientRecv[ index ]), index) == true && index != n -1){
			index--;
			n--;
		}

		index = ( index + 1 ) % n;
		run = !checkPlayers();
	}

	resetCheck();
	
	for(int fd : fdClientResp){
		char resp = Exit;
		CardSerialization::writeAction(fd, resp);
	}
}

bool Poker::handleInput(char input, int index)
{
	std::cout << "Am primit: " << (int)input << ", de la jucatorul: " << index << std::endl;

	switch (input)
	{
	case Check:
		//Nu face nimic
		m_jucatori[index].setCheck(true);
		break;

	case Fold:
		//Jucatorul iese din joc
	{
		m_jucatori.erase( m_jucatori.begin() + index);
		close(fdClientRecv[index]);

		char resp = Exit;
		write(fdClientResp[index], &resp, sizeof(resp));
		close(fdClientResp[index]);

		fdClientResp.erase( fdClientResp.begin() + index);
		fdClientRecv.erase( fdClientRecv.begin() + index);
		return true;
	}
		break;

	case Call:
		//Jucatorul pariaza
		//TODO
		break;

	case Raise:
		//Jucatorul creste suma pariata
		//TODO
		break;

	default:
		break;
	}

	return false;
	
}

bool Poker::checkPlayers()
{
	for(Player jucator : m_jucatori){
		if( jucator.getCheck() == false)
			return false;
	}

	return true;
}

void Poker::resetCheck()
{
	for(int i = 0, n = m_jucatori.size(); i < n; i++){
		m_jucatori[i].setCheck(false);
	}
}