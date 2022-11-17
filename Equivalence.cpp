#include <iostream>
#include <fstream>
#include <vector>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
using namespace std;

#include "CreateInput.h"
#include "Equivalence.h"

void GetFolder(string path,vector<string>& folder)
{
    DIR *pDir;
    struct dirent* ptr;
    if(!(pDir = opendir(path.c_str())))
        return;
    while((ptr = readdir(pDir))!=0) {
        if (ptr->d_type == DT_DIR && strcmp(ptr->d_name, ".") != 0 && strcmp(ptr->d_name, "..") != 0)
            folder.push_back(path + "/" + ptr->d_name);
    }
    closedir(pDir);
}

void GetCompareFiles(string path,vector<string>& filename)
{
    DIR *pDir;
    struct dirent* ptr;
    if(!(pDir = opendir(path.c_str())))
        return;
    while((ptr = readdir(pDir))!=0) {
        if (strcmp(ptr->d_name, ".") != 0 && strcmp(ptr->d_name, "..") != 0
            && strcmp(ptr->d_name, "stdin_format.txt") != 0 && strcmp(ptr->d_name, "random_input.txt") != 0)
            filename.push_back(path + "/" + ptr->d_name);
    }
    closedir(pDir);
}


/* Windows平台下，需要#include <io.h>

void getFolder(string path, vector<string>& folder)
{
    long long hFile = 0;     //注意一定要用long long
    struct _finddata_t fileInfo;
    string p;
    if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileInfo)) != -1)
    {
        do
        {
            if ((fileInfo.attrib & _A_SUBDIR)) //如果是目录，存入列表
            {
                if (strcmp(fileInfo.name, ".") != 0 && strcmp(fileInfo.name, "..") != 0)
                    folder.push_back(fileInfo.name);
            }
            else
            {
                continue;
            }
        } while (_findnext(hFile, &fileInfo) == 0);
    }
    _findclose(hFile);
}
*/

bool CompareOutputFile()
{
    ifstream file1;
    file1.open("output1.txt", ios::in);
    if(!file1.is_open()){
        cout << "输出文件1打开失败\n";
        return false;
    }
    ifstream file2;
    file2.open("output2.txt", ios::in);
    if(!file2.is_open()){
        cout << "输出文件2打开失败\n";
        file1.close();
        return false;
    }
    string s1, s2;
    bool flag = true;
    while(!file1.eof() && !file2.eof())
    {
        file1 >> s1;
        file2 >> s2;
        if(s1 != s2)
        {   
            flag = false;
            break;
        }
    }
    if(!file1.eof() || !file2.eof())
        flag = false;
    file1.close();
    file2.close();
    return flag;
}

bool CompareFiles(string file1, string file2, string path) //判断两文件是否等价
{
    ifstream infile;
    infile.open(path+"/random_input.txt", ios::in);
    if(!infile.is_open()){
        cout << "不存在随机创造输入文件\n";
        return false;
    }
    string input;
    for(int i = 0; i < TEST_TIMES && !infile.eof(); i += 1)
    {
        getline(infile, input);
        ofstream outfile;
        outfile.open("input.txt", ios::out);
        if(!outfile.is_open()){
            cout << "输入文件打开失败\n";
            return false;
        }
        outfile << input;
        outfile.close();
        system(("g++ "+file1).c_str());
        system("./a.out <input.txt >output1.txt");
        system(("g++ "+file2).c_str());
        system("./a.out <input.txt >output2.txt");
        if(!CompareOutputFile())
        {
            infile.close();
            return false;
        }
    }
    infile.close();
    return true;
}

void Equivalence(string dir_path)
{
    CreateRandomInput(dir_path);
    vector<string> input_files;
    GetCompareFiles(dir_path, input_files);

	ofstream equalfile;
	equalfile.open("output/equal.csv", ios::app);
    if(!equalfile.is_open())
    {
        cout << "equal.csv文件打开失败\n";
        return;
    }
    ofstream inequalfile;
	inequalfile.open("output/inequal.csv", ios::app);
    if(!inequalfile.is_open())
    {
        cout << "inequal.csv文件打开失败\n";
        return;
    }

    for(int i = 0; i < input_files.size()-1; i += 1)
    {
        for(int j = i+1; j < input_files.size(); j += 1)
        {
            if(CompareFiles(input_files[i], input_files[j], dir_path))
            {
                equalfile << input_files[i] << "," << input_files[j] << endl;
            }
            else
            {
                inequalfile << input_files[i] << "," << input_files[j] << endl;
            }
        }
    }
    equalfile.close();
    inequalfile.close();
}
