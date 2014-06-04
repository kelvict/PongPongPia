#include "CurlUtils.h"

#include "curl/curl.h"
#include "cocos2d.h"
#include <string>

USING_NS_CC;

std::string CurlUtils::useGet()
{
	CURL* curl = NULL;
	CURLcode res;
	std::string writeBackBuff;

	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, "http://pongpongpia.azurewebsites.net/test.xml");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeHtml);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &writeBackBuff);

		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);

		if (res == CURLE_OK) {
			//CCLog("Runtime %d", res);
			//CCLog("Get Data from server: %s", writeBackBuff.c_str());
			return writeBackBuff;
		}
	} else {
		CCLog("curl is null");
		return "";
	}
}

std::string CurlUtils::usePost(std::string url,map<string,string>& values)
{
	std::string sendout="";
	translate(values,sendout);

	CURL* curl = NULL;
	CURLcode res;
	std::string writeBackBuff;

	curl = curl_easy_init();

	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_POST, true);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, sendout.c_str());
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeHtml);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &writeBackBuff);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);

		if (res == CURLE_OK) {
			return writeBackBuff;
		}
		else{
			return "fuck";
		}
	} 
	else {
		CCLog("curl is null");
		return "gggg";
	}
}

size_t CurlUtils::writeHtml(void *ptr, size_t size, size_t nmemb, std::string *writerData)
{
	if (writerData == NULL)
		return 0;
	writerData->append((char*)ptr, size * nmemb);
	return size * nmemb;
}

void CurlUtils::translate(const map<std::string,std::string>& values,std::string&sendoutMsg){
	for(map<std::string,std::string>::const_iterator it = values.begin();it!=values.end();++it){
		if(it==values.begin()){
			sendoutMsg += (it->first+"="+it->second);
		}
		else{
			sendoutMsg += ("&"+it->first+"="+it->second);
		}

	}

}