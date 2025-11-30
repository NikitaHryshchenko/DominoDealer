// Compiler: MSVC 19.x / C++20

#include <iostream>
#include <limits>
#include "domino.hpp"
#include "stats.hpp"

bool read_int(const char* msg, int& v, int minVal, int maxVal) {
    std::cout << msg;
    if (!(std::cin >> v)) {
        std::cerr << "Error: expected integer\n";
        return false;
    }
    if (v < minVal || v > maxVal) {
        std::cerr << "Error: out of range\n";
        return false;
    }
    return true;
}

int main() {
    try {
        int n = 0;
        int dealsCount = 0;

        if (!read_int("Enter max tile value (n): ", n, 0, 1000)) return 1;
        if (!read_int("Enter number of deals: ", dealsCount, 1, 1000000)) return 1;

        DominoDealer dealer(n);
        std::vector<int> sizes;
        sizes.reserve(dealsCount);

        for (int i = 0; i < dealsCount; ++i)
            sizes.push_back(dealer.run_one_deal());

        DealStats stats = compute_deal_stats(sizes);
        print_deal_stats(stats, dealer.total_tiles());

        return 0;
    }
    catch (const std::exception& ex) {
        std::cerr << "Fatal error: " << ex.what() << "\n";
        return 1;
    }
    catch (...) {
        std::cerr << "Fatal error: unknown exception\n";
        return 1;
    }
}
