#include "rDato.h"




rDato::rDato(List<String^>^ data)
{
	{
		this->data = data;
	}
}

List<String^>^ rDato::getData()
{
	return data;
}
