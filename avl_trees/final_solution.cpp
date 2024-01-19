#include<bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
using namespace std;



// Forward declarations
class MetroStop;
class MetroLine;
class AVLNode;

// MetroStop class
class MetroStop {
private:
    std::string stopName;
    MetroStop* nextStop;
    MetroStop* prevStop;
    MetroLine* line;
    int fare;

public:
    MetroStop(std::string name, MetroLine* metroLine, int fare);

    // Getter methods
    std::string getStopName() const;
    MetroStop* getNextStop() const;
    MetroStop* getPrevStop() const;
    MetroLine* getLine() const;
    int getFare() const;

    // Setter methods
    void setNextStop(MetroStop* next);
    void setPrevStop(MetroStop* prev);
};

MetroStop::MetroStop(std::string name, MetroLine* metroLine, int fare) {
    stopName = name;
    nextStop = nullptr;
    prevStop = nullptr;
    line = metroLine;
    this->fare = fare;
}

std::string MetroStop::getStopName() const {
    return stopName;
}

MetroStop* MetroStop::getNextStop() const {
    return nextStop;
}

MetroStop* MetroStop::getPrevStop() const {
    return prevStop;
}

MetroLine* MetroStop::getLine() const {
    return line;
}

int MetroStop::getFare() const {
    return fare;
}

void MetroStop::setNextStop(MetroStop* next) {
    nextStop = next;
}

void MetroStop::setPrevStop(MetroStop* prev) {
    prevStop = prev;
}

// MetroLine class
class MetroLine {
private:
    std::string lineName;
    MetroStop* node;

public:
    MetroLine(std::string name);

    // Getter methods
    std::string getLineName() const;
    MetroStop* getNode() const;

    // Setter methods
    void setNode(MetroStop* node);

    void populateLine(std::string filename);

    // helper function
    void printLine() const;
    int getTotalStops() const;
};

MetroLine::MetroLine(std::string name) {
    lineName = name;
    node = nullptr;
}

std::string MetroLine::getLineName() const {
    return lineName;
}

MetroStop* MetroLine::getNode() const {
    return node;
}

void MetroLine::setNode(MetroStop* node) {
    this->node = node;
}

void MetroLine::printLine() const {
    MetroStop* stop = node;
    while (stop != nullptr) {
        cout << stop->getStopName() << endl;
        stop = stop->getNextStop();
    }
}

int MetroLine::getTotalStops() const {
    int i = 0;
    MetroStop* current = node;
    while (current != nullptr){
        i++;
        current = current->getNextStop();
    }
    return i;
}

void MetroLine::populateLine(std::string filename) {
    ifstream file;
    file.open(filename);
    string line;
    if (!file){
        cout << "File doesn't exist [OR] it isn't open";
    }
    else {
        MetroStop* current = node;
        MetroStop* prev = nullptr;
        while (getline(file, line)){
            string stop;
            string fare;

            int count = 0;
            for (int i=0; i<line.size(); i++){
                char s = line[i];
                if (s == ' '){
                    count++;
                }
            }

            int temp = 0;
            for (int i=0; i<line.size(); i++){
                char s = line[i];
                if (s == ' '){
                    temp++;
                }
                if (temp < count){
                    stop+=s;
                }
                else {
                    if (s != ','){
                        fare+=s;
                    }
                }
            }
            int int_fare = stoi(fare);
            // cout << stop << " " << int_fare << endl;

            // Making a Doubly Linked List
            MetroStop* ms = new MetroStop(stop, this, int_fare);
            if (node == nullptr) {
                node = ms;
                current = ms;
                continue;
            }
            while(current != nullptr) {
                prev = current;
                current = current->getNextStop();
            }
            if (current == nullptr) {
                prev->setNextStop(ms);
                ms->setPrevStop(prev);
                current = ms;
            }
        }
        // cout << node->getNextStop()->getNextStop()->getPrevStop()->getStopName();
    }
}


// AVLNode class
class AVLNode {
private:
    std::string stopName;
    std::vector<MetroStop*> stops;
    AVLNode* left;
    AVLNode* right;
    AVLNode* parent;

public:
    AVLNode(std::string name);

    // Getter methods
    std::string getStopName() const;
    const std::vector<MetroStop*>& getStops() const;
    AVLNode* getLeft() const;
    AVLNode* getRight() const;
    AVLNode* getParent() const;

    // Setter methods
    void addMetroStop(MetroStop* metroStop);
    void setLeft(AVLNode* left);
    void setRight(AVLNode* right);
    void setParent(AVLNode* parent);
};

AVLNode::AVLNode(std::string name) {
    stopName = name;
    left = nullptr;
    right = nullptr;
}

std::string AVLNode::getStopName() const {
    return stopName;
}

const std::vector<MetroStop*>& AVLNode::getStops() const {
    return stops;
}

AVLNode* AVLNode::getLeft() const {
    return left;
}

AVLNode* AVLNode::getRight() const {
    return right;
}

AVLNode* AVLNode::getParent() const {
    return parent;
}

void AVLNode::setLeft(AVLNode* left) {
    this->left = left;
}

void AVLNode::setRight(AVLNode* right) {
    this->right = right;
}

void AVLNode::setParent(AVLNode* parent) {
    this->parent = parent;
}

void AVLNode::addMetroStop(MetroStop* metroStop) {
    stops.push_back(metroStop);
}

// AVLTree class
class AVLTree {
    // Define your AVLTree implementation here.
private:
    AVLNode* root;

public:
    // getter methods
    AVLNode* getRoot() const;

    // setter methods
    void setRoot(AVLNode* root);

    // helper functions
    int height(AVLNode* node);
    int balanceFactor(AVLNode* node);
    void rotateLeft(AVLNode* node);
    void rotateRight(AVLNode* node);
    void balance(AVLNode* node, MetroStop*);
    int stringCompare(string s1, string s2);
    void insert(AVLNode* node, MetroStop* metroStop);
    void populateTree(MetroLine* metroLine);
    void inOrderTraversal(AVLNode* node);
    int getTotalNodes(AVLNode* node);
    AVLNode* searchStop(string stopName);
};

AVLNode* AVLTree::getRoot() const {
    return root;
}

void AVLTree::setRoot(AVLNode* root) {
    this->root = root;
}

int AVLTree::height(AVLNode* node) {
    int height_tree = 0;
    if (node != nullptr){
        int left_height = 0;
        int right_height = 0;
        if (node->getLeft() != nullptr) {
            left_height = height(node->getLeft());
        }
        if (node->getRight() != nullptr) {
            right_height = height(node->getRight());
        }
        height_tree = max(left_height, right_height);
        height_tree +=1;
    }
    return height_tree;
}

int AVLTree::stringCompare(string s1, string s2) {
    // use strcmp

    char *c1 = new char[s1.length() + 1];
    strcpy(c1, s1.c_str());

    char *c2 = new char[s2.length() + 1];
    strcpy(c2, s2.c_str());

    int result = strcmp(c1, c2);
    return result;
}

int AVLTree::balanceFactor(AVLNode* node) {
    int bf = 0;
    bf = height(node->getLeft()) - height(node->getRight());
    return bf;
}

// void AVLTree::rotateLeft(AVLNode* node) {
//     AVLNode* new_root = node->getRight();
//     node->setRight(new_root->getRight());
//     if (new_root->getLeft() != nullptr) {
//         new_root->getLeft()->setParent(node);
//     }
//     new_root->setLeft(node);
//     new_root->setParent(node->getParent());
//     node->setParent(new_root);
//     if (node == root) {
//         root = new_root;
//     }
//     else {
//         if (new_root->getParent()->getLeft() == node) {
//             new_root->getParent()->setLeft(new_root);
//         }
//         else {
//             new_root->getParent()->setRight(new_root);
//         }
//     }
//     cout << " Left Rotate Success ";
// }

void AVLTree::rotateLeft(AVLNode* node) {
    AVLNode* new_root = node->getRight();
    node->setRight(new_root->getLeft());
    if (new_root->getLeft() != nullptr) {
        new_root->getLeft()->setParent(node);
    }
    new_root->setLeft(node);
    new_root->setParent(node->getParent());
    node->setParent(new_root);
    if (node == root) {
        root = new_root;
    }
    else {
        if (new_root->getParent()->getLeft() == node) {
            new_root->getParent()->setLeft(new_root);
        }
        else {
            new_root->getParent()->setRight(new_root);
        }
    }
    // cout << " Left Rotate Success ";
}

void AVLTree::rotateRight(AVLNode* node) {
    AVLNode* new_root = node->getLeft();
    node->setLeft(new_root->getRight());
    if (new_root->getRight() != nullptr) {
        new_root->getRight()->setParent(node);
    }
    new_root->setRight(node);
    new_root->setParent(node->getParent());
    node->setParent(new_root);
    if (node == root) {
        root = new_root;
    }
    else {
        if (new_root->getParent()->getLeft() == node) {
            new_root->getParent()->setLeft(new_root);
        }
        else {
            new_root->getParent()->setRight(new_root);
        }
    }
    // cout << " Right Rotate Success ";
}

void AVLTree::balance(AVLNode* node, MetroStop* metroStop) {
    int bf = balanceFactor(node);
    // cout << " " << bf << " ";
    // For LL and LR
    if (bf > 1) {
        // LL Case
        if (stringCompare(node->getLeft()->getStopName() , metroStop->getStopName()) > 0){
            rotateRight(node);
        }
        // LR Case
        else if (stringCompare(node->getLeft()->getStopName() , metroStop->getStopName()) < 0){
            rotateLeft(node->getLeft());
            rotateRight(node);
        }
    }
    // For RL and RR
    else if (bf < -1) {
        // RR Case
        if (stringCompare(node->getRight()->getStopName() , metroStop->getStopName()) < 0){
            rotateLeft(node);
        }
        else if (stringCompare(node->getRight()->getStopName() , metroStop->getStopName()) > 0){
            rotateRight(node->getRight());
            rotateLeft(node);

        }
    }
}

void AVLTree::insert(AVLNode* node, MetroStop* metroStop) {
    // BinaryTreeNode* w = nullptr;
    // BinaryTreeNode* v = root;
    // while(v!=nullptr){
    //     w = v;
    //     if (stringCompare(v->getStopName() , metroStop->getStopName()) == 0) {
    //         v->addMetroStop(metroStop);
    //     }
    //     else if(stringCompare(v->getStopName() , metroStop->getStopName()) > 0){
    //         v = v->getLeft();
    //     }
    //     else{
    //         v =v->getRightPtr();
    //     }
    // }
    // node->setParentPtr(w);
    // if (key <= w->getDepartureTime()) {
    //     w->setLeftPtr(node);
    // }
    // else {
    //     w->setRightPtr(node);
    // }

    // if (node) {
    //     cout << "[" << stringCompare(node->getStopName() , metroStop->getStopName()) << "]";
    // }
    // else {
    //     cout << "*NULL*";
    // }
    // if (node == nullptr) {
    //     node = new AVLNode(metroStop->getStopName());
    //     node->addMetroStop(metroStop);
    //     return;
    // }
    if(stringCompare(node->getStopName() , metroStop->getStopName()) == 0) {
        node->addMetroStop(metroStop);
        // cout << "(ADDED)";
        return;
    }
    else if (stringCompare(node->getStopName() , metroStop->getStopName()) > 0){
        if (node->getLeft() == nullptr) {
            node->setLeft(new AVLNode(metroStop->getStopName()));
            node->getLeft()->addMetroStop(metroStop);
            node->getLeft()->setParent(node);
            // cout << "(INSERTED)";
        }
        else {
            insert(node->getLeft(), metroStop);
        }
        // node->getLeft()->setParent(node);
    }
    else {
        if (node->getRight() == nullptr) {
            node->setRight(new AVLNode(metroStop->getStopName()));
            node->getRight()->addMetroStop(metroStop);
            node->getRight()->setParent(node);
            // cout << "(INSERTED)";
        }
        else {
            insert(node->getRight(), metroStop);
        }
        //node->getRight()->setParent(node);
    }
    balance(node, metroStop);
    // cout << "(COOL)";
}

void AVLTree::populateTree(MetroLine* metroLine) {
    MetroStop* ms = metroLine->getNode();
    while (ms != nullptr) {
        // AVLNode* tree_node = new AVLNode(ms->getStopName());
        insert(root, ms);
        // if (ms->getNextStop() == nullptr) {
        //     cout << endl << " xxxxxxxxx " << endl;
        // }
        ms = ms->getNextStop();
    }
}

void AVLTree::inOrderTraversal(AVLNode* node) {
    if (node == nullptr) {
        return;
    }
    inOrderTraversal(node->getLeft());
    cout << node->getStopName() << endl;
    inOrderTraversal(node->getRight());
}

int AVLTree::getTotalNodes(AVLNode* node) {
    if (node == nullptr) {
        return 0;
    }
    return 1 + getTotalNodes(node->getLeft()) + getTotalNodes(node->getRight());
}

AVLNode* AVLTree::searchStop(string stopName) {
    AVLNode* node = root;
    while (node != nullptr) {
        if (stringCompare(stopName, node->getStopName()) == 0) {
            return node;
        }
        else if (stringCompare(stopName, node->getStopName()) < 0) {
            node = node->getLeft();
        }
        else {
            node = node->getRight();
        }
    }
    return nullptr;
}

// Trip class
class Trip {
private:
    MetroStop* node;
    Trip* prev;

public:
    Trip(MetroStop* metroStop, Trip* previousTrip);

    void setNode(MetroStop* replace_node);

    // Getter methods
    MetroStop* getNode() const;
    Trip* getPrev() const;
};

Trip::Trip(MetroStop* metroStop, Trip* previousTrip) {
    node = metroStop;
    prev = previousTrip;
}

MetroStop* Trip::getNode() const {
    return node;
}

Trip* Trip::getPrev() const {
    return prev;
}

void Trip::setNode(MetroStop* replace_node) {
    node = replace_node;
}

// Exploration class is a queue that stores unexplored Trip objects
class Exploration {
private:

    std::queue<Trip*> trips;

public:
    Exploration();

    // Getter methods
    std::queue<Trip*> getTrips() const;

    // Setter methods
    void enqueue(Trip* trip);
    Trip* dequeue();
    bool isEmpty() const;
};

Exploration::Exploration() {
}

std::queue<Trip*> Exploration::getTrips() const {
    return trips;
}

void Exploration::enqueue(Trip* trip) {
    trips.push(trip);
}

Trip* Exploration::dequeue() {
    if (trips.empty()) {
        return nullptr;
    }
    Trip* trip = trips.front();
    trips.pop();
    cout << "Dequeued: " << trip->getNode()->getStopName() << endl;
    return trip;
}

bool Exploration::isEmpty() const {
    return trips.empty();
}

class Path {
private:
    std::vector<MetroStop*> stops;
    int totalFare;

public:
    Path();

    // Getter methods
    std::vector<MetroStop*> getStops() const;
    int getTotalFare() const;

    // Setter methods
    void addStop(MetroStop* stop);
    void setTotalFare(int fare);

    // helper functions
    void printPath() const;
};

Path::Path() {
    totalFare = 0;
}

std::vector<MetroStop*> Path::getStops() const {
    return stops;
}

int Path::getTotalFare() const {
    return totalFare;
}

void Path::addStop(MetroStop* stop) {
    stops.push_back(stop);
}

void Path::setTotalFare(int fare) {
    totalFare = fare;
}

void Path::printPath() const {
    for (auto stop : stops) {
        cout << stop->getStopName() << endl;
    }
}

// PathFinder class
class PathFinder {
private:
    AVLTree* tree;
    std::vector<MetroLine*> lines;

public:
    PathFinder(AVLTree* avlTree, const std::vector<MetroLine*>& metroLines);
    void createAVLTree();
    Path* findPath(std::string origin, std::string destination);
    int traverse(Exploration* explo, Trip* trip, string trip_origin, string destination, Path* path_found);
    void compute_path(Trip* trip, Path* path_found);
    void compute_fare(Trip* trip, Path* path_found);

    // Getter methods
    AVLTree* getTree() const;
    const std::vector<MetroLine*>& getLines() const;
};

PathFinder::PathFinder(AVLTree* avlTree, const std::vector<MetroLine*>& metroLines) {
    tree = avlTree;
    lines = metroLines;
}

AVLTree* PathFinder::getTree() const {
    return tree;
}

const std::vector<MetroLine*>& PathFinder::getLines() const {
    return lines;
}

void PathFinder::createAVLTree() {
    // AVLTree* avl_tree = new AVLTree();
    // avl_tree->setRoot(nullptr);
    for (auto line : lines) {
        if (tree->getRoot() == nullptr) {
            tree->setRoot(new AVLNode(line->getNode()->getStopName()));
        }
        tree->populateTree(line);
    }
    // cout << "Height of tree: " << tree->height(tree->getRoot()) << endl;
    // cout << "Total nodes in tree: " << tree->getTotalNodes(tree->getRoot()) << endl;
    // assert(tree->height(tree->getRoot()) == 9);
    // assert(tree->getTotalNodes(tree->getRoot()) == 211);
}

void PathFinder::compute_path(Trip* trip, Path* path_found) {
    vector<MetroStop*> vec;
    while (trip->getPrev() != nullptr) {
        // cout << endl;
        string trip_origin;
        trip_origin = trip->getPrev()->getNode()->getStopName();
        MetroStop* ms = trip->getNode();
        MetroStop* test = ms;
        int flag=0;
        while (test != nullptr) {
            if (test->getStopName() == trip_origin) {
                flag = 1;
                break;
            }
            test = test->getNextStop();
        }
        // cout << flag << endl;
        if (flag == 1) {
            while (ms != nullptr) {
                if (ms->getStopName() == trip_origin) {
                    break;
                }
                vec.push_back(ms);
                ms = ms->getNextStop();
            }
        }
        else {
            while (ms != nullptr) {
                if (ms->getStopName() == trip_origin) {
                    break;
                }
                vec.push_back(ms);
                ms = ms->getPrevStop();
            }
        }
        trip = trip->getPrev();
    }
    vec.push_back(trip->getNode());
    // cout << vec.size() << endl;
    // for (int i=0; i<vec.size(); i++) {
    //     cout << vec[i]->getStopName() << endl;
    // }
    // cout << endl;

    vector<MetroStop*> reverse_vec;
    for (int i=0; i<vec.size(); i++) {
        reverse_vec.push_back(vec[vec.size()-1-i]);
    }

    for (int i=0; i<vec.size(); i++) {
        path_found->addStop(vec[i]);
    }
    // path_found->printPath();

    // cout << endl;
}

void PathFinder::compute_fare(Trip* trip, Path* path_found) {
    vector<MetroStop*> vec;
    while (trip->getPrev() != nullptr) {
        // cout << endl;
        string trip_origin;
        trip_origin = trip->getPrev()->getNode()->getStopName();
        MetroStop* ms = trip->getNode();
        MetroStop* test = ms;
        int flag=0;
        while (test != nullptr) {
            if (test->getStopName() == trip_origin) {
                flag = 1;
                break;
            }
            test = test->getNextStop();
        }
        // cout << flag << endl;
        if (flag == 1) {
            while (ms != nullptr) {
                vec.push_back(ms);
                if (ms->getStopName() == trip_origin) {
                    break;
                }
                ms = ms->getNextStop();
            }
        }
        else {
            while (ms != nullptr) {
                vec.push_back(ms);
                if (ms->getStopName() == trip_origin) {
                    break;
                }
                ms = ms->getPrevStop();
            }
        }
        trip = trip->getPrev();
    }
    vec.push_back(trip->getNode());
    // cout << "START" << endl;
    // for (int i=0; i<vec.size(); i++) {
    //     cout << vec[i]->getStopName() << endl;
    // }
    // cout << "STOP" << endl;


    // vector<MetroStop*> vec;
    // vec = path_found->getStops();
    int total_fare = 0;
    for (int i=0; i<vec.size()-1; i++) {
        string line_name = vec[i]->getLine()->getLineName();
        // cout << line_name;
        for (int j=0; j<tree->searchStop(vec[i+1]->getStopName())->getStops().size(); j++){

            if (tree->searchStop(vec[i+1]->getStopName())->getStops()[j]->getLine()->getLineName() == line_name){
                int comp_fare = 0;
                comp_fare = abs(vec[i]->getFare() - tree->searchStop(vec[i+1]->getStopName())->getStops()[j]->getFare());
                total_fare += comp_fare;
                // cout << comp_fare << endl;
            }
        }
    }
    path_found->setTotalFare(total_fare);
    // cout << path_found->getTotalFare() << endl;
}

int PathFinder::traverse(Exploration* explo, Trip* trip, string trip_origin, string destination, Path* path_found) {
    // cout << "TRAVERSING" << endl;
    MetroStop* ms = trip->getNode();
    MetroStop* test = ms;
    int flag = 0;
    if (trip->getPrev() != nullptr) {
        // cout << trip->getPrev()->getNode()->getStopName() << endl;
        trip_origin = trip->getPrev()->getNode()->getStopName();
    }
    while (test != nullptr) {
        if (test->getStopName() == trip_origin) {
            flag = 1;
            break;
        }
        test = test->getNextStop();
    }
    // cout << flag << endl;

    while (ms != nullptr) {
        if (ms->getStopName() == destination) {
            // cout << "WE WIN " << endl;
            Trip* check_trip = trip;
            // while (check_trip != nullptr) {
            //     cout << check_trip->getNode()->getStopName() << endl;
            //     check_trip = check_trip->getPrev();
            // }
            compute_path(trip, path_found);
            compute_fare(trip, path_found);
            return 1;
        }
        else if (tree->searchStop(ms->getStopName())->getStops().size() > 1) {
            // cout << tree->searchStop(ms->getStopName())->getStops().size() << " " << ms->getStopName() << endl;
            // for (int i=0; i<tree->searchStop(ms->getStopName())->getStops().size(); i++) {
            //     cout << i << "idx: " << tree->searchStop(ms->getStopName())->getStops()[i]->getLine()->getLineName() << endl;
            //     if (tree->searchStop(ms->getStopName())->getStops()[i]->getLine()->getLineName() != ms->getLine()->getLineName()) {
            //         cout << "The above should be enqueued." << endl;
            //     }
            // }
            for (int i=0; i<tree->searchStop(ms->getStopName())->getStops().size(); i++) {
                // cout << "ms: " <<ms->getStopName() << endl;
                if (tree->searchStop(ms->getStopName())->getStops()[i]->getLine()->getLineName() != ms->getLine()->getLineName()) {
                    if (tree->searchStop(ms->getStopName())->getStops()[i]->getNextStop() != nullptr) {
                        // trip* new1 = new Trip()
                        Trip* new_trip = new Trip(ms, trip->getPrev());
                        Trip* tp1 = new Trip(tree->searchStop(ms->getStopName())->getStops()[i]->getNextStop() , new_trip);
                        explo->enqueue(tp1);
                        // cout << "Enqueued 1" << endl;
                    }
                    if (tree->searchStop(ms->getStopName())->getStops()[i]->getPrevStop() != nullptr) {
                        Trip* new_trip = new Trip(ms, trip->getPrev());
                        Trip* tp2 = new Trip(tree->searchStop(ms->getStopName())->getStops()[i]->getPrevStop() , new_trip);
                        explo->enqueue(tp2);
                        // cout << "Enqueued 2" << endl;
                    }
                }
            }
        }
        if (flag ==0) {
            ms = ms->getNextStop();
        }
        else {
            ms = ms->getPrevStop();
        }
        trip->setNode(ms);
    }

    // if (flag == 0) {
    //     while (ms != nullptr) {
    //         if (ms->getStopName() == destination) {
    //             cout << "WE WIN " << endl;
    //             Trip* check_trip = trip;
    //             while (check_trip != nullptr) {
    //                 cout << check_trip->getNode()->getStopName() << endl;
    //                 check_trip = check_trip->getPrev();
    //             }
    //             compute_path(trip, path_found);
    //             compute_fare(trip, path_found);
    //             return 1;
    //         }
    //         else if (tree->searchStop(ms->getStopName())->getStops().size() > 1) {
    //             cout << tree->searchStop(ms->getStopName())->getStops().size() << " " << ms->getStopName() << endl;
    //             // for (int i=0; i<tree->searchStop(ms->getStopName())->getStops().size(); i++) {
    //             //     cout << i << "idx: " << tree->searchStop(ms->getStopName())->getStops()[i]->getLine()->getLineName() << endl;
    //             //     if (tree->searchStop(ms->getStopName())->getStops()[i]->getLine()->getLineName() != ms->getLine()->getLineName()) {
    //             //         cout << "The above should be enqueued." << endl;
    //             //     }
    //             // }
    //             for (int i=0; i<tree->searchStop(ms->getStopName())->getStops().size(); i++) {
    //                 // cout << "ms: " <<ms->getStopName() << endl;
    //                 if (tree->searchStop(ms->getStopName())->getStops()[i]->getLine()->getLineName() != ms->getLine()->getLineName()) {
    //                     if (tree->searchStop(ms->getStopName())->getStops()[i]->getNextStop() != nullptr) {
    //                         // trip* new1 = new Trip()
    //                         Trip* new_trip = new Trip(ms, trip->getPrev());
    //                         Trip* tp1 = new Trip(tree->searchStop(ms->getStopName())->getStops()[i]->getNextStop() , new_trip);
    //                         explo->enqueue(tp1);
    //                         cout << "Enqueued 1" << endl;
    //                     }
    //                     if (tree->searchStop(ms->getStopName())->getStops()[i]->getPrevStop() != nullptr) {
    //                         Trip* new_trip = new Trip(ms, trip->getPrev());
    //                         Trip* tp2 = new Trip(tree->searchStop(ms->getStopName())->getStops()[i]->getPrevStop() , new_trip);
    //                         explo->enqueue(tp2);
    //                         cout << "Enqueued 2" << endl;
    //                     }
    //                 }
    //             }
    //         }
    //         ms = ms->getNextStop();
    //         trip->setNode(ms);
    //     }
    // }
    // else {
    //     while (ms != nullptr) {
    //         if (ms->getStopName() == destination) {
    //             cout << "WE WIN " << endl;
    //             Trip* check_trip = trip;
    //             while (check_trip != nullptr) {
    //                 cout << check_trip->getNode()->getStopName() << endl;
    //                 check_trip = check_trip->getPrev();
    //             }
    //             compute_path(trip, path_found);
    //             compute_fare(trip, path_found);
    //             return 1;
    //         }
    //         else if (tree->searchStop(ms->getStopName())->getStops().size() > 1) {
    //             cout << tree->searchStop(ms->getStopName())->getStops().size() << " " << ms->getStopName() << endl;
    //             // for (int i=0; i<tree->searchStop(ms->getStopName())->getStops().size(); i++) {
    //             //     cout << i << "idx: " << tree->searchStop(ms->getStopName())->getStops()[i]->getLine()->getLineName() << endl;
    //             //     if (tree->searchStop(ms->getStopName())->getStops()[i]->getLine()->getLineName() != ms->getLine()->getLineName()) {
    //             //         cout << "The above should be enqueued." << endl;
    //             //     }
    //             // }
    //             for (int i=0; i<tree->searchStop(ms->getStopName())->getStops().size(); i++) {
    //                 // cout << "ms: " <<ms->getStopName() << endl;
    //                 if (tree->searchStop(ms->getStopName())->getStops()[i]->getLine()->getLineName() != ms->getLine()->getLineName()) {
    //                     if (tree->searchStop(ms->getStopName())->getStops()[i]->getNextStop() != nullptr) {
    //                         // trip* new1 = new Trip()
    //                         Trip* new_trip = new Trip(ms, trip->getPrev());
    //                         Trip* tp1 = new Trip(tree->searchStop(ms->getStopName())->getStops()[i]->getNextStop() , new_trip);
    //                         explo->enqueue(tp1);
    //                         cout << "Enqueued 1" << endl;
    //                     }
    //                     if (tree->searchStop(ms->getStopName())->getStops()[i]->getPrevStop() != nullptr) {
    //                         Trip* new_trip = new Trip(ms, trip->getPrev());
    //                         Trip* tp2 = new Trip(tree->searchStop(ms->getStopName())->getStops()[i]->getPrevStop() , new_trip);
    //                         explo->enqueue(tp2);
    //                         cout << "Enqueued 2" << endl;
    //                     }
    //                 }
    //             }
    //         }
    //         ms = ms->getPrevStop();
    //         trip->setNode(ms);
    //     }
    // }
    return 0;
}

Path* PathFinder::findPath(std::string origin, std::string destination) {
    Path* path_found = new Path();
    Exploration* explo = new Exploration();
    int num_lines = tree->searchStop(origin)->getStops().size();
    MetroStop* ms_origin = tree->searchStop(origin)->getStops()[0];
    Trip* trip_origin = new Trip(ms_origin, nullptr);
    if (num_lines == 1) {
        MetroStop* ms1 = tree->searchStop(origin)->getStops()[0];
        // ms1 = tree->searchStop(origin)->getStops()[0];
        if (ms1->getNextStop() != nullptr) {
            Trip* trip_1 = new Trip(ms1->getNextStop(), trip_origin);
            explo->enqueue(trip_1);
        }
        if (ms1->getPrevStop() != nullptr) {
            Trip* trip_2 = new Trip(ms1->getPrevStop(), trip_origin);
            explo->enqueue(trip_2);
        }
        // Trip* trip_1 = new Trip(ms1->getNextStop(), trip_origin);
        // Trip* trip_2 = new Trip(ms1->getPrevStop(), trip_origin);
        // explo->enqueue(trip_1);
        // explo->enqueue(trip_2);
        int check;
        string temp_origin;
        while (explo->isEmpty() == 0) {
            // cout << explo->getTrips().size();
            Trip* tp = explo->dequeue();
            // cout << tp->getNode()->getStopName() << endl;
            check = traverse (explo, tp, origin, destination, path_found);
            if (check == 1) {
                // cout << "DONE" << endl << endl;
                break;
            }
        }
    }
    else if (num_lines == 2) {
        MetroStop* ms1 = tree->searchStop(origin)->getStops()[0];
        MetroStop* ms2 = tree->searchStop(origin)->getStops()[1];
        if (ms1->getNextStop() != nullptr) {
            Trip* trip_1 = new Trip(ms1->getNextStop(), trip_origin);
            explo->enqueue(trip_1);
        }
        if (ms1->getPrevStop() != nullptr) {
            Trip* trip_2 = new Trip(ms1->getPrevStop(), trip_origin);
            explo->enqueue(trip_2);
        }
        if (ms2->getNextStop() != nullptr) {
            Trip* trip_3 = new Trip(ms2->getNextStop(), trip_origin);
            explo->enqueue(trip_3);
        }
        if (ms2->getPrevStop() != nullptr) {
            Trip* trip_4 = new Trip(ms2->getPrevStop(), trip_origin);
            explo->enqueue(trip_4);
        }
        int check;
        string temp_origin;
        while (explo->isEmpty() == 0) {
            // cout << explo->getTrips().size();
            Trip* tp = explo->dequeue();
            // cout << tp->getNode()->getStopName() << endl;
            check = traverse (explo, tp, origin, destination, path_found);
            if (check == 1) {
                // cout << "DONE" << endl << endl;
                break;
            }
        }
    }
    // path_found->printPath();
    // cout << path_found->getTotalFare() << endl;
    return path_found;
}

// int main() {
//     vector<MetroLine*> lines;

//     vector<string> filenames;
//     filenames.push_back("blue.txt");
//     filenames.push_back("green.txt");
//     filenames.push_back("magenta.txt");
//     filenames.push_back("orange.txt");
//     filenames.push_back("red.txt");
//     filenames.push_back("violet.txt");
//     filenames.push_back("yellow.txt");

//     for (int i = 0; i < filenames.size(); i++) {
//         string lineName = filenames[i].substr(0, filenames[i].length() - 4);
//         MetroLine* metroLine = new MetroLine(lineName);
//         metroLine->populateLine(filenames[i]);
//         lines.push_back(metroLine);
//         // cout << "Line name: " << metroLine->getLineName() << endl;
//         // cout << "Total stops: " << metroLine->getTotalStops() << endl;
//         // cout << endl;
//         // metroLine->printLine();
//     }
//     PathFinder* pf = new PathFinder(new AVLTree(), lines);
//     pf->createAVLTree();

//     // EXP :- 1
//     // AVLNode* sear = pf->getTree()->searchStop("Mandi House");
//     // cout << sear->getStops().size() << endl;
//     // OR
//     // cout << pf->getTree()->searchStop("Mandi House")->getStops().size() << endl;

//     // EXP :- 2
//     // AVLNode* asdf = pf->getTree()->searchStop("Inderlok");
//     // cout << "Size:" << asdf->getStops().size() << endl;
//     Path* path_found = pf->findPath("Shivaji Stadium", "Chirag Delhi");
//     cout << "Total Fare : " << path_found->getTotalFare();
//     return 0;
// }
