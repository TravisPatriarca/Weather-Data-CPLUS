#ifndef DATE_H
#define DATE_H

#include <iostream>

class date
{
    public:
        date();
        date(int d, int m, int y);
        /**
         * @brief get date day
         *
         * @return unsigned
         */
        int getDay() const;

        /**
         * @brief sets date day
         *
         * @param dd - day
         * @return void
         */
        void setDay(int dd);

        /**
         * @brief sets date month
         *
         * @return unsigned
         */
        int getMonth() const;

        /**
         * @brief gets date month
         *
         * @param mm - month
         * @return void
         */
        void setMonth(int mm);

        /**
         * @brief gets date year
         *
         * @return unsigned
         */
        int getYear() const;

        /**
         * @brief sets date year
         *
         * @param yyyy - year
         * @return void
         */
        void setYear(int yyyy);

        /**
         * @brief overloading less than operator
         *
         * @param const date
         * @return boolean
         */
        bool operator < (const date &r) const;

        /**
         * @brief overloading greater than operator
         *
         * @param const date
         * @return boolean
         */
        bool operator > (const date &r) const;

        /**
         * @brief overloading equality operator
         *
         * @param const date
         * @return boolean
         */
        bool operator == (const date& r) const;

    private:
        ///date day
        int day;
        ///date month
        int month;
        ///date year
        int year;
};

#endif
