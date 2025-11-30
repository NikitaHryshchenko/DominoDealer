#ifndef STATS_HPP
#define STATS_HPP

#include <vector>
#include <map>

struct DealStats {
    int totalDeals{};
    int minSize{};
    int maxSize{};
    double mean{};
    double median{};
    int mode{};
    std::map<int, int> frequencies;
};

DealStats compute_deal_stats(const std::vector<int>& sizes);
void print_deal_stats(const DealStats& stats, int totalTiles);

#endif
