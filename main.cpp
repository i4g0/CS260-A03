/*
 * ARIS BLOMS
 ************************************************************
 * This is the main file, it holds the menu function, and 
 * interacts with the user.
 *
 * File OUTPUT: data.dat
 * topicName;websiteAddr;summary;review;rating;
 * topicName;websiteAddr;summary;review;rating;
 * \n at the end of the file.
 ***********************************************************
*/ 


#include "prog3.hpp"
using namespace std;

void menu(void) {
    cout << "Welcome to the bookmarking program. Please enter...\n\t[A] to add a website to the favorites list.\n\t[R] to remove a website from the favorites list.\n\t[D] to display all websites in the favorites list.\n\t[C] to check if there is a website in the favorites.\n\t[Q] to save and quit.\n";
}

int main() {
    
    char * filename = new char[strlen("data.dat") + 1];
    strcpy(filename, "data.dat");
    
    hashTable table(filename);
    //hashTable table;
    
    char user, temp[MAX];
    
    char *topicName, *websiteAddr, *summary, *review;
    uint8_t rating;
    
    do {
        menu();
        
        cin >> user;
        while (cin.fail()) {
            cout << "Error! Try again." << endl;
            cin.clear();
            cin.ignore(100, '\n');
            menu();
            cin >> user;
        }
        
        cin.clear();
        cin.ignore(100, '\n');

        switch(toupper(user)) {
            case('A'):
                cout << "What is the topic of the website? : ";
                cin.getline(temp, MAX);
                topicName = new char[strlen(temp) + 1];
                strcpy(topicName, temp);

                cout << "What is the website address? : ";
                cin.getline(temp, MAX);
                websiteAddr = new char[strlen(temp) + 1];
                strcpy(websiteAddr, temp);

                cout << "Please give me a brief summary : ";
                cin.getline(temp, MAX);
                summary = new char[strlen(temp) + 1];
                strcpy(summary, temp);

                cout << "Please give a brief review of the" << 
                    " website : ";
                cin.getline(temp, MAX);
                review = new char[strlen(temp) + 1];
                strcpy(review, temp);

                cout << "Rate this website from 0 to 5 stars: ";
                cin >> rating;
                while (cin.fail()) {
                    cout << "Error! Try again." << endl;
                    cin.clear();
                    cin.ignore(100, '\n');
                    cout << "0 to 5 : ";
                    cin >> rating;
                }
                table.insert(*new website(topicName, websiteAddr, summary, review, rating)); 
                break;
            case('R'):
                cout << "What is the topic of the website? : ";
                
                cin.getline(temp, MAX);
                topicName = new char[strlen(temp) + 1];
                strcpy(topicName, temp);
                if (!table.remove(topicName)) {
                    cout << "Error! " << topicName << " couldn't be found!" << endl;
                }
                else 
                    cout << topicName << " removed." << endl;
                break;
            case('D'):
                table.displayAll();
                break;
            case('C'):
                cout << "Enter the topic name to search : ";
                cin.getline(temp, MAX);
                topicName = new char[strlen(temp) + 1];
                strcpy(topicName, temp);
                if (!table.display(topicName)) {
                    cout << topicName << " not found." << endl;
                }
                break;
            case('Q'):
                table.writeOut(filename);
                break;
            default:
                cout << "I'm sorry, I don't understand. " <<
                    "Try again." << endl;
        }
    } while (toupper(user) != 'Q');
    
    // deleting dynamically allocated variables....
    if (filename)
        delete[] filename;
    if (topicName)
        delete[] topicName;
    if (websiteAddr)
        delete[] websiteAddr;
    if (summary)
        delete[] summary;
    if (review)
        delete[] review;
    // ..........
    return 0;
}
