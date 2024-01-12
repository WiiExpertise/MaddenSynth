#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <filesystem>
#include "Scenario.h"

namespace fs = std::filesystem;

// Constant to represent program version
const std::string versionNum = "DEVELOPMENT";

// Storage of all scenario objects
std::vector<Scenario> scenarioList;

// Storage of all teams
std::vector<std::string> teamList;

// Global variable to check if scenarios have been loaded
bool setupComplete = false;

// Global variable to check if teams have been loaded
bool teamsLoaded = false;

// Loop function for main menu options
void MenuLoop();

// Primary worker function to generate a scenario
void GenerateScenario();

// Parses text files into scenario objects
void LoadScenarios();

// Parses team file into team list
void LoadTeams();

int main()
{
	std::cout << "Welcome to MaddenSynth v" << versionNum << "!" << std::endl << std::endl;
	MenuLoop();

	return 0;
}

void MenuLoop()
{
	char userOption;
	while(true)
	{
		std::cout << "MAIN MENU\nOptions:" << std::endl;
		std::cout << "g - Generate a scenario" << std::endl;
		std::cout << "r - Reload scenarios" << std::endl;
		std::cout << "q - Quit MaddenSynth" << std::endl;
		std::cout << std::endl;
		std::cout << "Select an option: ";
		std::cin >> userOption;

		if (tolower(userOption) == 'g')
		{
			std::cout << std::endl << "Function not yet implemented." << std::endl << std::endl;
		}
		else if (tolower(userOption) == 'r')
		{
			LoadScenarios();
		}
		else if (tolower(userOption) == 'q') // Quit case
		{
			break;
		}
		else
		{
			std::cout << std::endl << "Invalid option. Please try again." << std::endl << std::endl;
		}
	}
}

void GenerateScenario()
{
	if (!setupComplete)
	{
		LoadScenarios();
	}

	if (!teamsLoaded)
	{
		LoadTeams();
	}
}

void LoadScenarios()
{
	fs::path scenarioPath = "scenarios";

	scenarioList.clear();

	for (const auto& entry : fs::directory_iterator(scenarioPath))
	{
		if (entry.is_regular_file() && entry.path().extension() == ".txt")
		{
			std::ifstream file(entry.path());
			Scenario newScenario;

			if (file.is_open()) 
			{
				std::string line;
				for (int i = 0; std::getline(file, line); ++i) 
				{
					if (i == 0)
					{
						newScenario.SetTitle(line);
					}
					else if (i == 1)
					{
						newScenario.SetDescription(line);
					}
					else if (i == 2)
					{
						newScenario.SetEffects(line);
					}
					else if (i == 3)
					{
						newScenario.SetEligiblePeriod(line);
					}
					else if (i == 4)
					{
						newScenario.SetMinWeek(atoi(line.c_str()));
					}
					else if (i == 5)
					{
						newScenario.SetMaxWeek(atoi(line.c_str()));
					}
				}
				if (newScenario.IsComplete())
				{
					scenarioList.push_back(newScenario);
				}
				newScenario.DebugPrint();
			}
			else 
			{
				std::cout << "Unable to open file: " << entry.path() << std::endl << std::endl;
			}
		}
	}
}

void LoadTeams()
{
	std::string teamListPath = "teams/teams.txt";

	std::ifstream teams(teamListPath);

	// Throw error if unable to open teams list file
	if (!teams.is_open())
	{
		std::cout << "ERROR: Unable to open teams list file" << std::endl << std::endl;
		teamsLoaded = false;
		return;
	}

	// Empty team list before loading teams
	teamList.clear();

	std::string newTeam;

	// Add every line of teams file to team list
	while (std::getline(teams, newTeam))
	{
		teamList.push_back(newTeam);
	}

	// Check if teams were successfully loaded and adjust bool accordingly
	if (teamList.size() > 0)
	{
		teamsLoaded = true;
	}
	else
	{
		teamsLoaded = false;
	}

}