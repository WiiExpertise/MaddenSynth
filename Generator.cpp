#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <filesystem>
#include <ctime>
#include "Scenario.h"

namespace fs = std::filesystem;

// Constant to represent program name
const std::string PROGRAM_NAME = "MaddenSynth";

// Constant to represent program version
const std::string VERSION_NUM = "DEVELOPMENT";

// Constant for program author name (used for error messaging)
const std::string AUTHOR_NAME = "WiiMaster";

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
	srand(time(NULL));
	std::cout << "Welcome to " << PROGRAM_NAME << " v" << VERSION_NUM << "!" << std::endl << std::endl;
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
		std::cout << "t - Reload teams" << std::endl;
		std::cout << "q - Quit " << PROGRAM_NAME << std::endl;
		std::cout << std::endl;
		std::cout << "Select an option: ";
		std::cin >> userOption;

		if (tolower(userOption) == 'g')
		{
			//std::cout << std::endl << "Function not yet implemented." << std::endl << std::endl;
			system("cls");
			GenerateScenario();
			system("cls");
		}
		else if (tolower(userOption) == 'r')
		{
			LoadScenarios();
			if (!setupComplete)
			{
				std::cout << "Scenario setup failed. Please ensure the scenario files exist and are properly formatted. If this error persists, contact " << AUTHOR_NAME << "." << std::endl << std::endl;
				std::cin.ignore();
				std::cout << "Press enter to continue...";
				std::cin.get();
			}
			system("cls");
		}
		else if (tolower(userOption) == 't')
		{
			LoadTeams();
			if (!teamsLoaded)
			{
				std::cout << "Team setup failed. Please ensure the team list file exists and is properly formatted. If this error persists, contact " << AUTHOR_NAME << "." << std::endl << std::endl;
				std::cin.ignore();
				std::cout << "Press enter to continue...";
				std::cin.get();
			}
			system("cls");
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
		if (!setupComplete)
		{
			std::cout << "Scenario setup failed, aborting. Please ensure the scenario files exist and are properly formatted. If this error persists, contact " << AUTHOR_NAME << "." << std::endl << std::endl;
			std::cin.ignore();
			std::cout << "Press enter to continue...";
			std::cin.get();
			return;
		}
	}

	if (!teamsLoaded)
	{
		LoadTeams();
		if (!teamsLoaded)
		{
			std::cout << "Team setup failed, aborting. Please ensure the team list file exists and is properly formatted. If this error persists, contact " << AUTHOR_NAME << "." << std::endl << std::endl;
			std::cin.ignore();
			std::cout << "Press enter to continue...";
			std::cin.get();
			return;
		}
	}

	// Generate index of random team in team list
	int randomTeamIndex = rand() % teamList.size();
	
	// Variable to hold season status
	char seasonStatus;

	// Prompt user for season status
	std::cout << "What stage is your franchise in? Enter P for preseason, R for regular season, or O for offseason: ";
	std::cin >> seasonStatus;
	std::cout << std::endl;

	// Validate season status options
	while ((toupper(seasonStatus) != 'R') && (toupper(seasonStatus) != 'P') && (toupper(seasonStatus) != 'O'))
	{
		std::cout << "Invalid status. Please try again." << std::endl << std::endl;
		std::cout << "What stage is your franchise in? Enter P for preseason, R for regular season, or O for offseason: ";
		std::cin >> seasonStatus;
		std::cout << std::endl;
	}

	int currentWeek = -1;

	// Prompt and validate current week for regular season and preseason status
	if ((toupper(seasonStatus) == 'R') || (toupper(seasonStatus) == 'P'))
	{
		std::cout << "What week number is it? ";
		std::cin >> currentWeek;

		if ((toupper(seasonStatus) == 'P'))
		{
			while ((currentWeek < 1) || (currentWeek > 4))
			{
				std::cout << "That's not a possible preseason week! Try again." << std::endl << std::endl;
				std::cout << "What week number is it? ";
				std::cin >> currentWeek;
			}
		}
		else if ((toupper(seasonStatus) == 'R'))
		{
			while ((currentWeek < 1) || (currentWeek > 18))
			{
				std::cout << "That's not a possible regular season week! Try again." << std::endl << std::endl;
				std::cout << "What week number is it? ";
				std::cin >> currentWeek;
			}
		}
	}

	std::cout << std::endl;

	bool acceptableScenario = false;
	int randomScenarioIndex;

	while (!acceptableScenario)
	{
		// Generate index of random scenario in scenario list
		randomScenarioIndex = rand() % scenarioList.size();

		if ((toupper(seasonStatus) == 'R') && ((scenarioList[randomScenarioIndex].GetEligiblePeriod() != "R") && (scenarioList[randomScenarioIndex].GetEligiblePeriod() != "r")))
		{
			continue; // Scenario is not eligible for current season status (regular season)
		}

		if ((toupper(seasonStatus) == 'P') && ((scenarioList[randomScenarioIndex].GetEligiblePeriod() != "P") && (scenarioList[randomScenarioIndex].GetEligiblePeriod() != "p")))
		{
			continue; // Scenario is not eligible for current season status (preseason)
		}

		if ((toupper(seasonStatus) == 'O') && ((scenarioList[randomScenarioIndex].GetEligiblePeriod() != "O") && (scenarioList[randomScenarioIndex].GetEligiblePeriod() != "o")))
		{
			continue; // Scenario is not eligible for current season status (preseason)
		}

		if (((toupper(seasonStatus) == 'R') || (toupper(seasonStatus) == 'P')) && ((currentWeek < scenarioList[randomScenarioIndex].GetMinWeek()) || (currentWeek > scenarioList[randomScenarioIndex].GetMaxWeek())))
		{
			continue; // Scenario is not eligible based on current week
		}


		acceptableScenario = true; // Otherwise, scenario must be eligible so break loop
	}

	std::cout << teamList[randomTeamIndex] << " - ";
	scenarioList[randomScenarioIndex].Print();

	std::cin.ignore();
	std::cout << "Press enter to continue...";
	std::cin.get();

	std::cout << std::endl;
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
			}
			else 
			{
				std::cout << "Unable to open file: " << entry.path() << std::endl << std::endl;
			}
		}
	}

	// Check if scenario setup was successful and adjust bool accordingly
	if (scenarioList.size() > 0)
	{
		setupComplete = true;
	}
	else
	{
		setupComplete = false;
	}

	//std::cout << std::endl;
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