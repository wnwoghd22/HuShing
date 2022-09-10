#include "HArc.h"

namespace HuShing {
	extern int w[MAX + 1];
	extern int n;
	extern ll cp[MAX];
	extern int hnum;
	extern HArc* h[MAX];
	std::vector<HArc*> adjacent[MAX]; // push h-arc if an arc is processed temporarily

	HArc::HArc(int u, int v) :
		idx(++hnum), u(u), v(v), min(w[u] < w[v] ? u : v),
		mul((ll)w[u] * w[v]), num(0), den(cp[v] - cp[u] - mul), base(cp[v] - cp[u] - mul) {
		h[idx] = this;
	}
	ll HArc::S() const { return num / den; } // C(Hn,Hk) / (Wk:Wk') - Wk*Wk'
	bool HArc::isAbove(const HArc& other) const { return u <= other.u && other.v <= v; }

	ll HArc::get_min_mul() {
		if (idx == 1) return (ll)w[1] * w[2] + (ll)w[1] * w[n];

		if (u == min) {
			if (!adjacent[u].empty() && isAbove(*adjacent[u].back()))
				return adjacent[u].back()->mul;
			else return (ll)w[u] * w[u + 1];
		}
		else {
			if (!adjacent[v].empty() && isAbove(*adjacent[v].back()))
				return adjacent[v].back()->mul;
			else return (ll)w[v] * w[v - 1];
		}
	}
	ll HArc::H0() { return (ll)w[min] * (den + mul - get_min_mul()); }

	void HArc::remove(const HArc& h) {
		den += h.den;
		adjacent[h.u].pop_back();
		adjacent[h.v].pop_back();
		num = H0(); // renew the cost of Fan
	}
	void HArc::condense(const HArc& h) {
		// condense cost
		den += h.den;
		num += h.num;

		adjacent[h.u].pop_back();
		adjacent[h.v].pop_back();
	}

	void HArc::dfs() {
		if (children.empty()) { // leaf node
			num = H0(); // numrator is the cost of Fan

			// make self ceil to check either positive or negative
			adjacent[u].push_back(this);
			adjacent[v].push_back(this);
			ceil.push(this);
			return;
		}

		for (HArc* c : children) {
			c->dfs();
			den -= c->base;// remove (Wi:Wi') and add (Wi*Wi')
			while (!c->ceil.empty())
				ceil.push(c->ceil.top()), c->ceil.pop(); // merge priority queue
		}
		// get local optimum cost of subpolygon(Fan) bounced above by sons
		num = H0();

		while (!ceil.empty() && ceil.top()->S() >= w[min]) remove(*ceil.top()), ceil.pop();
		while (!ceil.empty() && S() <= ceil.top()->S()) condense(*ceil.top()), ceil.pop();

		adjacent[u].push_back(this);
		adjacent[v].push_back(this);
		ceil.push(this);
	}

	bool HArc::operator<(const HArc* h) const { return this->S() < h->S(); }
	bool HArc::operator<=(const HArc* h) const { return this->S() <= h->S(); }
	bool HArc::operator==(const HArc* h) const { return this->S() == h->S(); }
}