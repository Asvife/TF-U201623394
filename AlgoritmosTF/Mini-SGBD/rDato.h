#pragma once

using namespace System::Collections::Generic;
using namespace System;

ref class rDato
{
	List<String^>^ data;

public:
	rDato(List<String^>^ data);
	List<String^>^ getData();
};
