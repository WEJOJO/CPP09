#include <cstdlib>
#include <deque>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
/// vector 아끼기
// std::vector<std::string> split(std::string input, char delimiter) {
//     std::vector<std::string> result;
//     std::stringstream ss(input);
//     std::string tmp;

//    while (getline(ss, tmp, delimiter))
//        result.push_back(tmp);
//    return result;
//}
std::deque<std::string> split(std::string input, char delimiter) {
    std::deque<std::string> result;
    std::stringstream ss(input);
    std::string tmp;

    while (getline(ss, tmp, delimiter))
        result.push_back(tmp);
    return result;
}

/// atoi의 근거/////
// int main()
//{
//     std::string temp = "2018";
//     std::cout << atoi(temp.c_str()) << std::endl;
// }
//////
void testfuc(std::string &test) { test.erase(0, 1); }

int main() {
    std::string t = "2018-01-05";
    std::deque<std::string> _sstring;
    _sstring = split(t, '-');
    std::cout << _sstring.size() << std::endl;
    std::cout << _sstring[0] << std::endl;
    std::cout << _sstring[1] << std::endl;
    std::cout << _sstring[2] << std::endl;
    std::cout << "==============" << std::endl;
    std::cout << atoi(_sstring[0].c_str()) << std::endl;
    std::cout << "bf test func" << std::endl;
    testfuc(_sstring[0]);
    std::cout << _sstring[0] << std::endl;
    //////
}