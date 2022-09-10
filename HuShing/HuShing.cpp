#include "HuShing.h"
#include "HArc.h"
#include <iostream>
#include <algorithm>
#include <cstring>

namespace HuShing {
	int w[MAX + 1];
	int n;
	ll cp[MAX];
	int hnum;
	HArc* h[MAX];

	void get_cp() {
		int* V1 = std::min_element(w + 1, w + n + 1);
		std::rotate(w + 1, V1, w + n + 1);
		w[n + 1] = w[1];

		memset(cp, 0, sizeof cp);
		for (int i = 1; i <= n + 1; ++i) {
			cp[i] = (ll)w[i] * w[i - 1];
			cp[i] += cp[i - 1];
		}
	}
	HArc* one_sweep() {
		std::vector<int> _stack;
		std::vector<pii> temp, h_list;
		
		for (int i = 1; i <= n; ++i) {
			while (_stack.size() > 1 && w[_stack.back()] > w[i]) { // if Wt > Wc
				temp.push_back({ _stack[_stack.size() - 2], i }); // push V(t-1)-Vc arc
				_stack.pop_back(); // pop Vt
			}
			_stack.push_back(i); // push Vc
		}
		while (_stack.size() > 3) {
			temp.push_back({ 1, _stack[_stack.size() - 2] }); // push V(t-1)
			_stack.pop_back();
		}
		for (const pii& p : temp) {
			if (p.first == 1 || p.second == 1) continue;
			h_list.push_back(p);
		}
		return build_tree(h_list);
	}
	HArc* build_tree(std::vector<pii>& potential) {
		hnum = 0;
		std::vector<HArc*> _stack;
		HArc* root = new HArc(1, n + 1);

		for (const pii& p : potential) {
			HArc* h = new HArc(p.first, p.second);
			while (!_stack.empty() && h->isAbove(*_stack.back())) {
				h->children.push_back(_stack.back());
				_stack.pop_back();
			}
			_stack.push_back(h);
		}
		while (!_stack.empty()) {
			root->children.push_back(_stack.back());
			_stack.pop_back();
		}
		return root;
	}

	ll MCM() {
		int a, i;
		ll result = 0;
		std::cin >> n;

		++n;

		memset(w, 0, sizeof w);
		std::cin >> w[1] >> w[2];
		for (i = 3; i <= n; ++i) std::cin >> a >> w[i];

		if (n < 3) {
			std::cout << 0;
			return 0;
		}

		get_cp();
		HArc* root = one_sweep();
		root->dfs();

		while (!root->ceil.empty()) {
			result += root->ceil.top()->num;
			root->ceil.pop();
		}

		for (HArc* p : h) if (p) delete p;

		std::cout << result;

		return result;
	}

	ll MCM(std::vector<pii>& data) {
		ll result = 0;
		++n;

		n = data.size() + 1;

		if (n < 3) {
			std::cout << 0;
			return 0;
		}

		memset(w, 0, sizeof w);
		w[1] = data[0].first, w[2] = data[0].second;

		for (int i = 3; i <= n; ++i) w[i]=  data[i - 2].second;

		get_cp();
		HArc* root = one_sweep();
		root->dfs();

		while (!root->ceil.empty()) {
			result += root->ceil.top()->num;
			root->ceil.pop();
		}

		for (HArc* p : h) if (p) delete p;

		return result;
	}
}