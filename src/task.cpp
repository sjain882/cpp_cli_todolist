// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2023/24)
// Department of Computer Science, Swansea University
//
// Author: 2007908
//
// Canvas: https://canvas.swansea.ac.uk/courses/44636
// -----------------------------------------------------

#include "task.h"

// TODO Write a constructor that takes one parameter, a string identifier
//  and initialises the object and member data.
//
// Example:
//  Task tObj{"Task Name"};
Task::Task(std::string tIdent)
{
    ident = tIdent;
    completed = false;
    dueDate = Date();
}

// TODO Write a function, getIdent, that returns the identifier for the Task.
//
// Example:
//  Task tObj{"Task Name"};
//  auto ident = tObj.getIdent();
const std::string &Task::getIdent() const noexcept
{
    return ident;
}

// TODO Write a function, setIdent, that takes one parameter, a string for a new
//  Task identifier, and updates the member variable. It returns nothing.
//
// Example:
//  Task tObj{"Task Name"};
//  auto ident = tObj.setIdent("New Task Name");
void Task::setIdent(std::string tIdent) noexcept
{
    this->ident = tIdent;
}

// TODO Write a function, addTag, that takes one parameters, a tag
//  string and returns true if the entry was inserted into the
//  container or false if the tag already existed.
//
// Example:
//  Task tObj{"Task Name"};
//  tObj.addTag("tag");
bool Task::addTag(std::string tIdent)
{

    for (auto it = tags.begin(); it != tags.end(); it++)
    {
        if (tIdent == *it)
        {
            return false;
        }
    }

    tags.push_back(tIdent);

    return true;
}

// TODO Write a function, deleteTag, that takes one parameter, a tag
// string, deletes it from the container, and returns true if the tag
// string was deleted. If no tag exists with that name, throw an appropriate
// exception.
//
// Example:
//  Task tObj{"Task Name"};
//  tObj.addTag("tag");
//  tObj.deleteTag("tag");
bool Task::deleteTag(const std::string &tIdent) {

    for (auto it = tags.begin(); it != tags.end(); it++) {

        if (tIdent == *it) {
            tags.erase(it);
            return true;
        }
    }

    throw std::out_of_range("No such tag exists!");
}



// TODO Write a function, numTags, that takes no parameters and returns an
// unsigned int of the number of tags in the Task contains.
//
// Example:
//  Task tObj{"Task Name"};
//  tObj.numTags();
unsigned int Task::numTags() const noexcept
{
    return tags.size();
}


// TODO Write a function, containsTag, that takes one parameter, a tag string.
// If the tag exists, return true. Otherwise return false.
//
// Example:
//  Task tObj{"Task Name"};
//  tObj.addTag("tag");
//  tObj.findTag("tag");
bool Task::containsTag(const std::string &tIdent) const noexcept
{
    bool tagExists = false;

    for (auto it = tags.begin(); it != tags.end(); it++)
    {
        if (tIdent == *it)
        {
            tagExists = true;
        }
    }

    return tagExists;
}

// TODO Write a function, getDueDate, that returns the due date for the Task.
//
// Example:
//  Task tObj{"Task Name"};
//  tObj.getDueDate();
const Date &Task::getDueDate() const noexcept
{
    return dueDate;
}

// TODO Write a function, setDueDate, that takes one parameter, a Date for
// a new due date, and updates the member variable. It returns nothing.
//
// Example:
//  Task tObj{"Task Name"};
//  Date d = Date();
//  tObj.setDueDate(d);
void Task::setDueDate(Date newDate) noexcept
{
    dueDate = newDate;
}

// TODO Write a function, setComplete, that takes one parameter, a bool for
// a new completed state, and updates the member variable. It returns nothing.
//
// Example:
//  Task tObj{"Task Name"};
//  tObj.setComplete(true);
void Task::setComplete(bool isComplete) noexcept
{
    completed = isComplete;
}

// TODO Write a function, isComplete, that returns the completed state for the
// Task.
//
// Example:
//  Task tObj{"Task Name"};
//  if(tObj.isComplete()) {
//   ...
//  }
const bool &Task::isComplete() const noexcept
{
    return completed;
}

// Returns all the tags in a task
const std::vector<std::string> &Task::getTags() const noexcept
{
    return tags;
}

// TODO Write an == operator overload for the Task class, such that two
// Tasks objects are equal only if they have the same identifier, dueDate,
// completed state, and tags.
//
// Example:
//  Task tObj1{"Task Name"};
//  Task tObj2{"Task Name"};
//  if(tObj1 == tObj2) {
//   ...
//  }
bool operator==(const Task &t1, const Task &t2)
{
    return ((t1.getIdent() == t2.getIdent()) 
            && (t1.getDueDate() == t2.getDueDate())
            && (t1.isComplete() == t2.isComplete())
            && (t1.getTags() == t2.getTags()));
}

// TODO Write a function, str, that takes no parameters and returns a
//  std::string of the JSON representation of the data in the Item.
//
// See the coursework specification for how this JSON should look.
//
// Example:
//  Item iObj{"itemIdent"};
//  std::string s = iObj.str();
std::string Task::str() const
{
    std::stringstream sstream;

    sstream << "\"" << ident << "\":"; 

    sstream << "\"{completed\":" << completed << ",\"dueDate\": " << getDueDate().str()
         << ",\"tags\":[";

    for (unsigned int i = 0; i < tags.size(); ++i)
    {
        // Only include comma if it's not the last one
        if (i != (tags.size() - 1))
        {
            sstream << "\"" << tags[i] << "\",";
        }
        else
        {
            sstream << "\"" << tags[i] << "\"";
        }        
    }

    sstream << "]}";

    return sstream.str();
}

JsonObject Task::json() const
{
    JsonObject jsonObj;

    jsonObj[getIdent()] = JsonObject::object();
    jsonObj[getIdent()]["completed"] = isComplete();
    jsonObj[getIdent()]["dueDate"] = getDueDate().str();
    jsonObj[getIdent()]["tags"] = JsonObject::array();

    std::vector<std::string> tagsToAdd = getTags();

    for (auto it = tagsToAdd.begin(); it != tagsToAdd.end(); it++)
    {
        jsonObj[getIdent()]["tags"].push_back(*it);
    }

    return jsonObj;
}
