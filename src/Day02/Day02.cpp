// Day02.cpp : Source file for your target.
//

#include "Day02.h"
#include "Utils.h"

#include <ranges>
#include <algorithm>

int main()
{
	auto startTime = std::chrono::system_clock::now();

	std::filesystem::path inputFile("../Day02_input.txt");

	auto input = utils::ReadInput( inputFile );

	auto dbRanges = utils::Tokenize( input.front(), ',' );

	std::uint64_t val = 0;

	for( const std::string& r : dbRanges )
	{
		auto minmax = std::views::all( utils::Tokenize( r, '-' ) )
			| std::views::transform( []( const auto& str )
				{
					return std::stoull( str );
				} )
			| std::ranges::to<std::vector<std::uint64_t>>();

		for( auto i = minmax.front(); i <= minmax.back(); i++ )
		{
			std::string v = std::to_string( i );
			auto len = v.length();
			if( len % 2 == 0 && v.substr(0, len / 2) == v.substr( len/2 ) )
			{
				val += std::stoull( v );
			}
		}
	}

	utils::PrintResult(val, startTime);

	//Part 2:

	val = 0;
	for( const std::string& r : dbRanges )
	{
		auto minmax = std::views::all( utils::Tokenize( r, '-' ) )
			| std::views::transform( []( const auto& str )
				{
					return std::stoull( str );
				} )
			| std::ranges::to<std::vector<std::uint64_t>>();

		for( auto i = minmax.front(); i <= minmax.back(); i++ )
		{
			std::string v = std::to_string( i );
			auto len = v.length();

			for( int chunk = 1; chunk <= len / 2; chunk++ )
			{
				if( len % chunk == 0 )
				{
					std::string compStr = v.substr( 0, chunk );

					if( std::ranges::all_of( std::views::chunk( v, chunk ) | std::ranges::to<std::vector<std::string>>(), [&](const std::string& str) { return str == compStr; }) )
					{
						val += std::stoull( v );
						break;	//only count this once
					}
				}
			}
		} 
	}

	utils::PrintResult(val, startTime);

	return 0;
}
