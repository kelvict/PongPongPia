#include "Language.h"
#include <cocos2d.h>

USING_NS_CC;

Language::Language(void)
{
}


Language::~Language(void)
{
}

std::string Language::getChinese( std::string str )
{
	CCDictionary* strings = CCDictionary::createWithContentsOfFile("chinese.xml");
	std::string word = ((CCString*)strings->objectForKey(str))->m_sString;
	return word;
}
