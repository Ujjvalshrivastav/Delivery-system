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
    
    nlohmann::json startLocation = openfile("Thane fort, Thane", "loc1");
    nlohmann::json endLocation = openfile("Sitabuldi Fort, Nagpur", "loc2");
    double startLat, startLong, endLat, endLong;
    
    //std::cout << "Parsed Json data: " << startLocation.dump(4) << std::endl;
    //std::cout << "Parsed Json data: " << endLocation.dump(4) << std::endl;

    //get start and end coordinates
    std::string lat1 = startLocation[0]["lat"];
    std::string long1 = startLocation[0]["lon"];

    std::string lat2 = endLocation[0]["lat"];
    std::string long2 = endLocation[0]["lon"];

    startLat = std::stod(lat1);
    startLong = std::stod(long1);
    endLat = std::stod(lat2);
    endLong = std::stod(long2);
    
    //calculate direct distance for drone
    double distance = haversine(startLat, startLong, endLat, endLong);

    std::cout << "Direct distance between two points is:" << distance << " km" << std::endl;

    return 0;
}
