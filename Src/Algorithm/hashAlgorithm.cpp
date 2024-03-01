//
// Created by 董文杰 on 2024-02-26.
//

#include <iostream>
#include <unordered_map>
#include <fstream>
#include <vector>
#include <algorithm>


class hashAlgorithm {
private:
	std::vector<std::string> keywords = {
			"auto", "break", "case", "char", "const",
			"continue", "default", "do", "double", "else",
			"enum", "extern", "float", "for", "goto",
			"if", "int", "long", "register", "return",
			"short", "signed", "sizeof", "static", "struct",
			"switch", "typedef", "union", "unsigned", "void",
			"volatile", "while"
	};

	std::string inputPath, outputPath;

	void writeToFile(std::unordered_map<std::string, int>& keywordCount, std::string path) {
		std::ofstream fout;
		fout.open(path, std::ios::out);
		for (auto& x: keywordCount) {
			fout << x.first << ' ' << x.second << "\n";
		}
		fout.close();
	}

public:
	hashAlgorithm(
			std::string _inputPath = "E:\\cplusplusProject\\DataStructureClassDesign\\_src\\test.c",
			std::string _outputPath = "E:\\cplusplusProject\\DataStructureClassDesign\\_src"
	) : inputPath(_inputPath), outputPath(_outputPath) {
	}

	void stdHash() {
		// 打开文件
		std::ifstream fin;
		fin.open(inputPath, std::ios::in);

		std::unordered_map<std::string, int> keywordCount;

		// 异常处理
		if (!fin) {
			std::cerr << "Failed to open the file." << std::endl;
			return;
		}

		// 遍历文件
		std::string word;
		while (fin >> word) {
			// 移除标点符号
			word.erase(std::remove_if(word.begin(), word.end(), ispunct), word.end());

			if (std::count(keywords.begin(), keywords.end(), word)) {
				keywordCount[word]++;
			}
		}

		fin.close();

		// 利用哈希表写入文件
		writeToFile(keywordCount, outputPath + "\\hash_std.txt");

		return;
	}

	int selfHash() {
		// 打开文件
		std::ifstream fin;
		fin.open(inputPath, std::ios::in);

		std::unordered_map<std::string, int> keywordCount;
		int cnt = 0;

		// 异常处理
		if (!fin) {
			std::cerr << "Failed to open the file." << std::endl;
			return cnt;
		}

		// 构造哈希表
		const int Size = 2048;
		std::vector<std::string> myHash(Size, "");
		for (auto& word: keywords) {
			int hashNumber = (word[0] - 'a') * 100 + (word.back() - 'a') % 41;
			while (myHash[hashNumber] != "") {
				hashNumber = (hashNumber + 1) % Size;
			}
			myHash[hashNumber] = word;
		}

		// 遍历文件
		std::string word;
		while (fin >> word) {
			// 移除标点符号
			word.erase(std::remove_if(word.begin(), word.end(), ispunct), word.end());

			// 异常单词处理 - 如果单词中不全部都是字母，则跳过
			if (word == "" || !std::all_of(word.begin(), word.end(), isalpha)) {
				cnt++;
				continue;
			}

			for (auto& c: word) c = tolower(c);

			// 哈希搜索
			int count = 0;
			int hashNumber = (word[0] - 'a') * 100 + (word.back() - 'a') % 41;
			while (myHash[hashNumber] != "" && myHash[hashNumber] != word) {
				hashNumber = (hashNumber + 1) % Size;
				count++;
			}

			if (myHash[hashNumber] == word) {
				cnt++;
				keywordCount[word]++;
			}

			cnt += count;
		}

		fin.close();

		// 利用哈希表写入文件
		writeToFile(keywordCount, outputPath + "\\hash_self.txt");

		return cnt;
	}

	int binaryHash() {
		// 打开文件
		std::ifstream fin;
		fin.open(inputPath, std::ios::in);

		std::unordered_map<std::string, int> keywordCount;
		int cnt = 0;

		// 异常处理
		if (!fin) {
			std::cerr << "Failed to open the file." << std::endl;
			return cnt;
		}

		// 遍历文件
		std::sort(keywords.begin(), keywords.end());
		std::string word;
		while (fin >> word) {
			// 移除标点符号
			word.erase(std::remove_if(word.begin(), word.end(), ispunct), word.end());

			// 二分查找
			int l = 0, r = 31, count = 0;
			while (l < r) {
				int mid = (l + r) >> 1;
				if (keywords[mid] < word) l = mid + 1;
				else r = mid;
				count++;
			}
			cnt += count;
			if (keywords[r] == word) {
				keywordCount[word]++;
			}
		}

		fin.close();

		// 利用哈希表写入文件
		writeToFile(keywordCount, outputPath + "\\hash_binary.txt");

		return cnt;
	}
};
