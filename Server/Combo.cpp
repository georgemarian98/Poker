#include "Combo.h"

bool Combo::check(const std::vector<_Carte>& Pachet, std::vector<_Carte> carti) const
{
	topPriority = (float)std::max(Card::getIndex(carti[0]), Card::getIndex(carti[1])) 
				+ std::max(Card::getIndex(carti[0]), Card::getIndex(carti[1])) / 14;

	if(Card::compareToNumber(carti[0], carti[1]) == 0)
		return false;

	for(auto cartePachet : Pachet){
		for(auto carteMana : carti){
			if(Card::compareToNumber(cartePachet, carteMana) == 0)
				return false;
		}
	}
	return true;
}
