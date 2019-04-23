/* Yehuda Neumann 305539066 */
/* Adiel Matuf 307895268 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdexcept>
#include <climits>
#include "Document.h"
#pragma once

using std::string;

/**
 * An editor cli
 * 
 * Command Meaning
 * p prints the current line (ed maintains a current line)
 * n prints line number of current line followed by TAB followed by current line
 * %p prints all lines
 * k makes line #k-th the current line
 * a appends new text after the current line
 * i inserts new text before the current line
 * c changes the current line for text that follows
 * d deletes the current line
 * /text searches forward after current line for the specified text. The search wraps to the beginning of the buffer and continues down to the current line, if necessary
 * s/old/new/ replaces old string with new in current line (google: C++ split or token)
 * Q Quits the editor without saving
 * 
*/

class Editor {
private:
	Document doc;
	
	//command by regex
	// regex _print_current{R"(^p$)"};
 //   regex _print_info{R"(^n$)"};
 //   regex _print_all{R"(^%p$)"};
 //   regex _change_current{R"(^\d+$)"};
 //   regex _append{R"(^a$)"};
 //   regex _insert{R"(^i$)"};
 //   regex _change_line{R"(^c$)"};
 //   regex _delete_current{R"(^d$)"};
 //   regex _search{R"(^\/\w+)"};
 //   regex _replace{R"(^s\/\w+\/\w+\/)"};
 //   regex _quit{R"(^Q$)"};
    string _delimeter_eof;
    
    Editor(const Editor& ed);
    Editor& operator=(const Editor&);
	
public:
	Editor();
	~Editor();
	
	//waiting for user's input and using Document's methods
	void start();
	void append();
	void insert();
	void modify();
	void search(const string&);
	void replace(string&);
};

 
 