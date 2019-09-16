#include "ComboHand.h"

/////////////////////////////////////// One Pair //////////////////////////////////////////
/*
	O carte din mana are acelasi numar cu o carte de pe masa sau cu cealalta carte din mana
*/
bool OnePair::check(const std::vector<_Carte>& Pachet, std::vector<_Carte> carti) const
{
	
	if(Card::compareToNumber(*carti[0], *carti[1]) == 0){
		topPriority = Card::getIndex(*carti[0]) * 1.0f + Card::getIndex(*carti[1]) / 14.0f;
		return true;
	}

	for(auto cartePachet : Pachet){
		for(int i = 0; i < 2; i++){
			if(Card::compareToNumber(*cartePachet, *carti[i]) == 0){
				topPriority = Card::getIndex(*carti[i]) + Card::getIndex(*carti[(i + 1) % 2]) / 14.0f;
				return true;
			}
		}
	}

	return false;
}

float OnePair::priority( ) const
{
	return 2 * 14.0f + topPriority;
}

std::string OnePair::mesaj( ) const
{
	return "One Pair";
}

/////////////////////////////////////// Two Pair //////////////////////////////////////////
/*
	Ambele cartii din mana au acelasi numar cu 2 carti de pe masa
*/

bool TwoPair::check(const std::vector<_Carte>& Pachet, std::vector<_Carte> carti) const
{
	int hit[2] = {0, 0};
	int index = 0;

	for(auto carteMana : carti){
		for(auto cartePachet : Pachet){
			if(Card::compareToNumber(*cartePachet, *carteMana) == 0)
				hit[index] ++;
		}
		index++;
	}
	
	if(hit[0] == 1 && hit[1] == 1){
		topPriority = std::max(Card::getIndex(*carti[0]), Card::getIndex(*carti[1])) * 1.0f;
		return true;
	}

	return false;
}

float TwoPair::priority( ) const
{
	return 3.0f * 14.0f + topPriority;
}

std::string TwoPair::mesaj( ) const
{
	return "Two Pair ";
}

/////////////////////////////////////// Three of a kind //////////////////////////////////////////
/*
	O carte din mana are acelasi numar cu 2 carti de pe masa sau cartiile din mana sunt egale si mai este o carte pe masa cu acelasi numar
*/
bool ThreeOfAKind::check(const std::vector<_Carte>& Pachet, std::vector<_Carte> carti) const
{
	int hit[2] = {0, 0};
	int index = 0;

	if(Card::compareToNumber(*carti[0], *carti[1]) == 0)
		hit[0] += 1;

	for(auto carteMana : carti){
		for(auto cartePachet : Pachet){
			if(Card::compareToNumber(*cartePachet, *carteMana) == 0)
				hit[index] ++;
		}
		index++;
	}

	if(hit[0] == 2 ){
		topPriority = Card::getIndex(*carti[0]) + Card::getIndex(*carti[1]) / 14.0f;
		return true;
	}
	else if(hit[1] == 2){
		topPriority = Card::getIndex(*carti[1]) + Card::getIndex(*carti[0]) / 14.0f;
		return true;
	}

	return false;
}

float ThreeOfAKind::priority( ) const
{
	return 4 * 14.0f + topPriority;
}

std::string ThreeOfAKind::mesaj( ) const
{
	return "Three Of a Kind " ;
}

/////////////////////////////////////// Straight //////////////////////////////////////////
/*
	Sunt 5 cartii consecutive de culoari diferite
*/
bool Straight::check(const std::vector<_Carte>& Pachet, std::vector<_Carte> carti) const
{
	carti.insert( carti.end(), Pachet.begin(), Pachet.end());

	std::sort(carti.begin( ), carti.end( ), [ ](_Carte Left, _Carte Right){
		return (Card::getIndex(*Left) < Card::getIndex(*Right));
	});
	
	bool castigat = false;
	std::vector<_Carte> consecutive;
	_Carte precedent = nullptr;

	for(auto carte : carti){

		if(precedent != nullptr){
			
			int dif = Card::getIndex(*carte) - Card::getIndex(*precedent);
			if(dif == 1)
				consecutive.push_back(carte);
			else if (dif != 0 )
				consecutive.clear();
		}

		if(consecutive.size() == 4){
			topPriority = Card::getIndex(*consecutive.back( )) * 1.0f;
			return true;
		}

		precedent = carte;
	}

	return false;
}

float Straight::priority( ) const
{
	return 5.0f * 14.0f + topPriority;
}

std::string Straight::mesaj( ) const
{
	return "Straight";
}

/////////////////////////////////////// Flush //////////////////////////////////////////
/*
	5 cartii care au aceasi culoare 
*/
bool Flush::check(const std::vector<_Carte>& Pachet, std::vector<_Carte> carti) const
{
	carti.insert(carti.end( ), Pachet.begin( ), Pachet.end( ));

	int simbol[4] = {0, 0, 0, 0};

	for(auto carte : carti){
		int index = Card::getIndexSimbol(*carte);
		simbol[index]++;
	}

	if(simbol[0] == 5 || simbol[1] == 5 || simbol[2] == 5 || simbol[3] == 5)
		return true;

	return false;
}

float Flush::priority( ) const
{
	return 6.0f * 14.0f + topPriority;
}

std::string Flush::mesaj( ) const
{
	return "Flush";
}

/////////////////////////////////////// Full House //////////////////////////////////////////
/*
	O carte din mana are acelasi numar cu alte 2 de pe masa, iar cealalta carte din mana are acelasi numar cu alta carte depe masa
*/
bool FullHouse::check(const std::vector<_Carte>& Pachet, std::vector<_Carte> carti) const
{
	int hit[2] = {0, 0};
	int index = 0;

	for(_Carte carteMana : carti){
		for(_Carte cartePachet : Pachet){
			if(Card::compareToNumber(*carteMana, *cartePachet) == 0){
				hit[index]++;
			}
		}
		index++;
	}

	if((hit[0] == 2 && hit[1] == 1)){
		topPriority = Card::getIndex(*carti[0]) * 1.0f + Card::getIndex(*carti[1]) / 14.0f;
		return true;
	}
	else if((hit[0] == 1 && hit[1] == 2)){
		topPriority = Card::getIndex(*carti[1]) * 1.0f + Card::getIndex(*carti[0]) / 14.0f;
		return true;
	}

	return false;
}

float FullHouse::priority( ) const
{
	return 7.0f * 14.0f + topPriority;
}

std::string FullHouse::mesaj( ) const
{
	return"Full House ";
}

/////////////////////////////////////// Four Of The Kind //////////////////////////////////////////
/*
	Are 4 carti cu acelasi numar
*/

bool FourOfTheKind::check(const std::vector<_Carte>& Pachet, std::vector<_Carte> carti) const
{
	int hit[2] = {0, 0};
	int index = 0;

	if(Card::compareToNumber(*carti[0], *carti[1]) == 0)
		hit[0] += 1;

	for(auto carteMana : carti){
		for(auto cartePachet : Pachet){
			if(Card::compareToNumber(*cartePachet, *carteMana) == 0)
				hit[index] ++;
		}
		index++;
	}

	if(hit[0] == 3 || hit[1] == 3){
		return true;
	}

	return false;
}

float FourOfTheKind::priority( ) const
{
	return 8.0f * 14.0f + topPriority;
}

std::string FourOfTheKind::mesaj( ) const
{
	return "Four Of The Kind";
}

/////////////////////////////////////// Straight Flush //////////////////////////////////////////
/*
	Are 5 carti consecutive de aceasi culoare
*/

bool StraightFlush::check(const std::vector<_Carte>& Pachet, std::vector<_Carte> carti) const
{
	Straight conditie1;
	Flush conditie2;

	return (conditie1.check(Pachet, carti) == true && conditie2.check(Pachet, carti) == true);
}

float StraightFlush::priority( ) const
{
	return 9.0f * 14.0f + topPriority;
}

std::string StraightFlush::mesaj( ) const
{
	return "Straight Flush";
}

/////////////////////////////////////// Royal Flush //////////////////////////////////////////
/*
	10 J Q K A de aceasi culoare
*/

bool RoyalFlush::check(const std::vector<_Carte>& Pachet, std::vector<_Carte> carti) const
{
	Flush conditie;

	if(conditie.check(Pachet, carti) == true){
		carti.insert(carti.end( ), Pachet.begin( ), Pachet.end( ));

		std::sort(carti.begin( ), carti.end( ), [ ](_Carte Left, _Carte Right){
			return (Card::getIndex(*Left) < Card::getIndex(*Right));
		});

		bool castigat = false;
		int consecutive = 0;
		_Carte precedent = nullptr;

		for(auto carte : carti){

			if(precedent != nullptr){
				int indexPrima = Card::getIndex(*carte);
				int indexDoi = Card::getIndex(*precedent);

				if(indexPrima < 8 || indexDoi < 8)
					continue;

				int dif = indexPrima - indexDoi;
				if(dif == 1)
					consecutive++;
				else if(dif != 0)
					consecutive = 0;
			}

			if(consecutive == 4){
				return true;
			}

			precedent = carte;
		}
	}
	return false;
}

float RoyalFlush::priority( ) const
{
	return 10.0f * 14.0f + topPriority;
}

std::string RoyalFlush::mesaj( ) const
{
	return "Royal Flush";
}
