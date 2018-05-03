#include <iostream>
#include <algorithm>
#include "Aggregator.hpp"

bool Aggregator::sortByScore(const std::unique_ptr<Types::Choice>& lhs,
                             const std::unique_ptr<Types::Choice>& rhs) { return lhs->score > rhs->score; }

void Aggregator::aggregate(Types::Choices& choices) {

    std::sort(choices.begin(), choices.end(), sortByScore);

    if(beamSize < choices.size()) {
        choices.resize(beamSize);
    }

}