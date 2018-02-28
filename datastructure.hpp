//267937 Haifeng Xu haifeng.xu@student.tut.fi
#ifndef DATASTRUCTURE_HPP
#define DATASTRUCTURE_HPP
#include <iostream>
#include <string>

using namespace std;

const int NO_ERROR = 200;

class PiorityChores
{
public:
    PiorityChores();
    ~PiorityChores();
    //from start to end, iterate it and delete everything
    void destroy();
    //delete previous stuff and set the piority number again
    //"amount_piority_levels" is the amount of piority level given by the user
    void initialize(int amount_piority_levels);
    //add a chore, if the piority doesn't exist, create a new one and lined it with others
    //"piority_level" is to know which level this chore would be added.
    //"chore_name" is the name of chore
    void add_chore(int piority_level, string chore_name);
    //iterate all list and cout them
    void print();
    //cout 1 and erase(1)
    void next_chore();
    //erase and re-value all the running number
    void erase_chore(int erase_this_num);
    //return 2 important numbers to main function
    int return_amount_of_piority();
    int return_amount_of_all_chores();

private:
    struct Chore_list {
        int piority_level;
        int running_num;
        string chore;
        Chore_list* next_chore;
    };

    struct Piority_list {
        int piority_level;
        Chore_list* chore_list_start;
        Chore_list* chore_list_end;
        Piority_list* next_piority;
    };
    Piority_list* piority_list_start_;
    int amount_of_piority_ = 0;
    int amount_of_all_chores_ = 0;
};
#endif // DATASTRUCTURE_HPP
