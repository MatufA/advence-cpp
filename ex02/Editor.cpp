/* Yehuda Neumann 305539066 */
/* Adiel Matuf 307895268 */

#include "Editor.h"

Editor :: Editor(): _delimeter_eof{"."}{}

Editor :: ~Editor(){}

bool is_pos_integer(const string& s)
{
    return(strspn(s.c_str(), "0123456789") == s.size());
}

void Editor:: start()
{
  while(true)
  {
    string command = "";
    
    std::cin >> command;
    
    if(!command.compare("p"))
    {
    this-> doc.print_current(); 
    }
    else if (!command.compare("n"))
    {
      this-> doc.current_info();
    }
    else if (!command.compare("%p"))
    {
      this-> doc.print_all();
    }
    else if (!command.compare("a"))
    {
      this->append();
    }
    else if (!command.compare("i"))
    {
      this->insert();
    }
  	else if (!command.compare("c"))
    {
      this->modify(); 
    }
    else if (!command.compare("d"))
    {
      this-> doc.delete_current();
    }
    else if (!command.substr(0,1).compare("/"))
    {
      this->search(command.substr(1));
    }
    else if (!command.substr(0,2).compare("s/"))
    {
      command.pop_back();
      this->replace(command);
    }
    else if (!command.compare("Q"))
    {
      this-> doc.quit();
      return;
    }
    else if(is_pos_integer(command))
    {
      this-> doc.change_current(atoi(command.c_str()));
    }
    else
      // throw exception if there is no legal command.
      throw std::runtime_error("error, command not found!");
  }
}

void Editor :: append()
{
  string input = "";
  std::cin.ignore();
  std::getline(std::cin, input);
  while(input.compare(_delimeter_eof))
  {
    this->doc.append_after(input);
    std::getline(std::cin, input);
  }
}

void Editor :: insert()
{
  string input = "";
  std::cin.ignore();
  std::getline(std::cin, input);
  while(input.compare(_delimeter_eof))
  {
    this->doc.insert_before(input);
    std::getline(std::cin, input);
  }
}

void Editor :: modify()
{
  string input = "";
  std::cin.ignore();
  std::getline(std::cin, input);
  while(input.compare(_delimeter_eof))
  {
    this-> doc.change_line(input);
    std::getline(std::cin, input);
  } 
}

void Editor :: search(const string& keyword)
{
  int idx = this-> doc.search(keyword);
  doc.set_current_line(idx);
  doc.print_current();
}

void Editor :: replace(string& str)
{
  // string first index.
  size_t pos = 0;
  // find '/' char in a string.
  string delimiter = "/";
  // old word for replacing.
  string old;
  while ((pos = str.find(delimiter)) != std::string::npos) 
  {
    // store the first occurence, store the last one (ignore s). 
    old = str.substr(0, pos);
    // erase old.
    str.erase(0, pos + delimiter.length());
  }
  this-> doc.replace(old, str);
}
  