//
// Created by ���Ľ� on 2024-02-26.
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
	int hashSize;

	// std ����
	void writeToFile(std::unordered_map<std::string, int>& keywordCount, std::string path) {
		std::ofstream fout;
		fout.open(path, std::ios::out);
		for (auto& x: keywordCount) {
			fout << x.first << ' ' << x.second << "\n";
		}
		fout.close();
	}

	// �Զ����ϣ�����
	void writeToFile(std::vector<std::pair<std::string, int>>& keywordCount, std::string path) {
		std::ofstream fout;
		fout.open(path, std::ios::out);
		for (auto& x: keywordCount) {
			if (x.second > 0) {
				fout << x.first << ' ' << x.second << "\n";
			}
		}
		fout.close();
	}

public:
	hashAlgorithm(
			std::string _inputPath = "../Files/2.c",
			std::string _outputPath = "../Files"
	) : inputPath(_inputPath), outputPath(_outputPath) {
		hashSize = 3000;
	}

	void stdHash() {
		// ���ļ�
		std::ifstream fin;
		fin.open(inputPath, std::ios::in);

		std::unordered_map<std::string, int> keywordCount;

		// �쳣����
		if (!fin) {
			std::cerr << "Failed to open the file." << std::endl;
			return;
		}

		// �����ļ�
		std::string word;
		while (fin >> word) {
			// �Ƴ�������
			word.erase(std::remove_if(word.begin(), word.end(), ispunct), word.end());

			if (std::count(keywords.begin(), keywords.end(), word)) {
				keywordCount[word]++;
			}
		}

		fin.close();

		// ���ù�ϣ��д���ļ�
		writeToFile(keywordCount, outputPath + "\\hash_std.txt");

		return;
	}

	int selfHash() {
		// ���ļ�
		std::ifstream fin;
		fin.open(inputPath, std::ios::in);

		int cnt = 0;

		// �쳣����
		if (!fin) {
			std::cerr << "Failed to open the file." << std::endl;
			return cnt;
		}

		// �����ϣ��
		std::vector<std::pair<std::string, int>> myHash(hashSize, {"", -1});

		for (auto& word: keywords) {
			int hashNumber = (word[0] - 'a') * 100 + (word.back() - 'a') % 41;
			while (myHash[hashNumber].first != "") {
				hashNumber = (hashNumber + 1) % hashSize;
			}
			myHash[hashNumber] = {word, 0};
		}

		// �����ļ�
		std::string word;
		while (fin >> word) {
			// �Ƴ�������
			word.erase(std::remove_if(word.begin(), word.end(), ispunct), word.end());

			// �쳣���ʴ��� - ��������в�ȫ��������ĸ��������
			if (word == "" || !std::all_of(word.begin(), word.end(), isalpha)) {
				cnt++;
				continue;
			}

			for (auto& c: word) c = tolower(c);

			// ��ϣ����
			int count = 0;
			int hashNumber = (word[0] - 'a') * 100 + (word.back() - 'a') % 41;
			while (myHash[hashNumber].first != "" && myHash[hashNumber].first != word) {
				hashNumber = (hashNumber + 1) % hashSize;
				count++;
			}

			if (myHash[hashNumber].first == word) {
				cnt++;
				myHash[hashNumber].second++;
			}

			cnt += count;
		}

		fin.close();

		// ���ù�ϣ��д���ļ�
		writeToFile(myHash, outputPath + "\\hash_self.txt");

		return cnt;
	}

	int binaryHash() {
		// ���ļ�
		std::ifstream fin;
		fin.open(inputPath, std::ios::in);

		std::unordered_map<std::string, int> keywordCount;
		int cnt = 0;

		// �쳣����
		if (!fin) {
			std::cerr << "Failed to open the file." << std::endl;
			return cnt;
		}

		// �����ļ�
		std::sort(keywords.begin(), keywords.end());
		std::string word;
		while (fin >> word) {
			// �Ƴ�������
			word.erase(std::remove_if(word.begin(), word.end(), ispunct), word.end());

			// ���ֲ���
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

		// ���ù�ϣ��д���ļ�
		writeToFile(keywordCount, outputPath + "\\hash_binary.txt");

		return cnt;
	}
};
