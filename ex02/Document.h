/* Yehuda Neumann 305539066 */
/* Adiel Matuf 307895268 */

#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <stdexcept>
#pragma once

using std::string;
using std::vector;

class Document {
private:
	vector<string> _lines; //each line is a string
  int _current_line;
    
	Document(const Document& doc);
	Document& operator=(const Document& doc) { return *this;};
	
public:
	Document();
	~Document();
  void print_current() const; //prints the current line (ed maintains a current line)
	void current_info() const; //prints line number of current line followed by TAB followed by current line
	void print_all() const; //prints all lines
  void change_current(int); // makes line #7 the current line
  void append_after(const string&); // appends new text after the current line
  void insert_before(const string&); // inserts new text before the current line
  void change_line(const string&); // changes the current line for text that follows
  void delete_current(); // deletes the current line
  int search(const string&); // searches forward after current line for the specified text. 
                  // The search wraps to the beginning of the buffer and continues down to the current line, 
                  //if necessary
  void replace(string&, string&); //replaces old string with new in current line (google: C++ split or token)
  void quit(); //Quits the editor without 
  
  int get_current_line() const;
  void set_current_line(int);
};