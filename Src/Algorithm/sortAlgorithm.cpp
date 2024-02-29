//
// Created by 董文杰 on 2024-02-26.
//

#include <iostream>
#include <vector>
#include <functional>
#include <fstream>

class sortAlgorithm {
private:
	int Size, Range;
	std::string Path;
	std::vector<int> arr;

	// Generate num random numbers in [-range, range)
	void Generate(int num, int range) {
		std::ofstream fout;
		fout.open(Path + "\\generate_array.txt", std::ios::out);

		srand(time(nullptr));
		for (int i = 0; i < num; i++) {
			int data = rand() % (range << 1) - range;
			arr.push_back(data);
			fout << data << "\n";
		}
		fout.close();

		return;
	}

	// ShellSort
	int ShellSort(std::vector<int> a) {
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

		WriteToFile(Path + "\\shell_array.txt", a);

		return cnt;
	}

	// QuickSort
	int QuickSort(std::vector<int> a) {
		int cnt = 0;

		std::function<void(int, int)> Sort = [&](int l, int r) {
			if (l == r) return;

			int i = l - 1, j = r + 1, x = a[(i + j) >> 1];
			while (i < j) {
				while (a[++i] < x);
				while (a[--j] > x);
				if (i < j) std::swap(a[i], a[j]), cnt++;
			}
			Sort(l, j);
			Sort(j + 1, r);
		};

		Sort(0, a.size() - 1);

		WriteToFile(Path + "\\quick_array.txt", a);

		return cnt;
	}

	// HeapSort(largest top)
	int HeapSort(std::vector<int> a) {
		int cnt = 0;

		auto pushdown = [&](int top, int lim) {
			int j = 2 * top + 1;
			while (j <= lim) {
				j += j < lim && a[j] < a[j + 1];
				cnt++;
				if (a[top] <= a[j]) {
					cnt++;
					std::swap(a[top], a[j]);
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
			std::swap(a[0], a[n - i - 1]);
			pushdown(0, n - i - 2);
		}

		WriteToFile(Path + "\\heap_array.txt", a);

		return cnt;
	}

	// MergeSort - recursion
	int MergeSort(std::vector<int> a) {
		int cnt = 0;

		std::function<void(int, int)> mergeSort = [&](int l, int r) {
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

		WriteToFile(Path + "\\merge_array.txt", a);

		return cnt;
	}

	void WriteToFile(std::string path, std::vector<int>& a) {
		std::ofstream fout;
		fout.open(path);
		for (auto& x: a) {
			fout << x << "\n";
		}
		fout.close();
	}

public:
	sortAlgorithm(int _Size, int _Range, std::string _Path) : Size(_Size), Range(_Range), Path(_Path) {

		if (Size < 0 || Size >= 1e8) {
			std::cerr << "Invalid Size" << std::endl;
		}

		Generate(Size, Range);
	}

	int ShellSort() { return ShellSort(arr); }
	int QuickSort() { return QuickSort(arr); }
	int HeapSort() { return HeapSort(arr); }
	int MergeSort() { return MergeSort(arr); }
};
