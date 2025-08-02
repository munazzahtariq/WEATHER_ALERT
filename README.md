# CEP_CEW

# 🌦️ Weather Alert System (C Project)

A simple modular weather alert system written in C. This project demonstrates how to simulate and process weather data (like temperature or humidity) and trigger alerts based on defined conditions. All components are written in clean, separated C files using header files for modularity. For this project i used docker and not ubuntu software.

---

##  Project Structure

```
weather-alert/
├── main.c         # Entry point for the program
├── alert.c        # Contains alert-triggering logic
├── alert.h        # Header for alert.c
├── data.c         # Simulated weather data input/processing
├── data.h         # Header for data.c
├── .gitignore     # Files ignored by Git (like .exe outputs)
├── README.md      # Project documentation
└── weather_alert_full_project.zip  # (Optional) Full zip download
```

---

##  How to Compile

Use the following command in your terminal to compile all files:

```bash
gcc main.c alert.c data.c -o weather-app
```

---

##  How to Run

After compilation:

```bash
./weather-app
```

This will simulate weather data and display alerts based on defined logic.

---

##  Features

- Modular C code using multiple `.c` and `.h` files  
- Weather alert logic separated for clarity  
- Easily extensible for more alert types or real input sources

---
## Docker Commands
docker build -t weather-app (Build the docker image)
docker run --rm weather-app (Run the container)
