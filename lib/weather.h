#pragma once
#include <iostream>
#include <nlohmann/json.hpp>
#include <cpr/cpr.h>

struct City {
  std::string name;
  std::string country;
  double latitude;
  double longitude;
  nlohmann::json json_data;

  void GetCityInfo(const std::string& name, const std::string& key);

  void GetWeatherInfo();

};


