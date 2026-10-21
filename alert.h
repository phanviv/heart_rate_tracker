#pragma once
#include "readinglog.h"

class AlertSystem {
private:
    int highLimit;
    int lowLimit;
public:
    AlertSystem();
    void setLimits(int low, int high);
    bool isAlert(Reading r) const;
    void printAlerts(const ReadingLog& log) const;
};
