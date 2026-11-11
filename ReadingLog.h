#ifndef READING_LOG_H
#define READING_LOG_H
#include <vector>
#include "reading.h"
using namespace std;

class ReadingLog
{
private:
	vector<Reading> readings;

public:
	void addReading(Reading reading);
	void clear();
	void print();
	void printLast(int n);

	Reading get(int index) const;
	int size() const;
	int minBpm() const;
	int maxBpm() const;
	int avgBpm() const;
	int avgLast(int n) const;
	int avgSince(long seconds) const;
};
#endif