#include <iostream>
#include <unordered_map>
#include <map>
#include <random>
#include <ctime>
#include<iterator>
#include <fstream>
#include <sstream>
#include <vector>
#include "BookRec.h"
#include "Book.h"

using namespace std;

BookRec::BookRec()
{

	string filePath = "book1-100k2.txt";
	GetDataFromFile1(filePath);

	filePath = "book100k-200k.txt";
	GetDataFromFile2(filePath);

	this->list = edgeCreation();
}

void BookRec::GetDataFromFile1(string filePath)
{
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
			this->authorGraph[author].push_back(book);
			this->publisherGraph[publisher.substr(0, publisher.find(' '))].push_back(book);
			this->books.push_back(book);
		}

	}
	else {
		cout << "file wont open " << filePath << endl;
	}


}

void BookRec::GetDataFromFile2(string filePath)
{
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
			this->authorGraph[author].push_back(book);
			this->publisherGraph[publisher.substr(0, publisher.find(' '))].push_back(book);

		}

	}
	else {
		cout << "file wont open " << filePath << endl;
	}

}

map<string, vector<pair<Book, int>>> BookRec::edgeCreation()
{
	map<string, vector<pair<Book, int>>> adjacencyList;

	for (auto itr = this->authorGraph.begin(); itr != this->authorGraph.end(); itr++) {
		for (int i = 0; i < itr->second.size(); i++) {
			for (int j = 0; j < itr->second.size(); j++) {
				if (itr->second[i].GetName() == itr->second[j].GetName()) {
					continue;
				}
				int weight = 3;
				if (itr->second[i].GetAuthor() == itr->second[j].GetAuthor()) {
					weight--;
				}
				if (itr->second[i].GetPublisher() == itr->second[j].GetPublisher()) {
					weight--;
				}
				if (weight != 3) {
					adjacencyList[itr->second[i].GetName()].push_back(make_pair(itr->second[j], weight));
				}
			}
		}
	}


	return adjacencyList;
}





