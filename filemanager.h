#pragma once
#include <string>
#include "user.h"
#include "readinglog.h"
using namespace std;

class FileManager {
private:
    string filename;
public:
    FileManager(string f = "heart_data.txt");
    bool save(const UserProfile& user, const ReadingLog& log) const;
    bool load(UserProfile& user, ReadingLog& log) const;
};
