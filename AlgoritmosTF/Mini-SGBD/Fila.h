#pragma once
#include "Columna.h"

class Fila
{
	int row;
	vector<Columna*> cols;
public:
	Fila();
	Fila(string name);
	~Fila();
	void addCol(Columna* col);
	void changeRow(int row);
	void Init(vector<Dato*> data, vector<string>tags);
	void Read(string file);
	AvlTree* getCurrentTree();
	vector<Dato*> getCurrentVector();
	vector<string> getTags();
};

