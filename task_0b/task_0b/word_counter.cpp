#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <map>
#include <vector>
#include <cctype>

using namespace std;

class statistic_counter {
private:
	ifstream input_file;
	map<string, int>words;
	int full_count;
	int word_count;
public:
	statistic_counter(string name) {
		input_file.open(name);
		full_count = 0;
		word_count = 0;
	}
	~statistic_counter() {}

	void word_reader() {
		string buff, tmp;
		int space = 0;
		while (!(this->input_file).eof()) {
			getline(input_file, buff);
			for (size_t i = 0; i <= buff.size(); i++) {
				if (isalnum(buff[i]) && i < buff.size()) tmp += buff[i];
				else {
					if (i != 0 && !isalnum(buff[i - 1]) || i == buff.size() && buff.size() == 0)continue;
					full_count++;
					if (words[tmp] == 0) word_count++;
					words[tmp]++;
					tmp.clear();
				}
			}

			buff.clear();
		}
	}
	const map < string, int>& get_map() const {
		return words;
	}

	int get_full_count() const {
		return full_count;
	}
	int get_word_count() const {
		return word_count;
	}

};

class write_csv {
private:
	ofstream output_file;
	const statistic_counter* statistic;
public:
	write_csv(string name, const statistic_counter* stat) {
		output_file.open(name);
		statistic = stat;
	}
	~write_csv() {}

	void statistic_writer() {
		int n, word_count, print_count;
		//string print_word;
		double percents = 0;
		n = (*statistic).get_full_count();
		word_count = (*statistic).get_word_count();
		vector<pair< int,string>>sort_words(word_count);
		map<string, int> words = (*statistic).get_map();
		map<string, int>::iterator it = words.begin();
		for (int i=0; it != words.end(); it++, i++) {
			sort_words[i]=make_pair(it->second, it->first);
		}
		sort(sort_words.begin(), sort_words.end());
		for (int i = word_count - 1; i >= 0; i--) {
				print_count = sort_words[i].first;
				percents = print_count * 100;
				percents /= n;
				output_file << sort_words[i].second << ", " << print_count << ", " << percents << "%" << endl;
		}
	}
};

int main(int argc, char** argv)
{
	statistic_counter input_statistic(argv[1]);
	input_statistic.word_reader();
	write_csv csv(argv[2], &input_statistic);
	csv.statistic_writer();
	return 0;
}