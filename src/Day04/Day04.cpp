// Day04.cpp : Source file for your target.
//

#include "Day04.h"
#include "Utils.h"

#include <set>
#include <algorithm>

int main()
{
	auto startTime = std::chrono::system_clock::now();

	auto input = utils::ReadInput( "../Day04_input.txt" );

	std::set<utils::Pos> rolls;
	std::set<utils::Pos> accessible;

	for( std::size_t y = 0; y < input.size(); y++ )
	{
		for( std::size_t x = 0; x < input[y].size(); x++ )
		{
			if( input[y][x] == '@' )
			{
				rolls.emplace( x, y );
			}
		}
	}

	for( const auto& roll : rolls )
	{
		auto neighbours = roll.GetNeighbours( input );

		std::vector<utils::Pos> intersecting;

		std::set_intersection( neighbours.begin(), neighbours.end(), rolls.begin(), rolls.end(), std::back_inserter( intersecting ) );

		if( intersecting.size() < 4 )
		{
			accessible.insert( roll );
		}
	}

	utils::PrintResult(accessible.size(), startTime);

	//Part 2:

	auto initialCount = rolls.size();

	while( accessible.size() > 0 )
	{
		std::set<utils::Pos> remaining;

		std::set_difference( rolls.begin(), rolls.end(), accessible.begin(), accessible.end(), std::inserter( remaining, remaining.end() ) );

		std::swap( rolls, remaining );

		accessible.clear();

		for( const auto& roll : rolls )
		{
			auto neighbours = roll.GetNeighbours( input );

			std::vector<utils::Pos> intersecting;

			std::set_intersection( neighbours.begin(), neighbours.end(), rolls.begin(), rolls.end(), std::back_inserter( intersecting ) );

			if( intersecting.size() < 4 )
			{
				accessible.insert( roll );
			}
		}
	}

	utils::PrintResult(initialCount - rolls.size(), startTime);

	return 0;
}
