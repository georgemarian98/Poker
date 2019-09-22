#include "Poker.h"

Poker::Poker()
{
	m_server = CardSerialization::getInstance(port);

    //////////////////// Partea de joc ////////////////////

    int noJucatori = m_server->getNoClienti();
    m_jucatori.reserve(noJucatori);

	//Trimiterea cartiilor din mana catre jucatori 
	for(int i = 0; i < noJucatori; i++){
		m_jucatori.push_back(Player( ));
		m_server->writeClient(i, m_jucatori.back());

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
	m_server->destroy();

    for(auto& combinatii : combinatiiPosibile){
		delete combinatii;
	}
	
	Card::reset( );

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
	
	for(auto& jucator : m_jucatori){
		std::set<Combo*, Comparable> combinatii;
		
		for(auto const& combinatie : combinatiiPosibile){
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
	for(auto& castigator : castigatori.begin( )->second){
		std::vector<_Carte> aux = castigator.getCarti();
		cartiCastigatoare.insert(cartiCastigatoare.end(), aux.begin(), aux.end());
	}

	//trimitem datele
	m_server->writeAllClients(cartiCastigatoare , Date::Castigat , mesaj);
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
		m_server->writeAllClients(cartiPuse, Date::CartiMasa);
        m_cartiAratate.insert(m_cartiAratate.end(), cartiPuse.begin(), cartiPuse.end());

		//user input
		bids();
	}
	//desemnare castigator
	check( );
}

void Poker::bids()
{
	unsigned int index = 0;
	unsigned int n = m_jucatori.size();
	bool run = true;

	while( run ){
		char resp = 1;
		m_server->writeClientAction(index,resp);

		//daca o dat fold decrementam i ca sa nu sarim peste un jucator
		if( handleInput(m_server->readClientAction(index), index) == true && index != n -1){
			index--;
			n--;
		}

		index = ( index + 1 ) % n;
		run = !checkPlayers();
	}

	resetCheck();
	m_server->writeAllClientsAction(Exit);
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
		m_jucatori.erase( m_jucatori.begin() + index);
		m_server->writeClientAction(index, Exit);
		m_server->closeCommunication(index);
		return true;
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
	for(Player& jucator : m_jucatori){
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