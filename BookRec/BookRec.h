#pragma once
#include <vector>
#include <map>

using namespace std;


class BookRec {
public:
	map<string, vector<Book>> authorGraph;
	map<string, vector<Book>> publisherGraph;
	vector<Book> books;
	map<string, vector<pair<Book, int>>> list;

	BookRec();
	void GetDataFromFile1(string filePath);
	void GetDataFromFile2(string filePath);
	map<string, vector<pair<Book, int>>> edgeCreation();
};