# 🌦️ WeatherForecast

Welcome to the **WeatherForecast** repository! This project is designed to provide weather forecasts with terminal UI.

## 📚 Table of Contents

- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)

## 🌟 Features

- 🌍 Real-time weather data from various global sources
- 📈 Forecasts for multiple locations
- ⏱️ Hourly, daily, and weekly weather predictions
- 📊 Visual representation of weather data

## 🛠️ Installation

To install and run the WeatherForecast project, follow these steps:

1. **Clone the repository:**

    ```bash
    git clone https://github.com/xirzo/WeatherForecast.git
    cd WeatherForecast
    ```

2. **Build the project using CMake:**

    ```bash
    mkdir build
    cd build
    cmake ..
    cmake --build .
    ```

## 🚀 Usage

After building the project, you can run the WeatherForecast application with:

```bash
./WeatherForecast
```

### Launching

1. **Create `config.json` file in the directory that you`re gonna use the program:**

    ```json
    {
      "cities": [
        "Saint Petersburg",
        "Moscow"
      ],
      "frequency": 5,
      "days": 7,
      "API key" : "XXXXXXXXXXXXXXXXXX"
    }
    ```

    > **Note:** The API key should be obtained from [Api-Ninjas](https://api-ninjas.com/).

2. **Run the application with the configuration file:**

    ```bash
    ./WeatherForecast
    ```

### Navigation

- Press `n` to choose the next city.
- Press `p` to choose the previous city.

This will launch the WeatherForecast application with the specified cities, update frequency, and forecast days.

### Data Sources

- 🌐 **Open-Meteo** for weather forecasts: [Open-Meteo Documentation](https://open-meteo.com/en/docs#latitude=59.94&longitude=30.31&hourly=temperature_2m&forecast_days=16)
- 🌐 **Api-Ninjas** for determining coordinates by city name: [Api-Ninjas Documentation](https://api-ninjas.com/api/city)
