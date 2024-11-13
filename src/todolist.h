// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2023/24)
// Department of Computer Science, Swansea University
//
// Author: 2007908
//
// Canvas: https://canvas.swansea.ac.uk/courses/44636
// -----------------------------------------------------
// The root object that holds all data for 371todo. This
// class contains Projects, which in turn hold Tasks,
// which have a name, due date, completed status, and tags.
// -----------------------------------------------------

#ifndef TODOLIST_H
#define TODOLIST_H

#include "project.h"
#include "lib_json.hpp"
#include "date.h"
#include <fstream>
#include <sstream>

using ProjectContainer = std::vector<Project>;
using JsonObject = nlohmann::json;

class TodoList {

    private:
        ProjectContainer projects;

    public:
        TodoList();
        unsigned int size() const noexcept;

        const Project &newProject(const std::string &pIdent);
        bool addProject(Project project);

        ProjectContainer getProjects() const noexcept;
        Project getProject(const std::string &pIdent) const;
        bool deleteProject(const std::string &pIdent);

        void save(std::string dbFileName) const;
        void load(std::string dbFileName);
        void load_2(std::string dbFileName);

        friend bool operator==(const TodoList &t1, const TodoList &t2);

        nlohmann::json json() const;
        std::string str() const;

};

#endif // TODOLIST_H
