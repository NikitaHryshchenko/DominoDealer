#include "domino.hpp"
#include <stdexcept>

DominoDealer::DominoDealer(int maxValue)
    : n(maxValue), rng(std::random_device{}())
{
    if (n < 0) throw std::invalid_argument("n must be non-negative");
    totalTiles = (n + 1) * (n + 2) / 2;
    reset_deck();
}

void DominoDealer::reset_deck() {
    deck.clear();
    deck.reserve(totalTiles);
    for (int i = 0; i <= n; ++i)
        for (int j = i; j <= n; ++j)
            deck.push_back(DominoTile{ i, j });
}

std::optional<DominoTile> DominoDealer::operator()() {
    if (deck.empty()) return std::nullopt;
    std::uniform_int_distribution<std::size_t> dist(0, deck.size() - 1);
    std::size_t idx = dist(rng);
    DominoTile tile = deck[idx];
    deck[idx] = deck.back();
    deck.pop_back();
    return tile;
}

bool DominoDealer::try_attach_tile(const DominoTile& tile, int& left, int& right) {
    struct Candidate {
        int newLeft;
        int newRight;
        int matchedValue;
    };

    std::vector<Candidate> c;
    c.reserve(4);

    int a = tile.a;
    int b = tile.b;

    if (a == left) c.push_back({ b, right, a });
    if (b == left) c.push_back({ a, right, b });
    if (a == right) c.push_back({ left, b, a });
    if (b == right) c.push_back({ left, a, b });

    if (c.empty()) return false;

    auto best = c[0];
    for (auto& x : c)
        if (x.matchedValue < best.matchedValue)
            best = x;

    left = best.newLeft;
    right = best.newRight;
    return true;
}

int DominoDealer::run_one_deal() {
    reset_deck();

    auto first = (*this)();
    if (!first) return 0;

    int left = first->a;
    int right = first->b;
    int size = 1;

    while (true) {
        auto t = (*this)();
        if (!t) break;
        if (!try_attach_tile(*t, left, right)) break;
        ++size;
    }

    return size;
}
