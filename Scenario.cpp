#include "Scenario.h"
#include <iostream>

void Scenario::SetTitle(std::string newTitle)
{
	title = newTitle;
}

std::string Scenario::GetTitle()
{
	return title;
}

void Scenario::SetDescription(std::string newDescription)
{
	description = newDescription;
}

std::string Scenario::GetDescription()
{
	return description;
}

void Scenario::SetEffects(std::string newEffects)
{
	effects = newEffects;
}

std::string Scenario::GetEffects()
{
	return effects;
}

void Scenario::SetEligiblePeriod(std::string newEligiblePeriod)
{
	eligiblePeriod = newEligiblePeriod;
}

std::string Scenario::GetEligiblePeriod()
{
	return eligiblePeriod;
}

void Scenario::SetMinWeek(int newMinWeek)
{
	minWeek = newMinWeek;
}

int Scenario::GetMinWeek()
{
	return minWeek;
}

void Scenario::SetMaxWeek(int newMaxWeek)
{
	maxWeek = newMaxWeek;
}

int Scenario::GetMaxWeek()
{
	return maxWeek;
}