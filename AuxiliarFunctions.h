#ifndef AED2324_PRJ1_G1207_AUXILIARFUNCTIONS_H
#define AED2324_PRJ1_G1207_AUXILIARFUNCTIONS_H

#include "Student.h"
#include "Request.h"
#include "Schedule.h"
#include "Lesson.h"
#include "UC.h"
#include <string>
#include <set>
#include <utility>
#include <vector>
#include <queue>


using namespace std;

class AuxiliarFunctions {
    private:
        vector<Schedule> schedules;
        struct rejectedRequests_ {
            Request request;
            string reason;
            rejectedRequests_(Request request_, string reason_) : request(std::move(request_)), reason(std::move(reason_)) {};
        };

    public:

        static queue<Request> enrollmentRequests;
        static queue<Request> removalRequests;
        static queue<Request> switchRequests;
        static vector<rejectedRequests_> rejectedRequests;
        /**
        * Class constructor
        */
        AuxiliarFunctions();
        /**
         * Returns the student with the studentCode given
         *
         * @paramt studentCode : Student code;
         */
        static Student retStudent(const string &studentCode) ;

        /**
         * Concludes the enrollment request by adding that request to the queue of enrollmentRequests
         *
         * @paramt student : info of the student who wants to enroll;
         * @paramt UcClass : Uc class that the student given wants to enroll;
         */
        void concludeEnrollment(Student student, UC UcClass);

        /**
         * Concludes the removal request by adding that request to the queue of removalRequests
         *
         * @paramt student : info of the student who wants to leave;
         * @paramt UcClass : Uc class that the student given wants to leave;
         */
        void concludeRemoval(Student student, UC UcClass);

        /**
         * Concludes the switch request by adding that request to the queue of switchRequests
         *
         * @paramt student : info of the student who wants to switch;
         * @paramt UcClass : Uc class that the student given wants to switch;
         */
        void concludeSwitch(Student student, UC UcClass);

        // exceptions /////////////////////////////////////////////////////////////////////////////////
        // UC changes /////////////////////////////////////////////////////////////////////////////////
        /**
         * Returns a vector with the students of an Uc
         *
         * @paramt UcCode : Uc code;
         */
        vector<Schedule> UcClasses(const string& UcCode);
        /**
         * A student cannot be registered in more than 7 UCs at any given type
         *
         * @paramt request : request;
         */
        bool requestMax(Request &request);

        // there mut be at leas one class with a vacancy in the new UC/////////////////////////////////

        /**
         * Checks if the resulting schedule will not conflict with the student's original schedule
         *
         * @paramt request : request;
         */
        bool requestConflict(Request &request);
        // Class changes///////////////////////////////////////////////////////////////////////////////

        /**
         * Checks some conditions to secure the balance of the size os each class
         *
         * Requests:
         * A student cannot be in more than one class at once for a given UC;
         * A class can only accept a new student if its capacity has not been exceeded (consider that there is a maximum capacity Cap for classes);
         * A class can only accept a new student if the balance between class occupation is not disturbed (the balance of class occupation is maintained when the difference between the number of students in any class is less than or equal to 4).
         *
         * @paramt request : request;
         */
        static bool requestBalance(Request &request);

        /**
         * Checks if there is no conflict between the student’s schedule and the new class’s schedule
         *
         * @paramt uc1 : one Uc;
         * @paramt uc2 : another Uc;
         */
        bool lessonOverlap(UC uc1, UC uc2);

        /**
         * Returns a vector with the students of an Uc
         *
         * @paramt UcCode : Uc code;
         */
        vector<Student> UcStudents(const string& UcCode);

        /**
         * Get the total number of pending requests
         */
        int totalNumberOfPendingRequests();

        int totalNumberOfRejectedRequests();

        /**
         * Get request current UC Class
         *
         * @paramt request : request;
         */
        static UC getCurrentClass(Request &request);

        /**
         * See if request has any problem (unbalanced, conflict, extends the max)
         *
         * @paramt request : request;
         */
        void verifySwapRequest(Request &request);

        /**
         * See if request has any problem (conflict, extends the max)
         *
         * @paramt request : request;
         */
        void verifyEnrollmentRequest(Request &request);

        /**
         * Does the removal requests as it does not need any problem verification
         *
         * @paramt request : request;
         */
        void verifyRemovalRequest(Request &request);

        /**
         * Finalizes the requests
         */
        void RequestsManager();

        /**
         * Prints the requests that are pending
         */
        void seePendingRequests();

        /**
         * Prints the requests that were rejected
         */
        void seeRejectedRequests();

        /**
         * Prints the schedule of a given student
         *
         * @paramt StudentCode : Student code;
         */
        void seeStudentSchedule(const string& StudentCode) const;

        /**
         * Prints the schedule of a given class
         *
         * @paramt ClassCode : Class code;
         */
        void seeClassSchedule(const string& ClassCode);

        /**
         * Prints the schedule of a given Uc
         *
         * @paramt UcCode : Uc code;
         */
        void seeUcSchedule(const string& UcCode);

        /**
         * Prints the students of a given class
         *
         * @paramt UcClass : Uc class;
         * @paramt order_ : Way to sort the students of the class;
         */
        void seeClassStudents(const UC& UcClass, const int &order_);

        /**
         * Prints the students of a given Uc
         *
         * @paramt UcCode : Uc code;
         * @paramt order_ : Way to sort the students of the Uc;
         */
        void seeUcStudents(const string &UcCode, const int &sort_);

        /**
         * Prints the students of a given year
         *
         * @paramt year: Year;
         * @paramt sort : Way to sort the students of the Uc;
         */
        void seeYearStudents(int year, int sort);

        /**
         * Returns the number of students of a given Class and Uc
         *
         * @paramt UcClass : Uc code, Class code;
         */
        static int numberClassStudents(const UC& UcClass);

        /**
         * Returns the number of students of a given Class
         *
         * @paramt UcCode : Uc code;
         */
        int numberUcStudents(const string &UcCode);

        /**
         * Returns the number of students of a given Year
         *
         * @paramt Year : year;
         */
        int numberYearStudents(const int &Year);
};
#endif //AED2324_PRJ1_G1207_AUXILIARFUNCTIONS_H
