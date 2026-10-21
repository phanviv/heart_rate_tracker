#include <iostream>
#include <string>
#include "tasks.h"
#include "filemanager.h"
using namespace std;

// Reads a whole number between low and high, asking again if the input is bad
int readNumber(string prompt, int low, int high)
{
    int value;
    while (true)
    {
        cout << prompt;
        if (cin >> value && value >= low && value <= high)
        {
            cin.ignore(1000, '\n');
            return value;
        }
        cout << "Please enter a number from " << low << " to " << high << ".\n";
        cin.clear();
        cin.ignore(1000, '\n');
    }
}

void taskCreateProfile(UserProfile &user)
{
    string name;
    cout << "Name: ";
    getline(cin, name);
    int age = readNumber("Age: ", 1, 120);

    int restingHR = 0; // TODO: Choose based on user age

    user.setProfile(name, age, restingHR);
    cout << "\nProfile saved:\n";
    user.print();
}

void taskRunWorkout(HeartRateSensor &sensor, ReadingLog &log)
{
    string activity;
    cout << "Enter activity name: ";
    cin >> activity;

    sensor.start(activity);
    cout << "Sensor started. Press Enter for each new reading, or type q then Enter to stop.\n";

    string input;
    while (sensor.isRunning())
    {
        getline(cin, input);
        if (input == "q" || input == "Q")
        {
            sensor.stop();
        }
        else
        {
            Reading r = sensor.takeReading();
            r.print();
        }
    }

    // Copy this workout's readings into the main log
    const ReadingLog &workout = sensor.getReadings();
    for (int i = 0; i < workout.size(); i++)
    {
        log.add(workout.get(i));
    }

    cout << "\nWorkout finished. " << workout.size() << " reading(s) recorded.\n";
    if (workout.size() > 0)
    {
        cout << "Average BPM: " << sensor.getAverageBPM() << "\n";
        cout << "Average of last 30 seconds: " << sensor.getRecentAverageBPMFrom(30) << "\n";
        cout << "Average of last 5 readings: " << sensor.getLastAverageBPM(5) << "\n";
    }
}

void taskViewLatest(const ReadingLog &log)
{
    cout << "Latest readings:\n";
    log.printLast(5);
}

void taskSave(const UserProfile &user, const ReadingLog &log)
{
    FileManager fm;
    if (fm.save(user, log))
        cout << "Data saved to heart_data.txt\n";
    else
        cout << "Could not save data.\n";
}

void taskLoad(UserProfile &user, ReadingLog &log)
{
    FileManager fm;
    if (fm.load(user, log))
    {
        cout << "Data loaded. " << log.size() << " reading(s) for " << user.getName() << ".\n";
    }
    else
    {
        cout << "Could not load data (no saved file yet?).\n";
    }
}
