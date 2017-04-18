#ifndef __TOKENIZER_T_H__
#define __TOKENIZER_T_H__

#include <queue>

using namespace std;

class PreDefined_container_t;

class tokenizer_t
{
public:

	~tokenizer_t();
	tokenizer_t();

	size_t SeperateToTokens(const string& _line);  //return num of tokens;
	string GetToken();

private:

	tokenizer_t(const tokenizer_t& _tokenizer);
	tokenizer_t& operator =(const tokenizer_t& _tokenizer);
	
	queue<string>* m_tokens;
	string m_delimiters;
};

#endif //ifndef __TOKENIZER_T_H__
