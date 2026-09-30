#include <string>
#include <cctype>
using namespace std;

class Solution {
public:
    string toLowerCase(string s) {
        for (char &c : s) {
            c = tolower(static_cast<unsigned char>(c));
        }
        return s;
    }
};