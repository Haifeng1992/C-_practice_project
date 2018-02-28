//267937 Haifeng Xu haifeng.xu@student.tut.fi
#ifndef SPLITTER_HPP
#define SPLITTER_HPP
#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <boost/regex.hpp>

using namespace std;

const unsigned int SPLIT_ERROR = 0;

class Splitter {
public:
    Splitter(const string& string_to_split = "");
    void set_string_to_split(const string& string_to_split);
    void split();
    string command_;
    string level_or_runnum_;
    string chore_;

private:
    string string_to_split_ = "";

};
#endif // SPLITTER_HPP
