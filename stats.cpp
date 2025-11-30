#include "stats.hpp"
#include <algorithm>
#include <numeric>
#include <iostream>
#include <iomanip>
#include <stdexcept>

DealStats compute_deal_stats(const std::vector<int>& sizes) {
    if (sizes.empty()) throw std::invalid_argument("sizes is empty");

    DealStats r;
    r.totalDeals = (int)sizes.size();

    r.minSize = *std::min_element(sizes.begin(), sizes.end());
    r.maxSize = *std::max_element(sizes.begin(), sizes.end());

    double sum = std::accumulate(sizes.begin(), sizes.end(), 0.0);
    r.mean = sum / r.totalDeals;

    for (int x : sizes) r.frequencies[x]++;

    int bestSize = -1;
    int bestFreq = -1;
    for (auto& p : r.frequencies)
        if (p.second > bestFreq) {
            bestFreq = p.second;
            bestSize = p.first;
        }
    r.mode = bestSize;

    std::vector<int> sorted = sizes;
    std::sort(sorted.begin(), sorted.end());
    if (r.totalDeals % 2 == 1)
        r.median = sorted[r.totalDeals / 2];
    else
        r.median = (sorted[r.totalDeals / 2 - 1] + sorted[r.totalDeals / 2]) / 2.0;

    return r;
}

void print_deal_stats(const DealStats& s, int totalTiles) {
    using std::cout;
    using std::endl;

    cout << "Total deals: " << s.totalDeals << endl;
    cout << "Min size: " << s.minSize << endl;
    cout << "Max size: " << s.maxSize << endl;

    cout << std::fixed << std::setprecision(3);
    cout << "Mean: " << s.mean << endl;
    cout << "Median: " << s.median << endl;
    cout << "Mode: " << s.mode << endl;

    cout << endl << "Distribution (%):" << endl;
    for (auto& p : s.frequencies) {
        double perc = 100.0 * p.second / s.totalDeals;
        cout << "  size " << p.first << ": "
            << std::setprecision(2) << perc << "% (" << p.second << ")" << endl;
    }

    if (totalTiles > 0) {
        double rMean = s.mean / totalTiles;
        double rMed = s.median / totalTiles;
        cout << endl;
        cout << "Total tiles: " << totalTiles << endl;
        cout << "Mean/tiles: " << rMean << endl;
        cout << "Median/tiles: " << rMed << endl;
    }
}
