#include "Poker.h"
#include <functional>
Poker::Poker(int noJucatori)
{
	jucatori.reserve(noJucatori);

	for(int i = 0; i < noJucatori; i++){
		jucatori.push_back(Player( ));
	}

	std::weak_ptr<Carte> aux = Card::generareCarte( );

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

Poker::~Poker( )
{
	for(Combo* combinatii : combinatiiPosibile){
		delete combinatii;
	}

	combinatiiPosibile.clear( );

	Card::reset( );
}

void Poker::afisare( )
{
	system("cls");
	for(_Carte afis : cartiAratate){
		std::cout << *afis << " ";
	}
	std::cout << std::endl;

	int i = 1;
	for(Player afis : jucatori){
		std::cout << "Player " << i++ << ": " <<afis << "\n";
	}
}

void Poker::check( )
{
	struct Mesaj{
		float priority;
		std::string mesaj;
	};
	struct Greater{

		bool operator()(const Mesaj& Left,const Mesaj& Right) const
		{
			return (Left.priority > Right.priority);
		}
	};


	std::map<Mesaj, std::vector<Player>,Greater> castigatori;
	
	for(auto jucator : jucatori){
		std::set<Combo*, Comparable> combinatii;
		
		for(auto combinatie : combinatiiPosibile){

			if(combinatie->check(cartiAratate, jucator.getCarti( )) == true){
				combinatii.insert(combinatie);
			}
		}

		Combo* aux = *combinatii.begin( );

		castigatori[ {aux->priority( ), aux->mesaj()} ].push_back(jucator);
	}

	std::cout << std::endl << castigatori.begin( )->first.mesaj << std::endl ;
	std::cout << "Castigatorul este:" << std::endl;

	for(auto castigator : castigatori.begin( )->second){
		std::cout << castigator << std::endl;
	}
}

void Poker::run( )
{
	for(int i = 0; i < 3; i++){
		afisare( );

		int index = 0;
		while(index < cartiPuse[i]){

			cartiAratate.push_back(Card::generareCarte( ));
			index++;
		}
		std::weak_ptr<Carte> aux = Card::generareCarte( );

		std::cin.get( );
	}
	
	afisare( );
	
	check( );

	std::cin.get();
}
