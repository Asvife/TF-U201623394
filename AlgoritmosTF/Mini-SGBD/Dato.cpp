#include "Dato.h"




int Dato::_findByTag(string tag)
{
	for (int i = 0; i < Tags.size(); i++)
	{
		if (Tags[i] == tag)
			return i;
	}
	return -1;
}


Dato::Dato()
{
}


Dato::Dato(vector<string> Data, vector<string> Tags)
{
	this->Data = Data;
	this->Tags = Tags;
}


Dato::~Dato()
{
}

string Dato::findByTag(string tag)
{
	int i = _findByTag(tag);
	if (i != -1)
		return Data[i];
	else
		return nullptr;
}

vector<string> Dato::getData()
{
	return Data;
}

vector<string> Dato::getTags()
{
	return Tags;
}
