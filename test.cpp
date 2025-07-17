#include <string>
#include <iostream>

int main(){
    std::string currentTimestamp{"2020/03/17 17:01:24.884492"};
    int year = std::stoi(currentTimestamp.substr(0, 4));
    int month = std::stoi(currentTimestamp.substr(5, 2));
    int day = std::stoi(currentTimestamp.substr(8, 2));

    std::cout << year << std::endl;
    std::cout << month << std::endl;
    std::cout << day << std::endl;

    int daysToSubtract = 25 * 7;
    while (daysToSubtract > 0) {
        day--;
        if (day == 0) {
            month--;
            if (month == 0) {
                month = 12;
                year--;
            }
            // Days in month
            static const int daysInMonth[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
            bool leap = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
            day = daysInMonth[month];
            if (month == 2 && leap) day = 29;
        }
        daysToSubtract--;
    }
    std::cout << "====" << std::endl;
    std::cout << year << std::endl;
    std::cout << month << std::endl;
    std::cout << day << std::endl;

    std::string pastTimestamp{  std::to_string(year)+"/"
                                +std::to_string(month) +"/"
                                +std::to_string(day) + 
                                currentTimestamp.substr(10, currentTimestamp.size()-10)};

    std::cout << pastTimestamp << std::endl;
    
}