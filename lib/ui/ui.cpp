#include "ui.h"

#include <ftxui/dom/node.hpp>

ForecastComponent::ForecastComponent(Forecast& forecast, int& selected_day,
                                     std::function<void()> exit_callback)
    : forecast_(forecast), selected_day_(selected_day), exit_callback_(exit_callback) {}

Element ForecastComponent::Render() {
    return CreateForecastUI(forecast_, selected_day_);
}

Element CreatePeriodUI(const WeatherPeriod& period, const std::string& label) {
    return vbox(
               {text(label) | bold | center, separator(),
                hbox(
                    {text("Temp: " + std::to_string(period.temperature) + "° C") | flex}),
                hbox({text("Humidity: " + std::to_string(period.humidity) + "%") | flex}),
                hbox({text("Rain: " + std::to_string(period.rain) + " mm") | flex}),
                hbox({text("Cloud Cover: " + std::to_string(period.cloud_cover) + "%") |
                      flex}),
                hbox({text("Wind: " + std::to_string(period.wind_speed) + " m/s") |
                      flex})}) |
           flex | border;
}

Element CreateDayUI(const WeatherDay& day) {
    Element date_label = text("Date: " + day.date) | bold | center;

    Element day_periods = hbox({
                              CreatePeriodUI(day.morning, "Morning") | flex,
                              CreatePeriodUI(day.afternoon, "Afternoon") | flex,
                              CreatePeriodUI(day.evening, "Evening") | flex,
                              CreatePeriodUI(day.night, "Night") | flex,
                          }) |
                          flex;

    return vbox({date_label, separator(), day_periods}) | border | flex;
}

Element CreateForecastUI(const Forecast& forecast, int& selected_day) {
    Element cityTitle =
        hbox({text("📍 ") | bold, text(forecast.city_name) | dim}) | center;

    int32_t day_count = static_cast<int32_t>(forecast.days.size());

    std::vector<Element> days;

    for (size_t i = 0; i < forecast.days.size(); ++i) {
        days.push_back(CreateDayUI(forecast.days[i]));
    }

    Element selected_day_elements = vbox(days) | vscroll_indicator | yframe | yflex;

    Element document = vbox({cityTitle | border, separatorLight(),
                             selected_day_elements | flex, separator()}) |
                       flex | border;

    return document;
}
