#pragma once

void GetFolder(string path,vector<string>& folder);
void GetCompareFiles(string path,vector<string>& filename);

bool CompareOutputFile();
bool CompareFiles(string file1, string file2, string path); //true表示两个文件等价
void Equivalence(string dir_path);