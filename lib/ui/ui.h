#ifndef UI_H
#define UI_H

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <functional>

#include "forecast.h"
#include "weather_day.h"
#include "weather_period.h"

using namespace ftxui;

Element CreatePeriodUI(const WeatherPeriod& period, const std::string& label);
Element CreateDayUI(const WeatherDay& day);
Element CreateForecastUI(const Forecast& forecast, int& selected_day);

class ForecastComponent : public ComponentBase {
public:
    ForecastComponent(Forecast& forecast, int& selected_day,
                      std::function<void()> exit_callback);

    bool OnEvent(ftxui::Event event) override;
    Element Render() override;

private:
    const Event ExitKey = Event::Escape;
    const Event NextKey = Event::n;
    std::function<void()> exit_callback_;
    const Event PreviousKey = Event::p;
    Forecast& forecast_;
    int& selected_day_;
};

#endif  // UI_H
