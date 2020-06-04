#include "framework/json.hpp"
#include "framework/inja.hpp"

#include <sys/stat.h>

#include <iostream>
#include <fstream>
#include <iomanip>

using json = nlohmann::json;
using namespace std;
using namespace inja;

string typstr(int len) {
	if (len <= 8) {
		return "unsigned char";
	}
	if (len <= 16) {
		return "unsigned short";
	}
	if (len <= 32) {
		return "unsigned long";
	}
	return "char[" + to_string(len) + "]";
}

const char *temp = R"TEMPLATE(// class {{ Id }}
// Description: {{ Description }}
#include "../pgn.h"
class {{ Id }} {
  public:
## if isArray(Fields)
##  for field in Fields
##   if field.Id != "reserved"
    {% if field.BitLength <= 8 %}unsigned char {{ field.Id }}; {%
       else if field.BitLength <= 16 %}unsigned short {{ field.Id }}; {%
       else if field.BitLength <= 32 %}unsigned long {{ field.Id }}; {%
       else %}char {{field.Id}}[{{ field.BitLength }}]; {%
    endif %}
##   endif
##  endfor
## else
    {% if Fields.Field.BitLength <= 8 %}unsigned char {{ Fields.Field.Id }}; {%
       else if Fields.Field.BitLength <= 16 %}unsigned short {{ Fields.Field.Id }}; {%
       else if Fields.Field.BitLength <= 32 %}unsigned long {{ Fields.Field.Id }}; {%
       else %}char {{Fields.Field.Id}}[{{ Fields.Field.BitLength }}]; {%
    endif %}
## endif
    const pgn_t getPGN() { return {{ PGN }}; }
};
)TEMPLATE";
//## for field in Fields

int main(int argc, char *argv[]) {
    // Parse the pgns.json file
    json j;
    ifstream pgnfile("pgns.json");
    pgnfile >> j;

    mkdir("generated", 0777);
    int needed[] = { 59392, /* iso ack */
	    	     59904, /* iso req */
		     60928, /* iso address claim */
		     60416, /* multi packet conn mgmt TP.CM */
		     60160  /* multi packet data transfer TP.DT */
    };


    json pgns = j["PGNs"];
    for (json::iterator it = pgns.begin(); it != pgns.end(); ++it) {
	    auto pgnid = (*it)["PGN"].get<int>();
	    if (binary_search(needed, needed + sizeof(needed), pgnid)) {
		    Environment env;
		    string classname = (*it)["Id"].get<string>();
		    string filename = "generated/" + classname + ".cc";
		    ofstream classfile(filename);
		    render_to(classfile, temp, *it);
		    classfile.close();
	    }
    }
}
