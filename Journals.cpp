#ifndef JOURNALS_H
#define JOURNALS_H
#include "LibraryItem.cpp"
#include<iostream>
using namespace std;

class Journals : public LibraryItem
{
private:
    int ID;
    string title;

public:
    // Constructor
    Journals(int ID, const string &title)
        : ID(ID), title(title)
    {
    }
    int getID() const
    {
        return ID;
    }
    string getTitle() const
    {
        return title;
    }
    void printDetails() const override
    {
        cout << "ID: " << ID << "\nJournal Title: " << title << "\n";
    }
};
#endif 
