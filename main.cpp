#include "curl/curl.h"
#include <iostream>

using namespace std;

static size_t write_callback(void *content, size_t size, size_t nmemb, void *userp) {
    ((std::string *)userp)->append((char*) content, size *nmemb);
    return size * nmemb;
}

static bool is_function_available_in_cpp98(std::string function_name) {
    CURL* curl_handle;
    std::string curl_output;
    std::string reference_website = "https://legacy.cplusplus.com/" + function_name;
    curl_handle = curl_easy_init();
    if (!curl_handle) {
        exit(EXIT_FAILURE);
    }
    curl_easy_setopt(curl_handle, CURLOPT_URL, reference_website.c_str());
    curl_easy_setopt(curl_handle, CURLOPT_SSL_VERIFYPEER, 0);
    curl_easy_setopt(curl_handle, CURLOPT_SSL_VERIFYHOST, 0);
    curl_easy_setopt(curl_handle, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, &curl_output);
    curl_easy_perform(curl_handle);
    curl_easy_cleanup(curl_handle);
    if (curl_output.find("C_ico cpp11warning") != std::string::npos || curl_output.find("404 Page Not Found") != std::string::npos) {
        return false;
    }
    return true;

}

int main(int ac, char **av) {
    if (ac > 1) {
        for (int i = 1; i < ac; ++i) {
            bool res = is_function_available_in_cpp98(std::string(av[i]));
            cout << av[i];
            if (res) {
                 cout << ": is available in c++98\n";
            } else {
                cout << ": is not available in c++98\n";
            }
        }
    } else {
        cout << "USAGE: ./cpp98_function_checker function_name" << "\n";
    }
}
