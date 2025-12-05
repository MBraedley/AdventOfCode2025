// Day05.cpp : Source file for your target.
//

#include "Day05.h"
#include "Utils.h"

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


	//utils::PrintResult(val, startTime);

	return 0;
}
