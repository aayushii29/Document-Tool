#include <string> 
#include <vector>
#include <iostream>
#include "Node.h"
using namespace std;
class Matches{
    public:
    Node* head;
    int c;
    Matches();
    void insert(int book_code, int page, int paragraph, int sentence_no, int j);
    int count();
    ~Matches();
};
class SearchEngine {
private:
// public:
    // You can add attributes/helper functions here

public: 
    // Matches* M;
    vector<pair<string,vector<int>>> sentences;
    // vector<vector<string>> sentences;
    // vector<Node*> matches;/
    vector<int> RabinKarp(const string& x, const string& y);
    string toLower(const string& a);

    /* Please do not touch the attributes and 
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    SearchEngine();

    ~SearchEngine();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    Node* search(string pattern, int& n_matches);

    /* -----------------------------------------*/
};