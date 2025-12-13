// Day08.cpp : Source file for your target.
//

#include "Day08.h"
#include "Utils.h"

#include <ranges>
#include <map>
#include <set>
#include <list>
#include <cassert>
#include <sstream>

class Pos3D
{
public:
	std::int32_t x = 0;
	std::int32_t y = 0;
	std::int32_t z = 0;

	std::uint64_t DistSqrd(const Pos3D& other)
	{
		std::int64_t dx = x - other.x;
		std::int64_t dy = y - other.y;
		std::int64_t dz = z - other.z;

		return dx * dx + dy * dy + dz * dz;
	}

	auto operator<=>(const Pos3D& other) const
	{
		if (x == other.x)
		{
			if (y == other.y)
			{
				return z <=> other.z;
			}
			else
			{
				return y <=> other.y;
			}
		}
		else
		{
			return x <=> other.x;
		}
	}
};

std::istream& operator>>(std::istream& istrm, Pos3D& pos)
{
	//std::string line;
	//std::getline(istrm, line);

	//std::stringstream sstrm(line);
	char c;
	return istrm >> pos.x >> c >> pos.y >> c >> pos.z;

}

int main()
{
	auto startTime = std::chrono::system_clock::now();

	std::filesystem::path inputFile("../Day08_input.txt");

	std::ifstream istrm(inputFile);

	std::set<Pos3D> junctionBoxes;
	std::multimap<std::uint64_t, std::pair<Pos3D, Pos3D>> distances;

	Pos3D currentBox;
	while (istrm >> currentBox)
	{
		for (const Pos3D& otherBox : junctionBoxes)
		{
			auto dist = currentBox.DistSqrd(otherBox);
			distances.emplace(dist, std::make_pair(currentBox, otherBox));
		}
		junctionBoxes.insert(currentBox);
	}

	int connectionsMade = 0;

	std::list<std::set<Pos3D>> circuits;

	for (const auto& [dist, boxes] : distances)
	{
		if (std::ranges::none_of(circuits, [&boxes](const std::set<Pos3D>& circuit) {return circuit.contains(boxes.first) || circuit.contains(boxes.second);}))
		{
			// None of our circuits contains either box
			std::set<Pos3D> circuit;
			circuit.emplace(boxes.first);
			circuit.emplace(boxes.second);
			circuits.push_back(circuit);
			connectionsMade++;
		}
		else if (std::ranges::any_of(circuits, [&boxes](const std::set<Pos3D>& circuit) {return circuit.contains(boxes.first) && circuit.contains(boxes.second); }))
		{
			// Connection has already been made

			connectionsMade++;
			continue;
		}
		else
		{
			// One or both boxes is in a circuit already
			auto iterBox1 = std::find_if(circuits.begin(), circuits.end(), [&boxes](const auto& s) {return s.contains(boxes.first); });
			auto iterBox2 = std::find_if(circuits.begin(), circuits.end(), [&boxes](const auto& s) {return s.contains(boxes.second); });

			if( iterBox1 != circuits.end() && iterBox2 != circuits.end() )
			{
				iterBox1->insert(iterBox2->begin(), iterBox2->end());
				circuits.erase(iterBox2);
			}
			else if( iterBox1 != circuits.end() )
			{
				iterBox1->insert(boxes.second);
			}
			else if (iterBox2 != circuits.end())
			{
				iterBox2->insert(boxes.first);
			}
			else
			{
				assert(false);
			}

			connectionsMade++;
		}

		if (connectionsMade == 1000)
		{
			auto sizes = std::views::all(circuits) | std::views::transform([](const auto& v) -> std::size_t {return v.size(); }) | std::ranges::to<std::vector<std::size_t>>();
			std::sort(sizes.begin(), sizes.end(), std::greater());

			std::uint64_t val = *std::ranges::fold_left_first(
				std::views::all(sizes) | std::views::take(3),
				std::multiplies());

			utils::PrintResult(val, startTime);
		}

		//Part 2:
		if(connectionsMade > 1000 && circuits.size() == 1 && circuits.front().size() == junctionBoxes.size())
		{
			utils::PrintResult(static_cast<std::int64_t>(boxes.first.x) * static_cast<std::int64_t>(boxes.second.x), startTime);
		}
	}

	return 0;
}
