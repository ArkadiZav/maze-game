#include <string>
#include <iostream>

using namespace std;

#include "tokenizer.h"

tokenizer_t::tokenizer_t()
{
	m_tokens = new queue<string>();
	m_delimiters = ";|";	
}

tokenizer_t::~tokenizer_t()
{
	if (0 != m_tokens)
	{
		delete m_tokens;
		m_tokens = 0;
	}
}

size_t tokenizer_t::SeperateToTokens(const string& _line)
{
	size_t StartOfToken = 0;
	size_t EndOfToken = _line.find_first_of(m_delimiters);
	string token;
	
	while (string::npos != EndOfToken && EndOfToken < _line.length())
	{
		if (0 != EndOfToken - StartOfToken && !isspace(_line[StartOfToken]))
		{
			token = _line.substr(StartOfToken,EndOfToken - StartOfToken);
			m_tokens->push(token);
		}
		StartOfToken = EndOfToken + 1;
		EndOfToken = _line.find_first_of(m_delimiters,StartOfToken);	
	}
	
	if (0 < _line.length()-StartOfToken && !isspace(_line[StartOfToken]))
	{
		token = _line.substr(StartOfToken,_line.length()-StartOfToken);
		m_tokens->push(token);	
	}
	return m_tokens->size();
}

string tokenizer_t::GetToken()
{
	string token = m_tokens->front();
	m_tokens->pop();
	return token;
}
