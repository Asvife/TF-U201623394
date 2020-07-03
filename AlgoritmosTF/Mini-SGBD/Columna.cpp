#include "Columna.h"



Columna::Columna()
{
}

Columna::Columna(vector<Dato*> set, MATCH comp, string tag)
{
	Tags = set[0]->getTags();
	Col = new AvlTree(comp, tag);
	for each (Dato* var in set)
	{
		Col->add(var);
	}
}


Columna::~Columna()
{
}

AvlTree * Columna::getCol()
{
	return Col;
}

vector<Dato*> Columna::getVector()
{
	vector<Dato*> vec;
	Col->BSTtoVector(vec);
	return vec;
}

vector<string> Columna::getTags()
{
	return Tags;
}
