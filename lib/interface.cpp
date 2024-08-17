#include "Interface.h"


void UpdateWeatherData(std::vector<City>& cities) {
  for (auto& city : cities) {
	city.GetWeatherInfo();
  }
}

void PrintTable(const City& city, size_t& current_day_index) {
  auto weather_data = city.json_data;
  std::string city_name = city.name;

  printw("City: %s\n", city_name.c_str());
  printw("Date: %s\n", weather_data["hourly"]["time"][current_day_index * kHoursInDay].get<std::string>().substr(0,10).c_str());
  printw("%-18s%-25s%-35s%-25s%-30s\n", "Time Period", "Temperature (°C)", "Precipitation Probability (%)",
		 "Wind Speed (km/h)", "Cloud Cover (%)");

  std::vector<std::pair<int, int>> time_periods = {
	  {0, 6},   // Night
	  {6, 12},  // Morning
	  {12, 18}, // Arternoon
	  {18, 24}  // Evening
  };

  for (size_t i = 0; i < time_periods.size(); ++i) {
	int start_hour = time_periods[i].first;
	int end_hour = time_periods[i].second;
	double avg_temperature = 0.0;
	double avg_precipitation = 0.0;
	double avg_wind_speed = 0.0;
	double avg_cloud_cover = 0.0;

	for (size_t j = kHoursInDay * current_day_index; j < kHoursInDay * (current_day_index + 1); ++j) {
	  int hour = std::stoi(weather_data["hourly"]["time"][j].get<std::string>().substr(11, 2));
	  if (hour >= start_hour && hour < end_hour) {
		avg_temperature += weather_data["hourly"]["temperature_2m"][j].get<double>();
		avg_precipitation += weather_data["hourly"]["precipitation_probability"][j].get<double>();
		avg_wind_speed += weather_data["hourly"]["wind_speed_10m"][j].get<double>();
		avg_cloud_cover += weather_data["hourly"]["cloud_cover"][j].get<double>();
	  }
	}

	avg_temperature /= kQuaterOfDay;
	avg_precipitation /= kQuaterOfDay;
	avg_wind_speed /= kQuaterOfDay;
	avg_cloud_cover /= kQuaterOfDay;

	if (i == 0) {
	  attron(COLOR_PAIR(1));
	} else if (i == 1) {
	  attron(COLOR_PAIR(2));
	} else if (i == 2) {
	  attron(COLOR_PAIR(3));
	} else {
	  attron(COLOR_PAIR(4));
	}

	printw("%-18s%-25.1f%-35.1f%-25.1f%-30.1f\n",
		   (i == 0) ? "Night" : (i == 1) ? "Morning" : (i == 2) ? "Afternoon" : "Evening",
		   avg_temperature, avg_precipitation, avg_wind_speed, avg_cloud_cover);

	attroff(COLOR_PAIR(i + 1));
  }
  refresh();
}

void CreateForecast(std::vector<City>& cities, const nlohmann::json& config) {
  size_t city_index = 0;
  size_t current_day_index = config["forecast_days"];

  initscr();
  start_color();
  init_pair(1, COLOR_BLUE, COLOR_WHITE);
  init_pair(2, COLOR_YELLOW, COLOR_WHITE);
  init_pair(3, COLOR_GREEN, COLOR_WHITE);
  init_pair(4, COLOR_MAGENTA, COLOR_WHITE);
  noecho();
  curs_set(0);

  for (size_t i = 0; i < current_day_index; ++i) {
	PrintTable(cities[city_index], i);
  }

  auto last_update_time = std::chrono::steady_clock::now();
  while (true) {
	auto current_time = std::chrono::steady_clock::now();
	if (std::chrono::duration_cast<std::chrono::seconds>(current_time - last_update_time).count() >= config["update_frequency"]) {
	  UpdateWeatherData(cities);
	  last_update_time = current_time;
	  current_day_index = config["forecast_days"];
	  clear();
	  for (size_t i = 0; i < current_day_index; ++i) {
		PrintTable(cities[city_index], i);
	  }
	}
	char option = getch();
	switch (option) {
	  case '+':
		if (current_day_index < kMaxForecastDays){
		  PrintTable(cities[city_index], current_day_index);
		  current_day_index++;
		} else {
		  std::cerr<<"maximum number days of forecast is 16, please try again ";
		}
		break;

	  case 'n':
		(city_index < cities.size() - 1) ? city_index++ : city_index = 0;
		current_day_index = config["forecast_days"];
		clear();
		for (size_t i = 0; i < current_day_index; ++i) {
		  PrintTable(cities[city_index], i);
		}
		break;

	  case 'p':
		(city_index > 0) ? city_index-- : city_index = cities.size() - 1;
		current_day_index = config["forecast_days"];
		clear();
		for (size_t i = 0; i < current_day_index; ++i) {
		  PrintTable(cities[city_index], i);
		}
		break;

	  case '-':
		if (current_day_index > 0) {
		  clear();
		  current_day_index--;
		  for(size_t i = 0; i < current_day_index; ++i){
			PrintTable(cities[city_index], i);
		  }
		}
		break;

	  case 27:
		endwin();
		return;
	}
  }
}

