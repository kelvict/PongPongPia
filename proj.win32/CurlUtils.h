#pragma once

#include <string>
#include <map>

using namespace std;

#define API_URL "http://pongpongpia.kelvixx.com/"
#define POST(map) CurlUtils::usePost(API_URL,map)

class CurlUtils   
{   
public:
	std::string useGet();   
	static size_t writeHtml(void *ptr, size_t size, size_t nmemb, std::string *writerData); 
	static std::string usePost(std::string url,map<string,string>& values);
	static void translate(const map<std::string,std::string>& values,std::string& sendoutMsg);
}; 

