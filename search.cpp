#include "search.h"

Matches::Matches(){
    head = nullptr;
    c = 0;
}

void Matches::insert(int book_code, int page, int paragraph, int sentence_no, int j){
    Node* newNode = new Node(book_code, page, paragraph, sentence_no, j);
    newNode->left = nullptr;
    newNode->right = nullptr;
    if(head==nullptr){
        head=newNode;
        c = c + 1;
    }
    else{
       newNode->right = head;
       head = newNode;
       c = c + 1;
    }

}

int Matches::count(){
    return c;
}

Matches::~Matches(){
    Node* current= head;
    while(current != nullptr){
        Node* temp = current;
        current = current->right;
        delete temp;
    }
}

SearchEngine::SearchEngine(){
    sentences = {};
}

string SearchEngine::toLower(const string& a) {
    string b = a;
    for (int i = 0; i < b.size(); i++) {
        if (b[i] >= 'A' && b[i] <= 'Z') {
            b[i] = b[i] + 32;
        }
    }
    return b;
}


long long calculateHash(const string& str, long long q, int d) {
    long long hashValue = 0;
    for (char c : str) {
        hashValue = (d * hashValue + c) % q;
    }
    return hashValue;
}

vector<int> SearchEngine::RabinKarp(const string& x, const string& y) {
    string p = toLower(x);
    string t = toLower(y);
    vector<int> matches = {};
    int m = p.size();
    int n = t.size();
    long long q = 1000000007; 
    int d = 256;

    long long hashp = calculateHash(p, q, d);
    long long hasht = calculateHash(t.substr(0, m), q, d);
    long long h = 1;
    for (int i = 0; i < m - 1; i++) {
        h = (h * d) % q;
    }

    for (int i = 0; i <= n - m; i++) {
        if (hashp == hasht && t.substr(i, m) == p) {
            matches.push_back(i);
        }
        if (i < n - m) {
            hasht = (d * (hasht - t[i] * h) + t[i + m]) % q;
            if (hasht < 0) {
                hasht = (hasht + q);
            }
        }
    }
    return matches;
}

SearchEngine::~SearchEngine(){
   sentences.clear();
}

void SearchEngine::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    vector<int> info = {book_code,page,paragraph,sentence_no};
    sentences.push_back(make_pair(move(sentence),info));
}

Node* SearchEngine::search(string pattern, int& n_matches){
    Matches* M = new Matches();
    int count = 0;
    for (auto i = sentences.begin(); i != sentences.end(); ++i) {
        vector<int> match_positions = RabinKarp(pattern, i->first);
        for (int match : match_positions) {
            M->insert(i->second[0], i->second[1], i->second[2], i->second[3], match);
        }
    }
   
    n_matches = M->count();
    Node* h = M->head;
    return h;

}