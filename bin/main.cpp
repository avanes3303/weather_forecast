#include <iostream>
#include <fstream>
#include "../lib/Weather.h"
#include "../lib/Interface.h"



int main() {
  std::ifstream file("..//lib//config.json");
  if (!file.is_open()) {
	std::cerr << "Failed to open config.json" << std::endl;
  }
  nlohmann::json config = nlohmann::json::parse(file);
  std::vector<City> cities;
  for (const auto city : config["cities"]) {
	City new_city;
	try {
	  new_city.GetCityInfo(city, config["key"]);
	  new_city.GetWeatherInfo();
	}  catch (const std::exception& e) {
	  std::cerr << e.what() << std::endl;
	  return 1;
	}
	cities.push_back(new_city);
  }
  CreateForecast(cities, config);
  return 0;
}
