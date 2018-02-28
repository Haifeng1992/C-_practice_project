//267937 Haifeng Xu haifeng.xu@student.tut.fi
#include "datastructure.hpp"
#include "splitter.hpp"
#include <fstream>
using namespace std;

bool has_only_digits(const string s){
  return s.find_first_not_of( "0123456789" ) == string::npos;
}

int main() {
    PiorityChores data;
    Splitter input_splitter;
    bool alread_initialized = false;

    int error = NO_ERROR;
    while(1) {
        if (error != NO_ERROR) {
            cout << "Error: Wrong input command." << endl;
        }
        cin.clear();
        cout << "chores> ";

        string input = "";
        string command = "";
        string str_num = "";
        int number = 0;
        string chore = "";


        getline(cin, input);
        input_splitter.set_string_to_split(input);
        input_splitter.split();
        command = input_splitter.command_;
        str_num = input_splitter.level_or_runnum_;
        chore = input_splitter.chore_;
        if(command == "init"){
            if(str_num == ""){
                cout<<"Error: the number of priority levels is missing."<<endl;
                continue;
            }
            bool only_num = has_only_digits(str_num);
            if(only_num == true){
                number=std::stoi(str_num);
                if(number < 1){
                   cout<< "Error: it is not possible to create a priority list with 0 or less levels."<<endl;
                   continue;
                }else{
                    data.initialize(number);
                    alread_initialized = true;
                    int aop=data.return_amount_of_piority();
                    cout<<"New priority list with levels 1-"<<aop<<" initialized."<<endl;
                    continue;
                }
            }else{
                cout<<"Error: the number of priority levels must be an integer larger than 0."<<endl;
                continue;
            }
        }
        if(command == "add"){
            if(alread_initialized != true){
                cout<<"Error: initialization is not done."<<endl;
                continue;
            }
            if(str_num == ""){
                cout<<"Error: priority level and chore description are missing."<<endl;
                continue;
            }
            bool only_num = has_only_digits(str_num);
            if(only_num != true){
                int aop2=data.return_amount_of_piority();
                cout<<"Error: priority level must be an integer between 1-"<<aop2<<"."<<endl;
                continue;
            }else if(chore == ""){
                cout<<"Error: chore description is missing."<<endl;
                continue;
            }else{
                number=std::stoi(str_num);
                int aop3=data.return_amount_of_piority();
                if(number<1 || number>aop3){
                    cout<<"Error: priority level must be an integer between 1-"<<aop3<<"."<<endl;
                    continue;
                }else{
                    data.add_chore(number, chore);
                    cout<<"New chore added to priority level "<<number<<"."<<endl;
                    continue;
                }
            }
        }
        if(command == "print"){
            if(alread_initialized != true){
                cout<<"Error: initialization is not done."<<endl;
                continue;
            }
            if(str_num != ""){
                cout<<"Error: extra text after print command."<<endl;
                continue;
            }else{
                data.print();
                continue;
            }
        }
        if(command == "next"){
            if(alread_initialized != true){
                cout<<"Error: initialization is not done."<<endl;
                continue;
            }
            if(str_num != ""){
                cout<<"Error: extra text after next command."<<endl;
                continue;
            }else{
                data.next_chore();
                continue;
            }
        }
        if(command == "erase"){
            int aoc=data.return_amount_of_all_chores();
            if(alread_initialized != true){
                cout<<"Error: initialization is not done."<<endl;
                continue;
            }
            if(str_num == ""){
                cout<<"Error: the running number is missing."<<endl;
                continue;
            }
            number=std::stoi(str_num);
            if(number < 1){
                cout<<"Error: the running number must be larger than 0."<<endl;
                continue;
            }
            if(number > aoc){
                cout<<"Error: there is no such chore."<<endl;
                continue;
            }else{
                data.erase_chore(number);
                continue;
            }
        }
        if(command == "quit"){
            if(alread_initialized == false) {
                return 0;
            }
            data.destroy();
            return 0;
        }
        else{
            cout<<"Error: unknown command."<<endl;
            continue;
        }
    }
}
