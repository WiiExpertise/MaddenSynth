#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

// Constant to represent program version
const std::string versionNum = "DEVELOPMENT";

// Loop function for main menu options
void MenuLoop();

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
		std::cout << "q - Quit MaddenSynth" << std::endl;
		std::cout << std::endl;
		std::cout << "Select an option: ";
		std::cin >> userOption;

		if (tolower(userOption) == 'g')
		{
			std::cout << std::endl << "Function not yet implemented." << std::endl << std::endl;
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