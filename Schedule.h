#ifndef AED2324_PRJ1_G1207_SCHEDULE_H
#define AED2324_PRJ1_G1207_SCHEDULE_H

#include "Lesson.h"
#include "UC.h"
#include <iostream>
#include <vector>
#include <set>
using namespace std;

// this class represents a schedule
class Schedule {
    private:
        set<Lesson> lessons;
        set<Student> students;
        UC UcClass;
    public:
    /*
     * Class constructor
     *
     * Sets lessons
     *
     * @paramt lessons : private , Lessons to allocate to the students;
     */
        Schedule(set<Lesson> lessons);

        /*
         * Adds a lesson to the schedule
         */
        void addLesson(const Lesson lesson);

        /*
         * Removes a lesson from the schedule
         */
        void removeLesson(const Lesson lesson);

        /*
         * Returns a lesson from the schedule
         */
        set<Lesson> getLesson() const;

        /*
         * Prints the schedule
         */
        void drawSchedule() const;

        // verifies if it has the same UcCode
        bool hasSameUcCode(Schedule UcCode);
        // return the UC class
        UC getUcClass();
        // get students of a class
        set<Student> getStudents();
        void addStudent(Student student);
        void removeStudent(Student student);
};

#endif //AED2324_PRJ1_G1207_SCHEDULE_H
