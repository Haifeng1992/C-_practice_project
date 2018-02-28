//267937 Haifeng Xu haifeng.xu@student.tut.fi
#include "datastructure.hpp"

PiorityChores::PiorityChores(){}
PiorityChores::~PiorityChores(){}
void PiorityChores::destroy()
{
    auto iter_p = piority_list_start_;
    if(iter_p == nullptr){
        return;
    }else{
        while(iter_p != nullptr){
            auto iter_c = iter_p->chore_list_start;
            while (iter_c != nullptr) {
                auto remove_c=iter_c;
                iter_p->chore_list_start = iter_c->next_chore;
                //delete iter_c;
                delete remove_c;
                iter_c = iter_p->chore_list_start;
            }
            piority_list_start_=iter_p->next_piority;
            //delete iter_p;
            auto remove_p=iter_p;
            iter_p = iter_p->next_piority;
            delete remove_p;
        }
      }
}

void PiorityChores::initialize(int amount_piority_levels){
    if(amount_of_piority_ == 0){
        amount_of_piority_ = amount_piority_levels;
        piority_list_start_ = nullptr;
    }
    else{
        //delete previous
        auto iter_p = piority_list_start_;
        while(iter_p!=nullptr){
            auto iter_chore = iter_p->chore_list_start;
            while(iter_chore != nullptr){
                iter_p->chore_list_start = iter_chore->next_chore;
                delete iter_chore;
                iter_chore = iter_p->chore_list_start;
            }
            delete iter_chore;
            piority_list_start_ = iter_p->next_piority;
            delete iter_p;
            iter_p = piority_list_start_;
        }
        delete iter_p;
        piority_list_start_ = nullptr;
        amount_of_piority_ = 0;
        amount_of_all_chores_ = 0;
        //reallocate
        amount_of_piority_ = amount_piority_levels;
    }
}

void PiorityChores::add_chore(int piority_level, string chore_name){
    Chore_list* newchore = new Chore_list;
    newchore->next_chore = nullptr;
    newchore->piority_level = piority_level;
    newchore->chore = chore_name;
    newchore->running_num=0;

    auto p = piority_list_start_;
    Piority_list* previous = 0;
    if(p == nullptr){
        Piority_list* newpiority = new Piority_list;
        newpiority->chore_list_start = newchore;
        newpiority->chore_list_end = newchore;
        newpiority->next_piority = nullptr;
        newpiority->piority_level = newchore->piority_level;
        piority_list_start_=newpiority;
        //piority_list_end_=newpiority;
    }else{
        bool theend = true;
        while(p != nullptr){
            if(p->piority_level > newchore->piority_level){
                previous=p;
                p=p->next_piority;
                continue;
            }
            if(p->piority_level == newchore->piority_level){
                p->chore_list_end->next_chore=newchore;
                p->chore_list_end=newchore;
                theend = false;
                break;
            }
            if(p->piority_level < newchore->piority_level){
                Piority_list* newpiority = new Piority_list;
                newpiority->chore_list_start = newchore;
                newpiority->chore_list_end = newchore;
                newpiority->next_piority = nullptr;
                newpiority->piority_level = newchore->piority_level;
                if(previous == 0){
                    piority_list_start_ = newpiority;
                    newpiority->next_piority = p;
                    theend = false;
                    break;
                }else{
                    previous->next_piority = newpiority;
                    newpiority->next_piority=p;
                    theend = false;
                    break;
                }
            }
        }
        if(theend != false){
            Piority_list* newpiority = new Piority_list;
            newpiority->chore_list_start = newchore;
            newpiority->chore_list_end = newchore;
            newpiority->next_piority = nullptr;
            newpiority->piority_level = newchore->piority_level;
            previous->next_piority = newpiority;
        }
    }

    //remark running number
    auto iter_p = piority_list_start_;
    int running_num = 1;
    while(iter_p != nullptr){
        auto iter_c = iter_p->chore_list_start;
        while(iter_c!=nullptr){
            iter_c->running_num = running_num;
            running_num++;
            iter_c = iter_c->next_chore;
        }
        iter_p=iter_p->next_piority;
    }
    amount_of_all_chores_=running_num-1;
}

void PiorityChores::print(){
    auto iter_p = piority_list_start_;
    while(iter_p != nullptr ){
        cout<<"Priority level "<<iter_p->piority_level<<":"<<endl;
        auto iter_c = iter_p->chore_list_start;
        while(iter_c != nullptr){
            cout<<"  "<<iter_c->running_num<<". "<<iter_c->chore<<endl;
            iter_c = iter_c->next_chore;
        }
        iter_p=iter_p->next_piority;
    }
}

void PiorityChores::next_chore(){
    auto p = piority_list_start_;
    if(p == nullptr){
        cout<<"--- no chores left ---"<<endl;
        return;
    }
    auto q = p->chore_list_start;
    cout<<q->chore<<endl;
    erase_chore(1);
}

void PiorityChores::erase_chore(int given_num){
    auto p = piority_list_start_;
    Piority_list* previous_p = 0;
    bool already_delete = false;

    while (p!=nullptr)
    {
        auto c = p->chore_list_start;
        Chore_list* previous_c = 0;
        while (c!=nullptr){
            if(c->running_num == given_num){    //c is the first element
                if(p->chore_list_start == c){
                    if(c->next_chore == nullptr){ //p empty
                        delete c;
                        already_delete = true;
                        if(piority_list_start_ == p){
                            if(p->next_piority == nullptr){
                                delete p;
                                //amount_of_piority_--;
                                piority_list_start_ = nullptr;
                                break;
                            }else{
                                piority_list_start_ = p->next_piority;
                                delete p;
                                //amount_of_piority_--;
                                break;
                            }
                        }else{
                            previous_p->next_piority = p->next_piority;
                            delete p;
                            //amount_of_piority_--;
                            break;
                        }
                    }else{
                        p->chore_list_start=c->next_chore;
                        delete c;
                        already_delete = true;
                        break;
                    }
                }else if(p->chore_list_end == c){
                    delete c;
                    already_delete = true;
                    previous_c->next_chore = nullptr;
                    p->chore_list_end = previous_c;
                    break;
                }else{
                    previous_c->next_chore = c->next_chore;
                    delete c;
                    already_delete = true;
                    break;
                }
            }
            previous_c = c;
            c = c->next_chore;
        }
        if(already_delete == true){
            break;
        }
        else{
            previous_p = p;
            p = p->next_piority;
        }
    }

    //reduce running number after the erased one
    auto iter_p = piority_list_start_;
    int running_num = 1;
    while(iter_p != nullptr){
        auto iter_c = iter_p->chore_list_start;
        while(iter_c!=nullptr){
            iter_c->running_num = running_num;
            running_num++;
            iter_c = iter_c->next_chore;
        }
        iter_p=iter_p->next_piority;
    }
    amount_of_all_chores_=running_num-1;
}

int PiorityChores::return_amount_of_all_chores(){
    return amount_of_all_chores_;
}

int PiorityChores::return_amount_of_piority(){
    return amount_of_piority_;
}
