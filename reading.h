#ifndef READING_H
#define READING_H


class Reading
{

private:
    long timestamp;
    int bpm;

public:
    long getTimestamp();
    int getBPM();
    void print();

}
#endif 