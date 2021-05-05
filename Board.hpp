#pragma once
#include <iostream>
#include <string>
#include <map>
#include "City.hpp"

namespace pandemic
{
    class Board
    {
        int x; // לוח מפה של העולם ובו 48 ערים
      
      
        public:
            int& operator[](City city); // מזהה עיר >> קריאה + עדכון רמת מחלה
            bool is_clean();  // מחזירה אמת אם הלוח נקי מקוביות מחלה
            void remove_cures(); // הסרת תרופות שהתגלו עד כה
            friend std::ostream& operator<< (std::ostream& os, const Board& b); // מצב הלוח << רמת מחלה - תרופות - תחנות מחקר
    };
}
