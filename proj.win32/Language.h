#pragma once
#include<string>

#define CN(key) Language::getChinese(key)

class Language
{
public:
	Language(void);
	~Language(void);
	static std::string getChinese(std::string key);
};

