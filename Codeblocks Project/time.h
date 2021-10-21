#ifndef TIME_H
#define TIME_H

#include <iostream>

class time
{
    public:
        time();
        time(std::string hh, std::string mm);
        /**
         * @brief get hours
         *
         * @return string
         */
        std::string getHours() const;
        /**
         * @brief get minutes
         *
         * @return string
         */
        std::string getMinutes() const;
        /**
         * @brief set hours
         *
         * @param hh - string hours
         * @return void
         */
        void setHours(std::string hh);
        /**
         * @brief set minutes
         *
         * @param hh - string hours
         * @return void
         */
        void setMinutes(std::string mm);
    private:
        ///time hours
        std::string hours;
        ///time minutes
        std::string minutes;
};

#endif // TIME_H
