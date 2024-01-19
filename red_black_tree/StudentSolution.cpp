#include <bits/stdc++.h>
using namespace std;

class HybridNode {
public:
    string key;     // Word
    string element;    // Chapter
    HybridNode* parent;   // Parent node
    HybridNode* left_child;  // Left child node
    HybridNode* right_child;  // Right child node
    HybridNode* next_node;  // Next node in the linked list
    string color = "red";    // Color of the node

    HybridNode(string key_val, string element_val) : key(key_val), element(element_val), parent(nullptr), left_child(nullptr), right_child(nullptr), next_node(nullptr) {}

    void setColor(string str) {
        color = str;
    }

    void setKey(string str) {
        key = str;
    }

    void setElement(string str) {
        element = str;
    }

    void setParent(HybridNode* par) {
        parent = par;
    }

    void setLeftChild(HybridNode* lc) {
        left_child = lc;
    }

    void setRightChild(HybridNode* rc) {
        right_child = rc;
    }

    void setNext(HybridNode* nxt) {
        next_node = nxt;
    }

    string getKey() {
        return key;
    }

    string getElement() {
        return element;
    }

    string getColor() {
        return color;
    }

    HybridNode* getParent() {
        return parent;
    }

    HybridNode* getLeftChild() {
        return left_child;
    }

    HybridNode* getRightChild() {
        return right_child;
    }

    HybridNode* getNext() {
        return next_node;
    }
};

class RedBlackTree {
private:
    HybridNode* root;   // Root node

public:
    RedBlackTree() : root(nullptr) {}

    HybridNode* getRoot() {
        return root;  // Return the root node
    }

    void setRoot(HybridNode* node) {
        root = node;  // Set the root node
    }

    void rightrotate(HybridNode* node) {
        if (node->getLeftChild() != nullptr) {
            HybridNode* sam = node->getLeftChild();
            if (sam->getRightChild() != nullptr) {
                node->setLeftChild(sam->getRightChild());
                sam->getRightChild()->setParent(node);
            }
            else {
                node->setLeftChild(nullptr);
            }
            if (node->getParent() != nullptr) {
                sam->setParent(node->getParent());
            }
            if (node->getParent() == nullptr) {
                root = sam;
            }
            else {
                if (node == node->getParent()->getLeftChild()) {
                    node->getParent()->setLeftChild(sam);
                }
                else {
                    node->getParent()->setRightChild(sam);
                }
            }
            sam->setRightChild(node);
            node->setParent(sam);
        }
    }
    
    void leftrotate(HybridNode* node) {
        if (node->getRightChild() != nullptr) {
            HybridNode* sam = node->getRightChild();
            if (sam->getLeftChild() != nullptr) {
                node->setRightChild(sam->getLeftChild());
                sam->getLeftChild()->setParent(node);
            }
            else {
                node->setRightChild(nullptr);
            }
            if (node->getParent() != nullptr) {
                sam->setParent(node->getParent());
            }
            if (node->getParent() == nullptr) {
                root = sam;
            }
            else {
                if (node == node->getParent()->getLeftChild()) {
                    node->getParent()->setLeftChild(sam);
                }
                else {
                    node->getParent()->setRightChild(sam);
                }
            }
            sam->setLeftChild(node);
            node->setParent(sam);
        }
    }
    
    int stringCompare(string s1, string s2) {
        // use strcmp

        char *c1 = new char[s1.length() + 1];
        strcpy(c1, s1.c_str());

        char *c2 = new char[s2.length() + 1];
        strcpy(c2, s2.c_str());

        int result = strcmp(c1, c2);
        return result;
    }

    HybridNode* insert(string key, string element) {
        // When the root is tree is empty
        if (root == nullptr) {
            HybridNode* rt = new HybridNode(key, element);
            rt->setColor("black");
            root = rt;
            return rt;
        }
        else {
            HybridNode* node = new HybridNode(key, element);
            node->setColor("red");

            HybridNode* temp = root;
            HybridNode* temp_1 = root;
            // Searching the tree to insert a new node
            while (temp != nullptr) {
                temp_1 = temp;
                if (stringCompare(temp->getKey() , node->getKey()) >= 0) {
                    temp = temp->getLeftChild();
                }
                else {
                    temp = temp->getRightChild();
                }
            }
            // Inserting the node
            node->setParent(temp_1);
            if (stringCompare(temp_1->getKey() , node->getKey()) >= 0) {
                temp_1->setLeftChild(node);
                temp = temp_1->getLeftChild();
            }
            else {
                temp_1->setRightChild(node);
                temp = temp_1->getRightChild();
            }
            
            // Checking for double red and reconstruct/recolor accordingly
            while (temp->getParent() != nullptr && temp->getParent()->getColor() == "red") {
                HybridNode* grand_parent = temp->getParent()->getParent();
                if (grand_parent->getLeftChild() == temp->getParent()) {
                    if (grand_parent->getRightChild() != nullptr) {
                        HybridNode* sam = grand_parent->getRightChild();
                        if (sam->getColor() == "red") {
                            temp->getParent()->setColor("black");
                            sam->setColor("black");
                            grand_parent->setColor("red");
                            temp = grand_parent;
                        }
                        else {
                            if (temp->getParent()->getRightChild() == temp) {
                                temp = temp->getParent();
                                leftrotate(temp);
                            }
                            temp->getParent()->setColor("black");
                            grand_parent->setColor("red");
                            rightrotate(grand_parent);
                        }
                    }
                    else {
                        if (temp->getParent()->getRightChild() == temp) {
                            temp = temp->getParent();
                            leftrotate(temp);
                        }
                        temp->getParent()->setColor("black");
                        grand_parent->setColor("red");
                        rightrotate(grand_parent);
                    }
                }
                else {
                    if (grand_parent->getLeftChild() != nullptr) {
                        HybridNode* sam = grand_parent->getLeftChild();
                        if (sam->getColor() == "red") {
                            temp->getParent()->setColor("black");
                            sam->setColor("black");
                            grand_parent->setColor("red");
                            temp = grand_parent;
                        }
                        else {
                            if (temp->getParent()->getLeftChild() == temp) {
                                temp = temp->getParent();
                                rightrotate(temp);
                            }
                            temp->getParent()->setColor("black");
                            grand_parent->setColor("red");
                            leftrotate(grand_parent);
                        }
                    }
                    else {
                        if (temp->getParent()->getLeftChild() == temp) {
                            temp = temp->getParent();
                            rightrotate(temp);
                        }
                        temp->getParent()->setColor("black");
                        grand_parent->setColor("red");
                        leftrotate(grand_parent);
                    }
                }
            }
            if(root->getColor() == "red") {
                root->setColor("black");
            }
        }
        // Implement Red-Black Tree insertion
    }

    // Helper functions for delete function
    HybridNode* getUncle(HybridNode* node) {
        if (node->getParent() == nullptr || node->getParent()->getParent() == nullptr) {
            return nullptr;
        }
        if (node->getParent()->getParent()->getLeftChild() == node->getParent()) {
            return node->getParent()->getParent()->getRightChild();
        }
        else {
            return node->getParent()->getParent()->getLeftChild();
        }
    }

    HybridNode* getSibling(HybridNode* node) {
        if (node->getParent() ==nullptr) {
            return nullptr;
        }
        if (node->getParent()->getLeftChild() == node) {
            return node->getParent()->getRightChild();
        }
        else {
            return node->getParent()->getLeftChild();
        }
    }

    void move_down (HybridNode* node , HybridNode* replacement) {
        if (node->getParent() != nullptr) {
            if (node->getParent()->getLeftChild() == node) {
                node->getParent()->setLeftChild(replacement);
            }
            else {
                node->getParent()->setRightChild(replacement);
            }
        }
        replacement->setParent(node->getParent());
        node->setParent(replacement);
    }

    void left_rotate_delete (HybridNode* node) {
        HybridNode* new_parent = node->getRightChild();
        if (node == root) {
            root = new_parent;
        }
        move_down(node, new_parent);

        node->setRightChild(new_parent->getLeftChild());
        if (new_parent->getLeftChild() != nullptr) {
            new_parent->getLeftChild()->setParent(node);
        }
        new_parent->setLeftChild(node);
    }

    void right_rotate_delete (HybridNode* node) {
        HybridNode* new_parent = node->getLeftChild();
        if (node == root) {
            root = new_parent;
        }
        move_down(node, new_parent);

        node->setLeftChild(new_parent->getRightChild());
        if (new_parent->getRightChild() != nullptr) {
            new_parent->getRightChild()->setParent(node);
        }
        new_parent->setRightChild(node);
    }

    void swap_colors (HybridNode* node1, HybridNode* node2) {
        string temp = node1->getColor();
        node1->setColor(node2->getColor());
        node2->setColor(temp);
    }

    void swap_values (HybridNode* node1, HybridNode* node2) {
        string temp = node1->getKey();
        node1->setKey(node2->getKey());
        node2->setKey(temp);
    }

    HybridNode* get_successor (HybridNode* node) {
        HybridNode* temp = node;
        while (temp->getLeftChild() != nullptr) {
            temp = temp->getLeftChild();
        }
        return temp;
    }

    HybridNode* rbt_replace (HybridNode* node) {
        if (node->getLeftChild() != nullptr && node->getRightChild() != nullptr) {
            return get_successor(node->getRightChild());
        }
        if (node->getLeftChild() == nullptr && node->getRightChild() == nullptr) {
            return nullptr;
        }

        if (node->getLeftChild() != nullptr) {
            return node->getLeftChild();
        }
        else {
            return node->getRightChild();
        }
    }

    void fix_double_black(HybridNode* node) {
        if (node == root) {
            return;
        }

        HybridNode* sibling = getSibling(node);
        HybridNode* par = node->getParent();

        if (sibling == nullptr) {
            fix_double_black(par);
        }
        else {
            if (sibling->getColor() == "red") {
                par->setColor("red");
                sibling->setColor("black");
                if (sibling->getParent()->getLeftChild() == sibling) {
                    right_rotate_delete(par);
                }
                else {
                    left_rotate_delete(par);
                }
                fix_double_black(node);
            }
            else {
                if ((sibling->getLeftChild() != nullptr && sibling->getLeftChild()->getColor() == "red") || (sibling->getRightChild() != nullptr && sibling->getRightChild()->getColor() == "red")) {
                    if (sibling->getLeftChild() != nullptr && sibling->getLeftChild()->getColor() == "red") {
                        if (sibling->getParent()->getLeftChild() == sibling) {
                            sibling->getLeftChild()->setColor(sibling->getColor());
                            sibling->setColor(par->getColor());
                            right_rotate_delete(par);
                        }
                        else {
                            sibling->getLeftChild()->setColor(par->getColor());
                            right_rotate_delete(sibling);
                            left_rotate_delete(par);
                        }
                    }
                    else {
                        if (sibling->getParent()->getLeftChild() == sibling) {
                            sibling->getRightChild()->setColor(par->getColor());
                            left_rotate_delete(sibling);
                            right_rotate_delete(par);
                        }
                        else {
                            sibling->getRightChild()->setColor(sibling->getColor());
                            sibling->setColor(par->getColor());
                            left_rotate_delete(par);
                        }
                    }
                    par->setColor("black");
                }
                else {
                    sibling->setColor("red");
                    if (par->getColor() == "black") {
                        fix_double_black(par);
                    }
                    else {
                        par->setColor("black");
                    }
                }
            }
        }
    }

    void deleteHelp(HybridNode* node){
        
        HybridNode* asdf = rbt_replace(node);
        HybridNode* par = node->getParent();
        // cout << " WORKING " << endl;
        if (asdf == nullptr) {
            if (node == root) {
                root = nullptr;
            }
            else {
                if ((asdf==nullptr || asdf->getColor()=="black") && node->getColor() == "black") {
                    fix_double_black(node);
                }
                else {
                    if (getSibling(node) != nullptr) {
                        getSibling(node)->setColor("red");
                    }
                }
                if (node->getParent()->getLeftChild() == node) {
                    par->setLeftChild(nullptr);
                }
                else {
                    par->setRightChild(nullptr);
                }
            }
            delete node;
            return;
        }
        
        // cout << "CHECKPOINT1" << endl;
        if (node->getLeftChild() == nullptr || node->getRightChild() == nullptr) {
            if (node == root) {
                node->setElement(asdf->getElement());
                node->setLeftChild(nullptr);
                node->setRightChild(nullptr);
                delete asdf;
            }
            else {
                if (node->getParent()->getLeftChild() == node) {
                    par->setLeftChild(asdf);
                }
                else {
                    par->setRightChild(asdf);
                }
                delete node;
                asdf->setParent(par);
                if ((asdf==nullptr || asdf->getColor()=="black") && node->getColor() == "black") {
                    fix_double_black(asdf);
                }
                else {
                    asdf->setColor("black");
                }
            }
            return;
        }
        // cout << "CHECKPOINT1" << endl;

        swap_values(node, asdf);
        // cout << "CHECKPOINT1" << endl;
        deleteHelp(asdf);
    }

    bool deleteNode(string n) {
        if (root == NULL)
            return 0;
 
        HybridNode *v = search(n);
    
        if (v->key != n) {
            cout << "No node found to delete with value:" << n << endl;
            return 0;
        }
    
        deleteHelp(v);
        return 1;
        // Implement Red-Black Tree deletion
    }

    vector<HybridNode*> traverseUp(HybridNode* node) {
        vector<HybridNode*> vec;
        vec.push_back(node);
        while (node->getParent() != nullptr) {
            node = node->getParent();
            vec.push_back(node);
        }
        return vec;
        // Traverse up the tree from the given node to the root
        // Return the vector of nodes in the path
    }

    vector<HybridNode*> traverseDown(HybridNode* node, string bit_sequence) {
        // Traverse down the tree based on the bit sequence
        // Return the vector of nodes in the path
        vector<HybridNode*> path;
        for(int i=0;i<bit_sequence.size();i++){
            if(bit_sequence[i]=='1'){
                if(node==nullptr){
                    return path;
                }
                else{
                    path.push_back(node);
                    node = node->left_child;
                }
            }
            else{
                if(node==nullptr){
                    return path;
                }
                else{
                    path.push_back(node);
                    node = node->right_child;
                }
            }
        }
        // Traverse down the tree based on the bit sequence
        // Return the vector of nodes in the path
    }

    vector<HybridNode*> preorder_helper(HybridNode* node, int depth, vector<HybridNode*> vec) {
        if (depth ==1 || (node->getLeftChild() == nullptr && node->getRightChild() == nullptr)) {
            if (node != nullptr) {
                vec.push_back(node);
            }
            return vec;
        }
        else {
            if (node != nullptr) {
                vec.push_back(node);
            }
            if (node->getLeftChild() != nullptr) {
                vec = preorder_helper(node->getLeftChild() , depth-1 , vec);
                // for (int i=0; i<vec1.size(); i++) {
                //     vec.push_back(vec1[i]);
                // }
            }
            if (node->getRightChild() != nullptr) {
                vec = preorder_helper(node->getRightChild() , depth-1 , vec);
                // for (int i=0; i<vec2.size(); i++) {
                //     vec.push_back(vec2[i]);
                // }
            }
        }
        return vec;
    }

    vector<HybridNode*> preOrderTraversal(HybridNode* node, int depth) {
        vector<HybridNode*> vec100;
        vector<HybridNode*> vec_final = preorder_helper(node, depth+1, vec100);
        return vec_final;
        // Perform pre-order traversal staying within specified depth
    }

    vector<HybridNode*> inorder_helper(HybridNode* node, vector<HybridNode*> vec) {
        if (node->getLeftChild() == nullptr && node->getRightChild() == nullptr) {
            if (node != nullptr) {
                vec.push_back(node);
            }
            return vec;
        }
        else {
            if (node->getLeftChild() != nullptr) {
                vec = inorder_helper(node->getLeftChild() , vec);
                // for (int i=0; i<vec1.size(); i++) {
                //     vec.push_back(vec1[i]);
                // }
            }
            if (node != nullptr) {
                vec.push_back(node);
            }
            if (node->getRightChild() != nullptr) {
                vec = inorder_helper(node->getRightChild() , vec);
                // for (int i=0; i<vec2.size(); i++) {
                //     vec.push_back(vec2[i]);
                // }
            }
        }
        return vec;
    }

    vector<HybridNode*> inOrderTraversal() {
        vector<HybridNode*> vec100;
        vector<HybridNode*> vec_final = inorder_helper(root, vec100);
        return vec_final;
    }

    HybridNode* search(string key) {
        for (int i=0; i<key.size(); i++) {
            if (key[i] >= 65 && key[i] <= 90) {
                key[i] += 32;
            }
        }
        HybridNode* temp = root;
        while (temp != nullptr) {
            if (stringCompare(key, temp->getKey()) == 0) {
                return temp;
            }
            else if (stringCompare(key , temp->getKey()) > 0) {
                temp = temp->getRightChild();
            }
            else {
                temp = temp->getLeftChild();
            }
        }
        // Implement Red-Black Tree search
    }
    
    int blackheight(HybridNode* node){
        // int count = 0;
        // if (node->getColor() == "black") {
        //     count++;
        // }
        // while (node->getParent() != nullptr) {
        //     node = node->getParent();
        //     if (node->getColor() == "black") {
        //         count++;
        //     }
        // }

        int count = 1;
        while (node->getLeftChild() != nullptr) {
            if (node->getColor() == "black") {
                count += 1;
            }
            node = node->getLeftChild();
        }
        return count;
        // Implement blackheight
    }
};

class IndexEntry {
private:
    string word;
    vector<pair<string, int>> chapter_word_counts;  // List of (chapter, word_count) tuples

public:
    IndexEntry(string word_val) : word(word_val) {}

    void setWord(string word_val) {  // Set the word
        word = word_val;
    }

    string getWord() {  // Get the word
        return word;
    }

    void setChapterWordCounts(vector<pair<string, int>> chapter_word_counts_val) {  // Set the list of (chapter, word_count) tuples
        chapter_word_counts = chapter_word_counts_val;
    }

    vector<pair<string, int>> getChapterWordCounts() {  // Get the list of (chapter, word_count) tuples
        return chapter_word_counts;
    }
};

class MRU {
public:
    static const int HASH_TABLE_SIZE = 5000;
    IndexEntry*  hashTable[HASH_TABLE_SIZE];

    // Constructor
    MRU() {
        for (int i = 0; i < HASH_TABLE_SIZE; ++i) {
            hashTable[i] = nullptr;
        }
    }

    long long power(int m, int i){
        long long a=1;
        for(int j=0; j<i; j++){
             a = a * m;
        }
        return a;
    }

    long long computeHash(const string& str, int ins_ser){
        long long int p=1000000007;
        int m = 52;
        int probe = 27;
        long long hash=0;
        for (int i=0; i<str.size(); i++){
            long long int a = str[i];
            a = a * power(m,i);
            a = a % p;
            hash += a;
        }
        hash = hash % 5000;
        if (ins_ser == 0) {
            if (hashTable[hash] == nullptr) {
                return hash;
            }
            else {
                if (hashTable[hash]->getWord() == str) {
                    return hash;
                }
                else {
                    while (hashTable[hash] != nullptr) {
                        hash = (hash + probe) % 5000;
                    }
                    return hash;
                }
            }
        }
        else if (ins_ser == 1) {
            if (hashTable[hash]->getWord() == str) {
                return hash;
            }
            else {
                while (hashTable[hash]->getWord() != str) {
                    hash = (hash + probe) % 5000;
                }
                return hash;
            }
        }
        return hash;
    }
};
// vector<IndexEntry*>  global_vec;

// long long power(int m, int i){
//     long long a=1;
//     for(int j=0; j<i; j++){
//             a = a * m;
//     }
//     return a;
// }

// long long computeHash(const string& str){
//     long long int p=1000000007;
//     int m = 263;
//     long long hash=0;
//     for (int i=0; i<str.size(); i++){
//         long long int a = str[i];
//         a = a * power(m,i);
//         a = a % p;
//         hash += a;
//     }
//     hash = hash % m;
//     return hash;
// }

class Lexicon {
private:
    RedBlackTree red_black_tree;  // Red-Black Tree
    MRU ht;
    int number_of_chapters = 0;
public:
    Lexicon() {}

    void setRedBlackTree(RedBlackTree tree) {  // Set the Red-Black Tree
        red_black_tree = tree;
    }

    RedBlackTree getRedBlackTree() {  // Get the Red-Black Tree
        return red_black_tree;
    }

    void readChapters(vector<string> chapter_names) {
        number_of_chapters += chapter_names.size();
        for (int i=0; i<chapter_names.size(); i++) {
            // vector<string> to_insert consists of all the words to be inserted into the red-black tree
            vector<string> to_insert;
            string file_name;
            for (int j=0; j<chapter_names[i].size()-4 ; j++) {
                file_name += chapter_names[i][j];
            }
            // cout << endl << file_name << endl;
            ifstream file;
            file.open(chapter_names[i]);
            string line;
            if (!file){
                cout << "File does not exist [OR] it isn't open";
            }
            else {
                while (getline(file, line)){
                    string word;
                    for (int i=0; i<line.size(); i++){
                        char s=line[i];
                        if(s>=65 && s<=90){
                            s = s+32;
                        }
                        if((s>=97 && s<=122) || s==39 || s==45){
                            word+=s;
                        }
                        else {
                            if (word[0] == 39 || word[0] == 45){
                                word.erase(word.begin());
                            }
                            if (word[word.size()-1] == 39 || word[word.size()-1] == 45) {
                                word.erase(word.begin() + word.size() - 1);
                            }
                            if(word.size()!=0) {
                                to_insert.push_back(word);
                                // HybridNode* ss = red_black_tree.search(word);
                                // if (ss == nullptr) {
                                //     cout << word << " " << flush;
                                //     red_black_tree.insert(word , file_name);
                                // }
                            }
                            word.clear();
                        }
                        if (i==(line.size()-1) && ((s>=97 && s<=122) || s==39 || s==45)) {
                            if (word[0] == 39){
                                word.erase(word.begin());
                            }
                            if (word[word.size()-1] == 39 || word[word.size()-1] == 39) {
                                word.erase(word.begin() + word.size() - 1);
                            }
                            if(word.size()!=0) {
                                to_insert.push_back(word);
                                // HybridNode* ss = red_black_tree.search(word);
                                // if (ss == nullptr) {
                                //     cout << word << " " << flush;
                                //     red_black_tree.insert(word , file_name);
                                // }
                            }
                            word.clear();
                        }
                    }
                }
            }
            // Inserting the word into red black tree
            for (int j=0; j<to_insert.size(); j++) {
                HybridNode* ss = red_black_tree.search(to_insert[j]);
                // If the word in not in red black tree insert a new node
                if (ss == nullptr) {
                    // cout << to_insert[j] << " ";
                    red_black_tree.insert(to_insert[j] , file_name);
                }
                // If it is already present then insert this into next pointer of HybridNode
                // else {
                //     int flag = 0;
                //     HybridNode* temp = ss;
                //     while (temp != nullptr) {
                //         if (temp->getElement() == file_name) {
                //             flag = 1;
                //         }
                //         temp = temp->getNext();
                //     }
                //     if (flag == 0) {
                //         HybridNode* new_node = new HybridNode(to_insert[j] , file_name);
                //         temp = new_node;
                //     }
                // }

                // IMPLEMENTSTING INTO HASH TABLE for O(1) search
                //cout << hash << " ";
                int hash = ht.computeHash(to_insert[j] , 0);
                if (ht.hashTable[hash] == nullptr) {
                    vector<pair<string,int>> vec1;
                    pair<string,int> pair1(file_name , 1);
                    vec1.push_back(pair1);
                    IndexEntry* ie = new IndexEntry(to_insert[j]);
                    ie->setChapterWordCounts(vec1);
                    ht.hashTable[hash] = ie;
                    // cout << "Inserted a new IndexEntry" << endl;
                }
                else {
                    int flag = 0;
                    IndexEntry* ie = ht.hashTable[hash];
                    vector<pair<string,int>> vec1 = ie->getChapterWordCounts();
                    // cout << vec1.size();
                    for (int i=0; i<vec1.size(); i++) {
                        if (vec1[i].first == file_name) {
                            vec1[i].second += 1;
                            // cout << "Occurence = (" << vec1[i].second << ")";
                            flag = 1;
                        }
                    }

                    if (flag == 0) {
                        pair<string,int> pair1(file_name , 1);
                        vec1.push_back(pair1);
                    }
                    ie->setChapterWordCounts(vec1);
                    // cout << "Updated existing IndexEntry ";
                    // cout << "Vector Size = (" << vec1.size() << ")" << endl;
                }
            }
        }
        // cout << number_of_chapters << endl;

        vector<HybridNode*> vec;
        vec = red_black_tree.preOrderTraversal(red_black_tree.getRoot() , 15);

        vector<string> all_uwords;
        for (int i=0; i<vec.size(); i++) {
            all_uwords.push_back(vec[i]->getKey());
        }
        for (int i=0; i<all_uwords.size(); i++) {
            // cout << "[" << i << "]" << endl;
            // cout << "Vector Size = " << red_black_tree.inOrderTraversal().size() << endl;
            int hash = ht.computeHash(all_uwords[i], 1);
            int chaps = ht.hashTable[hash]->getChapterWordCounts().size();
            // cout << all_uwords[i] << " & " << chaps << endl;
            // cout << chaps << endl;
            if (chaps == number_of_chapters) {
                red_black_tree.deleteNode(all_uwords[i]);
                // cout << "DELETED SUCCESSFULLY" << endl;
            }
        }
        // Process words from a chapter and update the Red-Black Tree
        // chapter_names is a vector of chapter names
    }

    vector<IndexEntry> buildIndex() {
        // vector<HybridNode*> vec;
        // vec = red_black_tree.preOrderTraversal(red_black_tree.getRoot() , 15);

        // vector<string> all_uwords;
        // for (int i=0; i<vec.size(); i++) {
        //     all_uwords.push_back(vec[i]->getKey());
        // }


        // cout << vec.size() << endl;
        // cout << "*******************" << endl;
        // red_black_tree.deleteNode("a");
        // cout << "*******************" << endl;
        // red_black_tree.deleteNode("all");
        // cout << "*******************" << endl;
        // cout << vec.size() << endl;


        // for (int i=0; i<all_uwords.size(); i++) {
        //     // cout << "[" << i << "]" << endl;
        //     // cout << "Vector Size = " << red_black_tree.inOrderTraversal().size() << endl;
        //     int hash = ht.computeHash(all_uwords[i], 1);
        //     int chaps = ht.hashTable[hash]->getChapterWordCounts().size();
        //     // cout << all_uwords[i] << " & " << chaps << endl;
        //     // cout << chaps << endl;
        //     if (chaps == number_of_chapters) {
        //         red_black_tree.deleteNode(all_uwords[i]);
        //         // cout << "DELETED SUCCESSFULLY" << endl;
        //     }
        // }
        
        vector<HybridNode*> result_vec;
        result_vec = red_black_tree.inOrderTraversal();
        // for (int i=0; i<result_vec.size(); i++) {
        //     cout << result_vec[i]->getKey() << " ";
        // }
        // cout <<  "Final Size = " <<result_vec.size() << endl;

        vector<IndexEntry> ie_final;
        for (int i=0; i<result_vec.size(); i++) {
            IndexEntry ie = IndexEntry(result_vec[i]->getKey());
            int hash = ht.computeHash(result_vec[i]->getKey() , 1);
            IndexEntry* ie12345 = ht.hashTable[hash];
            vector<pair<string,int>> vec1 = ie12345->getChapterWordCounts();
            ie.setChapterWordCounts(vec1);
        }
        // HybridNode* hn = red_black_tree.search("once");
        // cout << 

        return ie_final;

        // Build the index using the remaining words in the Red-Black Tree
    }
};

// int main() {
//     vector<int> integer1;
//     integer1.push_back(1);
//     integer1.push_back(3);
//     integer1.push_back(5);
//     integer1.push_back(7);

//     vector<int> copy_integer1;
//     for (int i=0; i<integer1.size(); i++) {
//         copy_integer1.push_back(integer1[i]);
//     }
//     for (int i=0; i<copy_integer1.size(); i++) {
//         cout << copy_integer1[i] << endl;
//     }
//     // Testing insertion in red-black tree
//     RedBlackTree rbtree;
//     rbtree.insert("f", "cha1");
//     rbtree.insert("j", "cha1");
//     rbtree.insert("c", "cha1");
//     rbtree.insert("w", "cha1");
//     rbtree.insert("k", "cha1");
//     rbtree.insert("a", "cha1");
//     rbtree.insert("z", "cha1");
//     cout << rbtree.getRoot()->getColor() << endl;
//     cout << rbtree.getRoot()->getLeftChild()->getColor() << endl;
//     cout << rbtree.getRoot()->getRightChild()->getColor() << endl;
//     cout << rbtree.getRoot()->getRightChild()->getRightChild()->getColor() << endl;
//     cout << rbtree.getRoot()->getRightChild()->getRightChild()->getRightChild()->getColor() << endl;
//     cout << rbtree.getRoot()->getRightChild()->getLeftChild()->getColor() << endl;
//     cout << rbtree.getRoot()->getLeftChild()->getLeftChild()->getColor() << endl;
//     HybridNode* ser = rbtree.search("c");
//     cout << ser->getParent()->getKey() << endl;
//     cout << rbtree.blackheight(ser) << endl;
//     cout << "##################################" << endl;
    
//     RedBlackTree rbtree_1;
    
//     rbtree_1.insert("once", "cha1");
//     rbtree_1.insert("upon", "cha1");
//     rbtree_1.insert("a", "cha1");
//     rbtree_1.insert("time", "cha1");
//     rbtree_1.insert("there", "cha1");
//     rbtree_1.insert("was", "cha1");
//     rbtree_1.insert("curious", "cha1");
//     rbtree_1.insert("boy", "cha1");
//     rbtree_1.insert("his", "cha1");
//     rbtree_1.insert("name", "cha1");
//     rbtree_1.insert("tim", "cha1");
//     rbtree_1.insert("he", "cha1");
//     rbtree_1.insert("lived", "cha1");
//     rbtree_1.insert("in", "cha1");
//     rbtree_1.insert("small", "cha1");
//     rbtree_1.insert("town", "cha1");
//     rbtree_1.insert("always", "cha1");
//     rbtree_1.insert("looking", "cha1");
//     rbtree_1.insert("for", "cha1");
//     rbtree_1.insert("something", "cha1");
//     rbtree_1.insert("exciting", "cha1");
//     rbtree_1.insert("to", "cha1");
//     rbtree_1.insert("do", "cha1");
//     rbtree_1.insert("would", "cha1");
//     rbtree_1.insert("explore", "cha1");
//     rbtree_1.deleteNode("upon");
//     cout << rbtree_1.getRoot()->getRightChild()->getRightChild()->getLeftChild()->getLeftChild()->getKey() << endl;
//     cout << "Success" << endl;
//     cout << "##################################" << endl;

//     // Testing readChapters
//     Lexicon* lex = new Lexicon();
//     vector<string> chap;
//     chap.push_back("Chapter1.txt");
//     chap.push_back("Chapter2.txt");
//     chap.push_back("Chapter3.txt");
//     lex->readChapters(chap);
//     cout << "CheckPoint" << endl;
//     vector<IndexEntry> lmn = lex->buildIndex();
//     cout << lex->getRedBlackTree().getRoot()->getKey() <<endl;
//     // cout << "Number of unique words before deleation : " <<lex->getRedBlackTree().preOrderTraversal(lex->getRedBlackTree().getRoot() , 11).size() << endl;
//     cout <<"##################################" << endl;
//     return 0;
// }