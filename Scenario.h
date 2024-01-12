class Scenario
{
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
	private:
		std::string title;
		std::string description;
		std::string effects;
		std::string eligiblePeriod;
		int minWeek;
		int maxWeek;

};