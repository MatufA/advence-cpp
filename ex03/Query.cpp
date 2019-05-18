/* Yehuda Neumann 305539066 */
/* Adiel Matuf 307895268 */

#include "Query.h"
#include "TextQuery.h"
#include <memory>
#include <cstdlib>
#include <set>
#include <algorithm>
#include <iostream>
#include <cstddef>
#include <iterator>
#include <stdexcept>
#include <regex>
using std::regex;
using namespace std;

////////////////////////////////////////////////////////////////////////////////
std::shared_ptr<QueryBase> QueryBase::factory(const string& s)
{
  regex reg_one_word("^'?\\s*['\\w]+\\s*$");  // match one word only.
  regex reg_not("^\\s*NOT\\s+(['\\w]+)\\s*$");  // match if contains NOT and one word in the end.
  regex reg_and("^\\s*(['\\w]+)\\s+AND\\s+(['\\w]+)\\s*$");  // match if contains AND and one word befor and after.
  regex reg_or("^\\s*(['\\w]+)\\s+OR\\s+(['\\w]+)\\s*$");  // match if contains or and one word befor and after.
  regex reg_n("^\\s*(['\\w]+)\\s+(\\d+)\\s+(['\\w]+)\\s*$");  // match if contains n and one word befor and after.
  
  smatch result;  
  
  if(regex_match(s, reg_one_word)) 
    return std::shared_ptr<QueryBase>(new WordQuery(s));
  else if(regex_search(s, result, reg_not))
    return std::shared_ptr<QueryBase>(new NotQuery(result[1].str()));
  else if(regex_search(s, result, reg_and))
    return std::shared_ptr<QueryBase>(new AndQuery(result[1].str(), result[2].str()));
  else if(regex_search(s, result, reg_or))
    return std::shared_ptr<QueryBase>(new OrQuery(result[1].str(), result[2].str()));
  else if(regex_search(s, result, reg_n))
    return std::shared_ptr<QueryBase>(new NQuery(result[1].str(), result[3].str(), stoi(result[2].str())));
  else
    throw invalid_argument("Unrecognized search");
  
}
////////////////////////////////////////////////////////////////////////////////

QueryResult NotQuery::eval(const TextQuery &text) const
{
  QueryResult result = text.query(query_word);
  auto ret_lines = std::make_shared<std::set<line_no>>();
  auto beg = result.begin(), end = result.end();
  auto sz = result.get_file()->size();
  
  for (size_t n = 0; n != sz; ++n)
  {
    if (beg==end || *beg != n)
		ret_lines->insert(n);
    else if (beg != end)
		++beg;
  }
  return QueryResult(rep(), ret_lines, result.get_file());
    
}

QueryResult AndQuery::eval (const TextQuery& text) const
{
  QueryResult left_result = text.query(left_query);
  QueryResult right_result = text.query(right_query);
  
  auto ret_lines = std::make_shared<std::set<line_no>>();
  std::set_intersection(left_result.begin(), left_result.end(),
      right_result.begin(), right_result.end(), 
      std::inserter(*ret_lines, ret_lines->begin()));

  return QueryResult(rep(), ret_lines, left_result.get_file());
}

QueryResult OrQuery::eval(const TextQuery &text) const
{
  QueryResult left_result = text.query(left_query);
  QueryResult right_result = text.query(right_query);
  
  auto ret_lines = 
      std::make_shared<std::set<line_no>>(left_result.begin(), left_result.end());

  ret_lines->insert(right_result.begin(), right_result.end());

  return QueryResult(rep(), ret_lines, left_result.get_file());
}

/////////////////////////////////////////////////////////
QueryResult NQuery::eval(const TextQuery &text) const
{
  std::string query = "[\\.\",]?(" + left_query + "|" + right_query + ")[\\.\",]?";
  regex reg(query);  
  smatch res;
      
  QueryResult result = AndQuery::eval(text);
  auto ret_lines = std::make_shared<std::set<line_no>>();
  std::set<unsigned long>::iterator it;
      
  for (it = result.begin(); it != result.end(); ++it) {
    auto match = *(result.get_file()->begin() + *it);
    istringstream line(match);     // separate the line into words
    int count = 0;
    int flag = 0;
		std::string word;               
		while (line >> word) {        // for each word in that line
      flag += regex_search(word, res, reg);
		  if(flag && flag < 2) count++; 
		}
		if(count-1 <= dist) ret_lines->insert(*it);
  }
  
  return QueryResult(rep(), ret_lines, result.get_file());
}
/////////////////////////////////////////////////////////