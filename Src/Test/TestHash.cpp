//
// Created by 董文杰 on 2024-02-29.
//

#include <iostream>
#include "../Algorithm/hashAlgorithm.cpp"

using namespace std;

struct test2 {
	hashAlgorithm obj;

	void std() {
		obj.stdHash();
		cout << "std hash success!" << "\n";
	}

	void self() {
		int cnt = obj.selfHash();
		cout << "self hash: " << cnt << "\n";
	}

	void binary() {
		int cnt = obj.binaryHash();
		cout << "binary hash: " << cnt << "\n";
	}

};

