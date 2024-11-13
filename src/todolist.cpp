// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2023/24)
// Department of Computer Science, Swansea University
//
// Author: 2007908
//
// Canvas: https://canvas.swansea.ac.uk/courses/44636
// -----------------------------------------------------
#include "todolist.h"
#include <stdio.h>
#include <iostream>

// TODO Write a TodoList constructor that takes no parameters and constructs an
//  empty todolist.
//
// Example:
//  TodoList tObj{};
TodoList::TodoList() { }

// TODO Write a function, size, that takes no parameters and returns an unsigned
//  int of the number of projects the TodoList contains.
//
// Example:
//  TodoList tObj{};
//  auto size = tObj.size();
unsigned int TodoList::size() const noexcept
{
    return projects.size();
}

// TODO Write a function, newProject, that takes one parameter, a project
//  identifier, and returns the Project object as a reference. If an object
//  with the same identifier already exists, then the existing object should be
//  returned. Throw a std::runtime_error if the Project object cannot be
//  inserted into the container.
//
// Example:
//  TodoList tObj{};
//  tObj.newProject("projectIdent");
const Project &TodoList::newProject(const std::string &pIdent)
{
    std::vector<Project>::iterator it;

    for (it = projects.begin(); it != projects.end(); it++)
    {
        if (pIdent == it->getIdent())
        {
            return *it;
        }
    }

    Project newProject = Project(pIdent);
    projects.push_back(newProject);
    return getProject(pIdent);
}


// TODO Write a function, addProject, that takes one parameter, a Project
//  object, and returns true if the object was successfully inserted. If an
//  object with the same identifier already exists, then the contents should be
//  merged (see also Project::addTask) and then return false. Throw a
//  std::runtime_error if the Project object cannot be inserted into the
//  container for whatever reason.
//
// Example: 
//  TodoList tObj{};
//  Project cObj{"projectIdent"};
//  tObj.addProject(cObj);
bool TodoList::addProject(Project project)
{
    std::vector<Project>::iterator it;

    for (it = projects.begin(); it != projects.end(); it++)
    {
        if (project.getIdent() == it->getIdent())
        {

            // Add all the tasks from the proposed Project to add into the existing 
            TaskContainer tasksToAdd = project.getTasks();

            for (long unsigned int i = 0; i < tasksToAdd.size(); ++i)
            {
                it->addTask(tasksToAdd[i]);
            }

            return false;
        }
    }

    projects.push_back(project);
    return true;

}

// TODO Write a function, getProject, that takes one parameter, a Project
//  identifier and returns the Project. If no Project exists, throw an
//  appropriate exception.
//
// Example:
//  TodoList tObj{};
//  tObj.newProject("projectIdent");
//  auto cObj = tObj.getProject("projectIdent");
Project TodoList::getProject(const std::string &pIdent) const
{

    for (auto it = projects.begin(); it != projects.end(); it++)
    {
        if (pIdent == it->getIdent())
        {
            return *it;
        }
    }

    throw std::out_of_range("No such project exists!");
}


ProjectContainer TodoList::getProjects() const noexcept
{
    return projects;
}

// TODO Write a function, deleteProject, that takes one parameter, a Project
//  identifier, and deletes it from the container, and returns true if the
//  Project was deleted. If no Project exists, throw an appropriate exception.
//
// Example:
//  TodoList tObj{};
//  tObj.newProject("projectIdent");
//  tObj.deleteProject("projectIdent");
bool TodoList::deleteProject(const std::string &pIdent)
{

    for (auto it = projects.begin(); it != projects.end(); it++) {

        if (pIdent == it->getIdent()) {
            projects.erase(it);
            return true;
        }
    }

    throw std::out_of_range("No such project exists!");
}


// TODO Write a function, load, that takes one parameter, a std::string,
//  containing the filename for the database. Open the file, read the contents,
//  and populates the container for this TodoList. If the file does open throw
//  an appropriate exception (either std::runtime_error or a derived class).
//
// A note on clashes:
//  If you encounter two projects with the same key, or two tasks with the same
//  key within the same project, you may choose whichever project/task is parsed
//  by the nlohmann json library. The json spec on duplicate keys is undefined, so
//  you can default to the behaviour of the nlohmann json library.
//
// JSON formatting:
//  The JSON file has the following format (see the sample database.json file
//  also provided with the coursework framework):
// {
//     "Project 1" : {
//         "Task 1":  {
//             "completed": true,
//             "due": "2024-11-23",
//             "tags" : ["uni",
//                       "c++",
//                       "programming",
//                       "standard library"
//                       ...
//                      ]
//             ...
//         },
//         "Task 2":  {
//             "completed": false,
//             "tags" : ["uni",
//                       "c++",
//                       "programming",
//                       "inheritance"
//                       ...
//                      ]
//         },
//         ...
//     },
//     "Project 2": {
//         "Task 1": {
//             "completed": true
//         }
//         ...
//     }
// }
//
// More help:
//  To help you with this function, I've selected the nlohmann::json
//  library that you must use for your coursework. Read up on how to use it
//  here: https://github.com/nlohmann/json. You may not use any other external
//  library other than the one I have provided. You may choose to process the
//  JSON yourself without the help of the library but I guarantee this will be
//  more work.
//
//  Understanding how to use external libraries is part of this coursework! You
//  will need to use this file to deserialize the JSON from string
//  to the JSON object provided by this library. Don't just look at the code
//  provided below, or in the README on the GitHub and despair. Google search,
//  look around, try code out in a separate file to all figure out how to use
//  this library.
//
//  Once you have deserialized the JSON string into an object, you will need to
//  loop through this object, constructing Project and Task objects according
//  to the JSON data in the file.
//
// Example:
//  TodoList tObj{};
//  tObj.load("database.json");
void TodoList::load_2(std::string dbFileName)
{
        JsonObject jsonImport;
        std::ifstream file(dbFileName);

        // Check if file is empty
        if (file.peek() == std::ifstream::traits_type::eof())
        {
            throw std::runtime_error(dbFileName + " is empty");
        }

        // Check if we couldn't open the file at all
        if (file.fail())
        {
            throw std::runtime_error(dbFileName + " not found");
        }

        jsonImport = JsonObject::parse(file);

        // First level is the Project name / ident string
        for (JsonObject::iterator it = jsonImport.begin(); it != jsonImport.end(); ++it)
        {

            Project p = Project(it.key());

            // Second level is each task in that project
            for (JsonObject::iterator it2 = jsonImport.begin(); it2 != jsonImport.end(); ++it2)
            {

                Task t = Task(it2.key());

                // Set the completed state
                t.setComplete(jsonImport[it.key()][it2.key()]["completed"]);

                // Set the due date
                const std::string dueDateString = jsonImport[it.key()][it2.key()]["dueDate"];
                Date d = Date();
                d.setDateFromString(dueDateString);
                t.setDueDate(d);

                // Set the tags
                const std::vector<std::string> importedTags = jsonImport[it.key()][it2.key()]["tags"];

                for (auto it3 = importedTags.begin(); it3 != importedTags.end(); ++it3)
                {
                    t.addTag(*it3);

                p.addTask(t);
            }


            addProject(p);

        }
    }
}


void TodoList::load(std::string dbFileName)
{

    // Open and check file
    JsonObject jsonImport;
    std::ifstream file(dbFileName);

    // Check if file is empty
    if (file.peek() == std::ifstream::traits_type::eof())
    {
        throw std::runtime_error(dbFileName + " is empty");
    }

    // Check if we couldn't open the file at all
    if (file.fail())
    {
        throw std::runtime_error(dbFileName + " not found");
    }

    jsonImport = JsonObject::parse(file);

    // Iterate over imported json data
    // Use items() to keep aware of nesting levels
    // First level: projects
    for (auto& [pName, pVals] : jsonImport.items())
    {

        Project p = Project(pName);

        // Second level: tasks
        for (auto& [tName, tVals] : pVals.items())
        {

            Task t = Task(tName);

            // Set the completed status
            t.setComplete(jsonImport[pName][tName]["completed"]);

            // Set the date
            const std::string dueDateString = jsonImport[pName][tName]["dueDate"];
            Date d = Date();
            d.setDateFromString(dueDateString);
            t.setDueDate(d);

            // Import & set tags
            const std::vector<std::string> importedTags = jsonImport[pName][tName]["tags"];

            for (auto it = importedTags.begin(); it != importedTags.end(); ++it)
            {
                t.addTag(*it);
            }

            p.addTask(t);

        }
        addProject(p);
    }
}




// TODO Write a function, save, that takes one parameter, the path of the file
//  to write the database to. The function should serialise the TodoList object
//  as JSON.
//
// Example:
//  TodoList tObj{};
//  tObj.load("database.json");
//  ...
//  tObj.save("database.json");
void TodoList::save(std::string dbFileName) const
{
    // Open and check file
    JsonObject finalJson;
    std::ofstream file(dbFileName);

    // If we couldn't open the file at all
    if (file.fail())
    {
        throw std::runtime_error(dbFileName + " not found");
    }

    file << this->str();
}

// TODO Write an == operator overload for the TodoList class, such that two
//  TodoList objects are equal only if they have the exact same data.
//
// Example:
//  TodoList tObj1{};
//  TodoList tObj2{};
//  if(tObj1 == tObj2) {
//    ...
//  }
bool operator==(const TodoList &t1, const TodoList &t2)
{
    return ((t1.getProjects() == t2.getProjects()));
}

// TODO Write a function, str, that takes no parameters and returns a
//  std::string of the JSON representation of the data in the TodoList.
//
// Hint:
//  See the coursework specification for how this JSON should look.
//
// Example:
//  TodoList tObj{};
//  std::string s = tObj.str();
std::string TodoList::str() const
{

    std::stringstream sstream;

    sstream << "{";

    // Iterate over all projects
    for (long unsigned int i = 0; i < projects.size(); ++i)
    {
        // Only include comma if it's not the last one
        if (i != (projects.size() - 1))
        {
            sstream << projects[i].str() << "},";
        }
        else
        {
            sstream << projects[i].str() << "}";
        } 
    }

    sstream << "}";

    return sstream.str();
}

nlohmann::json TodoList::json() const
{
    JsonObject jsonObj = json();
    jsonObj = JsonObject::object();
    
    ProjectContainer projectsToAdd = getProjects();

    for (auto it = projectsToAdd.begin(); it != projectsToAdd.end(); it++)
    {
        jsonObj.push_back(it->json());
    }

    return jsonObj;
}