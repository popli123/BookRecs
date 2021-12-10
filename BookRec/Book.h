#pragma once
#include <string>
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