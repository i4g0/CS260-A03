/*
 * ARIS BLOMS
 *************************************************
 * This is the implemetation of the code.
 * It holds all of the function definitions.
 *
 * 
 * File OUTPUT: data.dat
 * topicName;websiteAddr;summary;review;rating;
 * topicName;websiteAddr;summary;review;rating;
 * \n at the end of the file.
 *************************************************
*/  

#include "prog3.hpp"
using namespace std;

website::~website() {
    if (this->topicName)
        delete[] this->topicName;
    if (this->websiteAddr)
        delete[] this->websiteAddr;
    if (this->summary)
        delete[] this->summary;
    if (this->review)
        delete[] this->review;
}

hashTable::hashTable() : size(0) {
    initializeTable();
}

hashTable::hashTable(char * filename) : size(0) {
    
    initializeTable();

    ifstream in;
    in.open(filename);
    char temp[MAX];
    char *topicName, *websiteAddr, *summary, *review;
    uint8_t rating;

    if (!in) {
        cerr << "Error! " << filename << " not found!" << endl;
        exit(1);
    }
    
    while (!in.eof() && in.peek() != '\n') {
        in.getline(temp, MAX, ';');
        topicName = new char[strlen(temp) + 1];
        strcpy(topicName, temp);

        in.getline(temp, MAX, ';');
        websiteAddr = new char[strlen(temp) + 1];
        strcpy(websiteAddr, temp);
        
        in.getline(temp, MAX, ';');
        summary = new char[strlen(temp) + 1];
        strcpy(summary, temp);

        in.getline(temp, MAX, ';');
        review = new char[strlen(temp) + 1];
        strcpy(review, temp);

        in >> rating;
        in.ignore(); // ';'

        insert(*new website(topicName, websiteAddr, summary, review, rating));
        in.ignore(); // \n
    }

    in.close();
}

hashTable::~hashTable() {
    destroyTable();
}

website::website() {
    topicName = NULL;
    websiteAddr = NULL;
    summary = NULL;
    review = NULL;
    return;
}

website::website(char* topicName, char* websiteAddr, char* summary, char *review, uint8_t rating) {
    setTopicName(topicName);
    setWebsiteAddr(websiteAddr);
    setSummary(summary);
    setReview(review);
    setRating(rating); 
}

char* website::getTopicName() {
    return topicName;
}

char* website::getWebsiteAddr() {
    return websiteAddr;
}

char* website::getSummary() {
    return summary;
}

char* website::getReview() {
    return review;
}

uint8_t website::getRating() {
    return rating;
}

void website::setTopicName(char* name) {
    topicName = name;
}

void website::setWebsiteAddr(char* web) {
    websiteAddr = web;
}

void website::setSummary(char* sum) {
    summary = sum;
}

void website::setReview(char* rev) {
    review = rev;
}

void website::setRating(uint8_t num) {
    rating = num;
}

void hashTable::destroyTable() {
    for (int i = 0; i < CAPACITY; i++) {
        node * head = table[i];
        node * current;
        while (head) {
            current = head->next;
            head->next = NULL;
            delete head;
            head = current;
        }
    }
    delete[] table; // deletes array
}

void hashTable::initializeTable() {
    table = new node*[CAPACITY];

    for (int i = 0; i < CAPACITY; i++) {
        table[i] = NULL;
    }
}

int hashTable::calculateIndex(char* key) const {
    char * c = key;
    int total = 0;

    while (*c) {
        total += *c; //adds ascii values together
        c++;
    }

    return total%CAPACITY; // sum of the values modulo CAPACITY
}

int hashTable::getSize() const {
    return size;
}

void hashTable::insert(website& aWebsite) {
   char *key;
   key = aWebsite.getTopicName();
   int index = calculateIndex(key);

   node * newNode = new node(aWebsite);
   assert(newNode);

   newNode->next = table[index];

   table[index] = newNode;
   size++;
}

bool hashTable::remove(char * key) {
    int index = calculateIndex(key);
    node * current = table[index];
    node * prev = NULL;
    char *name;
    while (current) {
        name = current->favorited.getTopicName();
        if (strcmp(name, key) == 0) {
            if (!prev)
                table[index] = current->next;
            else 
                prev->next = current->next;
            current->next = NULL;
            delete current;
            size--;
            return true;
        }
        else {
            prev = current;
            current = current->next;
        }
    }
    return false;
}

bool hashTable::retrieve(char* key, website output[], int& num_found) {
    int index = calculateIndex(key);
    if (index > CAPACITY)
        return false;
    num_found = 0;
    node * current = table[index];
    assert(current);
    char * name;
    while (current) {
        name = current->favorited.getTopicName();    
        if (strcmp(name, key) == 0) {
            output[num_found] = current->favorited;
            num_found++;
        }
        current = current->next;
    }
    return num_found > 0;
} 

bool hashTable::display(char * key) {
    website output[MAX];
    int count = 0;
    if(retrieve(key, output, count)) {
        
        cout << "Website data:\n\tTopic:\n\tURL:\n\tSummary:\n\tReview:\n\tRating (0 - 5 Stars):\n" << endl;
        for (int i = 0; i < count; i++) {
            
            cout << "\t" << output->getTopicName() <<
                "\n\t" << output->getWebsiteAddr() <<
                "\n\t" << output->getSummary() << 
                "\n\t" << output->getReview() << 
                "\n\t" << output->getRating() <<
                endl;
        }        
        return true;
    }
    else 
        return false;
}

void hashTable::displayAll() const {
    int i;
    node * current;
    cout << "Website data:\n\tTopic:\n\tURL:\n\tSummary:\n\tReview:\n\tRating (0 - 5 Stars):\n" << endl;
    for (i = 0; i < CAPACITY; i++) {
        for (current=table[i];current;current=current->next) {
            cout << "\t" << current->favorited.getTopicName() <<
                "\n\t" << current->favorited.getWebsiteAddr() <<
                "\n\t" << current->favorited.getSummary() << 
                "\n\t" << current->favorited.getReview() << 
                "\n\t" << current->favorited.getRating() <<
                endl;
            cout << endl;
        }
    }
}

bool hashTable::writeOut(char * filename) {
    ofstream out;
    out.open(filename);
    if (!out) 
        return false;
    node * current;
    for (int i = 0; i < CAPACITY; i++) {
        for (current=table[i]; current; current=current->next) {
            out <<current->favorited.getTopicName() << ";" <<
                current->favorited.getWebsiteAddr() << ";" <<
                current->favorited.getSummary() << ";" <<
                current->favorited.getReview() << ";" <<
                current->favorited.getRating() << ";\n";
        }
    }
    out << '\n'; // eof check
    out.close();
    return true;
}
