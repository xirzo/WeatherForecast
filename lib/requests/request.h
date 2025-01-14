#ifndef REQUEST_H
#define REQUEST_H

#include <string>

void get_weather_by_lat_lon();

void get_lat_lon_by_city_name(const std::string& city_name);

#endif  // !REQUEST_H
