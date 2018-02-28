//267937 Haifeng Xu haifeng.xu@student.tut.fi
#include "splitter.hpp"
#include "boost/regex.hpp"

Splitter::Splitter(const string& string_to_split) {
    string_to_split_ = string_to_split;
    command_.clear();
    level_or_runnum_.clear();
    chore_.clear();
}

//Clear the splitted string
void Splitter::set_string_to_split(const string& string_to_split) {
    string_to_split_ = string_to_split;
    command_.clear();
    level_or_runnum_.clear();
    chore_.clear();
}

//Split the string
void Splitter::split() {
    std::string::size_type pos;
    //string_to_split_+=pattern;
    std::string str = string_to_split_;
    //std::string pattern = "thisisforextend";
    //str+=pattern;
    unsigned int i=0;
    std::string s1 = "";
    std::string s2 = "";

    pos=str.find(" ",i);
    command_=str.substr(i,pos-i);
    s1=str.substr(i+pos+1, str.size()-pos);

    i=0;
    pos=s1.find(" ", i);
    if(pos > s1.size()){
        if(s1 == str){
            s1 = "";
            return;
        }
        level_or_runnum_=s1;
        return;
    }else{
        level_or_runnum_=s1.substr(i,pos-i);
        s2=s1.substr(i+pos+1, s1.size()-pos);
    }

    chore_=s2;
}


