#pragma once
#include "Dato.h"
#include "SimpleBST.h"
class Columna
{
	SimpleBST* Col;
	vector<string> Tags;
public:
	Columna();
	Columna(vector<Dato*> set, MATCH comp, string tag);
	~Columna();

	SimpleBST* getCol();
	vector<Dato*> getVector();
	vector<string> getTags();
};

