#include <cstdlib>
#include <deque>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>

std::string convertDouble(double value) {
  std::ostringstream o;
  if (!(o << value))
    return "";
  return o.str();
}

std::deque<std::string> split(std::string input, char delimiter) {
    std::deque<std::string> result;
    std::stringstream ss(input);
    std::string tmp;

    while (getline(ss, tmp, delimiter))
        result.push_back(tmp);
    return result;
}

bool isLeapYear(int year) {
    return ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
}

bool isValidDate(int year, int month, int day) {
    if (month < 1 || month > 12)
        return false;
    if (day < 1 || day > 31)
        return false;

    if (month == 4 || month == 6 || month == 9 || month == 11) {
        if (day > 30)
            return false;
    } else if (month == 2) {
        if (isLeapYear(year) && day > 29)
            return false;
        if (!isLeapYear(year) && day > 28)
            return false;
    }
    return true;
}

int check_val(std::string &line_, std::deque<std::string> &_strs) { /// 지운 후 저장을 위해 참조형 사용
    std::deque<std::string> string_s;
    std::deque<std::string> datetime_str;
    float check;
    int i = 0;
    int pipe_cnt = 0;
    int hipen_cnt = 0;
    int dot_cnt = 0; // 0 or 1 가능
    int sp_cnt = 0; // 2 아니면 무조건 에러
    int minus_cnt = 0; //이렇게까지 해야하나...
    while(line_[i])
    {
        if (pipe_cnt==0 && line_[i] == '-') // | 뒤의 -와 일반 하이픈과의 비교
            hipen_cnt++;
        else if(line_[i] == '|')
            pipe_cnt++;
        else if ((line_[i] < 48 || line_[i] > 57) && line_[i]!=32 && line_[i]!=46 && line_[i]!=45)//++98 space!
        {
            // std::cout << "where??: " << line_[i] << std::endl;
            std::cout << "Error: bad input => " << line_ << std::endl;
            return 0;
        }
        else if(line_[i]==32)
            sp_cnt++;
        else if (line_[i]==46)
        {
            dot_cnt++;
            if (pipe_cnt == 0) // pipe없이 dot 만난 경우
            {
                std::cout << "Error: bad input => " << line_ << std::endl;
                return 0;
            }
        }
        else if (pipe_cnt && line_[i] == '-')
            minus_cnt++;
        i++;
    }
    if (pipe_cnt != 1 || hipen_cnt != 2 || sp_cnt != 2 || dot_cnt > 1 || minus_cnt > 1)
    {
        // std::cout << "where??2: " << line_[i] << std::endl;
        std::cout << "Error: bad input => " << line_ << std::endl;
        return 0;
    }

	string_s = split(line_, '|');
	int datetime_len = string_s[0].size();
	if (string_s.size()!=2 || string_s[0][datetime_len-1] != ' ' || string_s[1][0] != ' ')
	{
        // std::cout << "where??3: " << line_[i] << std::endl;
		std::cout << "Error: bad input => " << line_ << std::endl;
		return 0;
	}
    string_s[0].erase(datetime_len-1,1);
	datetime_len = string_s[0].size(); //재할당
	string_s[1].erase(0,1);
    datetime_str = split(string_s[0], '-');


    // 뒤에 숫자 오는 케이스 처리 2012-01-012|~~~
    int t1 = atoi(datetime_str[0].c_str());
    int t2 = atoi(datetime_str[1].c_str());
    int t3 = atoi(datetime_str[2].c_str());

    // 각 각의 유효성 확인
    if (isValidDate(t1,t2,t3)==false || datetime_str.size()!=3)
	{
        // std::cout << "where??4: " << line_[i] << std::endl;
        std::cout << "Error: bad input => " << line_ << std::endl;
		return 0;
	}
    std::cout.precision(12);
    check = atof(string_s[1].c_str());
    if (check > 2147483647.0)
    {
        std::cout << "Error: too large a number." << std::endl;
        return 0;
    }
    if (check < 0)
    {
        std::cout << "Error: not a positive number." << std::endl;
        return 0;
    }
    std::cout.precision(7); //precision 초기화 6이 디폴트이긴 하지만 좀더 잘 찍기 위해 처리함
    _strs.push_back(string_s[0]);
    _strs.push_back(string_s[1]);
    return 1;
}

int main() {
    std::ifstream myfile;
    std::ifstream stand;
    std::string line;
    ///////////////// !!!!!!!!!!!!!!!!!input 여러 파일 받도록 처리해주기
    myfile.open("test.txt");////
    stand.open("data.csv");
    std::string key;
    bool flag;
    std::map<std::string, double> standard;
    std::map<std::string, double>::iterator it;
    int i;
    float _val;
	///////////////map 처리
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
	///////////////
    // int j = 1;
    // while(argv[j])
    // {
    //     myfile.open(argv[j]);
    // }
	///////////////
    if (myfile.is_open()) {
        flag = false;
        while (getline(myfile, line)) { //date | value
            std::deque<std::string> _strs;
            if (line == "date | value")
            {
                if (flag == true)
                {
                    std::cout << "Error: bad input => " << line << std::endl;
                    continue;
                }
                flag = true;
            }
            if (check_val(line,_strs) == 0)
                continue;
            // std::cout << "_strs[1] : " << _strs[1] << std::endl;
            ////////////////////////////////////////////////////////////////////////////////
            if (_strs[0] < standard.begin()->first) {
                    std::cout << "Error: No Standard Data. => " << _strs[0] << std::endl;
                    continue;
            }
            it = standard.lower_bound(_strs[0]); // lower??
            _val = atof(_strs[1].c_str());
            if (convertDouble(_val)!=_strs[1])
            {
                std::cout << "Error: bad input => " << line << std::endl;
                continue;
            }
            if (standard.find(_strs[0]) != standard.end())
            {
                std::cout << _strs[0] << " => " << _strs[1] << " = " <<  (it->second) * _val << std::endl; ///_ret이랑 곱하면 안될 것 같음.
            }
            else
            {
                std::cout << _strs[0] << " => " << _strs[1] << " = " <<  ((--it)->second) * _val << std::endl;
            }
            ////////////////////////////////////////////////////////////////////////////////
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