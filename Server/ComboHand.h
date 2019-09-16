#ifndef COMBOHAND_H
#define COMBOHAND_H

#include "Combo.h"

#include <algorithm>

/////////////////////////////////////// One Pair //////////////////////////////////////////
class OnePair : public Combo
{
private:
	mutable float topPriority = 0;

public:
	bool check(const std::vector<_Carte>& Pachet, std::vector<_Carte> carti) const override;
	float priority( ) const override;
	std::string mesaj( ) const override;
};

/////////////////////////////////////// Two Pair //////////////////////////////////////////
class TwoPair : public Combo
{
private:
	mutable float topPriority = 0;

public:
	bool check(const std::vector<_Carte>& Pachet, std::vector<_Carte> carti) const override;
	float priority( ) const override;
	std::string mesaj( ) const override;
};

/////////////////////////////////////// Three of a kind ////////////////////////////////////
class ThreeOfAKind : public Combo
{
private:
	mutable float topPriority = 0;

public:
	bool check(const std::vector<_Carte>& Pachet, std::vector<_Carte> carti) const override;
	float priority( ) const override;
	std::string mesaj( ) const override;
};

/////////////////////////////////////// Straight //////////////////////////////////////////
class Straight : public Combo
{
private:
	mutable float topPriority = 0;

public:
	bool check(const std::vector<_Carte>& Pachet, std::vector<_Carte> carti) const override;
	float priority( ) const override;
	std::string mesaj( ) const override;
};

/////////////////////////////////////// Flush //////////////////////////////////////////////
class Flush : public Combo
{
private:
	mutable float topPriority = 0;

public:
	bool check(const std::vector<_Carte>& Pachet, std::vector<_Carte> carti) const override;
	float priority( ) const override;
	std::string mesaj( ) const override;
};

/////////////////////////////////////// Full House //////////////////////////////////////////
class FullHouse : public Combo
{
private:
	mutable float topPriority = 0;

public:
	bool check(const std::vector<_Carte>& Pachet, std::vector<_Carte> carti) const override;
	float priority( ) const override;
	std::string mesaj( ) const override;
};

/////////////////////////////////////// Four Of The Kind ///////////////////////////////////////
class FourOfTheKind : public Combo
{
private:
	mutable float topPriority = 0;

public:
	bool check(const std::vector<_Carte>& Pachet, std::vector<_Carte> carti) const override;
	float priority( ) const override;
	std::string mesaj( ) const override;
};

/////////////////////////////////////// Straight Flush //////////////////////////////////////////
class StraightFlush : public Combo
{
private:
	mutable float topPriority = 0;

public:
	bool check(const std::vector<_Carte>& Pachet, std::vector<_Carte> carti) const override;
	float priority( ) const override;
	std::string mesaj( ) const override;
};

/////////////////////////////////////// Royal Flush //////////////////////////////////////////
class RoyalFlush : public Combo
{
private:
	mutable float topPriority = 0;

public:
	bool check(const std::vector<_Carte>& Pachet, std::vector<_Carte> carti) const override;
	float priority( ) const override;
	std::string mesaj( ) const override;
};

#endif