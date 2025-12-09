// Day07.cpp : Source file for your target.
//

#include "Day07.h"
#include "Utils.h"

#include <ranges>
#include <map>

int main()
{
	auto startTime = std::chrono::system_clock::now();

	auto input = utils::ReadInput( "../Day07_input.txt" );

	//std::vector<std::string> input =
	//{
	//	".......S.......",
	//	"...............",
	//	".......^.......",
	//	"...............",
	//	"......^.^......",
	//	"...............",
	//	".....^.^.^.....",
	//	"...............",
	//	"....^.^...^....",
	//	"...............",
	//	"...^.^...^.^...",
	//	"...............",
	//	"..^...^.....^..",
	//	"...............",
	//	".^.^.^.^.^...^.",
	//	"...............",
	//};

	input.front() = std::views::all( input.front() ) |
		std::views::transform( []( char c ) { return c == 'S' ? '|' : c; } ) |
		std::ranges::to<std::string>();

	std::uint64_t splits = 0;

	std::size_t row = 0;
	std::map<utils::Pos, std::uint64_t> paths;

	paths[utils::Pos( input.front().find_first_of( '|' ), row )] = 1;

	auto v = input | std::views::slide( 2 );

	for( std::ranges::viewable_range auto&& r : v )
	{
		std::string& up = r[0];
		std::string& down = r[1];

		for( std::size_t i = 0; i < up.size(); i++ )
		{
			if( up[i] == '|' )
			{
				if( down[i] == '^' )
				{
					splits++;
					down[i - 1] = '|';
					down[i + 1] = '|';

					paths[utils::Pos(i - 1, row + 1)] += paths[utils::Pos(i, row)];
					paths[utils::Pos(i + 1, row + 1)] += paths[utils::Pos( i, row )];
				}
				else
				{
					down[i] = '|';
					paths[utils::Pos(i, row + 1)] += paths[utils::Pos( i, row )];
				}
			}
		}

		row++;
	}

	utils::PrintResult(splits, startTime);

	//Part 2:

	auto totalPaths = *std::ranges::fold_left_first(
		std::views::all( paths ) |
			std::views::filter( [row]( const std::pair<utils::Pos, std::uint64_t>& p ) { return p.first.Y == row; } ) |
			std::views::values,
		std::plus() );

	utils::PrintResult(totalPaths, startTime);

	return 0;
}
