#include <iostream>
#include <unordered_map>
#include <map>
#include <random>
#include <ctime>
#include<iterator>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;


class Book {
	string name;
	string author;
	string publisher;
	int publishYear;
	double rating;

public:
	Book(string bookName, string bookAuthor, string bookPublisher, int bookYear, double bookRating);
	string GetName();
	string GetAuthor();
	string GetPublisher();
	int GetPublishYear();
	double GetRating();
	bool operator==(const Book& rhs) const;
};


void GetDataFromFile1(string filePath, map<string, vector<Book>>& authorGraph, map<string, vector<Book>>& publisherGraph, vector<Book>& books) {

	ifstream inFile(filePath);

	if (inFile.is_open()) {

		string lineFromFile;
		getline(inFile, lineFromFile);

		while (getline(inFile, lineFromFile)) {
			istringstream stream(lineFromFile);

			string name;
			string author;
			string publisher;
			int publishYear;
			double rating;

			string tempPublishYear;
			string tempRating;

			string id;
			string pagesNumber;


			getline(stream, id, '	');
			getline(stream, name, '	');
			getline(stream, pagesNumber, '	');
			getline(stream, publisher, '	');
			getline(stream, tempPublishYear, '	');
			getline(stream, author, '	');
			getline(stream, tempRating, '	');

			publishYear = stoi(tempPublishYear);
			rating = stod(tempRating);


			Book book(name, author, publisher, publishYear, rating);
			authorGraph[author].push_back(book);
			publisherGraph[publisher.substr(0, publisher.find(' '))].push_back(book);
			books.push_back(book);
		}

	}
	else {
		cout << "file wont open " << filePath << endl;
	}



}

void GetDataFromFile2(string filePath, map<string, vector<Book>>& authorGraph, map<string, vector<Book>>& publisherGraph) {

	ifstream inFile(filePath);

	if (inFile.is_open()) {

		string lineFromFile;
		getline(inFile, lineFromFile);

		while (getline(inFile, lineFromFile)) {
			istringstream stream(lineFromFile);

			string name;
			string author;
			string publisher;
			int publishYear;
			double rating;

			string tempPublishYear;
			string tempRating;

			string id;
			string pagesNumber;


			getline(stream, pagesNumber, '	');
			getline(stream, author, '	');
			getline(stream, publisher, '	');
			getline(stream, tempRating, '	');
			getline(stream, id, '	');
			getline(stream, tempPublishYear, '	');
			getline(stream, name, '	');

			publishYear = stoi(tempPublishYear);
			rating = stod(tempRating);


			Book book(name, author, publisher, publishYear, rating);
			authorGraph[author].push_back(book);
			publisherGraph[publisher.substr(0, publisher.find(' '))].push_back(book);

		}

	}
	else {
		cout << "file wont open " << filePath << endl;
	}



}

void SearchForAuthor(string match, map<string, vector<Book>>& authorGraph) {
	map<string, vector<Book>>::iterator iter;
	bool found = false;
	for (iter = authorGraph.begin(); iter != authorGraph.end(); iter++) {
		if (iter->first == match) {
			cout << match << ": ";
			for (int i = 0; i < iter->second.size(); i++) {
				cout << iter->second[i].GetName()<< " " << endl;
				found = true;
			}
		}
	}
	if (found == false)
	{
		cout << "No match found for " << match << endl;
	}

}

void SearchForPublisher(string match, map<string, vector<Book>>& publisherGraph) {
	map<string, vector<Book>>::iterator iter;
	bool found = false;
	for (iter = publisherGraph.begin(); iter != publisherGraph.end(); iter++) {
		if (iter->first == match) {
			cout << match << ": ";
			for (int i = 0; i < iter->second.size(); i++) {
				cout << iter->second[i].GetName() << " " << endl;
				found = true;
			}
		}
	}
	if (found == false)
	{
		cout << "No match found for " << match << endl;
	}

}

map<string, vector<pair<Book, int>>> edgeCreation(map<string, vector<Book>> authorGraph, vector<Book> books) {
	
	map<string, vector<pair<Book, int>>> adjacencyList;

	for (auto itr = authorGraph.begin(); itr != authorGraph.end(); itr++) {
		for (int i = 0; i < itr->second.size(); i++) {
			for (int j = 0; j < itr->second.size(); j++) {
				if (books[i].GetName() == books[j].GetName()) {
					continue;
				}
				int weight = 3;
				if (books[i].GetAuthor() == books[j].GetAuthor()) {
					weight--;
				}
				if (books[i].GetPublisher() == books[j].GetPublisher()) {
					weight--;
				}
				if (weight != 3) {
					adjacencyList[books[i].GetName()].push_back(make_pair(books[j], weight));
				}
			}
		}
	}

	/*
	for (int i = 0; i < books.size(); i++) {
		for (int j = 0; j < books.size(); j++) {
			if (books[i].GetName() == books[j].GetName()) {
				continue;
			}
			int weight = 3;
			if (books[i].GetAuthor() == books[j].GetAuthor()) {
				weight--;
			}
			if (books[i].GetPublisher() == books[j].GetPublisher()) {
				weight--;
			}
			if (weight != 3) {
				adjacencyList[books[i].GetName()].push_back(make_pair(books[j], weight));
			}
			
		}
	}
	*/



	return adjacencyList;
}

void printEdgeList(map<string, vector<pair<Book, int>>> list) {
	int i = 0;
	for (auto itr = list.begin(); itr != list.end(); itr++) {
		if (i == 25) {
			break;
		}
		cout << itr->first << ": ";
		for (int j = 0; j < itr->second.size(); j++) {
			cout << itr->second[j].second << " ";
		}
		cout << endl;
		i++;
	}
}

int main()
{
	cout << "program starting" << endl;


		map<string, vector<Book>> authorGraph;
		map<string, vector<Book>> publisherGraph;
		vector<Book> books;

		string filePath = "book1-100k2.txt";
		GetDataFromFile1(filePath, authorGraph, publisherGraph, books);

		filePath = "book100k-200k.txt";
		GetDataFromFile2(filePath, authorGraph, publisherGraph);

		cout << "The first dataset is complete" << endl;

		map<string, vector<pair<Book, int>>> list = edgeCreation(authorGraph, books);



	return 0;
}

Book::Book(string bookName, string bookAuthor, string bookPublisher, int bookYear, double bookRating)
{
	name = bookName;
	author = bookAuthor;
	publisher = bookPublisher;
	publishYear = bookYear;
	rating = bookRating;
}

string Book::GetName()
{
	return name;
}

string Book::GetAuthor()
{
	return author;
}

string Book::GetPublisher()
{
	return publisher;
}

int Book::GetPublishYear()
{
	return publishYear;
}

double Book::GetRating()
{
	return rating;
}

bool Book::operator==(const Book& rhs) const
{
	if (rhs.name == this->name) {
		return true;
	}
	return false;
}

