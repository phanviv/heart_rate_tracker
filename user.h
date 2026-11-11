#pragma once //only read this file once

#include <iostream>
#include <string>
#include <vector>
#include "settings.h" //Setting Class
#include "workout.h" //Workout Class

using namespace std;

class UserProfile
{
    private:
        string name;
        int age;
        int restingHR;
        Settings settings; //user's own settings
        vector<Workout> workouts; //list of all user's workouts

    public:

        UserProfile() //constructor that runs when a profile is created
        {
            name = ""; //starts with an empty name
            age = 0; //starts with an age of 0
            restingHR = 0; //starts with a resting heart rate of 0
        }

        void setProfile(string newName, int newAge, int newRestingHR) //sets all three values at once, void gives nothing back
        {
            name = newName; //copy new name into the class
            age = newAge; //copy new age into the class
            restingHR = newRestingHR; //copy new resting heart rate into the class
        }

        void setName(string newName) //sets only the name (for renaming)
        {
            name = newName; //copy name into class
        }

        string getName() //returns the name of the user
        {
            return name;
        }

        int getAge() //returns the age of the user
        {
            return age;
        }

        int getRestingHR() //returns the resting heart rate of the user
        {
            return restingHR;
        }

        Settings getSettings() //returns the settings of the user
        {
            return settings;
        }

        void setSettings(Settings newSettings) //sets the settings of the user
        {
            settings = newSettings; //copy the new setting into the class
        }

        int getMaxHR() //returns the max heart rate of the user
        {
            return 220 - age; //formula for max heart rate
        }

        int getZoneNumber(int bpm) //takes a heart rate and gives back its zone
        {
            int maxHR = getMaxHR(); //get the max heart rate of the user
            double percent = bpm * 100.0 / maxHR; //calculate the percentage of the max heart rate

            if (percent < 50)
            {
                return 0; //below zone 1
            }
            else if (percent < 60)
            {
                return 1; //zone 1
            }
            else if (percent < 70)
            {
                return 2; //zone 2
            }
            else if (percent < 80)
            {
                return 3; //zone 3
            }
            else if (percent < 90)
            {
                return 4; //zone 4
            }
            else if (percent <= 100)
            {
                return 5; //zone 5
            }
            return 6; //above zone 5
        }

        string getZoneName(int zone) //takes zone, gives back its name
        {
            if (zone == 0)
            {
                return "Below Zone 1";
            }
            else if (zone == 1)
            {
                return "Warm-up/Recovery Zone";
            }
            else if (zone == 2)
            {
                return "Fat-Burning Zone";
            }
            else if (zone == 3)
            {
                return "Aerobic Zone";
            }
            else if (zone == 4)
            {
                return "Anaerobic Zone";
            }
            else if (zone == 5)
            {
                return "Red-Line Zone";
            }
            else if (zone == 6)
            {
                return "Above Max";
            }
            return "Unknown Zone";
        }

        void addWorkout(Workout w) //adds a workout to the user's list of workouts
        {
            workouts.push_back(w); //add the new workout to the end of the vector
        }

        vector<Workout> getWorkouts() //returns the list of workouts
        {
            return workouts; //return the vector of workouts
        }

        Workout getLatestWorkout() //returns the newest workout, call hasWorkouts() first so the list is not empty
        {
            return workouts[workouts.size()-1]; //return the last workout in the vector
        }

        bool hasWorkouts() //returns true if the user has any workouts, false if not
        {
            return workouts.size() > 0; //return true if the vector is not empty, false if it is
        }

        void print() //shows the profile on the screen
        {
            cout << "Name: " << name << endl;
            cout << "Age: " << age << endl;
            cout << "Resting Heart Rate: " << restingHR << endl;
            cout << "Max Heart Rate: " << getMaxHR() << endl;
            cout << "Workouts: " << workouts.size() << endl; //how many workouts there are
        }
};

