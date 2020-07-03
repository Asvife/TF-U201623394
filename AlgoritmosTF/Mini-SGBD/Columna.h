#pragma once
#include "Dato.h"
#include "AvlTree.h"
class Columna
{
	AvlTree* Col;
	vector<string> Tags;
public:
	Columna();
	Columna(vector<Dato*> set, MATCH comp, string tag);
	~Columna();

	AvlTree* getCol();
	vector<Dato*> getVector();
	vector<string> getTags();
};

