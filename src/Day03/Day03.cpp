// Day03.cpp : Source file for your target.
//

#include "Day03.h"
#include "Utils.h"

#include <cassert>

int main()
{
	auto startTime = std::chrono::system_clock::now();

	auto input = utils::ReadInput( "../Day03_input.txt" );

	std::uint64_t val = 0;

	for( const auto& bank : input )
	{
		int digit1 = 0;
		std::size_t pos = 0;

		for( std::size_t i = 0; i < bank.size() - 1; i++ )
		{
			if( bank[i] - '0' > digit1 )
			{
				digit1 = bank[i] - '0';
				pos = i;
			}
		}

		int digit0 = 0;

		for( std::size_t i = pos + 1; i < bank.size(); i++ )
		{
			if( bank[i] - '0' > digit0 )
			{
				digit0 = bank[i] - '0';
			}
		}

		val += digit1 * 10 + digit0;
	}

	utils::PrintResult(val, startTime);

	//Part 2:

	val = 0;

	for( const auto& bank : input )
	{
		std::array<std::uint8_t, 12> joltage{};
		std::size_t pos = 0;
		for( std::size_t i = 0; i < 12; i++ )
		{
			for( std::size_t j = pos; j < bank.size() - 11 + i; j++ )
			{
				if( bank[j] - '0' > joltage[i] )
				{
					joltage[i] = bank[j] - '0';
					pos = j + 1;
				}
			}
		}

		std::uint64_t j = 0;
		for( auto i : joltage )
		{
			j = j * 10 + i;
		}

		//utils::PrintResult( j, startTime );

		val += j;
	}

	utils::PrintResult(val, startTime);

	return 0;
}
