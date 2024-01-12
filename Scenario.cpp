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

bool Scenario::IsComplete()
{
	if ((title != "0") && (description != "0") && (effects != "0") && (eligiblePeriod != "0") && (minWeek != -1) && (maxWeek != -1))
	{
		return true;
	}
	return false;
}

void Scenario::DebugPrint()
{
	std::cout << "Title: " << title << std::endl;
	std::cout << "Description: " << description << std::endl;
	std::cout << "Effects: " << effects << std::endl;
	std::cout << "Eligible Period: " << eligiblePeriod << std::endl;
	std::cout << "Min Week: " << minWeek << std::endl;
	std::cout << "Max Week: " << maxWeek << std::endl;
}