#include "Book.h"

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