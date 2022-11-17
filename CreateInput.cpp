#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>
#include <string.h>
using namespace std;

#include "CreateInput.h"

void CreateRandomInput(string dir_path)
{
    ifstream infile;
    infile.open(dir_path+"/stdin_format.txt", ios::in);
    if(!infile.is_open()){
        cout << "不存在输入格式文件\n";
        return;
    }
    vector<input_format> format;
    string f;
    input_format inf;
    while(!infile.eof())
    {
        infile >> f;
        if(f == "char")
        {
            inf = {"char", 0, 0};
        }
        else if(f.find("int") != string::npos)
        {
            string sa="", sb="";
            int k = 4;
            for(; f[k] != ','; k += 1)
            {
                sa += f[k];
            }
            for(k+=1;f[k] != ')'; k += 1)
            {
                sb += f[k];
            }
            int a = stoi(sa.c_str());
            int b = stoi(sb.c_str());
            inf = {"int", a, b};
        }
        else if(f.find("string") != string::npos)
        {
            string sa="", sb="";
            int k = 7;
            for(; f[k] != ','; k += 1)
            {
                sa += f[k];
            }
            for(k+=1;f[k] != ')'; k += 1)
            {
                sb += f[k];
            }
            int a = stoi(sa.c_str());
            int b = stoi(sb.c_str());
            inf = {"string", a, b};
        }
        else
        {
            inf = {"error", 0, 0};
        }
        format.push_back(inf);
    }
    infile.close();
    
    ofstream outfile;
    outfile.open(dir_path+"/random_input.txt", ios::out);
    if(!outfile.is_open()){
        cout << "随机输入文件打开失败\n";
        return;
    }
	srand((unsigned)time(NULL));
    for(int t = 0; t < TEST_TIMES; t += 1)
    {
        for(int i = 0; i < format.size(); i += 1)
        {
            if(format[i].type == "char")
            {
                char c = rand()%26 + (rand()%2 ? 65: 97);
                outfile << c;
            }
            else if(format[i].type == "int")
            {
                int r = format[i].a + rand() % (format[i].b - format[i].a + 1);
                outfile << r;
            }
            else if(format[i].type == "string")
            {
                int length = format[i].a + rand() % (format[i].b - format[i].a + 1);
                string s = "";
                for(int j = 0; j < length ; j += 1)
                {
                    s += rand()%26 + (rand()%2 ? 65: 97);
                }
                outfile << s;
            }
            outfile << " ";
        }
        outfile << "\n";
    }
    outfile.close();
}