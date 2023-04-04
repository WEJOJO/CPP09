#include <cstdlib>
#include <deque>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>

std::deque<std::string> split(std::string input, char delimiter) {
    std::deque<std::string> result;
    std::stringstream ss(input);
    std::string tmp;

    while (getline(ss, tmp, delimiter))
        result.push_back(tmp);
    return result;
}
int check_val2(std::string &line_) { // 지운 후 저장을 위해 참조형 사용
    if (line_[0] != ' ')
        return -1;
    line_.erase(0, 1);
    float check;
    check = atof(line_.c_str());
    if (check > (2147483648))
        return -2;
    if (check < 0)
        return -3;
    return check;
}

int check_val1(std::string &line_) { /// 지운 후 저장을 위해 참조형 사용
    int _size = line_.size();
    // 뒤에 숫자 오는 케이스 처리 2012-01-012|~~~
    if (line_[_size - 1] != ' ') {
        return 0;
    }
    line_.erase(_size - 1, 1);
    std::deque<std::string> string_s;
    string_s = split(line_, '-');
    // split시 갯수가 3개인지 확인
    if (string_s.size() != 3)
        return 0;
    int t1 = atoi(string_s[0].c_str());
    int t2 = atoi(string_s[1].c_str());
    int t3 = atoi(string_s[2].c_str());

    // 각 각의 유효성 확인
    if (t1 < 0 || t1 > 2023 || t2 < 1 || t2 > 12 || t3 < 1 || t3 > 12) {
        std::cout << "t1 : " << t1 << std::endl;
        std::cout << "t2 : " << t2 << std::endl;
        std::cout << "t3 : " << t3 << std::endl;

        return 0;
    }
    return 1;
}

int main() {
    std::ifstream myfile;
    std::ifstream stand;
    std::string line;
    /// input 여러 파일 받도록 처리해주기
    myfile.open("test.txt");
    stand.open("testdata.csv");
    std::string key;
    std::map<std::string, double> standard;
    std::map<std::string, double>::iterator it;
    int i;
    if (stand.is_open()) {
        while (getline(stand, key, ',')) { //,에서 전진을 멈춤
            if (key == "date") {
                getline(stand, key);
                continue;
            }
            std::string val;
            getline(stand, val); /// 예외처리?
            standard[key] = atof(val.c_str());
        }
    }
    // it = standard.begin();
    // for (; it != standard.end(); it++) {
    //     std::cout << it->first << ":" << it->second << std::endl;
    // }

    if (myfile.is_open()) {
        std::string _str;
        while (getline(myfile, line, '|')) {
            if (line.size() != 11 ||
                check_val1(line) == 0) { // 맨 뒤 공백 고려하기
                std::cout << "bad input => " << line << std::endl;
                getline(myfile, line);
                continue;
            }
            _str += line;
            getline(myfile, line); // 맨 앞 공백 고려하기
            int ret = check_val2(line);
            if (ret == -1) { // 1badinput , 2오버플로, 3음수 0성공
                std::cout << "Error: bad input => not a space before |"
                          << std::endl;
                _str = "";
                continue;
            } else if (ret == -2) {
                std::cout << "Error: too large a number." << std::endl;
            } else if (ret == -3) {
                std::cout << "Error: not a positive number." << std::endl;
            } else {
                std::string _key = _str; //[-1]이 빠지기 전임??
                _str += " => ";
                _str +=
                    line; //[0]이 빠지기 전임.?? > 참조형이라 빠졌다고 생각함
                _str += " = ";
                if (_key < standard.begin()->first) {
                    std::cout << "Error: No Standard Data. => " << _key
                              << std::endl;
                    _str = "";
                    continue;
                }
                it = standard.lower_bound(_key); // lower??
                if (standard.find(_key) != standard.end()) {
                    std::cout << _str << (it->second) * ret << std::endl;
                } else
                    std::cout << _str << ((--it)->second) * ret << std::endl;

                // 값이 존재하거나 맨 앞인 경우, (ret * standard[_key] >
                // 혹은 lowerbound?) 2011-01-03 => 3 = 0.9
                // str초기화
                _str = "";
            }
        }
        myfile.close();
        stand.close();
    }
}

/// atoi의 근거/////
// int main()
//{
//     std::string temp = "2018";
//     std::cout << atoi(temp.c_str()) << std::endl;
// }
//////