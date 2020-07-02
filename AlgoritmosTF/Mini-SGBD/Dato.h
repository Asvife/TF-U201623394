#pragma once
#include <vector>
#include <string>
using namespace std;

class Dato
{
	vector<string> Data;
	vector<string> Tags;
	int _findByTag(string tag);
public:
	Dato();
	Dato(vector<string> Data, vector<string> Tags);
	~Dato();
	string findByTag(string tag);
	vector<string> getData();
	vector<string> getTags();
};