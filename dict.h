// Do NOT add any other includes
#include <string> 
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

class RBNode{
    public:
        int colour;  // Black=>0 , Red=>1 , Terminal Node => 2
        string s;
        RBNode* left;
        RBNode* right;
        int book_code;
        int page;
        int paragraph;
        int sentence_number;
        int offset;
        int depth;
        int count;

        RBNode();

        ~RBNode();

        RBNode(string s);
        RBNode(int book_code, int page, int paragraph, int sentence_no, string word, int offset);

        void setDepth(RBNode* k, RBNode* j);
        RBNode* DepthCorrectAlgo(RBNode* k, vector <RBNode*> Ancestors);
        RBNode* Root(RBNode* k, vector <RBNode*> Ancestors);
        RBNode* UncleRed(RBNode* k, vector <RBNode*> Ancestors); //2 and 4 and 6 and 8
        RBNode* UncleBlackTri(RBNode* k, vector <RBNode*> Ancestors);  //3 and 7
        RBNode* UncleBlackline(RBNode* k, vector <RBNode*> Ancestors);  //1 and 5
        
        // void Remove();  Dont know the use;

};
class Dict {
private:
    
    

    RBNode* DoesExist(string k);
    void insert(int book_code, int page, int paragraph, int sentence_no, string word, int offset);
    void setDepth(RBNode* k, RBNode* j);
    // You can add attributes/helper functions here

public: 
    RBNode* root;
    int size;
    /* Please do not touch the attributes and 
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    Dict();

    ~Dict();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence); //RB Insert

    int get_word_count(string word); //RB Search

    void dump_dictionary(string filename); //Read/Dump to a file
    

    /* -----------------------------------------*/
    vector<RBNode*> InorderVector(RBNode* r);
    void PP(RBNode* r);
};

