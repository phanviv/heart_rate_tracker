# heart_rate_tracker

This progam simulates a wearable heart rate tracker. The system allows users to manage user profiles, log active workouts, simulate heart rate sensor inputs, track heart rate zones, and evaluate health alerts.

Prerequisites:
Before compiling and running this project, ensure you have the following installed on your system:
• C++ Compiler: GCC (g++) supporting C++11 or higher.
• Build System (Optional): make utility for automated compilation.
Build Instructions
This project consists of multiple implementation files that need to be compiled together.
Option 1: Compiling via Terminal Directly
Navigate to the repository directory and execute the following compilation command:
g++ -std=c++11 main.cpp tasks_data.cpp tasks_analysis.cpp readings.cpp User.cpp Sensor.cpp Filemanager.cpp readingl.cpp alert.cpp -o hr_tracker

Option 2: Compiling via Makefile (If available)
If a Makefile is present in the repository, simply run:
make
Run Instructions
Once the project is successfully compiled, execute the binary executable generated in your terminal:
./hr_tracker

Application Controls
Upon launching, the interactive text-based console menu will guide you through the following capabilities:

1. Create/Select Profile: Configure user demographics like Name and Age.
2. Start Workout: Log active sessions and measure activity metrics.
3. View Latest Readings: Review recently polled heartbeats.
4. Save Data: Serialize active logs to a local data file via FileManager.
5. Load Data: Pull historical user statistics from disk storage.
6. View Full History: Access complete recorded logs over time.
7. Statistics: Display minimum, maximum, and average BPM readings.
8. Heart Rate Zones (HRR): Categorize activity metrics against target zones.
9. Alerts: Assess occurrences of critical spikes over safety thresholds.
10. Exit: quit and close the application environment.
During simulated sensor polling routines, input q to stop data collection.
