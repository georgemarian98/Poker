#pragma once
#include "Card.h"
#include <algorithm>

class Combo{
private:
	mutable float topPriority = 0;
public:
	virtual bool check(const std::vector<_Carte>& Pachet, std::vector<_Carte> carti) const;
	virtual float priority( ) const { return topPriority; };
	virtual std::string mesaj( ) const { return "Nimic"; };
};

struct Comparable{
	bool operator()(Combo* Left, Combo* Right) const
	{
		return (Left->priority( ) > Right->priority( ));
	}
};


