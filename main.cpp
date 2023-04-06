#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

using ll = long long;
using vb = vector<bool>;
using vi = vector<int>;
using vl = vector<ll>;
using vvl = vector<vl>;

ll mx;
vvl mLeft(int n, const vvl& bd) {
	auto ret = vvl(n, vl(n, 0));

	for (auto r = 0; r < n; ++r) {
		auto nowC = int{ 0 };
		for (auto c = 0; c < n; ++c) {
			if (0 == bd[r][c]) {
				continue;
			}

			if (n - 1 == c) {
				ret[r][nowC] = bd[r][c];
				continue;
			}

			auto searchC = int{ c + 1 };
			while (searchC < n && 0 == bd[r][searchC]) {
				++searchC;
			}

			if (searchC < n && bd[r][c] == bd[r][searchC]) {
				ret[r][nowC] = 2 * bd[r][c];
				++nowC;
				c = searchC;
				continue;
			}

			ret[r][nowC] = bd[r][c];
			c = searchC - 1;
			++nowC;
		}
	}

	return ret;
}

vvl mRight(int n, const vvl& bd) {
	auto ret = vvl(n, vl(n, 0));

	for (auto r = 0; r < n; ++r) {
		auto nowC = int{ n - 1 };
		for (auto c = n - 1; 0 <= c; --c) {
			if (0 == bd[r][c]) {
				continue;
			}

			if (0 == c) {
				ret[r][nowC] = bd[r][c];
				continue;
			}

			auto searchC = int{ c - 1 };
			while (0 <= searchC && 0 == bd[r][searchC]) {
				--searchC;
			}

			if (0 <= searchC && bd[r][c] == bd[r][searchC]) {
				ret[r][nowC] = 2 * bd[r][c];
				--nowC;
				c = searchC;
				continue;
			}

			ret[r][nowC] = bd[r][c];
			c = searchC + 1;
			--nowC;
		}
	}

	return ret;
}

vvl mUp(int n, const vvl& bd) {
	auto ret = vvl(n, vl(n, 0));

	for (auto c = 0; c < n; ++c) {
		auto nowR = int{ 0 };
		for (auto r = 0; r < n; ++r) {
			if (0 == bd[r][c]) {
				continue;
			}

			if (n - 1 == r) {
				ret[nowR][c] = bd[r][c];
				continue;
			}

			auto searchR = int{ r + 1 };
			while (searchR < n && 0 == bd[searchR][c]) {
				++searchR;
			}

			if (searchR < n && bd[r][c] == bd[searchR][c]) {
				ret[nowR][c] = 2 * bd[r][c];
				++nowR;
				r = searchR;
				continue;
			}

			ret[nowR][c] = bd[r][c];
			r = searchR - 1;
			++nowR;
		}
	}

	return ret;
}

vvl mDown(int n, const vvl& bd) {
	auto ret = vvl(n, vl(n, 0));

	for (auto c = 0; c < n; ++c) {
		auto nowR = int{ n - 1 };
		for (auto r = n - 1; 0 <= r; --r) {
			if (0 == bd[r][c]) {
				continue;
			}

			if (0 == r) {
				ret[nowR][c] = bd[r][c];
				continue;
			}

			auto searchR = int{ r - 1 };
			while (0 <= searchR && 0 == bd[searchR][c]) {
				--searchR;
			}

			if (0 <= searchR && bd[r][c] == bd[searchR][c]) {
				ret[nowR][c] = 2 * bd[r][c];
				--nowR;
				r = searchR;
				continue;
			}

			ret[nowR][c] = bd[r][c];
			r = searchR + 1;
			--nowR;
		}
	}

	return ret;
}

void solve(int n, const vvl& bd, int mv) {
	if (5 == mv) {
		for (const auto& r : bd) {
			for (const auto& x : r) {
				if (mx < x) {
					mx = x;
				}
			}
		}

		return;
	}

	const auto& bd1 = mLeft(n, bd);
	solve(n, bd1, mv + 1);

	const auto& bd2 = mRight(n, bd);
	solve(n, bd2, mv + 1);

	const auto& bd3 = mUp(n, bd);
	solve(n, bd3, mv + 1);

	const auto& bd4 = mDown(n, bd);
	solve(n, bd4, mv + 1);
}

int main() {
	ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int n;
	cin >> n;

	auto bd = vvl(n, vl(n));
	for (auto i = 0; i < n; ++i) {
		for (auto j = 0; j < n; ++j) {
			cin >> bd[i][j];
		}
	}

	solve(n, bd, 0);
	cout << mx;

	return 0;
}