#include <bits/stdc++.h>
using namespace std;


class StudentRecord{
private:
    string studentName;
    string rollNumber;

public:
    string get_studentName() {
        return studentName;
    }
    void set_studentName(string Name) {
        studentName = Name;
    }
    string get_rollNumber() {
        return rollNumber;
    }
    void set_rollNumber(string rollnum) {
        rollNumber = rollnum;
    }
};

class Node{
	private:
		Node* next;
		StudentRecord* element;
	public:
	    Node* get_next() {
	        return next; 
	    }
	    StudentRecord* get_element() {
	        return element; 
	    }

	    Node* set_next(Node* value){
	    	next = value;
	    }
	    StudentRecord* set_element(StudentRecord* student){
	    	element = student;
	    }

};

class Entity {
private:
    string name;
    Node* iterator;

public:
    string get_name() {
        return name;
    }
    void set_name(string Name) {
        name = Name;
    }
    Node* get_iterator() {
        return iterator;
    }
    void set_iterator(Node* iter) {
        iterator = iter;
    }
};
vector<StudentRecord> students;

class LinkedList : public Entity {
    public:
        void add_student(StudentRecord student){
            StudentRecord* newstud = new StudentRecord;
            newstud->set_studentName(student.get_studentName());
            newstud->set_rollNumber(student.get_rollNumber()); 

            Node* newNode = new Node;
            newNode->set_element(newstud);
            newNode->set_next(nullptr);

            Node* current = get_iterator();
            if (!current) {
                set_iterator(newNode);
            }
            else {
                while (current->get_next()) {
                    current = current->get_next();
                }
                current->set_next(newNode);
            }
        }

        void delete_student(string studentName){
            Node* current = get_iterator();
            Node* prev = nullptr;

            while (current) {
                if (current->get_element()->get_studentName() == studentName) {
                    if (prev) {
                        prev->set_next(current->get_next());
                    }
                    else {
                        set_iterator(current->get_next());
                    }
                }

                prev = current;
                current = current->get_next();
            }
        }
};
vector<LinkedList> EntityArray;

void read_input_file(string file_path){
    ifstream file;
    string line;
    int nl=0;
    file.open(file_path);

    // To check if the file has opened
    // cout << file.is_open();

    if(!file) {
        cout<<"File does not exist [OR] it isn't open.";
    }
    else{
        while(getline(file, line)){
            StudentRecord stud;
            string word;
            int count=0;
            for (int i=0; i<line.size(); i++){
                char s = line[i];
                
                if(s == ',' || s == '[' || s ==']'){
                    if(count==0){
                        stud.set_studentName(word);
                    }
                    else if(count==1){
                        stud.set_rollNumber(word);
                        students.push_back(stud);
                    }
                    else{
                        int flag=0;
                        int idx=0;
                        int j=0;
                        for(j = 0 ; j < EntityArray.size() ; j++){
                            if (EntityArray[j].get_name() == word){
                                flag=1;
                                idx=j;
                                break;
                            }
                        }
                        if(flag == 1){
                            EntityArray[idx].add_student(students[nl]);
                        }
                        else if(flag == 0 && word.size()!=0){
                            //cout << count;

                            StudentRecord* p = new StudentRecord;
                            p->set_studentName(students[nl].get_studentName());
                            p->set_rollNumber(students[nl].get_rollNumber());

                            LinkedList entityy;
                            entityy.set_name(word);
                            Node* ptr = new Node;
                            ptr->set_element(p);
                            ptr->set_next(nullptr);
                            entityy.set_iterator(ptr);
                            EntityArray.push_back(entityy);

                        }
                    }
                    count++;
                    word.clear();
                }
                else{
                    word+=s;
                }
            }
            nl++;
        }
    }
}
