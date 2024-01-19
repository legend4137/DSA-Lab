#include <iostream>
#include <vector>
#include <map>
using namespace std;

class Vehicle;

class Trip {
public:
    Trip(Vehicle* vehicle, std::string pick_up_location, std::string drop_location, int departure_time)
        : vehicle(vehicle), pick_up_location(pick_up_location), drop_location(drop_location), departure_time(departure_time), booked_seats(0) {}

    // Getter functions
    Vehicle* getVehicle() const {
        return vehicle;
    }

    std::string getPickUpLocation() const {
        return pick_up_location;
    }

    std::string getDropLocation() const {
        return drop_location;
    }

    int getDepartureTime() const {
        return departure_time;
    }

    int getBookedSeats() const {
        return booked_seats;
    }

    // Setter functions
    void setVehicle(Vehicle* v) {
        vehicle = v;
    }

    void setPickUpLocation(std::string location) {
        pick_up_location = location;
    }

    void setDropLocation(std::string location) {
        drop_location = location;
    }

    void setDepartureTime(int time) {
        departure_time = time;
    }

    void setBookedSeats(int seats) {
        booked_seats = seats;
    }

private:
    Vehicle* vehicle;
    std::string pick_up_location;
    std::string drop_location;
    int departure_time;
    int booked_seats;
};

class BinaryTreeNode;

class TransportService {
public:
    TransportService(std::string name) : name(name), BSThead(nullptr) {}

    // Getter functions
    std::string getName() const {
        return name;
    }

    BinaryTreeNode* getBSTHead() const {
        return BSThead;
    }

    // Setter functions
    void setName(std::string service_name) {
        name = service_name;
    }

    void setBSTHead(BinaryTreeNode* node) {
        BSThead = node;
    }

    void addTrip(int key, Trip* trip);

private:
    std::string name;
    BinaryTreeNode* BSThead;
};

class BinaryTreeNode {
public:
    BinaryTreeNode(int departuretime = 0, Trip* tripenodeptr = nullptr, BinaryTreeNode* parentptr = nullptr)
        : leftptr(nullptr), rightptr(nullptr), parentptr(parentptr), departuretime(departuretime), tripnodeptr(tripenodeptr) {}

    // Getter functions
    BinaryTreeNode* getLeftPtr() const {
        return leftptr;
    }

    BinaryTreeNode* getRightPtr() const {
        return rightptr;
    }

    BinaryTreeNode* getParentPtr() const {
        return parentptr;
    }

    int getDepartureTime() const {
        return departuretime;
    }

    Trip* getTripNodePtr() const {
        return tripnodeptr;
    }

    // Setter functions
    void setLeftPtr(BinaryTreeNode* left) {
        leftptr = left;
    }

    void setRightPtr(BinaryTreeNode* right) {
        rightptr = right;
    }

    void setParentPtr(BinaryTreeNode* parent) {
        parentptr = parent;
    }

    void setDepartureTime(int time) {
        departuretime = time;
    }

    void setTripNodePtr(Trip* trip) {
        tripnodeptr = trip;
    }

private:
    BinaryTreeNode* leftptr;
    BinaryTreeNode* rightptr;
    BinaryTreeNode* parentptr;
    int departuretime;
    Trip* tripnodeptr;
};

class Vehicle {
public:
    Vehicle(std::string vehicle_number, int seating_capacity)
        : vehicle_number(vehicle_number), seating_capacity(seating_capacity) {}

    // Getter functions
    std::string getVehicleNumber() const {
        return vehicle_number;
    }

    int getSeatingCapacity() const {
        return seating_capacity;
    }

    const std::vector<Trip*>& getTrips() const {
        return trips;
    }

    // Setter functions
    void setVehicleNumber(std::string number) {
        vehicle_number = number;
    }

    void setSeatingCapacity(int capacity) {
        seating_capacity = capacity;
    }

    void addTrip(Trip* trip) {
        trips.push_back(trip);
    }

private:
    std::string vehicle_number;
    int seating_capacity;
    std::vector<Trip*> trips;
};

class Location {
public:
    Location(std::string name) : name(name) {}

    // Getter functions
    std::string getName() const {
        return name;
    }

    TransportService* getServicePtr(std::string droplocation) const {
        for (int i=0; i<serviceptrs.size(); i++){
            if (serviceptrs[i]->getName() == droplocation){
                return serviceptrs[i];
            }
        }
        return nullptr;
    }

    vector<TransportService*> getVectorTS(){
        return serviceptrs;
    }

    vector<Trip*> getVectorTrip(){
        return trips;
    }

    // Setter functions
    void setName(std::string location_name) {
        name = location_name;
    }

    TransportService* setServicePtr(std::string droplocation) {
        return nullptr;
    }

    void addTrip(Trip* trip) {
        trips.push_back(trip);
    }

    void addTransportService(TransportService* ts){
        serviceptrs.push_back(ts);
    }

private:
    std::string name;
    std::vector<TransportService*> serviceptrs;
    std::vector<Trip*> trips;
};

class BinaryTree {
protected:
    BinaryTreeNode* root;

public:
    BinaryTree() : root(nullptr) {}

    int getHeight() const {
        vector<BinaryTreeNode*> vec;
        int height = 0;
        vec.push_back(root);
        while (true) {
            int levelNodes = vec.size();

            if (levelNodes == 0) {
                return height;
            }

            height++;

            while (levelNodes > 0) {
                BinaryTreeNode* node = vec.front();
                vec.erase(vec.begin());
                if (node->getLeftPtr()) {
                    vec.push_back(node->getLeftPtr());
                }
                if (node->getRightPtr()) {
                    vec.push_back(node->getRightPtr());
                }
                levelNodes--;
            }
        }
        return 0; // Placeholder
    }

    int getNumberOfNodes() const {
        int count = 0;
        stack<BinaryTreeNode*> nodeStack;
        BinaryTreeNode* current = root;

        while (current != nullptr || nodeStack.empty() == 0) {
            while (current != nullptr) {
                nodeStack.push(current);
                current = current->getLeftPtr();
            }

            current = nodeStack.top();
            nodeStack.pop();

            count ++;

            current = current->getRightPtr();
        }
        return count; // Placeholder
    }
};

class BinarySearchTree : public BinaryTree {
public:
    BinarySearchTree() {}

    BinaryTreeNode* getElementWithMinimumKey() const {
        if (root == nullptr) {
            return nullptr;
        }

        BinaryTreeNode* current = root;
        while(current->getLeftPtr() != nullptr) {
            current = current->getLeftPtr();
        }
        return current; // Placeholder
    }

    BinaryTreeNode* getElementWithMaximumKey() const {
        if (root == nullptr) {
            return nullptr;
        }

        BinaryTreeNode* current = root;
        while(current->getRightPtr() != nullptr) {
            current = current->getRightPtr();
        }
        return current; // Placeholder
    }

    BinaryTreeNode* searchNodeWithKey(int key) const {

        BinaryTreeNode* current = root;

        while (current != nullptr) {
            if (current->getDepartureTime() == key) {
                return current;
            }
            else if (current->getDepartureTime() > key) {
                current = current->getLeftPtr();
            }
            else {
                current =current->getRightPtr();
            }
        }

        return nullptr; // Placeholder
    }

    BinaryTreeNode* getSuccessorNode(BinaryTreeNode* node) const {
        if (node == nullptr) {
            return nullptr;
        }

        if (node->getRightPtr() != nullptr){
            node = node->getRightPtr();
            while (node->getLeftPtr() != nullptr){
                node = node->getLeftPtr();
            }
            return node;
        }
        BinaryTreeNode* w = node->getParentPtr();
        while (w!=nullptr && node == w->getRightPtr()){
            node = w;
            w = w-> getParentPtr();
        }
        return w;
        // return nullptr; // Placeholder
    }

    BinaryTreeNode* getSuccessorNodeByKey(int key) const {
        BinaryTreeNode* current = root;

        while (current != nullptr) {
            if (current->getDepartureTime() == key) {
                break;
            }
            else if (current->getDepartureTime() > key) {
                current = current->getLeftPtr();
            }
            else {
                current =current->getRightPtr();
            }
        }

        if (current == nullptr) {
            return nullptr;
        }

        if (current->getRightPtr() != nullptr){
            current = current->getRightPtr();
            while (current->getLeftPtr() != nullptr){
                current = current->getLeftPtr();
            }
            return current;
        }
        BinaryTreeNode* w = current->getParentPtr();
        while (w!=nullptr && current == w->getRightPtr()){
            current = w;
            w = w-> getParentPtr();
        }
        return w;
        // return nullptr; // Placeholder
    }

    BinaryTreeNode* getPredecessorNode(BinaryTreeNode* node) const {
        if (node == nullptr) {
            return nullptr;
        }

        if (node->getLeftPtr() != nullptr){
            node = node->getLeftPtr();
            while (node->getRightPtr() != nullptr){
                node = node->getRightPtr();
            }
            return node;
        }
        BinaryTreeNode* w = node->getParentPtr();
        while (w!=nullptr && node == w->getLeftPtr()){
            node = w;
            w = w-> getParentPtr();
        }
        return w;
        // Implement this function to return the predecessor node of the given node
        // return nullptr; // Placeholder
    }

    BinaryTreeNode* getPredecessorNodeByKey(int key) const {
        BinaryTreeNode* current = root;

        while (current != nullptr) {
            if (current->getDepartureTime() == key) {
                break;
            }
            else if (current->getDepartureTime() > key) {
                current = current->getLeftPtr();
            }
            else {
                current =current->getRightPtr();
            }
        }

        if (current == nullptr) {
            return nullptr;
        }

        if (current->getLeftPtr() != nullptr){
            current = current->getLeftPtr();
            while (current->getRightPtr() != nullptr){
                current = current->getRightPtr();
            }
            return current;
        }
        BinaryTreeNode* w = current->getParentPtr();
        while (w!=nullptr && current == w->getLeftPtr()){
            current = w;
            w = w-> getParentPtr();
        }
        return w;
        // return nullptr; // Placeholder
    }
};

// Function to insert node into a BST
void insert_node(BinaryTreeNode* root, BinaryTreeNode* node,int key){
    BinaryTreeNode* w = nullptr;
    BinaryTreeNode* v = root;
    while(v!=nullptr){
        w = v;
        if(key <= v->getDepartureTime()){
            v = v->getLeftPtr();
        }
        else{
            v =v->getRightPtr();
        }
    }
    node->setParentPtr(w);
    if (key <= w->getDepartureTime()) {
        w->setLeftPtr(node);
    }
    else {
        w->setRightPtr(node);
    }
}

// Recursive Function to traverse through the BST and return vector of all the trip pointers such that key(departure time) lies int he range
vector<Trip*> pre_order_trips(BinaryTreeNode* root, int after_time, int before_time, vector<Trip*> tp){
    BinaryTreeNode* node = root;
    if (node->getDepartureTime() < before_time && node->getDepartureTime() >= after_time){
        Trip* temp = node->getTripNodePtr();
        tp.push_back(temp);
    }
    if (node->getLeftPtr() != nullptr){
        tp = pre_order_trips(node->getLeftPtr(), after_time, before_time, tp);
    }
    if (node->getRightPtr() != nullptr) {
        tp =pre_order_trips(node->getRightPtr(), after_time, before_time, tp);
    }
    return tp;
}

// Finding the minimum of a BST or a BST sub tree
BinaryTreeNode* minimum_key_node(BinaryTreeNode* root, BinaryTreeNode* node){
    while (node->getLeftPtr() != nullptr){
        node = node->getLeftPtr();
    }
    return node;
}

// Function to find the node with key just greater than the input key
BinaryTreeNode* successor_node(BinaryTreeNode* root, BinaryTreeNode* node){
    if (node->getRightPtr() != nullptr){
        return minimum_key_node(root, node);
    }
    BinaryTreeNode* w = node->getParentPtr();
    while (w!=nullptr && node==w->getRightPtr()){
        node = w;
        w = w->getParentPtr();
    }
    return w;
}

// Deleting a node from tree, taking all the 3 cases into consideration
void delete_node(BinaryTreeNode* root, BinaryTreeNode* node){
    BinaryTreeNode* w;
    if(node->getLeftPtr() == nullptr || node->getRightPtr() ==  nullptr){
        w = node;
    }
    else {
        w = successor_node(root,node);
    }
    BinaryTreeNode* v;
    if (w->getLeftPtr() != nullptr){
        v = w->getLeftPtr();
    }
    else {
        v = w->getRightPtr();
    }
    if (v != nullptr){
        v->setParentPtr(w->getParentPtr());
    }

    if(w->getParentPtr() == nullptr){
        root = v;
    }
    else if (w == w->getParentPtr()->getLeftPtr()){
        w->getParentPtr()->setLeftPtr(v);
    }
    else {
        w->getParentPtr()->setRightPtr(v);
    }
    if (w != node){
        node->setDepartureTime(w->getDepartureTime());
    }
}

class TravelDesk {
public:
    void addTrip(std::string vehicle_number, int seating_capacity, std::string pick_up_location, std::string drop_location, int departure_time) {
        // Checking if the vehicle already exists in the vehicles<vector> and finding the index if it exists
        int flag_v=0;
        int idx_v=0;
        for (int i=0; i<vehicles.size(); i++){
            if(vehicles[i]->getVehicleNumber() == vehicle_number){
                flag_v=1;
                idx_v=i;
            }
        }
        
        // Adding the vehicle if it doesn't exisit 
        if(flag_v==0){
            Vehicle* veh = new Vehicle(vehicle_number,seating_capacity);
            vehicles.push_back(veh);
            idx_v=vehicles.size()-1;
            // delete veh;
            // cout << "Successfully created new vehicle" << endl;
        }
        // Creating a Trip object to link it to the vehicle
        Trip* tp = new Trip(vehicles[idx_v], pick_up_location, drop_location, departure_time);
        vehicles[idx_v]->addTrip(tp);
        // Checking if the pickup location already exists in the locations<vector> and finding the index if it exists
        int flag_l=0;
        int idx_l=0;
        for (int i=0; i<locations.size(); i++){
            if(locations[i]->getName() == pick_up_location){
                flag_l=1;
                idx_l=i;
            }
        }
        // Adding the location if it doesn't exist and creating a Transport Service for the given
        if (flag_l==0) {
            Location* loc = new Location(pick_up_location);
            locations.push_back(loc);
            locations[locations.size()-1]->addTrip(tp);
            TransportService* ts = new TransportService(drop_location);
            locations[locations.size()-1]->addTransportService(ts);

            // Creating a new BST (head) for this location->TransportService->BSThead
            BinaryTreeNode* head = new BinaryTreeNode(departure_time, tp, nullptr);
            ts->setBSTHead(head);
            // delete loc;
            // delete ts;
            // delete head;
            // cout << "Successfully created new location, transport service and BST head"<< endl;
        }
        // Adding a node to the BST coresponding to a pick up location (from the services vector)
        else {
            int flag=0;
            vector<TransportService*> tsvec = locations[idx_l]->getVectorTS();
            for (int i=0; i<tsvec.size(); i++){
                if(tsvec[i]->getName() == drop_location){
                    BinaryTreeNode* root = tsvec[i]->getBSTHead();
                    BinaryTreeNode* tree_node = new BinaryTreeNode(departure_time, tp, nullptr);
                    insert_node(root,tree_node, departure_time);
                    flag = 1;
                }
            }
            if(flag == 0){
                locations[idx_l]->addTrip(tp);
                TransportService* ts = new TransportService(drop_location);
                locations[idx_l]->addTransportService(ts);
                BinaryTreeNode* head = new BinaryTreeNode(departure_time, tp, nullptr);
                ts->setBSTHead(head);
            }
            // delete node;
            // cout << "Successfully added the node"<< endl;
        }
        // cout << "Add Trip Successful"<< endl;;
    }

    std::vector<Trip*> showTrips(std::string pick_up_location, int after_time, int before_time) {
        vector<Trip*> tp;

        // Finding the index of location in Locations
        int flag_l=0;
        int idx_l=0;
        for (int i=0; i<locations.size(); i++){
            if(locations[i]->getName() == pick_up_location){
                flag_l=1;
                idx_l=i;
            }
        }
        // If location doesn't exist it returns the vector with no elements
        if (flag_l == 0) {
            return tp;
        }
        // If the location exists, all the transport servies and checked and all the trips coresponding to trasport service is pushed into the vector to be returned
        else {
            for (int i=0; i<locations[idx_l]->getVectorTS().size(); i++){
                BinaryTreeNode* root = locations[idx_l]->getVectorTS()[i]->getBSTHead();
                tp = pre_order_trips(root, after_time, before_time, tp);   
            } 
        }
        return tp;
    }
    std::vector<Trip*> showTripsbydestination(std::string pick_up_location, std::string destination,int after_time, int before_time) {
        vector<Trip*> tp1;
        vector<Trip*> tp;
        tp = showTrips(pick_up_location, after_time, before_time);

        for (int i=0; i<tp.size(); i++) {
            if (tp[i]->getDropLocation() == destination) {
                tp1.push_back(tp[i]);
            }
        }
        return tp1;
    }

    Trip* bookTrip(std::string pick_up_location, std::string drop_location, std::string vehicle_number, int departure_time) {
        // Finding the index of pick_up_location in Locations vector
        int flag_l = 0;
        int idx_l=0;
        for (int i=0; i<locations.size(); i++){
            if(locations[i]->getName() == pick_up_location){
                idx_l=i;
                flag_l = 1;
                break;
            }
        }
        
        // If the pick_up_locaiton exists in locations 
        if (flag_l == 1){
            int idx=0;
            int flag=0;
            for (int i=0; i<locations[idx_l]->getVectorTS().size(); i++){
                if(locations[idx_l]->getVectorTS()[i]->getName() == drop_location){
                    idx = i;
                    flag = 1;
                    break;
                }
            }
            if (flag == 1){
                BinaryTreeNode* root = locations[idx_l]->getVectorTS()[idx]->getBSTHead();
                BinaryTreeNode* node = root;
                while(node != nullptr){
                    if(node->getDepartureTime() == departure_time){
                        if ((node->getTripNodePtr()->getBookedSeats() + 1) == node->getTripNodePtr()->getVehicle()->getSeatingCapacity()){
                            node->getTripNodePtr()->setBookedSeats(node->getTripNodePtr()->getBookedSeats()+1);
                            delete_node(root, node);
                        }
                        else{
                            node->getTripNodePtr()->setBookedSeats(node->getTripNodePtr()->getBookedSeats()+1);
                        }
                        return node->getTripNodePtr();
                    }
                    else if (departure_time < node->getDepartureTime()){
                        node = node->getLeftPtr();
                    }
                    else {
                        node = node->getRightPtr();
                    }
                }
            }
        }
        return nullptr;
    }
    Location* getLocation(std::string location){
        for (int i=0; i<locations.size(); i++){
            if (locations[i]->getName() == location){
                return locations[i];
            }
        }
        return nullptr;
    }

private:
    std::vector<Vehicle*> vehicles;
    std::vector<Location*> locations;
};
