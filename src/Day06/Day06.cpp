// Day06.cpp : Source file for your target.
//

#include "Day06.h"
#include "Utils.h"

#include <ranges>

int main()
{
	auto startTime = std::chrono::system_clock::now();

	auto input = utils::ReadInput( "../Day06_input.txt" );

	std::vector<std::string> operations = utils::Tokenize(input.back(), ' ');
	input.pop_back();

	std::vector<std::vector<std::uint64_t>> vals;
	for (const auto& line : input)
	{
		vals.push_back(
			std::views::all(utils::Tokenize(line, ' ')) |
			std::views::transform([](const auto& v) { return std::stoull(v); }) |
			std::ranges::to<std::vector<std::uint64_t>>());
	}

	vals = utils::Transpose(vals);

	std::uint64_t val = 0;
	for (std::size_t i = 0; i < vals.size(); i++)
	{
		if (operations[i] == "+")
		{
			val += *std::ranges::fold_left_first(vals[i], std::plus());
		}
		else
		{
			val += *std::ranges::fold_left_first(vals[i], std::multiplies());
		}
	}

	utils::PrintResult(val, startTime);

	//Part 2:

	auto nums = utils::Transpose(input) | std::ranges::to<std::deque<std::string>>();
	val = 0;

	for (std::size_t i = 0; i < operations.size(); i++)
	{
		if (operations[i] == "+")
		{
			std::uint64_t inter = 0;
			while (!nums.empty() && !std::ranges::all_of(std::views::all(nums.front()), [](const auto& c) {return c == ' '; }))
			{
				inter += std::stoull(nums.front());
				nums.pop_front();
			}

			if (!nums.empty())
			{
				//pop the empty value
				nums.pop_front();
			}

			val += inter;
		}
		else
		{
			std::uint64_t inter = 1;
			while (!nums.empty() && !std::ranges::all_of(std::views::all(nums.front()), [](const auto& c) {return c == ' '; }))
			{
				inter *= std::stoull(nums.front());
				nums.pop_front();
			}

			if (!nums.empty())
			{
				//pop the empty value
				nums.pop_front();
			}

			val += inter;
		}
	}

	utils::PrintResult(val, startTime);

	return 0;
}
