#ifndef ___console_inc
#define ___console_inc 1

#include<list>
#include<iostream> // Evil

#include<sstream>

#define MAKE_STRING( msg )  ( ((std::ostringstream&)(std::ostringstream() << msg)).str() )

#include <iostream>  // I/O 
#include <fstream>   // file I/O

using std::list;
using std::string;
using std::ofstream;
using std::ios;
using std::endl;

#include<rackam_types.hpp>

namespace Blackbeard {
class Console {
    public:
        // Public data members go here.
        Console(); // Constructor
        ~Console(); // Destructor

        void log(std::string line);
        void fatal(std::string line);
        void box_log(std::string line);
        void open_log_file(void);


        list<std::string> loglines;
        string input;
        bool print_logs;
        bool print_on_delete;
        bool keep_logs;
        bool save_to_file;
        ofstream out;

    private:
        // Private members go here.
    protected:
        // Protected members go here.
};

extern Console *console;

}

#endif
