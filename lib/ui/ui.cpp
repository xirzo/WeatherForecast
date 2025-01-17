#include "ui.h"

ForecastComponent::ForecastComponent(Forecast& forecast, int& selected_day,
                                     std::function<void()> exit_callback)
    : forecast_(forecast), selected_day_(selected_day), exit_callback_(exit_callback) {}

bool ForecastComponent::OnEvent(ftxui::Event event) {
    if (event == ExitKey) {
        exit_callback_();
        return true;
    }

    if (event == NextKey) {
        if (selected_day_ < static_cast<int>(forecast_.days.size()) - 1) {
            selected_day_++;
            return true;
        }
    }

    if (event == PreviousKey) {
        selected_day_--;
        return true;
    }
    return false;
}

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

    int day_count = static_cast<int>(forecast.days.size());
    if (selected_day < 0) selected_day = 0;
    if (selected_day >= day_count) selected_day = day_count - 1;

    Element selected_day_element = CreateDayUI(forecast.days[selected_day]);

    Element navigation_hints = hbox({
        text("Previous Day (p)") |
            color(selected_day > 0 ? Color::Green : Color::GrayDark),
        filler(),
        text("Next Day (n)") |
            color(selected_day < day_count - 1 ? Color::Green : Color::GrayDark),
    });

    Component slider =
        Container::Horizontal({Slider("", &selected_day, 0, day_count - 1)});

    Element slider_section =
        vbox({text("Select Day") | center,
              slider->Render() | size(WIDTH, GREATER_THAN, 50) | border | yframe});

    Element document =
        vbox({cityTitle | border, text("UTC: 2025-01-17 20:12:07") | dim | center,
              separatorLight(), selected_day_element | flex, separator(),
              navigation_hints | border, separator(), slider_section}) |
        flex | border;

    return document;
}
