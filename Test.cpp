#include "doctest.h"
#include "Notebook.hpp"

#include <iostream>
#include <string>
#include <vector>

using namespace std;
using ariel::Direction;

ariel::Notebook notebook;

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

TEST_CASE("Horizontal tests")
{
    vector<string> words = {"hello world", "test phrase", "ariel university", "c++ is nice", "1 + 1 = 2",
                            "welcome to the metaverse",
                            "i am mark zuckerberg"};
    string word;

    const size_t pages = 5;
    size_t rows = words.size();
    size_t num_of_letters = 0;

    // horizontal writing
    for (size_t i = 0; i < pages; ++i)
    {
        for (size_t j = 0; j < rows; ++j)
        {
            int col = random(0, ariel::LINE_LEN - 1);
            size_t idx = j % words.size();

            notebook.write(i, idx, col, Direction::Horizontal, words[idx]);
            CHECK(notebook.read(i, j, col, Direction::Horizontal, words[idx].size()) == words[idx]);
            if (col > 0)
            {
                if (notebook.read(i, j, col - 1, Direction::Horizontal, words[idx].size() + 2) != "_" + words[idx] + "_")
                {
                    cout << "INFO:\n\trow (j): " << j << "\n\tcol (col): " << col << "\n\tword length: " << words[idx].size() << endl;
                }
                CHECK(notebook.read(i, j, col - 1, Direction::Horizontal, words[idx].size() + 2) == "_" + words[idx] + "_");
            }

            if ((size_t)col + words[idx].size() > ariel::LINE_LEN)
            {
                j++;
            }
        }
    }
}

TEST_CASE("Vertical tests"){

}