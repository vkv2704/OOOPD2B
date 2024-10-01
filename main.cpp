#ifndef MAIN_H
#define MAIN_H
#include "LibraryItem.cpp"
#include "Library.cpp"
#include "functions.h"
#include "Book.cpp"
#include "Journals.cpp"
#include "PublicationRank.cpp"
#include "User.cpp" // Include User.cpp 

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <cstring>
#include <cctype>
#include <limits>
#include <chrono>
#include <thread>
#include <iomanip>

// Avoid `using namespace std;` in larger projects
// Instead, use fully qualified names: std::cout, std::string, etc.

int main()
{
    Library library;
    // int ID = 1;

    // Opening journal.csv
    ifstream journalFile("journals.csv");
    if (journalFile.is_open())
    {
        string line;
        // Read and discard the header line
        // getline(journalFile, line);

        while (getline(journalFile, line))
        {
            // Define an array to store fields

            const int fieldCount = 2;
            string fields[fieldCount];

            // Parse CSV line into fields
            splitLine(line, fields, fieldCount);

            if (fieldCount >= 2)
            {
                string title = fields[0];

                Journals *journal = new Journals(ID, title);
                // journal-> printDetails();
                // cout << "------------------------\n";
                library.addItem(journal);
                ID++;
            }
        }

        journalFile.close();
    }
    else
    {
        cerr << "Failed to open journals.csv\n";
    }
    //  Opening book.csv
    ifstream bookFile("books.csv");
    if (bookFile.is_open())
    {
        string line;
        // Read and discard the header line
        getline(bookFile, line);
        while (getline(bookFile, line))
        {
            const int fieldCount = 24;
            string fields[fieldCount];
            if (fieldCount >= 24) {
            int book_id, isbn;
            string title, authors;
            double original_publication_year;
            
            istringstream ss(line);
            ss >> book_id; 
            for (int i = 0; i < 5; ++i)
            {
                ss.ignore(256, ','); // Ignore fields until the next comma
            }
            ss >> isbn; // Read isbn until the next comma
            ss.ignore(256, ',');
            ss.ignore(256, ',');
            if (line.find("\"") != std::string::npos)
            {
                // Handle quoted fields
                stringstream ss(line);
                string field;
                getline(ss, field, ','); // Read the first field
                ss.ignore(256, ','); 
                ss.ignore(256, ',');
                getline(ss, authors, ','); // Read the authors field with quotes
                authors = authors.substr(1, authors.size() - 2); // Remove leading and trailing quotes 
                ss.ignore(256, ',');
                ss >> original_publication_year;
                ss.ignore(256, ',');
                ss.ignore(256, ',');
                //getline(ss, title, ',');
                getline(ss, title, ','); // Read the title field with quotes
                title = title.substr(1, title.size() - 2); // Remove leading and trailing quotes 
                ss.ignore(256, ',');

            }
            else
            {
                // Handle unquoted fields (normal parsing)
                istringstream ss(line);
                ss >> book_id; 
                for (int i = 0; i < 5; ++i)
                {
                    ss.ignore(256, ','); // Ignore fields until the next comma
                }
                ss >> isbn; // Read isbn until the next comma
                ss.ignore(256, ',');
                ss.ignore(256, ',');
                getline(ss, authors, ',');
                ss.ignore(256, ',');
                ss >> original_publication_year;
                ss.ignore(256, ',');
                ss.ignore(256, ',');
                //getline(ss, title, ',');
                getline(ss, title, ',');
                ss.ignore(256, ',');
            }

            Book *book = new Book(ID, book_id, isbn, title, authors, original_publication_year);
            // book->printDetails();
            // cout << "------------------------\n";
            library.addItem(book);
            ID++;
         }

        }
        bookFile.close();
    }
    else
    {
        cerr << "Failed to open books.csv\n";
    }

    // opening publicatin_rank.csv

    ifstream publicationFile("publications_rank.csv");
    if (publicationFile.is_open())
    {
        string line;
        // Read and discard the header line
        getline(publicationFile, line);

        while (getline(publicationFile, line))
        {
            // Define an array to store fields
            const int fieldCount = 11;
            string fields[fieldCount];

            // Parse CSV line into fields
            splitCSVLine(line, fields, fieldCount);

            if (fieldCount >= 11)
            {
                string publication = fields[0];
                int rank = stoi(fields[1]);
                double totalPaid = stod(fields[2]);

                PublicationRank *publicationRank = new PublicationRank(ID, publication, rank, totalPaid);

                // publicationRank-> printDetails();
                // cout << "------------------------\n";
                library.addItem(publicationRank);
                ID++;
            }
        }
        publicationFile.close();
    }
    else
    {
        cerr << "Failed to open publications_rank.csv\n";
    }
    
    // library.printAllItems();

    int choice;
    do
    {
        std::cout << "Menu:" << std::endl;
        std::cout << "1. Register as a Student" << std::endl;
        std::cout << "2. Register as a Teacher" << std::endl;
        std::cout << "3. Search any item" << std::endl;
        std::cout << "4. Borrow any item" << std::endl;
        std::cout << "5. Purchase a book" << std::endl;
        std::cout << "6. Show all item lists" << std::endl;
        std::cout << "7. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
        {
            // Register as a Student
            string userName;
            do
            {
                std::cout << "Enter your name: ";
                std::cin.ignore();
                std::getline(std::cin, userName);

                if (!isValidUserName(userName))
                {
                    std::cout << "Invalid input. Please enter a valid name." << std::endl;
                }
            } while (!isValidUserName(userName));

            library.registerUser(userName, false); // Register as a student
            library.showAllRegisteredUsers();
            break;
        }
        case 2:
        {
            // Register as a Teacher
            string userName;
            do
            {
                std::cout << "Enter your name: ";
                std::cin.ignore();
                std::getline(std::cin, userName);

                if (!isValidUserName(userName))
                {
                    std::cout << "Invalid input. Please enter a valid name." << std::endl;
                }
            } while (!isValidUserName(userName));

            library.registerUser(userName, true); // Register as a teacher
            library.showAllRegisteredUsers();
            break;
        }
        case 3:
        {
            int choice;
            char phy, book;
            std::cout << "For physical items, press 'Y' or 'y' otherwise for electronic items:" << std::endl;
            std::cin >> phy;
            if (phy == 'Y' || phy == 'y')
            {
                std::cout << "For book, type 'Y' or 'y', otherwise for magazines :" << std::endl;
                std::cin >> book;
                if (book == 'Y' || book == 'y')
                {
                    std::cout << "Book can be search by:  \n1. Book ID \n2. ISBN \n3. Author's Name \n4. Title \nEnter your choice:";
                    std::cin >> choice;
                    switch (choice)
                    {
                    case 1:
                    {
                        // Search for a Book by book_id
                        int bookIdToSearch;
                        bool validInput = false;
                        do
                        {
                            std::cout << "Enter the book_id to search: ";

                            // Try to read the input as an integer
                            if (std::cin >> bookIdToSearch)
                            {
                                validInput = true;
                            }
                            else
                            {
                                std::cout << "Invalid input. Please enter a valid integer." << std::endl;
                                // Clear the input buffer to handle invalid input
                                std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            }
                        } while (!validInput);

                        Book *foundBook = library.getBookByID(bookIdToSearch);
                        if (foundBook != nullptr)
                        {
                            std::cout << "Book Found!!!!!!!!!!!!:\nID: "<<foundBook->getID()<<"\nTitle: " << foundBook->getTitle() << "\nISBN: " << foundBook->getISBN() << "\nAuthours: "
                                 << foundBook->getAuthors() << "\nPublication Year: " << foundBook->getPublicationYear() << std::endl;
                            std::cout << "-----------------------\n";
                        }
                        else
                        {
                            std::cout << "Book not found." << std::endl;
                        }
                        break;
                    }
                    case 2:
                    {
                        // Search for a Book by ISBN
                        int ISBNToSearch;
                        bool validInput = false;
                        do
                        {
                            std::cout << "Enter the ISBN to search: ";

                            // Try to read the input as an integer
                            if (std::cin >> ISBNToSearch)
                            {
                                validInput = true;
                            }
                            else
                            {
                                std::cout << "Invalid input. Please enter a valid integer." << std::endl;
                                // Clear the input buffer to handle invalid input
                                std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            }
                        } while (!validInput);

                        Book *foundBook = library.getBookByIsbn(ISBNToSearch);
                        if (foundBook != nullptr)
                        {
                            std::cout << "Book Found!!!!!!!!!!!!:\nID: "<<foundBook->getID()<<"\nTitle: " << foundBook->getTitle() << "\nISBN: " << foundBook->getISBN() << "\nAuthours: "
                                 << foundBook->getAuthors() << "\nPublication Year: " << foundBook->getPublicationYear() << std::endl;
                            std::cout << "-----------------------\n";
                        }
                        else
                        {
                            std::cout << "Book not found." << std::endl;
                        }
                        break;
                    }
                    case 3:
                    {
                        // Search for a Book by Author's Name
                        string authorNameToSearch;
                        do
                        {
                            std::cout << "Enter the author name to search: ";
                            std::cin.ignore();
                            std::getline(std::cin, authorNameToSearch);

                            if (!isValidUserName(authorNameToSearch))
                            {
                                std::cout << "Invalid input. Please enter a valid name." << std::endl;
                            }
                        } while (!isValidUserName(authorNameToSearch));

                        const int maxMatchingBooks = 100; // Define a maximum limit for matching books
                        Book *matchingBooks[maxMatchingBooks];
                        int matchingCount = 0;

                        library.searchBooksByAuthor(authorNameToSearch, matchingBooks, matchingCount);

                        if (matchingCount > 0)
                        {
                            std::cout << "Books by " << authorNameToSearch << ":" << std::endl;
                            std::cout << "--------------------------------\n";
                            for (int i = 0; i < matchingCount; i++)
                            {   std::cout <<"Id: "<<matchingBooks[i]->getID()<<std::endl;
                                std::cout << "BookID: " << matchingBooks[i]->getBookID() << "\nTitle: " << matchingBooks[i]->getTitle() << "\nISBN: " << matchingBooks[i]->getISBN() << std::endl;
                                std::cout << "Author Name: " << matchingBooks[i]->getAuthors() << std::endl;
                                std::cout << "--------------------------------\n";
                            }
                        }
                        else
                        {
                            std::cout << "No books by " << authorNameToSearch << " found." << std::endl;
                        }
                        break;
                    }
                    case 4:
                    {
                        // Search for a Book by its Title
                        string Title;
                        do
                        {
                            std::cout << "Enter the Title to search: ";
                            std::cin.ignore();
                            std::getline(std::cin, Title);

                            if (!isValidUserName(Title))
                            {
                                std::cout << "Invalid input. Please enter a valid name." << std::endl;
                            }
                        } while (!isValidUserName(Title));

                        const int maxMatchingBooks = 100; // Define a maximum limit for matching books
                        Book *matchingBooks[maxMatchingBooks];
                        int matchingCount = 0;

                        library.searchBooksByTitle(Title, matchingBooks, matchingCount);

                        if (matchingCount > 0)
                        {
                            std::cout << "Books by " << Title << ":" << std::endl;
                            std::cout << "--------------------------------\n";
                            for (int i = 0; i < matchingCount; i++)
                            {   std::cout <<"Id: "<<matchingBooks[i]->getID()<<std::endl;
                                std::cout << "BookID: " << matchingBooks[i]->getBookID() << "\nTitle: " << matchingBooks[i]->getTitle() << "\nISBN: " << matchingBooks[i]->getISBN() << std::endl;
                                std::cout << "Author Name: " << matchingBooks[i]->getAuthors() << std::endl;
                                std::cout << "--------------------------------\n";
                            }
                        }
                        else
                        {
                            std::cout << "No books by " << Title << " found." << std::endl;
                        }
                        break;
                    }
                    }
                }
                else
                {
                    string magazine;
                    do
                    {
                        std::cout << "Enter the name of magzine you want to search:";
                        std::cin.ignore();
                        std::getline(std::cin, magazine);

                        if (!isValidUserName(magazine))
                        {
                            std::cout << "Invalid input. Please enter a valid name." << std::endl;
                        }
                    } while (!isValidUserName(magazine));

                    const int maxMatchingBooks = 100; // Define a maximum limit for matching books
                    PublicationRank *matchingBooks[maxMatchingBooks];
                    int matchingCount = 0;

                    library.searchPublication(magazine, matchingBooks, matchingCount);

                    if (matchingCount > 0)
                    {
                        std::cout << "Magazine by " << magazine << ":" << std::endl;
                        std::cout << "--------------------------------\n";
                        for (int i = 0; i < matchingCount; i++)
                        {   std::cout <<"Id: "<<matchingBooks[i]->getID() <<std::endl;
                            std::cout << "Publication: " << matchingBooks[i]->getPublication() << "\nRank: " << matchingBooks[i]->getrank() << "\nTotal Paid: " << matchingBooks[i]->gettotalPaid() << std::endl;
                            std::cout << "--------------------------------\n";
                        }
                    }
                    else
                    {
                        std::cout << "No Publication by " << magazine << " found." << std::endl;
                    }
                    break;
                }
            } // to check physical item
            else
            {
                std::cout << "Electronic items" << std::endl;
                string magazine;
                do
                {
                    std::cout << "Enter the name of journal you want to search: ";
                    std::cin.ignore();
                    std::getline(std::cin, magazine);

                    if (!isValidUserName(magazine))
                    {
                        std::cout << "Invalid input. Please enter a valid name." << std::endl;
                    }
                } while (!isValidUserName(magazine));

                const int maxMatchingBooks = 100; // Define a maximum limit for matching books
                Journals *matchingBooks[maxMatchingBooks];
                int matchingCount = 0;

                library.searchJournal(magazine, matchingBooks, matchingCount);

                if (matchingCount > 0)
                {
                    std::cout << "Journal by " << magazine << ":" << std::endl;
                    std::cout << "--------------------------------\n";
                    for (int i = 0; i < matchingCount; i++)
                    {
                        std::cout << "ID: " << matchingBooks[i]->getID() << "\nTitle: " << matchingBooks[i]->getTitle() << std::endl;
                        std::cout << "--------------------------------\n";
                    }
                }
                else
                {
                    std::cout << "No Journal by " << magazine << " found." << std::endl;
                }
                break;
            }
            break;
        } // case 3 to search items
        case 4:
        {
            char phy, book;
            std::cout << "For physical items, press 'Y' or 'y' otherwise for electronic items:" << std::endl;
            std::cin >> phy;
            if (phy == 'Y' || phy == 'y')
            {
                std::cout << "For book, type 'Y' or 'y', otherwise for magazines :" << std::endl;
                std::cin >> book;
                if (book == 'Y' || book == 'y')
                {

                    string userNameToBorrow;
                    int bookIdToBorrow;
                    do
                    {
                        std::cout << "Enter your name: ";
                        std::cin.ignore();
                        std::getline(std::cin, userNameToBorrow);

                        if (!isValidUserName(userNameToBorrow))
                        {
                            std::cout << "Invalid input. Please enter a valid name." << std::endl;
                        }
                    } while (!isValidUserName(userNameToBorrow));

                    bool validInput = false;
                    do
                    {
                        std::cout << "Enter the book_id to borrow: ";

                        // Try to read the input as an integer
                        if (std::cin >> bookIdToBorrow)
                        {
                            validInput = true;
                        }
                        else
                        {
                            std::cout << "Invalid input. Please enter a valid integer." << std::endl;
                            // Clear the input buffer to handle invalid input
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        }
                    } while (!validInput);

                    if (library.borrowBook(userNameToBorrow, bookIdToBorrow))
                    {
                        // Book successfully borrowed
                    }
                    else
                    {
                        // Error message already printed in the borrowBook function
                    }
                    break;
                }

                else
                {

                    string userNameToBorrow;
                    int publication;
                    do
                    {
                        std::cout << "Enter your name: ";
                        std::cin.ignore();
                        std::getline(std::cin, userNameToBorrow);

                        if (!isValidUserName(userNameToBorrow))
                        {
                            std::cout << "Invalid input. Please enter a valid name." << std::endl;
                        }
                    } while (!isValidUserName(userNameToBorrow));

                    bool validInput = false;
                    do
                    {
                        std::cout << "Enter the id to borrow magazine: ";

                        // Try to read the input as an integer
                        if (std::cin >> publication)
                        {
                            validInput = true;
                        }
                        else
                        {
                            std::cout << "Invalid input. Please enter a valid integer." << std::endl;
                            // Clear the input buffer to handle invalid input
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        }
                    } while (!validInput);

                    if (library.borrowPublication(userNameToBorrow, publication))
                    {
                        // Book successfully borrowed
                    }
                    else
                    {
                        // Error message already printed in the borrowBook function
                    }
                    break;
                }
            }
            else
            {
                string userNameToBorrow;
                int title;
                do
                {
                    std::cout << "Enter your name: ";
                    std::cin.ignore();
                    std::getline(std::cin, userNameToBorrow);

                    if (!isValidUserName(userNameToBorrow))
                    {
                        std::cout << "Invalid input. Please enter a valid name." << std::endl;
                    }
                } while (!isValidUserName(userNameToBorrow));

               bool validInput = false;
                    do
                    {
                        std::cout << "Enter the id to borrow journal: ";

                        // Try to read the input as an integer
                        if (std::cin >> title)
                        {
                            validInput = true;
                        }
                        else
                        {
                            std::cout << "Invalid input. Please enter a valid integer." << std::endl;
                            // Clear the input buffer to handle invalid input
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        }
                    } while (!validInput);

                if (library.borrowJournal(userNameToBorrow, title))
                {
                    // Book successfully borrowed
                }
                else
                {
                    // Error message already printed in the borrowBook function
                }
                break;
            }
            break;
        } // case 4 ends
        case 5:
        {

            string author, title;
            int originalPublicationYear;

            int isbn;
            bool validInput = false;
            do
            {
                std::cout << "Enter the ISBN : ";

                // Try to read the input as an integer
                if (std::cin >> isbn)
                {
                    validInput = true;
                }
                else
                {
                    std::cout << "Invalid input. Please enter a valid integer." << std::endl;
                    // Clear the input buffer to handle invalid input
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            } while (!validInput);

            do
            {
                std::cout << "Enter the author name : ";
                std::cin.ignore();
                std::getline(std::cin, author);

                if (!isValidUserName(author))
                {
                    std::cout << "Invalid input. Please enter a valid name." << std::endl;
                }
            } while (!isValidUserName(author));

            do
            {
                std::cout << "Enter the title of book: ";
                std::cin.ignore();
                std::getline(std::cin, title);

                if (!isValidUserName(title))
                {
                    std::cout << "Invalid input. Please enter a valid name." << std::endl;
                }
            } while (!isValidUserName(title));

            while (true)
            {
                std::cout << "Enter the year of publication: ";
                if (std::cin >> originalPublicationYear && originalPublicationYear >= 1900 && originalPublicationYear <= 2023)
                {
                    if (std::cin.peek() == '\n')
                    {
                        // Valid input
                        break;
                    }
                }

                std::cout << "Invalid input. Please enter an integer originalPublicationYear between 1990 to 2023." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            library.addBook(isbn, author, title, originalPublicationYear);
            break;
        }
        case 6:
            library.printAllItems();
            // cout << "To print journal:" << endl;
            // Journals *journal = new Journals(ID, title);
            // journal->printDetails();
            break;
        case 7:
            std::cout << "Exiting program." << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 7);
    return 0;
}

#endif
