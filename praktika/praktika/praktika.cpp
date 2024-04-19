#include <iostream>
#include <curl/curl.h>
#include <libxml/HTMLparser.h>
#include <string>

#pragma comment(lib, "libcurl.lib")
#pragma comment(lib, "libxml2.lib")

using namespace std;

size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* data) {
    data->append((char*)contents, size * nmemb);
    return size * nmemb;
}

string GetWeatherForecast(const string& city) {
    string url = "https://ua.sinoptik.ua/погода-" + city;
    CURL* curl = curl_easy_init();
    string response;

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
        }

        curl_easy_cleanup(curl);
    }

    return response;
}

void ParseWeatherForecast(const string& html) {
    
}

int main() {
    vector<string> cities = { "Київ", "Харків", "Львів", "Одеса", "Дніпро", "Запоріжжя", "Вінниця", "Житомир", "Чернігів", "Суми" };

    for (const auto& city : cities) {
        string html = GetWeatherForecast(city);
        ParseWeatherForecast(html);
    }

    return 0;
}
