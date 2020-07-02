#include "Fila.h"



Fila::Fila()
{
	row = 0;
}

Fila::Fila(string name)
{
	row = 0;
	Read(name);
}


Fila::~Fila()
{
}

void Fila::addCol(Columna * col)
{
	cols.push_back(col);
}

void Fila::changeRow(int row)
{
	if (row < cols.size())
		this->row = row;
	else
		this->row = 0;
}

void Fila::Init(vector<Dato*> data, vector<string>tags)
{
	vector<Columna*> cols;
	Columna* col;
	for each (string tag in tags)
	{
		col = new Columna(data,
			[](Dato* a, Dato*b, string tag)
		{
			if (a->findByTag(tag) > b->findByTag(tag))
				return -1;
			if (a->findByTag(tag) == b->findByTag(tag))
				return 0;
			else
				return 1;
		}, tag
		);
		cols.push_back(col);
	}

	for each (Columna* col in cols)
	{
		addCol(col);
	}
}

void Fila::Read(string file)
{
	ifstream is(file);
	string ss;
	string data;
	vector<string> dato;
	vector<string> tags;
	vector<Dato*> datos;
	Dato* nuevo;
	if (!is.eof())
	{
		getline(is, ss);
		std::istringstream iline(ss);
		while (getline(iline, data, ','))
		{
			tags.push_back(data);
		}
	}

	while (!is.eof())
	{
		getline(is, ss);
		if (ss.length() > 0) {
			dato.clear();
			std::istringstream iline(ss);
			while (getline(iline, data, ','))
			{
				dato.push_back(data);
			}
			nuevo = new Dato(dato, tags);
			datos.push_back(nuevo);
		}
	}
	vector<Columna*> cols;
	Columna* col;
	for each (string tag in tags)
	{
		col = new Columna(datos,
			[](Dato* a, Dato*b, string tag)
		{
			if (a->findByTag(tag) > b->findByTag(tag))
				return -1;
			if (a->findByTag(tag) == b->findByTag(tag))
				return 0;
			else
				return 1;
		}, tag
		);
		cols.push_back(col);
	}

	for each (Columna* col in cols)
	{
		addCol(col);
	}

	
}

SimpleBST * Fila::getCurrentTree()
{
	return cols[row]->getCol();
}

vector<Dato*> Fila::getCurrentVector()
{
	return cols[row]->getVector();
}

vector<string> Fila::getTags()
{
	return cols[0]->getTags();
}
