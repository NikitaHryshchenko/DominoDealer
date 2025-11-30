#ifndef DOMINO_HPP
#define DOMINO_HPP

#include <vector>
#include <optional>
#include <random>

struct DominoTile {
    int a{};
    int b{};
};

class DominoDealer {
public:
    explicit DominoDealer(int maxValue);

    DominoDealer(const DominoDealer&) = delete;
    DominoDealer& operator=(const DominoDealer&) = delete;

    DominoDealer(DominoDealer&&) = default;
    DominoDealer& operator=(DominoDealer&&) = default;

    void reset_deck();
    std::optional<DominoTile> operator()();
    int run_one_deal();

    int total_tiles() const noexcept { return totalTiles; }

private:
    int n;
    int totalTiles{};
    std::vector<DominoTile> deck;
    std::mt19937 rng;

    static bool try_attach_tile(const DominoTile& tile, int& left, int& right);
};

#endif
