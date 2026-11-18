#include "ReadingLog.h"
#include <iostream>
#include <algorithm>

using namespace std;

// Adds a new reading to the log
void ReadingLog::addReading(Reading reading) {
    readings.push_back(reading);
}

// Clears all readings from the log
void ReadingLog::clear() {
    readings.clear();
}

// Prints all readings in the log (non-const to match header)
void ReadingLog::print() {
    if (readings.empty()) {
        cout << "No readings in the log." << endl;
        return;
    }
    for (size_t i = 0; i < readings.size(); ++i) {
        cout << "[" << i << "] ";
        readings[i].print();
    }
}

// Prints the last n readings in the log (non-const to match header)
void ReadingLog::printLast(int n) {
    if (readings.empty()) {
        cout << "No readings in the log." << endl;
        return;
    }
    
    int start = max(0, static_cast<int>(readings.size()) - n);
    for (size_t i = start; i < readings.size(); ++i) {
        cout << "[" << i << "] ";
        readings[i].print();
    }
}

// Gets a specific reading by index
Reading ReadingLog::get(int index) const {
    if (index >= 0 && index < static_cast<int>(readings.size())) {
        return readings[index];
    }
    return Reading(); // Returns a default Reading if out of bounds
}

// Returns the full vector of readings
vector<Reading> ReadingLog::getReadings() const {
    return readings;
}

// Returns the total number of readings
int ReadingLog::size() const {
    return static_cast<int>(readings.size());
}

// Returns the minimum BPM recorded, or 0 if empty
int ReadingLog::minBpm() const {
    if (readings.empty()) return 0;
    
    int minVal = readings[0].getBPM();
    for (const auto& r : readings) {
        if (r.getBPM() < minVal) {
            minVal = r.getBPM();
        }
    }
    return minVal;
}

// Returns the maximum BPM recorded, or 0 if empty
int ReadingLog::maxBpm() const {
    if (readings.empty()) return 0;
    
    int maxVal = readings[0].getBPM();
    for (const auto& r : readings) {
        if (r.getBPM() > maxVal) {
            maxVal = r.getBPM();
        }
    }
    return maxVal;
}

// Returns the overall average BPM, or 0 if empty
int ReadingLog::avgBpm() const {
    if (readings.empty()) return 0;
    
    long long sum = 0;
    for (const auto& r : readings) {
        sum += r.getBPM();
    }
    return static_cast<int>(sum / readings.size());
}

// Returns the average BPM of the last n readings
int ReadingLog::avgLast(int n) const {
    if (readings.empty() || n <= 0) return 0;
    
    int count = min(n, static_cast<int>(readings.size()));
    int start = readings.size() - count;
    
    long long sum = 0;
    for (int i = start; i < static_cast<int>(readings.size()); ++i) {
        sum += readings[i].getBPM();
    }
    return static_cast<int>(sum / count);
}

// Returns the average BPM of readings taken within the last specified number of seconds
int ReadingLog::avgSince(long seconds) const {
    if (readings.empty() || seconds <= 0) return 0;
    
    time_t latestTime = readings.back().getTimestamp();
    time_t thresholdTime = latestTime - seconds;
    
    long long sum = 0;
    int count = 0;
    
    for (auto it = readings.rbegin(); it != readings.rend(); ++it) {
        if (it->getTimestamp() >= thresholdTime) {
            sum += it->getBPM();
            count++;
        } else {
            break; 
        }
    }
    
    if (count == 0) return 0;
    return static_cast<int>(sum / count);
}
