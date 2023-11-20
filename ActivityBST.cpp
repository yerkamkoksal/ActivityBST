// YUSUF ERKAM KOKSAL    29512    CS204 HW4



#include <iostream>
#include <string>
#include "ActivityBST.h"
using namespace std;


string fill_with_zeros(int num_zeros, const string& input){
   int zeros_to_add = num_zeros - input.length();
   if (zeros_to_add < 0) zeros_to_add = 0;
   return string(zeros_to_add, '0') + input;
}

string number_to_time(int number){
   return fill_with_zeros(2, to_string(number/100))+":"+ fill_with_zeros(2, to_string(number%100));
}

bool checkTime(int num){ // Checks if the given time is in hh:mm format.
    
    int mm;
    int hh;
    
    mm = (num % 100);
    hh = num - mm;
    
    if (0<= mm && mm<=59) {
        if (0<=hh && hh<=2300) {
            return true;
        }
    }
    return false;
}

ActivityBST::ActivityBST(){
    root = nullptr;
}


void ActivityBST::add(int time, const string& activity){
    string output;
    if (checkTime(time)) {
        if (root == nullptr) {
            root = new tree_node(time, activity);
        }
        else {
            tree_node *curr = root;
            tree_node *new_node;
            new_node = new tree_node(time, activity);
            bool added = false;
            while (!added) {
                if (curr->time == time){
                    curr->activity = activity;
                    added = true;
                    delete new_node;
                }
                else if (curr->time > time) {
                    if (curr->left == nullptr) {
                        new_node->parent = curr;
                        curr->left = new_node;
                        added = true;
                    } else {
                        curr = curr->left;
                    }
                } else if (curr->time < time) {
                    if (curr->right == nullptr) {
                        new_node->parent = curr;
                        curr->right = new_node;
                        added = true;
                    } else {
                        curr = curr->right;
                    }
                }
            }
        }
    }
}


void ActivityBST::operator=(const ActivityBST& equalBST){
    root = equalBST.root;
}

void ActivityBST::preorderRec(ActivityBST& obj1, tree_node* root)const {
    if (root){
        obj1.add(root -> time, root->activity);
        preorderRec(obj1, root->left);
        preorderRec(obj1, root->right);
    }
    return;
}

ActivityBST::ActivityBST(const ActivityBST& bst2){
    ActivityBST temp;
    tree_node* nodePtr = bst2.root;
    preorderRec(temp, nodePtr);
    this->root = temp.root;
}


ActivityBST ActivityBST::operator+=(const ActivityBST& obj2) const {
    ActivityBST obj1;
    tree_node* nodePtr;
    nodePtr = obj2.root;
    preorderRec(obj1, nodePtr);
    return obj1;
}

ActivityBST ActivityBST::operator+(const ActivityBST& obj2) const {
    ActivityBST obj3;
    tree_node* nodePtr;
    tree_node* nodePtr2;
    nodePtr = this->root;
    nodePtr2 = obj2.root;
    preorderRec(obj3, nodePtr);
    preorderRec(obj3, nodePtr2);
    return obj3;
}



string ActivityBST::print_all_activities(tree_node* root, string& output) const {
    if (root!= nullptr){
        print_all_activities(root-> left, output);
        output+= "[" + number_to_time(root->time) + "] - " + root->activity + '\n';
        print_all_activities(root-> right,output);
    }
    return output;
}

ostream & operator<<(ostream &out, const ActivityBST& bst)
{
    string output;
    out<<bst.print_all_activities(bst.root,output);
    return out;
}

ActivityBST::~ActivityBST(){}


int main() {
    ActivityBST uni_calendar;
    uni_calendar.add(1000, "meeting");
    uni_calendar.add(1200, "class");
    uni_calendar.add(1100, "lecture");
    uni_calendar.add(2400, "all-nighter"); // not added because
                                           // time value is illegal
    ActivityBST sport_calendar;
    sport_calendar.add(930, "walk");
    sport_calendar.add(2100, "walk");
    cout << "Uni calendar: \n" << uni_calendar << "Sport calendar: \n" << sport_calendar;
    ActivityBST personal_calendar;
    personal_calendar.add(900, "breakfast");
    personal_calendar.add(2300, "sleep");
    personal_calendar.add(1600, "nap");
    personal_calendar.add(1230, "lunch");
    cout << "Personal calendar: \n" << personal_calendar;
    ActivityBST overall_calendar = sport_calendar + personal_calendar;
    cout << "Overall calendar: \n" << overall_calendar;
    ActivityBST extended_calendar(uni_calendar);
    extended_calendar.add(1500, "homework");
    cout << "Extended calendar: \n" << extended_calendar;
    extended_calendar+=personal_calendar+= sport_calendar;
    cout << "Personal calendar: \n" << personal_calendar;
    cout << "Extended calendar: \n" << extended_calendar;
    return 0;
}
