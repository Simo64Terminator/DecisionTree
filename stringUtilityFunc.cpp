#include "stringUtility.h"

// Functions used to standardize/manipulate strings

void removeBlanksAndLower(string& s)
{
	size_t found = s.find_first_of(" ");
	
	while(found!=string::npos)
	{
		s.erase(found,1);
		found = s.find_first_of(" ");
	}

	stringLower(s);
}


void stringLower(string& s)
{
	for(string::size_type i=0; i < s.length(); ++i)
		s[i] = tolower(s[i]);
}
