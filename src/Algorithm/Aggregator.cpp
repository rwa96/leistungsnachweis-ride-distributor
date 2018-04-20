#include <algorithm>
#include "Aggregator.hpp"

/** Sort Choices descending by score function. */
bool sortByScore(const Choice& lhs, const Choice& rhs) { return lhs.score > rhs.score; }

void aggregate(Types::Choices& choices) {

	std::sort(choices.begin(), choices.end(), sortByScore);

	for (Choice& choice : choices)
	{
		std::cout << choice->score;
	}

	if(beamSize < choices.size())
		choices.resize(beamSize);

}