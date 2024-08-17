#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include "Weather.h"
#include "ncurses.h"


const int kHoursInDay = 24;
const int kQuaterOfDay = 6;
const int kMaxForecastDays = 16;

void UpdateWeatherData(std::vector<City>& cities);

void PrintTable(const City& city, size_t& current_day_index);

void CreateForecast(std::vector<City>& cities, const nlohmann::json& config);

