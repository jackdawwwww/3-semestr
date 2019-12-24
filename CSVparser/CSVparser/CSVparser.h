#pragma once
#include<iostream>
#include<tuple>
#include<vector>
#include<string>
#include<fstream>
#include<sstream>
#include<limits>

template<size_t i, typename... Args>
typename std::enable_if<(i >= sizeof...(Args))>::type
printTuple(std::ostream&, const std::tuple<Args...>&) { return; }

template<size_t i, typename... Args>
typename std::enable_if<(i < sizeof...(Args))>::type
	printTuple(std::ostream& os, const std::tuple<Args...>& tup) {
	if (i != 0) os << ", ";
	os << std::get<i>(tup);
	printTuple<i + 1>(os, tup);
}

template<typename... Args>
std::ostream& operator<<(std::ostream& os, const std::tuple<Args...>& tup) {
	printTuple<0>(os, tup);
	return os << std::endl;
}

//convert tuple to types
template<typename T>
T convert(const std::string& cell) {
	T t;
	std::stringstream ss(cell);
	ss >> t;
	return T(t);
}

template<>
std::string convert(const std::string& cell) {
	return cell;
}

std::vector<std::string> parseLine(const std::string& line, char delimiter) {
	std::vector<std::string> parsedLine;

	for (size_t i = 0; i < line.size(); ++i) {
		std::string cell;

		while (i < line.size() && line[i] != delimiter) {
			cell += line[i];
			i++;
		}

		if (!cell.empty()) {
			parsedLine.push_back(cell);
		}
	}
	return parsedLine;
}

//creating tuple
template<size_t n, typename... Args>
typename std::enable_if<(n >= sizeof...(Args))>::type
makeTuple(const std::vector<std::string>& cells, std::tuple<Args...>& tup) {
	return;
}

template<size_t n, typename... Args>
typename std::enable_if<(n < sizeof...(Args))>::type
	makeTuple(const std::vector<std::string>& cells, std::tuple<Args...>& tup) {
	std::get<n>(tup) = convert<typename std::tuple_element<n, std::tuple<Args...>>::type>(cells[n]);
	makeTuple<n + 1>(cells, tup);
}

template<typename ... Args>
class CSVparser {
private:
	char delimiter;
	std::ifstream& stream;

public:
	class Iterator;

	explicit CSVparser(std::ifstream& stream, size_t skipLines = 0) : stream(stream) {
		std::string line;
		delimiter = ';';
		for (size_t i = 0; i < skipLines; ++i) {
			std::getline(this->stream, line);
		}
	}

	void setDelimiter(char delimiter) { this->delimiter = delimiter; }

	Iterator begin() const {
		return Iterator(stream);
	}

	Iterator end() const {
		return Iterator();
	}

	class Iterator {
	private:
		char delimiter;
		size_t index;
		std::ifstream* stream;
		std::tuple<Args...> row;

		void readNextRow(std::ifstream& stream, char delimiter) {
			std::string line;
			stream.seekg(index);
			std::getline(stream, line);
			index = stream.tellg();

			if (stream.eof() || line.empty())
				return;
			makeTuple<0>(parseLine(line, delimiter), row);
		}

	public:
		Iterator(std::ifstream& stream, char delimiter = ';') : stream(&stream), delimiter(delimiter) {
			index = 0;
			readNextRow(*(this->stream), delimiter);
		}

		Iterator() : stream(nullptr) {}

		std::tuple<Args...> const& operator*() const { return row; }

		Iterator& operator++() {
			readNextRow((*stream), delimiter);
			if (stream->eof()) stream = nullptr;
			return *this;
		}

		bool operator==(Iterator& it) {
			return ((index == it.index) || ((this->stream == nullptr) && (it.stream == nullptr)));
		}

		bool operator!=(Iterator& it) { return !((*this) == it); }
	};
};
