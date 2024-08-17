#include "Weather.h"

void City::GetCityInfo(const std::string& name, const std::string& key) {
  cpr::Response response = cpr::Get(cpr::Url{"https://api.api-ninjas.com/v1/city"},
									cpr::Header{{"X-Api-Key", key}},
									cpr::Parameters{{"name", name}});
  if (response.status_code == 200) {
	nlohmann::json response_data = nlohmann::json::parse(response.text);
	this->name = response_data[0]["name"];
	this->country = response_data[0]["country"];
	this->latitude = response_data[0]["latitude"];
	this->longitude = response_data[0]["longitude"];
  } else {
	throw std::runtime_error("Failed to get information of city");
  }
}

void City::GetWeatherInfo() {
  cpr::Response response = cpr::Get(cpr::Url{"https://api.open-meteo.com/v1/forecast"},
									cpr::Parameters{{"latitude", std::to_string(this->latitude)},
													{"longitude", std::to_string(this->longitude)},
													{"hourly", "temperature_2m,precipitation_probability,wind_speed_10m,cloud_cover"},
													{"timezone", "auto"},
													{"forecast_days", "16"}});
  if (response.status_code == 200) {
	this->json_data = nlohmann::json::parse(response.text);
  } else {
	throw std::runtime_error("Failed to get weather data");
  }
}

