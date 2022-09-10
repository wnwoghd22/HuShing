#include <iostream>
#include <cstring>
#include "Normal.h"

#define MAX (1 << 30)

namespace Normal {
    int cache[500][500], row[500], col[500];

    int dp(int a, int b) {
        if (a == b) return 0;

        int& result = cache[a][b], i;
        if (result) return result;

        for (result = MAX, i = a; i < b; ++i)
            result = std::min(result, dp(a, i) + dp(i + 1, b) + row[a] * col[i] * col[b]);

        return result;
    }

    int MCM() {
        int N, i;
        std::cin >> N;
        for (i = 0; i < N; ++i) std::cin >> row[i] >> col[i];
        std::cout << dp(0, N - 1) << '\n';

        return dp(0, N - 1);
    }

    int MCM(std::vector<std::pair<int, int>>& data) {
        memset(cache, 0, sizeof cache);

        int N = data.size();
        for (int i = 0; i < N; ++i)
            row[i] = data[i].first, col[i] = data[i].second;

        return dp(0, N - 1);
    }
}