/*
 ************************************************************
 * This program is a database for storing favorite websites
 * that you want to bookmark.  
 *
 * Name: Aris Bloms
 * CS260 PCC
 * Date: Nov. 7
 * Assignment 3
 *
 * class website 
 *      contains all the website data
 *
 * class hashTable
 *      contains the hashTable
 *
 *      class node
 *          contains the storage of the websites
 *
 ************************************************************
*/ 

#ifndef __PROG_3__
#define __PROG_3__

#include<iostream>
#include<iomanip> 
#include<cassert>
#include<cstring>
#include<fstream>


const static int CAPACITY = 11;
const int MAX = 256;

class website {
    char * topicName; // website topic
    char * websiteAddr; // URL
    char * summary; // summary of the website
    char * review; // review of the website
    uint8_t rating; // 0 to five star rating
public:
    website();
    website(char* topicName, char* websiteAddr, char* summary, char *review, uint8_t rating); // creates a website
    ~website();                // website destructor

    char* getTopicName();   //returns topicName
    char* getWebsiteAddr(); //returns websiteAddr
    char* getSummary();     //returns summary
    char* getReview();      //returns review
    uint8_t getRating();    //returns rating

    void setTopicName(char *);      //sets topicName
    void setWebsiteAddr(char *);    //sets websiteAddr
    void setSummary(char*);         //sets summary
    void setReview(char*);          //sets review
    void setRating(uint8_t);        //sets rating
}; // end of website class

class hashTable {
private: // still only in hashTable
    struct node { 
        website favorited;
        node * next;

        node() {                  // node default constructor
            next = NULL;
        }
        
        node(website& aWebsite) { // node constructor
            favorited = aWebsite;
            next = NULL;
        }
        ~node() {                 // node destructor
            delete next;
        }
    }; // end of node struct

    // private: hashTable

    node ** table;
    int size;
        
    void destroyTable(); // sets all table values to NULL and deletes
    void initializeTable(); // sets all table values to \0
    int calculateIndex(char * key) const; // creates hash
    bool retrieve(char*, website[], int&);//retrieves a website

public: // hashTable public functions
    hashTable();
    hashTable(char * filename);     //loads file
    ~hashTable();                   //destructor

    void insert(website&);          //inserts a website
    bool remove(char* key);         //removes a website
    void displayAll(void) const;    //displays all websites
    bool display(char * key);       //displays a website
    int getSize(void) const;        //returns size
    bool writeOut(char * filename); //writes to file
};




#endif
