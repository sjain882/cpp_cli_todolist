// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2023/24)
// Department of Computer Science, Swansea University
//
// Author: 2007908
//
// Canvas: https://canvas.swansea.ac.uk/courses/44636
// -----------------------------------------------------
// A Task class contains multiple 'tags' (e.g., a tag might be 'home' and
// another tag could be 'uni'). A Task also has a identifier (e.g. 'Complete
// Coursework') a completed status (completed or not) and due date. An
// uninitialised due date (see date.cpp/date.h) means the task does not have a
// due date.
// -----------------------------------------------------

#ifndef TASK_H
#define TASK_H

#include "date.h"
#include "lib_json.hpp"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

using TagContainer = std::vector<std::string>;
using JsonObject = nlohmann::json;

class Task {

    private:
        std::string ident;
        TagContainer tags;
        bool completed;
        Date dueDate;

    public:
        explicit Task(std::string tIdent);
        const std::string &getIdent() const noexcept;
        void setIdent(std::string tIdent) noexcept;

        const std::vector<std::string> &getTags() const noexcept;
        bool addTag(std::string tIdent);
        bool deleteTag(const std::string &tIdent);
        unsigned int numTags() const noexcept;
        bool containsTag(const std::string &tIdent) const noexcept;

        const Date &getDueDate() const noexcept;
        void setDueDate(Date newDate) noexcept;

        const bool &isComplete() const noexcept;
        void setComplete(bool isComplete) noexcept;

        friend bool operator==(const Task &t1, const Task &t2);

        nlohmann::json json() const;
        std::string str() const;

};

#endif // TASK_H
