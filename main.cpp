#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

#include "CreateInput.h"
<<<<<<< HEAD
=======
#include "Equivalence.h"
>>>>>>> output


int main()
{
<<<<<<< HEAD
    CreateRandomInput("input");
    //output module
=======
    system("mkdir output");
    vector<string> input_folder;
    GetFolder("input", input_folder);
    for(int i = 0; i < input_folder.size(); i += 1)
    {
        Equivalence(input_folder[i]);
    }
    system("rm -f *.txt");
    system("rm -f a.out");
>>>>>>> output
}