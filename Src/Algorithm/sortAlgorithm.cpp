//
// Created by 董文杰 on 2024-02-26.
//

#include <iostream>
#include <vector>
#include <functional>

using namespace std;

class sortAlgorithm {
private:
	int Size;
	string path;
	vector<int> arr;

	// Generate num random numbers in [0, range)
	vector<int> Generate(int num, int range) {
		srand(time(nullptr));
		vector<int> res;
		for (int i = 0; i < num; i++) {
			res.push_back(rand() % range);
		}
		return res;
	}

	// ShellSort
	int ShellSort(vector<int> a) {
		int cnt = 0;

		auto Sort = [&]() {
			for (int gap = a.size() >> 1; gap > 0; gap >>= 1) {
				for (int i = gap; i < a.size(); i++) {
					int temp = a[i], j;
					for (j = i; j >= gap && a[j - gap] > temp; j -= gap) {
						a[j] = a[j - gap];
						cnt++;
					}
					a[j] = temp;
				}
			}
		};

		Sort();

		return cnt;
	}

	// QuickSort
	int QuickSort(vector<int> a) {
		int cnt = 0;

		function<void(int, int)> Sort = [&](int l, int r) {
			if (l == r) return;

			int i = l - 1, j = r + 1, x = a[(i + j) >> 1];
			while (i < j) {
				while (a[++i] < x);
				while (a[--j] > x);
				if (i < j) swap(a[i], a[j]), cnt++;
			}
			Sort(l, j);
			Sort(j + 1, r);
		};

		Sort(0, a.size() - 1);

		return cnt;
	}

	// HeapSort(largest top)
	int HeapSort(vector<int> a) {
		int cnt = 0;

		auto pushdown = [&](int top, int lim) {
			int j = 2 * top + 1;
			while (j <= lim) {
				j += j < lim && a[j] < a[j + 1];
				cnt++;
				if (a[top] <= a[j]) {
					cnt++;
					swap(a[top], a[j]);
					top = j;
					j = 2 * top + 1;
				} else {
					break;  // have to add it, or it's a dead loop
				}
			}
		};

		// ini heap
		int n = a.size();
		for (int i = n / 2 - 1; i >= 0; i--) {
			pushdown(i, n - 1);
		}

		// modify heap
		for (int i = 0; i < n - 1; i++) {
			swap(a[0], a[n - i - 1]);
			pushdown(0, n - i - 2);
		}

		return cnt;
	}

	// MergeSort - recursion
	int MergeSort(vector<int> a) {
		int cnt = 0;

		function<void(int, int)> mergeSort = [&](int l, int r) {
			if (l >= r) return;

			// divide
			int mid = (l + r) >> 1;

			// conquer
			mergeSort(l, mid), mergeSort(mid + 1, r);

			// combine
			int t[a.size()], i = l, j = mid + 1, k = 0;
			while (i <= mid && j <= r) {
				if (a[i] < a[j]) t[k++] = a[i++];
				else t[k++] = a[j++];
				cnt++;
			}
			while (i <= mid) t[k++] = a[i++];
			while (j <= r) t[k++] = a[j++];

			for (i = l, j = 0; i <= r; i++) a[i] = t[j++];
		};

		mergeSort(0, a.size() - 1);

		return cnt;
	}


public:
	sortAlgorithm(int _Size, int range = 1000, string _path = "D:/desktop/Algorithm.txt") {
		Size = _Size;
		path = _path;
		arr = Generate(Size, range);
	}

	int ShellSort() { return ShellSort(arr); }
	int QuickSort() { return QuickSort(arr); }
	int HeapSort() { return HeapSort(arr); }
	int MergeSort() { return MergeSort(arr); }
};
