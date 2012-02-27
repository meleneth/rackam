#ifndef ___webdatafetcher_inc
#define ___webdatafetcher_inc 1

#include "web_request.hpp"
#include <string>
#include <vector>

using std::string;
using std::vector;

class WebDataFetcher {
    public:
        WebDataFetcher(WebRequest *request);
        virtual ~WebDataFetcher();

        virtual int tick(void);
        virtual string info_update_string(void);
        string table_id(string id);

        WebRequest *request;

        vector<string> output_lines;
        unsigned int line_no;
        unsigned int num_lines;
        string title;

    private:
    protected:
};

#endif
