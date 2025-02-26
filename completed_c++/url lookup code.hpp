#include <iostream>
#include <string>
#include <curl/curl.h>
#include<fstream>
#include<nlohmann/json.hpp>



// Function to write the response from the API into a string
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int fetchCoordinates(const std::string& location, const std::string& filename){
    CURL* curl;
    CURLcode res;
    std::string readBuffer, escapedLocation="";
    
    curl = curl_easy_init();
    
    for(char c: location){
        if(!isalpha(c)) c = '+';
        escapedLocation += c;
    }
    
    // Construct the Nominatim reverse geocoding API URL
    std::string nominatimUrl = "https://nominatim.openstreetmap.org/search?q=" + escapedLocation + "&format=json";
    std::cout << nominatimUrl << std::endl;
    
    if(curl){
        // Set the URL for the Nominatim API query
        curl_easy_setopt(curl, CURLOPT_URL, nominatimUrl.c_str());

        // Define the callback function to handle the data
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

        // Pass the string to store the data from the web query
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        // Set the User-Agent (Nominatim requires a User-Agent header)
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0");

        // Include certificate to perform cURL
        curl_easy_setopt(curl, CURLOPT_CAINFO, "C:\\Program Files\\OpenSSL-Win64\\bin\\PEM\\cacert.pem");

        // Perform the request
        res = curl_easy_perform(curl);

        // Check for errors
        if(res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } 
        else {
            auto jsonResponse = nlohmann::json::parse(readBuffer);

            std::ofstream outputfile(filename+".json");
            
            if (outputfile.is_open()){
                    outputfile << jsonResponse.dump(4);
                std::cout << "Response written to:" << filename << std::endl;
                outputfile.close();
            }
            else
                std::cerr << "Error!" << std::endl;
            
        }
        // Cleanup
        curl_easy_cleanup(curl);
    }   
    return 0;
}
