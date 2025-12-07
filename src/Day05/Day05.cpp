// Day05.cpp : Source file for your target.
//

#include "Day05.h"
#include "Utils.h"

#include <ranges>
#include <algorithm>

int main()
{
	auto startTime = std::chrono::system_clock::now();

	std::filesystem::path inputFile( "../Day05_input.txt" );

	std::ifstream istrm( inputFile );

	std::vector<std::pair<std::uint64_t, std::uint64_t>> ranges;

	std::uint64_t first, last, item;
	char c;

	std::string line;
	std::getline( istrm, line );

	while( !line.empty() )
	{
		std::stringstream sstrm( line );
		sstrm >> first >> c >> last;
		ranges.emplace_back( first, last );
		std::getline( istrm, line );
	}

	std::uint32_t count = 0;
	
	while( istrm >> item )
	{
		for( const auto& [r1, r2] : ranges )
		{
			if( item >= r1 && item <= r2 )
			{
				count++;
				break;
			}
		}
	}

	utils::PrintResult(count, startTime);

	//Part 2:

	std::ranges::sort(std::views::all(ranges), [](const auto& lhs, const auto& rhs) { return lhs.first < rhs.first; });

	std::deque<std::pair<std::uint64_t, std::uint64_t>> rangesDeque = ranges | std::ranges::to<std::deque<std::pair<std::uint64_t, std::uint64_t>>>();
	std::deque<std::pair<std::uint64_t, std::uint64_t>> resultRanges;

	resultRanges.push_back(rangesDeque.front());
	rangesDeque.pop_front();

	while (!rangesDeque.empty())
	{
		if (rangesDeque.front().first > resultRanges.back().second)
		{
			resultRanges.push_back(rangesDeque.front());
		}
		else if (rangesDeque.front().second > resultRanges.back().second)
		{
			resultRanges.back().second = rangesDeque.front().second;
		}

		rangesDeque.pop_front();
	}

	std::uint64_t val = 0;

	for (const auto& [left, right] : resultRanges)
	{
		val += right - left + 1;
	}

	utils::PrintResult(val, startTime);

	return 0;
}
