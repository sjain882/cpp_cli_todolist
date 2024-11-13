// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2023/24)
// Department of Computer Science, Swansea University
//
// Author: 2007908
//
// Canvas: https://canvas.swansea.ac.uk/courses/44636
// -----------------------------------------------------

#include "project.h"

// *DONE TODO Write a constructor that takes one parameter, a string identifier and
// initialises the object and member data.
//
// Example:
//  Project p{"projectIdent"};
Project::Project(std::string projectIdent)
{
    ident = projectIdent;

}

// *DONE TODO Write a function, size, that takes no parameters and returns an unsigned
// int of the number of Tasks in the Project contains.
//
// Example:
//  Project p{"projectIdent"};
//  auto size = p.size();
unsigned int Project::size() const noexcept
{
    return tasks.size();
}

// TODO Write a function, getIdent, that returns the identifier for the Project.
//
// Example:
//  Project pObj{"projectIdent"};
//  auto ident = pObj.getIdent();
const std::string& Project::getIdent() const noexcept
{
    return ident;
}

// TODO Write a function, setIdent, that takes one parameter, a string for a new
// Project identifier, and updates the member variable. It returns nothing.
//
// Example:
//  Project pObj{"projectIdent"};
//  pObj.setIdent("projectIdent2");
void Project::setIdent(std::string pIdent) noexcept
{
    ident = pIdent;
}

// TODO Write a function, newTask, that takes one parameter, a Task identifier,
// (a string) and returns the Task object as a reference. If an object with the
// same identifier already exists, then the existing object should be returned.
// Throw a std::runtime_error if the Task object cannot be inserted into the
// container for whatever reason.
//
// Example:
//  Project pObj{"projectIdent"};
//  pObj.newTask("newTaskName");
Task &Project::newTask(const std::string &tIdent)
{

    std::vector<Task>::iterator it;

    for (it = tasks.begin(); it != tasks.end(); it++)
    {
        if (tIdent == it->getIdent())
        {
            return *it;
        }
    }

    Task newTask = Task(tIdent);
    tasks.push_back(newTask);

    return getTask(tIdent);

}

// TODO Write a function, addTask, that takes one parameter, a Task object, and
// returns true if the object was successfully inserted. If an object with the
// same identifier already exists, then:
//  - the tags should be merged
//  - completed status overwritten by the task being added
//  - dueDate overwritten by the task being added
//  - false should be returned.
//
// Example:
//  Project pObj{"projectIdent"};
//  Task tObj{"taskIdent"};
//  pObj.addItem(tObj);
bool Project::addTask(Task task)
{
    std::vector<Task>::iterator it;

    for (it = tasks.begin(); it != tasks.end(); it++)
    {
        if (task.getIdent() == it->getIdent())
        {

            // Add all the tags from the proposed Task to add into the existing 
            TagContainer tagsToAdd = task.getTags();

            for (unsigned int i = 0; i < tagsToAdd.size(); ++i)
            {
                it->addTag(tagsToAdd[i]);
            }

            it->setComplete(task.isComplete());
            it->setDueDate(task.getDueDate());
            return false;
        }
    }

    tasks.push_back(task);
    return true;

}

// TODO Write a function, getTask, that takes one parameter, a Task identifier
// (a string) and returns the Task as a reference. If no Task exists, throw an
// appropriate exception.
//
// Hint:
//  See the test scripts for the exception expected.
//
// Example:
//  Project pObj{"projectIdent"};
//  pObj.newTask("newTaskName");
//  auto tObj = pObj.getTask("newTaskName");
Task &Project::getTask(const std::string &tIdent)
{
    for (auto it = tasks.begin(); it != tasks.end(); it++)
    {
        if (it->getIdent() == tIdent)
        {
            return *it;
        }
    }

    throw std::out_of_range("No Task exists with this identity");
}


// TODO Write a function, deleteTask, that takes one parameter, a Task
// identifier (a string), deletes it from the container, and returns true if the
// Task was deleted. If no Task exists, throw an appropriate exception.
//
// Example:
//  Project pObj{"projectIdent"};
//  pObj.newTask("newTaskName");
//  bool result = pObj.deleteTask("newTaskName");
bool Project::deleteTask(const std::string &tIdent)
{
    for (auto it = tasks.begin(); it != tasks.end(); it++)
    {
        if (it->getIdent() == tIdent)
        {
            tasks.erase(it);
            return true;
        }
    }

    throw std::out_of_range("No Task exists with this identity");

}

// TODO Write an == operator overload for the Project class, such that two
// Project objects are equal only if they have the same identifier and same
// Tasks.
//
// Example:
//  Project pObj{"projectIdent1"};
//  pObj.newTask("newTaskName");
//  Project pObj1{"projectIdent2"};
//  if(pObj1 == pObj2) {
//    ...
//  }
bool operator==(const Project &c1, const Project &c2)
{
    return (c1.getTasks() == c2.getTasks() && c1.getIdent() == c2.getIdent());
}

const TaskContainer &Project::getTasks() const noexcept
{
    return tasks;
}

// TODO Write a function, str, that takes no parameters and returns a
// std::string of the JSON representation of the data in the Project.
//
// See the coursework specification for how this JSON should look.
//
// Example:
//  Project pObj{"projectIdent"};
//  std::string s = pObj.str();
std::string Project::str() const
{

    std::stringstream sstream;

    sstream << "\"" << ident << "\":{";

    for (long unsigned int i = 0; i < tasks.size(); ++i)
    {
        if (i != (tasks.size() - 1))
        {
            sstream << tasks[i].str() << "},";
        }
        else
        {
            sstream << tasks[i].str() << "}";
        } 
    }

    return sstream.str();

}

nlohmann::json Project::json() const
{
    JsonObject jsonObj = json();
    jsonObj[getIdent()] = JsonObject::object();
    
    TaskContainer tasksToAdd = getTasks();

    for (auto it = tasksToAdd.begin(); it != tasksToAdd.end(); it++)
    {
        jsonObj[getIdent()].push_back(it->json());
    }

    return jsonObj;
}