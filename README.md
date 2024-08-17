# Прогноз погоды

## Описание
Консольное приложение, отображающее прогноз погоды для выбранных городов. Данные о погоде загружаются с сайта [Open-Meteo](https://open-meteo.com/en/docs#latitude=59.94&longitude=30.31&hourly=temperature_2m&forecast_days=16).

Список городов, частота обновления, количество дней прогноза задаются в конфигурационном файле формата json. Также в нём необходимо указать свой ключ API с сайта [Api-Ninjas](https://api-ninjas.com/api/city).

С помощью клавиш "n" и "p" можно переключаться между городами, с помощью "+" и "-" менять количество отображаемых дней. Завершается работа приложения нажатием Esc.

В качестве библиотеки для HTTP-запросов используется [C++ Requests](https://github.com/libcpr/cpr), для работы с json данными - [nlohman json](https://github.com/nlohmann/json?ysclid=lzxexc8e9v933134807),
для визуализации - [ncurses](https://habr.com/ru/articles/778040/).


    
