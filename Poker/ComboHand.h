#pragma once
#include "Combo.h"

#include <algorithm>

class OnePair : public Combo
{
private:
	mutable float topPriority = 0;

public:
	bool check(const std::vector<_Carte>& Pachet, std::vector<_Carte> carti) const override;
	float priority( ) const override;
	std::string mesaj( ) const override;
};

class TwoPair : public Combo
{
private:
	mutable float topPriority = 0;

public:
	bool check(const std::vector<_Carte>& Pachet, std::vector<_Carte> carti) const override;
	float priority( ) const override;
	std::string mesaj( ) const override;
};

class ThreeOfAKind : public Combo
{
private:
	mutable float topPriority = 0;

public:
	bool check(const std::vector<_Carte>& Pachet, std::vector<_Carte> carti) const override;
	float priority( ) const override;
	std::string mesaj( ) const override;
};

class Straight : public Combo
{
private:
	mutable float topPriority = 0;

public:
	bool check(const std::vector<_Carte>& Pachet, std::vector<_Carte> carti) const override;
	float priority( ) const override;
	std::string mesaj( ) const override;
};

class Flush : public Combo
{
private:
	mutable float topPriority = 0;

public:
	bool check(const std::vector<_Carte>& Pachet, std::vector<_Carte> carti) const override;
	float priority( ) const override;
	std::string mesaj( ) const override;
};

class FullHouse : public Combo
{
private:
	mutable float topPriority = 0;

public:
	bool check(const std::vector<_Carte>& Pachet, std::vector<_Carte> carti) const override;
	float priority( ) const override;
	std::string mesaj( ) const override;
};

class FourOfTheKind : public Combo
{
private:
	mutable float topPriority = 0;

public:
	bool check(const std::vector<_Carte>& Pachet, std::vector<_Carte> carti) const override;
	float priority( ) const override;
	std::string mesaj( ) const override;
};

class StraightFlush : public Combo
{
private:
	mutable float topPriority = 0;

public:
	bool check(const std::vector<_Carte>& Pachet, std::vector<_Carte> carti) const override;
	float priority( ) const override;
	std::string mesaj( ) const override;
};

class RoyalFlush : public Combo
{
private:
	mutable float topPriority = 0;

public:
	bool check(const std::vector<_Carte>& Pachet, std::vector<_Carte> carti) const override;
	float priority( ) const override;
	std::string mesaj( ) const override;
};

