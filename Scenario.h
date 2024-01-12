#include <string>

class Scenario
{
	private:
		std::string title = "0";
		std::string description = "0";
		std::string effects = "0";
		std::string eligiblePeriod = "0";
		int minWeek = -1;
		int maxWeek = -1;
	public:
		void SetTitle(std::string newTitle);
		std::string GetTitle();

		void SetDescription(std::string newDescription);
		std::string GetDescription();

		void SetEffects(std::string newEffects);
		std::string GetEffects();

		void SetEligiblePeriod(std::string newEligiblePeriod);
		std::string GetEligiblePeriod();

		void SetMinWeek(int newMinWeek);
		int GetMinWeek();

		void SetMaxWeek(int newMaxWeek);
		int GetMaxWeek();

		bool IsComplete();

		void DebugPrint();
};