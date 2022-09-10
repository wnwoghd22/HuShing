#ifndef __HUSHING_H__
#define __HUSHING_H__

#include <queue>
#include <vector>

#define MAX 200'001

/// <summary>
/// O(n log n)
/// </summary>
namespace HuShing {
	typedef long long int ll;
	typedef std::pair<int, int> pii;
	class HArc;

	void get_cp(); // step 0
	HArc* one_sweep(); // step 1
	HArc* build_tree(std::vector<pii>&);

	ll MCM();
	ll MCM(std::vector<pii>&);
}

#endif // !__HUSHING_H__
