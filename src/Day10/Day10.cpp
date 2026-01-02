// Day10.cpp : Source file for your target.
//

#include "Day10.h"
#include "Utils.h"

#include <ranges>
#include <bitset>

struct MachineConsole
{
	std::bitset<10> lights;
	std::vector<std::bitset<10>> buttons;
	std::vector<std::uint16_t> joltage;
};


int main()
{
	auto startTime = std::chrono::system_clock::now();

	std::filesystem::path inputFile("../Day10_input.txt");

	std::ifstream instrm(inputFile);
	std::string line;

	std::vector<MachineConsole> machines;

	while (std::getline(instrm, line))
	{
		auto tokens = utils::Tokenize(line, ' ') | std::ranges::to<std::deque<std::string>>();

		std::string lights = tokens.front();
		tokens.pop_front();

		MachineConsole mc;

		std::bitset<10> bs(std::ranges::reverse_view(lights) | std::ranges::to<std::string>(), 1, lights.size() - 2, '.', '#');

		mc.lights = bs;

		std::ranges::for_each(
			std::views::all(tokens) | std::views::take_while([](const std::string& s) { return s.starts_with("("); }),
			[&](const std::string& s)
			{
				bs.reset();
				std::ranges::for_each(
					std::views::all(s) | std::views::filter([](const char& c) { return c >= '0' && c <= '9'; }) | std::views::transform([](const char& c) { return c - '0'; }),
					[&](const auto& i)
					{
						bs.set(i);
					});
				mc.buttons.push_back(bs);
			});
	}

	//utils::PrintResult(val, startTime);

	//Part 2:


	//utils::PrintResult(val, startTime);

	return 0;
}
