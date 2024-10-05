#include<cmath>
const double R = 6371.0;

const double PI = 3.14159265358979323846;

double deg2rad(double deg){
    return deg * PI/ 180.0;
}

double haversine(double lat1, double long1, double lat2, double long2){
    double dLat = deg2rad(lat2 - lat1);
    double dLong = deg2rad(long2 - long1);

    lat1 = deg2rad(lat1);
    lat2 = deg2rad(lat2);

    double a = sin(dLat/2) * sin(dLat/2) + cos(lat1) * cos(lat2) * sin(dLong/2) * sin(dLong/2);
    double c = 2 * atan2(sqrt(a), sqrt(1-a));

    return R * c;
}
