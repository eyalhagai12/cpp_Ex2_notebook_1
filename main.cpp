#include "Notebook.hpp"
#include <iostream>
#include "Direction.hpp"
#include <vector>
#include <string>

using ariel::Direction;
using namespace std;

int main(int argc, char const *argv[])
{

    ariel::Notebook notebook;
    notebook.write(/*page=*/100, /*row=*/100, /*column=*/50, Direction::Horizontal, "abcd");
    notebook.write(/*page=*/100, /*row=*/97, /*column=*/67, Direction::Horizontal, "asgdjsjahsb");
    cout << notebook.read(/*page=*/100, /*row=*/99, /*column=*/51, Direction::Vertical, /*length=*/3) << endl;
    // prints "_b_" (starts at row 99 which is empty; then at row 100 there is "b"; then row 101 is empty again).
    // notebook.write(/*page=*/100, /*row=*/99, /*column=*/52, Direction::Vertical, "xyz");
    // throws error because writing the letter y will intersect with the letter c
    notebook.erase(/*page=*/100, /*row=*/99, /*column=*/51, Direction::Vertical, /*length=*/3);
    notebook.erase(100, 97, 69, Direction::Horizontal, 5);
    notebook.erase(/*page=*/100, /*row=*/95, /*column=*/75, Direction::Vertical, /*length=*/5);
    // writes ~ instead of _ in line 99, b in line 100 and _ again in line 99

    notebook.show(100); // shows the notebook's page in a reasonable way. For example:
                        //    98:  _________
                        //    99:  ___~_____
                        //    100: __a~cd___
                        //    101: ___~_____
                        //    102: _________

    cout << notebook.read(/*page=*/100, /*row=*/97, /*column=*/65, Direction::Horizontal, /*length=*/15) << endl;
    return 0;
}
