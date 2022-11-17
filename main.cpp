#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

#include "CreateInput.h"
#include "Equivalence.h"


int main()
{
    system("mkdir output");
    vector<string> input_folder;
    GetFolder("input", input_folder);
    for(int i = 0; i < input_folder.size(); i += 1)
    {
        Equivalence(input_folder[i]);
    }
    system("rm -f *.txt");
    system("rm -f a.out");
}