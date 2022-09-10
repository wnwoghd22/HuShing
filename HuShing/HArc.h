#ifndef __H_ARC_H__
#define __H_ARC_H__

#include "HuShing.h"

namespace HuShing {
	class HArc {
	public:
		int idx, u, v, min;
		ll mul, num, den, base; // numerator, denominator
		std::vector<HArc*> children;
		std::priority_queue<HArc*> ceil;

		HArc(int u, int v);
		ll S() const; // get support weight
		bool isAbove(const HArc& other) const;

		ll get_min_mul();
		ll H0(); // get optimum cost of Fan

		void condense(const HArc& h);
		void remove(const HArc& h);

		void dfs();

		bool operator<(const HArc*) const;
		bool operator<=(const HArc*) const;
		bool operator==(const HArc*) const;
	};
}

#endif // !__H_ARC_H__
