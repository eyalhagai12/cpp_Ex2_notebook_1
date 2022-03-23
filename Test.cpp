#include "doctest.h"
#include "Notebook.hpp"

#include <iostream>
#include <string>
#include <vector>

using namespace std;
using ariel::Direction;

ariel::Notebook notebook;
vector<string> words = {"hello world", "test phrase", "ariel university", "c++ is nice", "1 + 1 = 2",
						"welcome to the metaverse",
						"i am mark zuckerberg"};

string word;

const size_t pages = 5;
size_t rows = words.size();
size_t num_of_letters = 0;

int random(int min, int max) // range : [min, max]
{
	static bool first = true;
	if (first)
	{
		srand(time(NULL)); // seeding for the first time only!
		first = false;
	}
	return min + rand() % ((max + 1) - min);
}

TEST_CASE("horizontal write test")
{
	// horizontal writing
	for (size_t i = 0; i < pages; ++i)
	{
		for (size_t j = 0; j < rows; ++j)
		{
			int col = random(1, ariel::LINE_LEN - 2 - words[j].size());

			notebook.write(i, j, col, Direction::Horizontal, words[j]);
			CHECK(notebook.read(i, j, col, Direction::Horizontal, words[j].size()) == words[j]);
			CHECK(notebook.read(i, j, col - 1, Direction::Horizontal, words[j].size() + 2) == "_" + words[j] + "_");
		}
	}
}

TEST_CASE("vertical write test")
{
	// vertical writing
	for (size_t i = pages; i < pages * 2; ++i)
	{
		for (size_t j = 0; j < rows; ++j)
		{
			int col = random(0, ariel::LINE_LEN - 1);
			size_t idx = j % words.size();

			notebook.write(i, col, idx, Direction::Vertical, words[idx]);
			CHECK(notebook.read(i, col, j, Direction::Vertical, words[idx].size()) == words[idx]);
			if (col > 0)
			{
				if (notebook.read(i, col - 1, j, Direction::Vertical, words[idx].size() + 2) != "_" + words[idx] + "_")
				{
					cout << "INFO:\n\trow (col): " << j << "\n\tcol (j): " << col << "\n\tword length: " << words[idx].size() << endl;
				}
				CHECK(notebook.read(i, col - 1, j, Direction::Vertical, words[idx].size() + 2) == "_" + words[idx] + "_");
			}

			if ((size_t)col + words[idx].size() > ariel::LINE_LEN)
			{
				j++;
			}
		}
	}
}

TEST_CASE("writing on existing stuff")
{
	// set up some parameters
	word = "welcome to the metaverse";
	int page = 126;
	int row = 5;
	int col = 40;

	// write to some place
	notebook.write(page, row, col, Direction::Horizontal, word);

	// write on the above row multiple type
	for (size_t i = (size_t)col - (word.size() - 1); i < word.size() * 2; ++i)
	{
		CHECK_THROWS(notebook.write(page, row, i, Direction::Horizontal, word));
	}

	// change page and columns
	page++;
	row = 40;
	col = 5;

	// check writing vertical
	notebook.write(page, row, col, Direction::Horizontal, word);

	for (int i = 0; i < word.size(); ++i)
	{
		for (int j = (size_t)row - (word.size() - 1); j < word.size(); ++j)
		{
			CHECK_THROWS(notebook.write(page, j, col + i, Direction::Vertical, word));
		}
	}

	// change parameters
	page++;
	row = 5;
	col = 40;

	// write to the notebook
	notebook.write(page, row, col, Direction::Vertical, word);

	// write Horizontally in the vertical text
	for (size_t i = 0; i < word.size(); ++i)
	{
		for (size_t j = (size_t)row - (word.size() - 1); j < word.size(); ++j)
		{
			CHECK_THROWS(notebook.write(page, j, (size_t)col + i, Direction::Horizontal, word));
		}
	}

	// change parameters
	page++;
	row = 40;
	col = 5;

	// write the word to the page
	notebook.write(page, row, col, Direction::Vertical, word);

	// write verticaly on verticaly written
	for (size_t i = (size_t)row - (word.size() - 1); i < word.size() * 2; ++i)
	{
		CHECK_THROWS(notebook.write(page, i, col, Direction::Vertical, word));
	}
}

TEST_CASE("text, read and erase exceeds line length")
{
	// define parameters
	string word = "hello world";
	int page = 50;
	int row = 10;
	int col = ariel::LINE_LEN - word.size() + 1;

	// try to write out of row bounds
	for (size_t i = 0; i < word.size(); ++i)
	{
		CHECK_THROWS(notebook.write(page, row, (size_t)col + i, Direction::Horizontal, word));
	}

	// try to read out of row bounds
	for (size_t i = 0; i < word.size(); ++i)
	{
		CHECK_THROWS(notebook.read(page, row, (size_t)col + i, Direction::Horizontal, word.size()));
	}

	// try to read out of row bounds
	for (size_t i = 0; i < word.size(); ++i)
	{
		CHECK_THROWS(notebook.erase(page, row, (size_t)col + i, Direction::Horizontal, word.size()));
	}
	

}