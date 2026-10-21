#pragma once
#include "reading.h"

const int MAX_READINGS = 1000;

class ReadingLog {
private:
    Reading readings[MAX_READINGS];
    int count;
public:
    ReadingLog();
    bool add(Reading r);
    int size() const;
    Reading get(int index) const;
    int minBpm() const;
    int maxBpm() const;
    double avgBpm() const;
    void print() const;
    void printLast(int n) const;
    void clear();
};
