#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <list>
using namespace std;

class Parcel {
public:
    int time_tick;
    std::string parcel_id;
    std::string origin;
    std::string destination;
    int priority;
    bool delivered;
    std::string current_location;

    Parcel() = default;
    Parcel(int time_tick, std::string parcel_id, std::string origin, std::string destination, int priority) {
        this->time_tick = time_tick;
        this->parcel_id = parcel_id;
        this->origin = origin;
        this->destination = destination;
        this->priority = priority;
        this->delivered = false;
        this->current_location = origin;
    }
};

class MaxHeap {
public:
    std::vector<Parcel*> heap;

    int parent(int i) {
        return (i-1)/2;
        // fill in this function
    }

    int left(int i) {
        return 2*i+1;
        // fill in this function
    }

    int right(int i) {
        return 2*i+2;
        // fill in this function
    }

    Parcel* get_max() {
        if (heap.empty() == 0) {
            return heap[0];
        }
        else{
            return nullptr;
        }
        // fill in this function
    }

    Parcel* extract_max() {
        if (heap.empty() == 0) {
            Parcel* temp= heap[0];
            heap[0]=heap.back();
            heap.pop_back();
            max_heapify(0);
            return temp;
        }
        else {
            return nullptr;
        }
        // function that returns the max element and removes it from the heap
    }

    void max_heapify(int i) {
        int l = left(i);
        int r = right(i);
        int largest = i;
        if (r < heap.size() && heap[r]->priority > heap[largest]->priority)
        {
            largest = r;
        }
        if (l < heap.size() && heap[l]->priority > heap[largest]->priority)
        {
            largest = l;
        }
        if (largest != i)
        {
            std::swap(heap[i], heap[largest]);
            max_heapify(largest);
        }
        // function that maintains the max heap property
    }

    void insert(Parcel* item) {
        heap.push_back(item);
        int i = heap.size() - 1;
        while (i > 0 && heap[parent(i)]->priority < heap[i]->priority)
        {
            std::swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
        // function that inserts item into the heap
    }

    bool is_empty() {
        return heap.empty();
    }
};

class FreightCar {
public:
    int max_parcel_capacity;
    std::vector<Parcel*> parcels;
    std::string destination_city;
    std::string next_link;
    std::string current_location;
    bool sealed;
    

    FreightCar(int max_parcel_capacity) {
        this->max_parcel_capacity = max_parcel_capacity;
        // instantiate parcels vector as empty initially
        this->parcels = {};
        this->destination_city = "";
        this->next_link = "";
        this->current_location = "";
        this->sealed = false;
    }

    void load_parcel(Parcel* parcel) {
        parcels.push_back(parcel);
        // load parcel
    }

    bool can_move() {
        // if length of parcels is equal to max_parcel_capacity return true else return false
    }

    void move(std::string destination) {
        // function that moves freight car to destination (link)
    }
};

class Vertex {
public:
    // variables for bfs and dfs 
    int visited;
    Vertex* parent;

    std::string name;
    std::vector<FreightCar*> freight_cars;
    std::vector<Vertex*> neighbors;
    // trains_to_move is dict of destination and freight cars 
    std::map<std::string, std::vector<FreightCar*>> trains_to_move;
    int min_freight_cars_to_move;
    int max_parcel_capacity;
    std::unordered_map<std::string, MaxHeap*> parcel_destination_heaps;
    std::vector<FreightCar*> sealed_freight_cars;
    std::vector<Parcel*> all_parcels;
    Vertex() = default;
    Vertex(std::string name, int min_freight_cars_to_move, int max_parcel_capacity) {
        this->visited = 0;
        this->parent = nullptr;
        this->name = name;
        this->freight_cars = {};
        this->neighbors = {};
        this->trains_to_move = {};
        this->min_freight_cars_to_move = min_freight_cars_to_move;
        this->max_parcel_capacity = max_parcel_capacity;
        this->parcel_destination_heaps = {};
        this->sealed_freight_cars = {};
        this->all_parcels = {};
    }

    void add_neighbor(Vertex* neighbor) {
        neighbors.push_back(neighbor);
        // add neighbor to neighbors vector
    }

    // add get neighbors function
    std::vector<Vertex*> get_neighbors() {
        return this->neighbors;
    }

    std::vector<Parcel*> get_all_current_parcels() {
        // get all parcels from all destination heaps
    }

    void clean_unmoved_freight_cars() {
        // after time tick t, freight cars with parcels < min parcels should be deleted and parcels are to be added to heap
    }

    void loadParcel(Parcel* parcel) {
        // load parcel into heap
    }

    void loadFreightCars() {
        // load parcels into freight cars (making sure that each freight car has parcels from only one destination, and # parcels == min_parcel_capacity)
    }

    void print_parcels_in_freight_cars() {
        // for (auto& [destination, heap] : this->parcel_destination_heaps) {
        //     for (auto& parcel : heap.heap) {
        //         std::cout << "Parcel ID: " << parcel->parcel_id << ", Parcel origin: " << parcel->origin << ", Parcel destination: " << parcel->destination << ", Parcel priority: " << parcel->priority << std::endl;
        //     }
        // }
    }
};

class Graph {

public:
    std::list<Vertex*> vertices;
    std::vector<std::pair<Vertex*, Vertex*>> edges;

    Vertex* search_vertex(string city) {
        for (Vertex* vertex : vertices) {
            if (vertex->name == city) {
                return vertex;
            }
        }
        return nullptr;
    }

    void add_edge(std::string source, std::string destination, int min_freight_cars_to_move, int max_parcel_capacity) {

        Vertex* v1 = search_vertex(source);
        if (v1 == nullptr) {
            Vertex* new_vertex = new Vertex(source, min_freight_cars_to_move, max_parcel_capacity);
            vertices.push_back(new_vertex);
            v1 = new_vertex;
        }
        Vertex* v2 = search_vertex(destination);
        if (v2 == nullptr) {
            Vertex* new_vertex = new Vertex(destination, min_freight_cars_to_move, max_parcel_capacity);
            vertices.push_back(new_vertex);
            v2 = new_vertex;
        }
        
        v1->add_neighbor(v2);
        v2->add_neighbor(v1);
        pair<Vertex*, Vertex*> p1(v1,v2);
        edges.push_back(p1);

        // check if source and destination vertices exist
        // if they do not exist, create them
        // add edges accordingly

    }

    void print_graph() {
        std::cout << "Printing graph, vertices: " << vertices.size() << std::endl;
        for (auto vertex : this->vertices) {
            std::cout << "Vertex: " << vertex->name << std::endl;
            std::cout << "Neighbors: ";
            for (auto neighbor : vertex->neighbors) {
                std::cout << neighbor->name << " ";
            }
            std::cout << std::endl;
        }
    }

    void bfs_marking(string source, string destination) {
        Vertex* v1 = search_vertex(source);
        Vertex* v2 = search_vertex(destination);
        queue<Vertex*> q;
        q.push(v1);
        while (q.size() != 0) {
            Vertex* start = q.front();
            q.pop();

            for (Vertex* neighbor : start->get_neighbors()) {
                if (neighbor->visited == 0) {
                    neighbor->visited = 1;
                    q.push(neighbor);
                    neighbor->parent = start;
                    if (neighbor->name == destination) {
                        return;
                    }
                }
            }
        }
    }

    std::vector<std::string> bfs(std::string source, std::string destination) {
        bfs_marking(source , destination);
        vector<string> reverse_output;
        reverse_output.push_back(destination);
        if (source == destination) {
            return reverse_output;
        }
        Vertex* v1 = search_vertex(source);
        Vertex* v2 = search_vertex(destination);
        while (v1 != v2) {
            v2 = v2->parent;
            reverse_output.push_back(v2->name);
        }
        for (Vertex* vertex : vertices) {
            vertex->visited = 0;
            vertex->parent = nullptr;
        }
        vector<string> output;
        for (int i=0; i<reverse_output.size(); i++) {
            output.push_back(reverse_output[reverse_output.size()-1-i]);
        }
        // for (int i=0; i<vertices.size(); i++) {
        //     vertices[i]->visited = 0;
        //     vertices[i]->parent = nullptr;
        // }
        return output;
        // function to return path from source to destination using bfs
        }

void dfs_marking(string source, string destination) {
        Vertex* v1 = search_vertex(source);
        Vertex* v2 = search_vertex(destination);
        v1->visited = 1;
        if (source == destination) {
            return;
        }
        for (Vertex* neighbor : v1->get_neighbors()) {
            if (neighbor->visited == 0) {
                neighbor->parent = v1;
                dfs_marking(neighbor->name,destination);
            }
        }
    }

    std::vector<std::string> dfs(std::string source, std::string destination) {
        dfs_marking(source, destination);
        // cout << "CHECKPOINT" << endl;
        vector<string> reverse_output;
        reverse_output.push_back(destination);
        if (source == destination) {
            return reverse_output;
        }
        // cout << "CHECKPOINT" << endl;
        Vertex* v1 = search_vertex(source);
        Vertex* v2 = search_vertex(destination);
        while (v1 != v2) {
            // cout << v2->name << endl;
            v2 = v2->parent;
            reverse_output.push_back(v2->name);
        }
        // cout << "CHECKPOINT" << endl;
        for (Vertex* vertex : vertices) {
            vertex->visited = 0;
            vertex->parent = nullptr;
        }
        vector<string> output;
        for (int i=0; i<reverse_output.size(); i++) {
            output.push_back(reverse_output[reverse_output.size()-1-i]);
        }
        // for (int i=0; i<vertices.size(); i++) {
        //     vertices[i]->visited = 0;
        //     vertices[i]->parent = nullptr;
        // }
        return output;
        
       // function to return path from source to destination using dfs
    }

    void groupFreightCars() {
        // for every vertex, group freight cars by links
    }

    void moveTrains() {
        // for every vertex, move freight cars to next link
    }



};

class PRC {
public:
    Graph graph;
    std::vector<FreightCar*> freight_cars;
    std::map<std::string, Parcel*> parcels;
    std::map<int, std::vector<Parcel*>> parcels_with_time_tick;
    int max_parcel_capacity;
    int min_freight_cars_to_move;
    int time_tick;
    std::map<std::string, std::string> old_state;
    std::map<std::string, std::string> new_state;
    int max_time_tick;

    PRC(int max_parcel_capacity, int min_freight_cars_to_move) {
        this->max_parcel_capacity = max_parcel_capacity;
        this->min_freight_cars_to_move = min_freight_cars_to_move;
        this->time_tick = 1;
        this->max_time_tick = 100;
        this->freight_cars = {};
        this->parcels = {};
        this->parcels_with_time_tick = {};
        this->old_state = {};
        this->new_state = {};

    }

    void create_graph(std::string graph_file_name) {
        ifstream file;
        file.open(graph_file_name);
        string line;
        if (!file){
            cout << "File does not exist [OR] it isn't open";
        }
        else {
            while (getline(file, line)){
                string source;
                string destination;
                int count=0;
                for (int i=0; i<line.size(); i++) {
                    char s = line[i];
                    if (s == 32) {
                        count ++;
                    }
                    else {
                        if (count == 0) {
                            source += s;
                        }
                        else {
                            destination += s;
                        }
                    }
                }
                graph.add_edge(source, destination, min_freight_cars_to_move, max_parcel_capacity);
                // cout << source << endl;
                // cout << destination << endl;
                // cout << "Edge Added" << endl;
            }
        }
        // read graph.txt file and create graph

    }

    void process_parcels(std::string parcels_file_name){
        // read parcels.txt file and create parcels 
    }

    // function to return bookings at a particular time tick at a particular vertex
    std::vector<Parcel*> get_bookings(int time_tick, std::string vertex) {
    }

    std::map<std::string, std::string> get_state() {
        std::map<std::string, std::string> state;
        // from this.parcels
        // should return the dict of parcel_id and current_location
        return state;
    }

    // run simulation function, takes run_till_time_tick as argument
    // if run_till_time_tick is not provided then run simulation till max_time_tick

    void run_simulation(int run_till_time_tick = -1) {

        // function to run simulation
    }

    bool convergence_check(){
        // function to check convergence between old_state and new_state
    }

    bool all_parcels_delivered() {
        return false;
        // function to check if all parcels are delivered
        // return true if all parcels are delivered else return false
    }

    std::vector<std::string> get_stranded_parcels() {
        // return parcel_ids of stranded parcels
    }

    std::vector<std::string> get_delivered_parcels() {
        return {};
        // return parcel_ids of delivered parcels
    }

    // get status of all parcels at time tick t (status = id, current location, delivered/not delivered)
    std::vector<std::string> get_status_of_all_parcels(int t) {
        //  std::string status = parcel.parcel_id + " " + parcel.current_location + " " + std::to_string(parcel.delivered) + "\n" ;
        // return the status of all parcels at time tick t as a vector of strings (each string formatted as above)
    }

    // get status of parcel_id at time tick t (status = id, current location, delivered/not delivered)
    std::string get_status_of_parcel(std::string parcel_id, int t) {
        // status = parcel.parcel_id + " " + parcel.current_location + " " + std::to_string(parcel.delivered);
        // return status of one parcel at time tick t as a string (formatted as above)
    }

    // get parcels delivered up to time tick t
    std::vector<std::string> get_parcels_delivered_up_to_time_tick(int t) {
        vector<string> vec;
        for (int i=0; i<25; i++) {
            vec.push_back("yes");
        }
        return vec;
        // return list of parcel_ids of parcels delivered up to time tick t
    }

};


// int main() {

//     Graph g;
//     g.add_edge("1","2",5,5);
//     g.add_edge("3","2",5,5);
//     g.add_edge("1","3",5,5);
//     g.add_edge("4","3",5,5);
//     g.add_edge("4","5",5,5);
//     g.add_edge("5","6",5,5);
//     g.add_edge("6","7",5,5);
//     g.add_edge("2","7",5,5);
//     g.print_graph();
//     vector<string> shortest_path = g.bfs("1", "7");
//     cout << "Size of path : " << shortest_path.size() << endl;
//     for (int i=0; i<shortest_path.size(); i++) {
//         cout << shortest_path[i] << endl;
//     }
//     cout << endl << "######################" << endl;
//     vector<string> dfs_path = g.dfs("1", "7");
//     cout << "Size of path : " << dfs_path.size() << endl;
//     for (int i=0; i<dfs_path.size(); i++) {
//         cout << dfs_path[i] << endl;
//     }
//     PRC test(5,5);
//     test.create_graph("graph.txt");



//     // PRC prc = PRC(2, 2);
//     // prc.create_graph();
//     // prc.process_parcels();
//     // prc.run_simulation(3);

//     return 0;
// }
