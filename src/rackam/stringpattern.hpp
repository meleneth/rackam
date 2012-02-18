#ifndef ___stringpattern_inc
#define ___stringpattern_inc 1

#include<string>
#include<list>
#include<vector>

using std::vector;
using std::string;

class StringPattern {
    public:
        // Public data members go here.
        StringPattern(unsigned int max_part_no);
        ~StringPattern(); 
        
        void add_breaker(string pattern);
        void add_breaker(unsigned int part_no);

        int match(string target);

        string get_piece(unsigned int index);
        int get_piecen(unsigned int index);

        std::list<string> breakers;
        vector<unsigned int> part_order;
        unsigned int max_part_no;

        vector<string> results;
        string name;
    private:
        // Private members go here.
    protected:
        // Protected members go here.
};

#endif
