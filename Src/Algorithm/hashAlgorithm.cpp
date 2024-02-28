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

	std::string path;

public:
	hashAlgorithm(std::string _path="E:\\cplusplusProject\\DataStructureClassDesign\\_src\\test.c") :path(_path) {}

	std::unordered_map<std::string, int> stdHash() {
		std::ifstream fin;
		fin.open(path, std::ios::in);

		std::unordered_map<std::string, int> keywordCount;

		if (!fin) {
			std::cerr << "Failed to open the file." << std::endl;
			return keywordCount;
		}

		std::string word;
		while (fin >> word) {
			// 移除标点符号
			word.erase(std::remove_if(word.begin(), word.end(), ispunct), word.end());

			if (std::count(keywords.begin(), keywords.end(), word)) {
				keywordCount[word]++;
			}
		}

		fin.close();

		return keywordCount;
	}

	std::pair<std::unordered_map<std::string, int>, int> selfHash() {
		std::ifstream fin;
		fin.open(path, std::ios::in);

		// 自定义哈希
		std::string word;
		while (fin >> word) {
			word.erase(std::remove_if(word.begin(), word.end(), ispunct), word.end());

			if (std::count(keywords.begin(), keywords.end(), word)) {

			}
		}

		fin.close();

		return {keywordCount, cnt};
	}

	std::pair<std::unordered_map<std::string, int>, int> binaryHash() {

	}
};