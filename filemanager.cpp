#include <iostream>
#include "filemanager.h"
using namespace std;

FileManager::FileManager(string f) {
    filename = f;
}

bool FileManager::save(const UserProfile& user, const ReadingLog& log) const {
    cout << "Not implemented yet" << endl;
    return false;
}

bool FileManager::load(UserProfile& user, ReadingLog& log) const {
    cout << "Not implemented yet" << endl;
    return false;
}
