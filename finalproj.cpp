#include "url lookup code.hpp"
#include "haversine.hpp"
#include<fstream>

nlohmann::json openfile(const std::string& location, const std::string& filename){
    fetchCoordinates(location, filename);
    
    nlohmann::json jsonObject;

    std::ifstream inputfile(filename+".json");

    if(!inputfile.is_open()){   
        std::cerr << "Error opening file" << std::endl; 
        throw std::runtime_error("File could not be opened");
    }

    try{
        inputfile >> jsonObject;
    } catch(const nlohmann::json::parse_error& e){
        std::cerr << "Parse error:" << e.what() << std::endl;
        throw;
    }

    inputfile.close();
    return jsonObject;
}

int main(){
    //get the start and end locations
    std::string  loc1, loc2;

    std::cout << "Enter location 1: ";
    std::cin >> loc1;
    std::cout << std::endl << "Enter location 2: ";
    std::cin >> loc2;
    
    nlohmann::json startLocation = openfile(loc1, "loc1");
    nlohmann::json endLocation = openfile(loc2, "loc2");
    double startLat, startLong, endLat, endLong;
    
    std::cout << "Parsed Json data: " << startLocation.dump(4) << std::endl;
    std::cout << "Parsed Json data: " << endLocation.dump(4) << std::endl;

    //get start and end coordinates
    for(auto& element: startLocation.items()){
        if(element.key() == "lat")    double startLat = std::stod(element.key());

        if(element.key() == "lon")    double startLong = std::stod(element.key());
    }

    for(auto& element: endLocation.items()){
        if(element.key() == "lat")    endLat = std::stod(element.key());
        if(element.key() == "lon")    endLong = std::stod(element.key());
    }
    //calculate direct distance for drone
    double distance = haversine(startLat, startLong, endLat, endLong);

    std::cout << "Direct distance between two points is:" << distance << " km" << std::endl;

    return 0;
}