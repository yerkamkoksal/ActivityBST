
#ifndef ActivityBST_h
#define ActivityBST_h
#include <iostream>
#include <string>
using namespace std;
struct tree_node {
   int time;
   string activity;
   tree_node *right;
   tree_node *left;
   tree_node *parent;
   tree_node(int t, const string &a) : time(t), activity(a),
    right(nullptr), left(nullptr),parent(nullptr) {}
};

class ActivityBST {
    
private:
    tree_node* root;
    
public:
    ActivityBST(); //Constructor
    
    ActivityBST(const ActivityBST& bst2); //Copy Constructor
    
    void add(int time, const string& activity);
            
    void preorderRec(ActivityBST& obj1, tree_node* root) const;
    
    void operator=(const ActivityBST& equalBST);
    
    ActivityBST operator+(const ActivityBST& plusBST) const;
    
    ActivityBST operator+=(const ActivityBST& pleqBST) const ;
    
    friend ostream & operator<<(ostream &out, const ActivityBST &bst);
    
    string print_all_activities(tree_node* root,string& output) const ;
    
    ~ActivityBST(); // Destructor

};

string fill_with_zeros(int num_zeros, const string& input);

string number_to_time(int number);

bool checkTime(int num);


    
#endif /* ActivityBST_h */
