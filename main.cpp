// Name: Nikhil Suthar
// Project: Event Ticket Booking System (Concerts & Seminars)
// Topic: Inheritance, Virtual Functions, Static & Constant Members, Exception Handling

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Custom exception class to block oversold tickets
class OversoldException {
public:
    string message;
    OversoldException(string msg) {
        message = msg;
    }
};

// Base class
class Ticket {
protected:
    int ticketId;
    string customerName;
    string category;
    double basePrice;

    // Static member to count total tickets booked across all categories
    static int totalTicketsSold;

public:
    Ticket(int id, string name, string cat, double base) {
        ticketId = id;
        customerName = name;
        category = cat;
        basePrice = base;
        totalTicketsSold++; // increment total count whenever any ticket is made
    }

    virtual ~Ticket() {}

    // Pure virtual function for category-wise pricing
    virtual double price() = 0;

    // Static member function to get total count
    static int getTotalTicketsSold() {
        return totalTicketsSold;
    }

    // Virtual function to display ticket details
    virtual void display() {
        cout << "Ticket #" << ticketId << " | " << customerName 
             << " | " << category << " | Base: ₹" << basePrice 
             << " | Final Amount: ₹" << price() << endl;
    }

    int getId() { return ticketId; }
    string getName() { return customerName; }
    string getCategory() { return category; }
};

// Static member initialization
int Ticket::totalTicketsSold = 0;

// Derived class 1: Regular Ticket
class RegularTicket : public Ticket {
private:
    double convenienceFee; // 5% fee

public:
    RegularTicket(int id, string name, double base = 500) 
        : Ticket(id, name, "Regular", base) {
        convenienceFee = 0.05 * basePrice; // 5% of base price
    }

    // Overriding virtual price() function
    double price() {
        return basePrice + convenienceFee;
    }
};

// Derived class 2: VIP Ticket
class VIPTicket : public Ticket {
private:
    double loungePerks; // special lounge and refreshment charges
    double convenienceFee;

public:
    VIPTicket(int id, string name, double base = 1500) 
        : Ticket(id, name, "VIP", base) {
        loungePerks = 300; // Rs. 300 for VIP pass
        convenienceFee = 0.10 * basePrice; // 10% fee
    }

    // Overriding price(): Base + VIP Perks + 10% Fee
    double price() {
        return basePrice + loungePerks + convenienceFee;
    }

    void display() {
        cout << "Ticket #" << ticketId << " | " << customerName 
             << " | " << category << " | Base: ₹" << basePrice 
             << " | Final Amount: ₹" << price() << " (Includes Lounge Perks)" << endl;
    }
};

// Derived class 3: Student Ticket
class StudentTicket : public Ticket {
private:
    double discount;
    double fixedFee;

public:
    StudentTicket(int id, string name, double base = 400) 
        : Ticket(id, name, "Student", base) {
        discount = 0.20 * basePrice; // 20% discount on base price
        fixedFee = 20; // subsidized Rs. 20 fee
    }

    // Overriding price(): (Base - 20% Discount) + Rs. 20 Fee
    double price() {
        return (basePrice - discount) + fixedFee;
    }

    void display() {
        cout << "Ticket #" << ticketId << " | " << customerName 
             << " | " << category << " | Base: ₹" << basePrice 
             << " | Final Amount: ₹" << price() << " (Student Discount Applied)" << endl;
    }
};

// Event class
class Event {
private:
    string eventName;
    
    // Constant member: venue capacity cannot be changed once initialized
    const int venueCapacity;

    // Category limits to demonstrate category sold out exceptions
    int regularLimit;
    int vipLimit;
    int studentLimit;

    int regularCount;
    int vipCount;
    int studentCount;

    // Vector to store all booked tickets polymorphically
    vector<Ticket*> bookedTickets;

public:
    // Constructor uses member initializer list for the const member
    Event(string name, int capacity) 
        : venueCapacity(capacity) {
        eventName = name;
        regularLimit = 3;
        vipLimit = 2;
        studentLimit = 2;
        regularCount = 0;
        vipCount = 0;
        studentCount = 0;
    }

    ~Event() {
        // Freeing dynamic memory
        for (int i = 0; i < bookedTickets.size(); i++) {
            delete bookedTickets[i];
        }
        bookedTickets.clear();
    }

    // Function to book ticket and throw exceptions if full
    void bookTicket(int categoryChoice, string name) {
        // Check 1: Venue capacity check
        if (Ticket::getTotalTicketsSold() >= venueCapacity) {
            throw OversoldException("VENUE FULL: Total capacity of " + to_string(venueCapacity) + " seats reached for '" + eventName + "'!");
        }

        int newId = 101 + Ticket::getTotalTicketsSold();
        Ticket* t = NULL;

        // Check 2: Category limits check
        if (categoryChoice == 1) {
            if (regularCount >= regularLimit) {
                throw OversoldException("CATEGORY SOLD OUT: Regular tickets are completely sold out!");
            }
            t = new RegularTicket(newId, name, 600);
            regularCount++;
        }
        else if (categoryChoice == 2) {
            if (vipCount >= vipLimit) {
                throw OversoldException("CATEGORY SOLD OUT: VIP tickets are completely sold out!");
            }
            t = new VIPTicket(newId, name, 1500);
            vipCount++;
        }
        else if (categoryChoice == 3) {
            if (studentCount >= studentLimit) {
                throw OversoldException("CATEGORY SOLD OUT: Student tickets are completely sold out!");
            }
            t = new StudentTicket(newId, name, 450);
            studentCount++;
        }
        else {
            cout << "Invalid category choice selected." << endl;
            return;
        }

        bookedTickets.push_back(t);

        cout << "\n----------------------------------------" << endl;
        cout << "Booking Confirmed for " << name << "!" << endl;
        cout << "Ticket ID    : #" << t->getId() << endl;
        cout << "Category     : " << t->getCategory() << endl;
        cout << "Final Price  : ₹" << t->price() << " (Rs. " << t->price() << ")" << endl;
        cout << "----------------------------------------\n" << endl;
    }

    // Display all tickets booked so far
    void showAllTickets() {
        cout << "\n--- All Booked Tickets for " << eventName << " ---" << endl;
        if (bookedTickets.size() == 0) {
            cout << "No tickets booked yet." << endl;
            return;
        }

        for (int i = 0; i < bookedTickets.size(); i++) {
            bookedTickets[i]->display(); // Runtime polymorphism
        }
        cout << "--------------------------------------------\n" << endl;
    }

    // Display status of seats
    void showStatus() {
        cout << "\n--- Venue and Seat Status ---" << endl;
        cout << "Event Name    : " << eventName << endl;
        cout << "Venue Capacity: " << venueCapacity << " (Const Member)" << endl;
        cout << "Total Sold    : " << Ticket::getTotalTicketsSold() << " / " << venueCapacity << endl;
        cout << "Remaining     : " << (venueCapacity - Ticket::getTotalTicketsSold()) << endl;
        cout << "Seats Booked per Category:" << endl;
        cout << "  Regular : " << regularCount << "/" << regularLimit << endl;
        cout << "  VIP     : " << vipCount << "/" << vipLimit << endl;
        cout << "  Student : " << studentCount << "/" << studentLimit << endl;
        cout << "-----------------------------\n" << endl;
    }

    string getEventName() { return eventName; }
    int getCapacity() { return venueCapacity; }
};

int main() {
    cout << "========================================" << endl;
    cout << "   Event Ticket Booking System" << endl;
    cout << "   Made by: Nikhil Suthar" << endl;
    cout << "========================================" << endl;

    // Venue capacity is fixed to 6 seats for testing
    Event myEvent("College Live Concert 2026", 6);

    cout << "Event: " << myEvent.getEventName() << endl;
    cout << "Venue Capacity: " << myEvent.getCapacity() << " seats\n" << endl;

    int choice = 0;

    while (choice != 5) {
        cout << "1. Book Ticket" << endl;
        cout << "2. View Pricing Rules" << endl;
        cout << "3. View Venue Status" << endl;
        cout << "4. Show All Booked Tickets" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice (1-5): ";
        cin >> choice;

        if (choice == 1) {
            int cat;
            string name;

            cout << "\nChoose Category:" << endl;
            cout << "1. Regular (Base ₹600 + 5% fee)" << endl;
            cout << "2. VIP (Base ₹1500 + ₹300 perks + 10% fee)" << endl;
            cout << "3. Student (Base ₹450 - 20% discount + ₹20 fee)" << endl;
            cout << "Enter category (1-3): ";
            cin >> cat;

            cout << "Enter Attendee Name: ";
            cin.ignore();
            getline(cin, name);

            if (name == "") {
                name = "Guest";
            }

            // Exception handling with try and catch
            try {
                myEvent.bookTicket(cat, name);
            }
            catch (OversoldException &e) {
                cout << "\n[EXCEPTION CAUGHT] " << e.message << "\n" << endl;
            }
        }
        else if (choice == 2) {
            cout << "\n--- Pricing Rules ---" << endl;
            cout << "Regular : ₹600 base + 5% fee = ₹630" << endl;
            cout << "VIP     : ₹1500 base + ₹300 perks + 10% fee = ₹1950" << endl;
            cout << "Student : ₹450 base - 20% discount + ₹20 fee = ₹380" << endl;
            cout << "---------------------\n" << endl;
        }
        else if (choice == 3) {
            myEvent.showStatus();
        }
        else if (choice == 4) {
            myEvent.showAllTickets();
        }
        else if (choice == 5) {
            cout << "\nExiting... Program submitted by Nikhil Suthar." << endl;
        }
        else {
            cout << "Invalid choice, please enter between 1 and 5.\n" << endl;
        }
    }

    return 0;
}
