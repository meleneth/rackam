#include "console.hpp"

#include<iomanip>

using std::string;
using std::stringstream;
using std::list;
using std::setprecision;
using namespace Blackbeard;

#define CONSOLE_MAX_SIZE 1000

// Public data members go here.
Console::Console() // Constructor
{
    print_logs = 0;
    input = "";
    print_on_delete = 0;
    keep_logs = 1;
    save_to_file = 0;

    box_log("Console Initialized");
}

Console::~Console() // Destructor
{
    if(print_on_delete){
        list<string>::iterator i;
        for(i = loglines.end(); ;)
        {
            --i;
            printf("%s\n", i->c_str());
            if ( i == loglines.begin()){
                break;
            }
        }
    }
    if(save_to_file){
        out.close();
    }
}

void Console::open_log_file(void)
{
    out.open("console.log", ios::out);
    save_to_file = 1;
}

void Console::log(string line)
{
    if(keep_logs)
        loglines.push_front(line);
    if(print_logs){
        printf("%s\n", line.c_str());
        fflush(stdout);
    }
    if(save_to_file){
        out << line << endl;
    }
}

void Console::fatal(string line)
{
    log(line);
}

void Console::box_log(string line)
{
    string Border(line.length() + 2, '-');

    log("+" + Border + "+");
    log("| " + line + " |");
    log("+" + Border + "+");
}

