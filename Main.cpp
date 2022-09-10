#include <iostream>

#include "Normal/Normal.h"
#include "HuShing/HuShing.h"

int main() {
	int n, a, b;
	std::cin >> n;

	std::vector<std::pair<int, int>> v;

	while (n--) {
		std::cin >> a >> b;
		v.push_back({ a, b });
	}

	std::cout << Normal::MCM(v)
		<< '\n' << HuShing::MCM(v);
}
