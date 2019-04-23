/* Yehuda Neumann 305539066 */
/* Adiel Matuf 307895268 */

#include "Document.h"

Document :: Document(): _current_line(-1){}

Document:: ~Document(){}
    
void Document :: print_current() const
{
    std::cout << this-> _lines.at(_current_line) << std::endl;
}
    
void Document :: current_info() const
{
    std::cout << _current_line+1 << "\t";
    std::cout << _lines.at(_current_line) << std::endl;
}

void Document :: print_all() const
{
    for (int i = 0; i < (int)this-> _lines.size(); i++) {
        std::cout << this-> _lines.at(i) << std::endl;
    }
}

void Document :: change_current(int new_current)
{
    int fix_current = new_current-1;
    if(fix_current <= (int)_lines.size())
        this-> _current_line = fix_current;
    else
        throw std::runtime_error("error, new current line is out of scope!");
    
}

void Document :: append_after(const string& append)
{
    if(_current_line >= 0 && _current_line < (int)_lines.size()-1)
    {
        vector<string>::iterator it = this->_lines.begin() + this->_current_line+1;
        this->_lines.insert(it, append);
    }
    else
        this-> _lines.push_back(append);
    this-> _current_line++;
        
}

void Document :: insert_before(const string& insert)
{
    vector<string>::iterator it = this->_lines.begin() + this->_current_line;
    this->_lines.insert(it, insert);
    this->_current_line++;
}

void Document :: change_line(const string& new_line)
{
    _lines.at(_current_line) = new_line;
}

void Document :: delete_current()
{
    vector<string>::iterator it;
    it = this->_lines.begin() + this->_current_line;
    this->_lines.erase(it);
    this->_current_line = (this-> _current_line == 0)? 0: this->_current_line-1;
}

int Document :: search(const string& index)
{
    // string first index.
    size_t pos = 0;
    for (int i = 0; i < (int)this-> _lines.size(); i++) {
        if((pos = this->_lines.at(i).find(index)) != std::string::npos)
            return i;
    }
    return -1;
}

void Document :: replace(string& old, string& new_word)
{
    int f_idx = this->search(old);
    if(f_idx < 0)
    {
        std::cout << old + " not found." << std::endl;
        return;   
    }
    
    // string first index.
    size_t pos = this->_lines.at(f_idx).find(old);
    // copy the prefix of the word, until pos.
    string prefix = this->_lines.at(f_idx).substr(0, pos);
    // copy the postfix, from the end of the old word to the end.
    string postfix = this->_lines.at(f_idx).substr(pos + (size_t)old.size());
    // replace.
    this->_lines.at(f_idx) = prefix + new_word + postfix;
}

void Document :: quit()
{
    this-> _lines.clear();
    this->_current_line = -1;
}

void Document::set_current_line(int n_line)
{
    _current_line = n_line;
}

int Document::get_current_line() const
{
    return _current_line;
}
