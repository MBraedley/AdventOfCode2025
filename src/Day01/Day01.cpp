// Day01.cpp : Source file for your target.
//

#include "Day01.h"
#include "Utils.h"

#include <ranges>
#include <algorithm>
#include <cassert>

int main()
{
	auto startTime = std::chrono::system_clock::now();

	std::filesystem::path inputFile("../Day01_input.txt");

	auto input = utils::ReadFormattedInput<R"((L|R)(\d+))">( inputFile );

	std::uint32_t val = 0;
	std::int32_t pos = 50;

	for( const auto& line : input )
	{
		std::int32_t distance = std::stoi( line[2] );
		if( line[1] == "R" )
		{
			pos += distance;
		}
		else
		{
			pos -= distance;
		}

		if( pos % 100 == 0 )
		{
			val++;
		}
	}

	utils::PrintResult(val, startTime);

	//Part 2:

	val = 0;
	pos = 50;

	//input =
	//{
	//	{ "L68", "L", "68" },
	//	{ "L30", "L", "30" },
	//	{ "R48", "R", "348" },
	//	{ "L5", "L", "5" },
	//	{ "R60", "R", "60" },
	//	{ "L55", "L", "355" },
	//	{ "L1", "L", "1" },
	//	{ "L99", "L", "499" },
	//	{ "R14", "R", "14" },
	//	{ "L82", "L", "82" },
	//};

	for( const auto& line : input )
	{
		std::int32_t distance = std::stoi( line[2] );
		auto start = pos;

		if( line[1] == "R" )
		{
			pos += distance % 100;
		}
		else
		{
			pos -= distance % 100;
		}

		//std::cout << "Dial ends on " << (pos + 100) % 100 << ".";

		if( (pos >= 100 || pos <= 0) && start != 0 )
		{
			val++;
			//std::cout << " Dial clicked over 0.";
		}

		if( distance >= 100 )
		{
			val += distance / 100;
			//std::cout << " Dial clicked over " << distance / 100 << " additional times.";
		}

		//std::cout << std::endl;

		while( pos < 0 )
		{
			pos += 100;
		}

		pos %= 100;
	}

	utils::PrintResult(val, startTime);
	
	return 0;
}
