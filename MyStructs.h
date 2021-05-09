#ifndef MYSTRUCTS_H
#define MYSTRUCTS_H
#include <string>

#include "List.h"
#include "HashTable.h"
#include "AVL.h"

class Passanger {
public:
    std::string passport_number;	// size = 12
    std::string birth_date;		// size = 128
    std::string full_name;		// size = 64
    std::string issue_date;


    Passanger() : passport_number(), birth_date(), full_name(), issue_date() {};

    Passanger(std::string pass_num, std::string full_name, std::string birth_date, std::string issue_date) :
        passport_number(pass_num), birth_date(birth_date), full_name(full_name), issue_date(issue_date) {};

    Passanger(std::string pass_num) :
        passport_number(pass_num), birth_date(), full_name() {};

    bool operator> (const Passanger* b)
    {
        return this->passport_number > b->passport_number;
    }

    friend bool operator>  (const Passanger& a, const Passanger& b)
    {
        return a.passport_number > b.passport_number ? true : false;
    }

    friend bool operator<  (const Passanger& a, const Passanger& b)
    {
        return a.passport_number < b.passport_number ? true : false;
    }

    friend bool operator== (const Passanger& a, const Passanger& b)
    {
        return a.passport_number == b.passport_number ? true : false;
    }

    /*friend std::ostream& operator << (std::ostream& out, Passanger& a)
    {
        return out << "passport_number: " << a.passport_number << endl <<
            "place_date: " << a.place_date << endl <<
            "full_name: " << a.full_name << endl;
    }*/
};

class Flight {
public:
    std::string flight_number;	// size = 8
    std::string airline_name;	// size = 64
    std::string a_from;			// size = 64
    std::string a_to;			// size = 64
    std::string date;			// size = 11
    std::string time;			// size = 6
    unsigned int all_seats;
    unsigned int free_seats;

    Flight() : flight_number(), airline_name(), a_from(), a_to(),
        date(), time(), all_seats(0), free_seats(0) {};

    Flight(std::string f_num, std::string a_name, std::string a_from, std::string a_to, std::string date,
        std::string time, unsigned int all_seats, unsigned int free_seats)
    {
        this->flight_number = f_num;
        this->airline_name = a_name;
        this->a_from = a_from;
        this->a_to = a_to;
        this->date = date;
        this->time = time;
        this->all_seats = all_seats;
        this->free_seats = free_seats;
    }

    Flight(std::string f_num)
    {
        this->flight_number = f_num;
        this->airline_name = "";
        this->a_from = "";
        this->a_to = "";
        this->date = "";
        this->time = "";
        this->all_seats = 0;
        this->free_seats = 0;
    }

    friend bool operator> (const Flight& a, const Flight& b)
    {
        return a.flight_number > b.flight_number ? true : false;
    }

    friend bool operator< (const Flight& a, const Flight& b)
    {
        return a.flight_number < b.flight_number ? true : false;
    }

    friend bool operator== (const Flight& a, const Flight& b)
    {
        return a.flight_number == b.flight_number ? true : false;
    }

    /*friend std::ostream& operator << (std::ostream& out, Flight& a)
    {
        return out << "flight_num: " << a.flight_number << endl <<
            "airline_name: " << a.airline_name << endl << endl << endl;
    }*/
};

class Ticket {
public:
    std::string passport_number; // size = 11
    std::string flight_number;	// size = 7
    std::string ticket_number;	// size = 9

    Ticket() : passport_number(), flight_number(), ticket_number() {};

    Ticket(std::string pas_num, std::string fly_num, std::string tick_num) : passport_number(pas_num),
        flight_number(fly_num), ticket_number(tick_num) {};

    Ticket(std::string tick_num) : passport_number(),
        flight_number(), ticket_number(tick_num) {};

    friend bool operator> (const Ticket& a, const Ticket& b)
    {
        return a.ticket_number > b.ticket_number;
    }

    friend bool operator>= (const Ticket& a, const Ticket& b)
    {
        return a.ticket_number >= b.ticket_number;
    }

    bool operator<  (const Ticket& b)
    {
        return this->ticket_number < b.ticket_number;
    }

    friend bool operator== (const Ticket& a, const Ticket& b)
    {
        return a.ticket_number == b.ticket_number;
    }

    /*friend std::ostream& operator << (std::ostream& out, Ticket& a)
    {
        return out << "pass: " << a.passport_number << endl <<
            "flight_num: " << a.flight_number << endl <<
            "ticket_num: " << a.ticket_number << endl;
    }*/
};

#endif // MYSTRUCTS_H
