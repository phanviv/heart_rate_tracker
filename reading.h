#pragma once

class Reading {
private:
    int timeSec;
    int bpm;
    int activity;   // 1 = Rest, 2 = Walk, 3 = Run
public:
    Reading(int t = 0, int b = 0, int a = 1);
    int getTime() const;
    int getBpm() const;
    int getActivity() const;
    void print() const;
};
