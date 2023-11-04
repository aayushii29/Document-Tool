// Do NOT add any other includes
#include "dict.h"

RBNode::RBNode(){ //setting sentinel node
    colour=2;
    s="";
    left=nullptr;
    // left->colour=2;
    right=nullptr;
    // right->colour=2;
    depth=1;
    count=0;
}
RBNode::RBNode(string k){
    colour=0;
    s=k;
    left=new RBNode();
    // left->colour=2;
    right=new RBNode();
    // right->colour=2;
    depth=0;
    count=1;
}
RBNode::RBNode(int a, int b, int c, int d, string word, int e){
    colour=0;
    s=word;
    left=new RBNode();
    // left->colour=2;
    right=new RBNode();
    // right->colour=2;
    depth=0;
    book_code=a;
    page=b;
    paragraph=c;
    sentence_number=d;
    s=word;
    offset=e;
    count=1;


}
// void Dict::setDepth(RBNode* k,RBNode* root){
//     RBNode* current=root;
//     int h=0;
//     if(k!=nullptr){
//         return;
//     }
//     else if(k->colour==2){
//         return;
//     }
//     else{
//         while(current->colour!=2 && current!=nullptr && current->s!=k->s){
//             if(current->s < k->s){
//                 if(current->colour==0){
//                     h++;
//                 }
//                 current=current->right;
//             }
//             else if(current->s > k->s){
//                 if(current->colour==0){
//                     h++;
//                 }
//                 current=current->left;
//             }
//             else{
//                 break;
//             }
//         }
//         if(current==k){
//             k->depth=h;
//         }   
//     }
//     return;

// }
RBNode* Dict::DoesExist(string g){
    RBNode* ans=new RBNode();
    if(root==nullptr){
        return ans;
    }
    else{
        
        RBNode* current=root;
        while(current!=nullptr && current->colour!=2 && current->s!=g){
            if(current->s>g){
                current=current->left;
            }
            else if(current->s<g){
                current=current->right;
            }
            
        }
        if(current->s==g){ans=current;}
        return ans;
    }
    return ans;
}
void Dict::insert(int book_code, int page, int paragraph, int sentence_no, string word, int offset){
    
    if(root==nullptr){
        root=new RBNode (book_code , page , paragraph , sentence_no , word , offset);
        root->left->depth=1;
        root->right->depth=1;
        root->colour=0;
    }
    else{
        RBNode* h=DoesExist(word);
        if(h->colour!=2){
            h->count++;
        }
        else{
            RBNode* current=root;
            vector <RBNode*> anc={};
            RBNode* final;
            while(current->colour!=2 && current!=nullptr){
                anc.push_back(current);
                if(current->s>word){
                    if(current->left->colour!=2){
                        
                        current=current->left;
                        // anc.push_back(current);
                    }
                    else{
                        current->left=new RBNode (book_code , page , paragraph , sentence_no , word , offset);
                        final=current->left;
                        final->colour=1;
                        // setDepth(final->left,root);
                        // setDepth(final->right,root);
                        break;

                    }
                }
                else{
                    if(current->right->colour!=2){
                        current=current->right;
                        // anc.push_back(current);
                    }
                    else{
                        current->right=new RBNode (book_code , page , paragraph , sentence_no , word , offset);
                        final=current->right;
                        final->colour=1;
                        // setDepth(final->left,root);
                        // setDepth(final->right,root);
                        break;
                    }
                }
            }
            // int j=0;
            RBNode* j=final->RBNode::DepthCorrectAlgo(final,anc);
            if(j!=nullptr && j->colour!=2){
                root=j;
            }
            root->colour=0;
            // if(j==1){root=final->RBNode::DepthCorrectAlgo(final,anc);}
            
        }
    }
}

RBNode* RBNode::DepthCorrectAlgo(RBNode* h, vector <RBNode*> k){
    RBNode* a=nullptr;
    if(k[k.size()-1]->colour==0){
        return new RBNode();
    }
    else{
        if(k[k.size()-2]->right==k[k.size()-1]){
            if(k[k.size()-2]->left->colour==1 ){
                a=UncleRed(h , k);
                if(a->left==k[0] || a->right==k[0]){}
                else{a=new RBNode();}
                
            }
            else if(k[k.size()-2]->left->colour==0 || k[k.size()-2]->left->colour==2 ){
                if(k[k.size()-1]->left==h){
                    a=UncleBlackTri(h,k);
                    if((a->left==k[0] || a->right==k[0])){}
                    else{a=new RBNode();}
                }
                else{
                    a=UncleBlackline(h,k);
                    if((a->left==k[0] || a->right==k[0])){}
                    else{a=new RBNode();}
                }
            }
        }
        else{
            if(k[k.size()-2]->right->colour==1 ){
                a=UncleRed(h , k);
                if(a->left==k[0] || a->right==k[0]){}
                else{a=new RBNode();}
            }
            else if(k[k.size()-2]->right->colour==0 || k[k.size()-2]->right->colour==2){
                if(k[k.size()-1]->right==h){
                    a=UncleBlackTri(h,k);
                    if((a->left==k[0] || a->right==k[0])){}
                    else{a=new RBNode();}
                }
                else{
                    a=UncleBlackline(h,k);
                    if((a->left==k[0] || a->right==k[0])){}
                    else{a=new RBNode();}
                }
            }
        }

    }
    return a;

}
RBNode* RBNode::UncleBlackline(RBNode* h, vector <RBNode*> k){
    RBNode* a=k[k.size()-1];
    RBNode* b=k[k.size()-2];
    if(k[k.size()-1]->right==h){
        RBNode* c=k[k.size()-2]->left;
        RBNode* temp = a->left;
        a->left=b;
        b->right=temp;
        if(k.size()>2){
            if(k[k.size()-3]->right==b){k[k.size()-3]->right=a;}
            else{k[k.size()-3]->left=a;}
        }
        a->colour=0;
        b->colour=1;
        a->depth=a->depth-1;
    }
    else{
        RBNode* c=k[k.size()-2]->right;
        RBNode* temp = a->right;
        a->right=b;
        b->left=temp;
        if(k.size()>2){
            if(k[k.size()-3]->right==b){k[k.size()-3]->right=a;}
            else{k[k.size()-3]->left=a;}
        }
        a->colour=0;
        b->colour=1;
        a->depth=a->depth-1;

    }
    return a;
}
RBNode* RBNode::UncleRed(RBNode* h, vector <RBNode*> k){
    RBNode* a=k[k.size()-1];
    RBNode* b=k[k.size()-2];
    if(b->right==a){ //2 and 4
        if(b->left->colour==1){RBNode* c=b->left; c->colour=0; c->depth=c->depth-1;}
        a->colour=0;
        b->colour=1;
        vector <RBNode*> hi={};
        // (a->depth)=(a->depth)-1;
        // cout<<"Hi";
        RBNode* r=nullptr;
        if(k.size()>2){
            for(int i=0; i<k.size()-2; i++){
                hi.push_back(k[i]);
            } 
            r=DepthCorrectAlgo(b,hi);
            if((r->left==hi[0] || r->right==hi[0])){
                b=r;
            }
        }

    }
    else{ // 6 and 8
        if(b->right->colour==1){RBNode* c=b->right; c->colour=0; c->depth=c->depth-1;}
        a->colour=0;
        b->colour=1;
        vector <RBNode*> hi;
        // a->depth=a->depth-1;
        RBNode* r=nullptr;
        if(k.size()>2){
            for(int i=0; i<k.size()-2; i++){
                hi.push_back(k[i]);
            } 
            r=DepthCorrectAlgo(b,hi);
            if((r->left==hi[0] || r->right==hi[0])){
                b=r;
            }
        }
        
    }
     /// Have to confirm
    return b;
}

RBNode* RBNode::UncleBlackTri(RBNode* h, vector <RBNode*> k){
    RBNode* a=k[k.size()-1];
    RBNode* b=k[k.size()-2];
    if(b->right==a){
        b->right=h;
        RBNode* temp=h->right;
        // b->right=h;
        h->right=a;
        a->left=temp;
        k.pop_back();
        k.push_back(h);
        b=UncleBlackline(a,k);//
    }
    else{
        b->left=h;
        RBNode* temp=h->left;
        // b->left=h;
        h->left=a;
        a->right=temp;
        k.pop_back();
        k.push_back(h);
        b=UncleBlackline(a,k);//
    }
    return b;//

}

// RBNode* RBNode::CorrectBDepthAlgo(RBNode* h, vector <RBNode*> k ){
//     if(k[k.size()-1]->colour==0){
//         return h;
//     }
//     else{
//         if(k.size()>=2){
//             if(k[k.size()-1]->right==h ){
//                 if(k[k.size()-2]->left->colour==1){
//                     k[k.size()-2]->colour=1;
//                     k[k.size()-2]->left->colour=0;
//                     k[k.size()-2]->left->depth=k[k.size()-2]->left->depth-1;
//                     k[k.size()-2]->right->colour=0;
//                     k[k.size()-2]->right->depth=k[k.size()-2]->right->depth-1;
//                     //Recursive call left on Parent Left.
//                 }
//                 else{
//                     if(k.size()>2){
//                         RBNode* a=k[k.size()-1];
//                         RBNode* b=k[k.size()-2];
//                         RBNode* c=k[k.size()-2]->left;
//                         RBNode* p=k[k.size()-3];
//                         if(k[k.size()-3]->left==b){k[k.size()-3]->left=a; a->colour=0;}
//                         else if(k[k.size()-3]->right==b){k[k.size()-3]->right=a; a->colour=0;}
//                         b->right=a->left;
//                         a->left=b;
//                         b->colour=1;
//                         a->colour=0;
//                     }
//                     else if(k.size()==2){
//                         RBNode* a=k[k.size()-1];
//                         RBNode* b=k[k.size()-2];
//                         RBNode* c=k[k.size()-2]->left;
//                         // RBNode* p=k[k.size()-3];
//                         // if(k[k.size()-3]->left==b){k[k.size()-3]->left=a; a->colour=0;}
//                         // else if(k[k.size()-3]->right==b){k[k.size()-3]->right=a; a->colour=0;}
//                         b->right=a->left;
//                         a->left=b;
//                         b->colour=1;
//                         a->colour=0;
//                     }
//                 }
//             }
//             else{

//             }
//         }
//         else{

//         }
//     }
// }


RBNode::~RBNode(){
    // if(left!=nullptr){delete left;}
    // if(right!=nullptr){delete right;}
    delete left; delete right;
}

Dict::Dict(){
    // Implement your function here
    root=nullptr;
    size=0;
}

Dict::~Dict(){
    // Implement your function here
    delete root;
}

void Dict::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    // Implement your function here
    string k="";
    int j=0; 
    // int h=1; 
    for(int i=0; i<sentence.length() ; i++){
        j=sentence[i];
        if(sentence[i]==' ' || sentence[i]=='.' || sentence[i]==',' || sentence[i]=='-' || sentence[i]==':' || sentence[i]=='!' || sentence[i]=='"' || sentence[i]=='(' || sentence[i]==')' || sentence[i]=='?' || sentence[i]=='[' || sentence[i]==']' || sentence[i]=='@' || sentence[i]==';'){
            // cout<<h<<endl;
            // h++;
            if(k!=""){
                // cout<<k<<endl;
                insert(book_code , page , paragraph, sentence_no, k , i );
                // cout<<"Hi"<<endl;
                size++;
            }// cout<<i+1<<endl;
            
            k="";
        }
        else if(j==39){
            // cout<<h<<endl;
            // h++;
            if(k!=""){
                // cout<<k<<endl;
                insert(book_code , page , paragraph, sentence_no, k , i );
                size++;
            }
            k="";
        }
        else if(i==sentence.length()-1){
            if (sentence[i] >= 'A' && sentence[i] <= 'Z') {
                sentence[i] = sentence[i] + 32;
            }

            k=k+sentence[i];
            if(k!=""){
                // cout<<k<<endl;
                insert(book_code , page , paragraph, sentence_no, k , i );
                // cout<<"Hi"<<endl;
                size++;
            }// cout<<i+1<<endl;
            
            k="";
        }
        else {
            if (sentence[i] >= 'A' && sentence[i] <= 'Z') {
                sentence[i] = sentence[i] + 32;
            }

            k=k+sentence[i];
        }  
    }
    return;
}

int Dict::get_word_count(string word){
    // Implement your function here
    int ans=0;
    if(root==nullptr){
        return 0;
    }
    else{
        RBNode* current=root;
        while(current!=nullptr && current->colour!=2){
            if(current->s>word){
                current=current->left;
            }
            else if(current->s<word){
                current=current->right;
            }
            else{
                ans=current->count;
                break;
            }
        }
        return ans;
    }
    return ans;
    // return -1;
}
// void HelperDump(string f, RBNode* root){
//     std::ofstream outputFile("filename.txt");
//     if(outputFile.is_open()) {
//         // Write each element of the vector to a new line in the file
//         if(root->left->colour!=2){
//             HelperDump(f, root->left);
//         }
//         if(root->colour!=2){   
//             outputFile << root->s <<", "<<root->count << std::endl;
//         }
//         if(root->left->colour!=2){
//             HelperDump(f, root->right);
//         }   
//         // Close the file stream
//         outputFile.close();
//         // std::cout << "Vector elements have been written to the file with each element on a new line." << std::endl;
//     }
// }

// void Dict::dump_dictionary(string filename){
//     std::ofstream outputFile("filename");
//     vector <RBNode*> h= InorderVector(root);
//     // Check if the file is successfully opened
//     if(outputFile.is_open()) {
//         // Write each element of the vector to a new line in the file
//         HelperDump(filename,root);
//         // Close the file stream
//         // outputFile.close();
//         // std::cout << "Vector elements have been written to the file with each element on a new line." << std::endl;
//     } else {
//         // If the file cannot be opened, print an error message
//         std::cout << "Error: Unable to open the file." << std::endl;
//     }      
//     return;
// }
void HelperDump(std::ofstream& outputFile, RBNode* root) {
    if (root == nullptr) {
        return;
    }
    
    if (root->left != nullptr && root->left->colour != 2) {
        HelperDump(outputFile, root->left);
    }
    
    if (root->colour != 2) {
        outputFile << root->s << ", " << root->count << std::endl;
    }
    
    if (root->right != nullptr && root->right->colour != 2) {
        HelperDump(outputFile, root->right);
    }
}

void Dict::dump_dictionary(std::string filename) {
    std::ofstream outputFile(filename); // Use the provided filename here
    if (outputFile.is_open()) {
        HelperDump(outputFile, root);
        outputFile.close(); // Close the file stream after writing
        // std::cout << "Dictionary elements have been written to the file." << std::endl;
    } else {
        // std::cout << "Error: Unable to open the file." << std::endl;
    }
}
void Dict::PP(RBNode* h){
    if(h->colour==2){
        return;
    }
    else{

        PP(h->left);
        cout<<h->s<<endl;

        // cout<<1<<endl;
        PP(h->right);
    }
    
}
// vector<RBNode*> Dict::InorderVector(RBNode* t){
//     RBNode* k=t;
//     vector <RBNode*> vec1={k};
    
//     if (t->left!=nullptr){
//         vector <RBNode*> l=InorderVector(t->left);
//         l.insert(l.end(),vec1.begin(),vec1.end());
//         vec1=l;
//     }
//     if (t->right!=nullptr){
//         vector <RBNode*> r=InorderVector(t->right);
//         vec1.insert(vec1.end(),r.begin(),r.end());
//     }
//     return vec1; 
// }
// Errors to be fixed==> set Depth function. Make all small before inserting. Sentense end handling. One special case for Red Uncle. Does exist problem
// int main(){
//     Dict* k=new Dict();
//     k->insert_sentence(1,1,1,1,"Amidst the towering mountains and lush green valleys, nestled a quaint little village, untouched by the hustle and bustle of the modern world. The villagers, with their warm smiles and traditional customs, welcomed visitors with open arms, inviting them to experience the serenity and simplicity of their lives. Each morning, the aroma of freshly brewed coffee and the melodious chirping of birds filled the air, creating a harmonious symphony of nature. Children, with their curious eyes and playful laughter, could be seen running along the cobblestone pathways, while the elders gathered under the ancient banyan tree, sharing stories of generations past. As the sun dipped below the horizon, painting the sky with hues of orange and pink, the village came alive with the soft glow of lanterns, illuminating the pathways and creating a magical ambiance. It was a place where time seemed to stand still, and in every corner, there was a tale waiting to be discovered, making it a haven for wanderers seeking solace and a deeper connection with the soul.");
//     cout<<"Hi"<<endl;
//     k->PP(k->root);
    
//     // int sum;
//     // vector<RBNode*> f = k->InorderVector(k->root); 
//     // for(int i=0;i<f.size();i++){
//     //     sum=sum+f[i]->count;
        
//     // }
//     k->dump_dictionary("ans.txt");
//     cout<<"Hi"<<endl;
//     // cout<<f.size()<<endl;
//     // cout<<sum<<endl;
//     // cout<<k->root->left->right->count<<endl;
//     return 0;
// }
// int main() {
//     Dict* dictionary = new Dict();

//     // Test Case 1: Insertion and Counting
//     dictionary->insert_sentence(1, 1, 1, 1, "The quick brown fox jumps over the lazy dog.");
//     dictionary->insert_sentence(2, 1, 1, 2, "Hello world!");
//     dictionary->insert_sentence(3, 1, 1, 3, "The sun rises in the east.");
//     dictionary->insert_sentence(1, 1, 1, 4, "Hello world!");

//     // Output: "the": 2 times, "quick": 1 time, "brown": 1 time, "fox": 1 time, "jumps": 1 time, "over": 1 time,
//     // "lazy": 1 time, "dog": 1 time, "hello": 2 times, "world": 2 times, "sun": 1 time, "rises": 1 time, "in": 1 time, "east": 1 time
//     cout << "Count of 'the': " << dictionary->get_word_count("the") << endl;
//     cout << "Count of 'quick': " << dictionary->get_word_count("quick") << endl;
//     cout << "Count of 'hello': " << dictionary->get_word_count("hello") << endl;

//     // Test Case 2: Dumping to File
//     dictionary->dump_dictionary("output.txt");

//     // Test Case 3: Checking if a word exists in the dictionary
//     // cout << "'quick' exists in the dictionary: " << (dictionary->DoesExist("quick")->colour == 2 ? "No" : "Yes") << endl;
//     // cout << "'nonexistent' exists in the dictionary: " << (dictionary->DoesExist("nonexistent")->colour == 2 ? "No" : "Yes") << endl;

//     // Test Case 4: Word Count after Insertion
//     cout << "Count of 'quick' after insertion: " << dictionary->get_word_count("quick") << endl;

//     delete dictionary;
//     return 0;
// }
// int main() {
//     Dict* dictionary = new Dict();

//     // Insert a large number of sentences into the dictionary
//     for (int i = 1; i <= 100000; ++i) {
//         string sentence = "This is sentence number " + to_string(i);
//         dictionary->insert_sentence(1, 1, 1, i, sentence);
//     }

//     // Check the count of a specific word in the last inserted sentence
//     cout << "Count of 'sentence' in the last inserted sentence: " << dictionary->get_word_count("sentence") << endl;

//     delete dictionary;
//     return 0;
// }
// int main() {
//     Dict* dictionary = new Dict();

//     // Insert a sentence with special characters and multiple spaces
//     dictionary->insert_sentence(1, 1, 1, 1, "The @quick brown  fox   jumps over the lazy dog!!!");

//     // Check word counts for words with special characters and spaces
//     cout << "Count of '@quick': " << dictionary->get_word_count("quick") << endl; // Output: 1
//     cout << "Count of 'fox': " << dictionary->get_word_count("fox") << endl; // Output: 1
//     cout << "Count of 'jumps': " << dictionary->get_word_count("jumps") << endl; // Output: 1

//     delete dictionary;
//     return 0;
// }
