#include"Exceptions.h"
#include<string>
#include<iostream>
#include<fstream>
#include"executor.h"
#include"Commands.h"
#include<vector>
#include<algorithm>
#include<numeric>

using namespace std;

void read_file::doing(executor* ex, size_t num) {
	ifstream input_file;
	string str, buff, tmp;
	tmp = ex->get_word(num, 1);
		try {
			input_file.open(tmp);
			input_file.exceptions(ifstream::failbit | ifstream::badbit);
			if (input_file.fail() || input_file.bad()) throw commands_exceptions("no read access");
			while (!input_file.eof()) {
				getline(input_file, buff);
				str += buff;
				if (!input_file.eof()) {
					str += '\n';
				}
			}
		}
		catch (commands_exceptions & e) {
			cout << e.error() << endl;
			return;
		}
	ex->edit_text(str);
	return;
}
void replace::doing(executor* ex, size_t num) {
	string word1 = (ex->get_word(num, 1));
	string word2 = (ex->get_word(num, 2));
	string text = ex->get_text();
	size_t pos = text.find(word1);
		while (pos != -1) {
			text.replace(text.find(word1), word1.length(), word2);
			pos = text.find(word1);
		}
	ex->edit_text(text);
	return;
}
void sorting::doing(executor* ex, size_t num) {
	string text = ex->get_text();
	vector<string>words;
	string tmp = "init";
	if (text.empty())return;
		while (1) {
			tmp = ex->get_word(text, 0);
			if (tmp.empty()) break;
			words.push_back(tmp);
			text.erase(0, tmp.size() + 1);
		}
		sort(words.begin(), words.end());
		text.clear();
		for (const auto& piece : words) {
			text += piece;
			text += " ";
		}
		text.resize(text.size() - 1);
	ex->edit_text(text);
	return;
}
void grep::doing(executor* ex, size_t num) {
	std::string new_text, text = ex->get_text();
	std::vector<std::string>words;
	std::string tmp, word1 = ex->get_word(num, 1);
	int i, pos = text.find(word1);
		while (pos != -1) {
			for (i = pos; i > 0; i--) {
				if (i == 0)break;
				if ((text[i - 1]) == '\n')break;
			}
			for (; i < (int)text.size(); i++) {
				if (text[i] == '\n') {
					tmp += '\n';
					break;
				}
				tmp += text[i];
			}
			pos += tmp.size() - word1.size();
			new_text += tmp;
			pos = text.find(word1, pos + 1);
			tmp.clear();
		}
	ex->edit_text(new_text);
	return;
}

void dump::doing(executor* ex, size_t num) {
	ofstream output_file;
	try {
		output_file.open(ex->get_word(num, 1));
		output_file.exceptions(ios_base::failbit || ios_base::badbit);
		if (output_file.fail() || output_file.bad()) throw commands_exceptions("no write access");
		output_file << ex->get_text();
	}
	catch (commands_exceptions & e) {
		cout << e.error() << endl;
		return;
	}
	return;
}

void write_file::doing(executor* ex, size_t num) {
	ofstream output_file;
	try {
		output_file.open(ex->get_word(num, 1));
		output_file.exceptions(ios_base::failbit || ios_base::badbit);
		if (output_file.fail() || output_file.bad()) throw commands_exceptions("no write access");
		output_file << ex->get_text();
	}
	catch (commands_exceptions & e){
		cout << e.error() << endl;
		return;
	}
	ex->edit_text(true);
	return;
}