// Day09.cpp : Source file for your target.
//

#include "Day09.h"
#include "Utils.h"

#include <set>
#include <map>
#include <ranges>

int main()
{
	auto startTime = std::chrono::system_clock::now();

	std::filesystem::path inputFile("../Day09_input.txt");

	std::ifstream istrm(inputFile);

	std::multimap<std::uint64_t, std::pair<utils::Pos, utils::Pos>> areas;
	std::set<utils::Pos> tiles;

	for (utils::Pos p; istrm >> p; )
	{
		for (const utils::Pos tile : tiles)
		{
			auto diff = p - tile;
			std::uint64_t area = (std::abs(diff.X) + 1) * (std::abs(diff.Y) + 1);

			areas.emplace(area, std::make_pair(p, tile));
		}

		tiles.insert(p);
	}

	utils::PrintResult(areas.rbegin()->first, startTime);

	//Part 2:

	auto isWithin = [](const utils::Pos& p, const std::pair<utils::Pos, utils::Pos>& corners) -> bool
		{
			return p.X > std::min(corners.first.X, corners.second.X)
				&& p.X < std::max(corners.first.X, corners.second.X)
				&& p.Y > std::min(corners.first.Y, corners.second.Y)
				&& p.Y < std::max(corners.first.Y, corners.second.Y);
		};

	auto isOnEdge = [](const utils::Pos& p, const std::pair<utils::Pos, utils::Pos>& corners) -> bool
		{
			return (p.X == std::min(corners.first.X, corners.second.X)
					&& p.Y >= std::min(corners.first.Y, corners.second.Y)
					&& p.Y <= std::max(corners.first.Y, corners.second.Y))
				|| (p.X == std::max(corners.first.X, corners.second.X)
					&& p.Y >= std::min(corners.first.Y, corners.second.Y)
					&& p.Y <= std::max(corners.first.Y, corners.second.Y))
				|| (p.Y == std::min(corners.first.Y, corners.second.Y)
					&& p.X >= std::min(corners.first.X, corners.second.X)
					&& p.X <= std::max(corners.first.X, corners.second.X))
				|| (p.Y == std::max(corners.first.Y, corners.second.Y)
					&& p.X >= std::min(corners.first.X, corners.second.X)
					&& p.X <= std::max(corners.first.X, corners.second.X));
		};

	for (auto iter = areas.rbegin(); iter != areas.rend(); iter++)
	{
		if (std::ranges::none_of(tiles, [=](const utils::Pos& p) { return isWithin(p, iter->second); })
			&& std::ranges::count_if(tiles, [=](const utils::Pos& p) { return isOnEdge(p, iter->second); }) % 2 == 0)
		{
			utils::PrintResult(iter->first, startTime);
			break;
		}
	}

	return 0;
}
