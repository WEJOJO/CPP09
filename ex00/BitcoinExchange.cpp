#include "BitcoinExchange.hpp"
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////Orthodox////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
BitcoinExchange::BitcoinExchange() {
    std::cout << std::setw(15) << "[BitcoinExchange] " << "create!!" << std::endl;
    // standard
    this->stand.open("data.csv");
    if (this->stand.is_open())
        MakeMap();
    else
        std::cout << "File Err" << std::endl;
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &ref) {
    *this = ref;
    std::cout << std::setw(15) << "[BitcoinExchange] "
              << "copy!!" << std::endl;
}

BitcoinExchange::~BitcoinExchange() {
    std::cout << std::setw(15) << "[BitcoinExchange] "
              << "delete!!" << std::endl;
    this->stand.close(); /////close!
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &ref) {
    std::cout << std::setw(15) << "[BitcoinExchange] "
              << "operator=!!" << std::endl;
    this->standard = ref.standard;
    return (*this);
}
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////Orthodox////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////Utils///////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
bool BitcoinExchange::IsLeapYear(int year)
{
    return ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
}

bool BitcoinExchange::IsValidDate(int year, int month, int day)
{
    if (month < 1 || month > 12)
        return false;
    if (day < 1 || day > 31)
        return false;

    if (month == 4 || month == 6 || month == 9 || month == 11) {
        if (day > 30)
            return false;
    } else if (month == 2) {
        if (this->IsLeapYear(year) && day > 29)
            return false;
        if (!(this->IsLeapYear(year)) && day > 28)
            return false;
    }
    return true;
}

std::deque<std::string> BitcoinExchange::Split(std::string input, char delimiter)
{
    std::deque<std::string> result;
    std::stringstream ss(input);
    std::string tmp;

    while (getline(ss, tmp, delimiter))
        result.push_back(tmp);
    return result;
}

std::string BitcoinExchange::ConvertDouble(double value)
{
    std::ostringstream o;
    if (!(o << value))
        return "";
    return o.str();
}

void BitcoinExchange::MakeMap()
{
    std::string key;
    std::cout << "=========Make Map=========" << std::endl;
    while (getline(this->stand, key, ','))
    { //,에서 전진을 멈춤
        if (key == "date") {
            getline(this->stand, key);
            continue;
        }
        std::string val;
        getline(this->stand, val); /// 예외처리?
        this->standard[key] = atof(val.c_str());
    }
}

//MakeChange의 호출이 잦아 line을 스태틱영역으로 넣음. 그것을 참조하는 방향으로 진행.
int BitcoinExchange::ValidationCheck(std::string &line_, std::deque<std::string> &_strs)
{ /// 지운 후 저장을 위해 참조형 사용
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

	string_s = this->Split(line_, '|');
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
    datetime_str = this->Split(string_s[0], '-');


    // 뒤에 숫자 오는 케이스 처리 2012-01-012|~~~
    int t1 = atoi(datetime_str[0].c_str());
    int t2 = atoi(datetime_str[1].c_str());
    int t3 = atoi(datetime_str[2].c_str());

    // 각 각의 유효성 확인
    if (this->IsValidDate(t1,t2,t3)==false || datetime_str.size()!=3)
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

void BitcoinExchange::MakeChange(char *_argv)
{
    bool flag = false;
    std::string line;
    std::map<std::string, double>::iterator it;
    float _val;

    this->myfile.open(_argv);
    if (this->myfile.is_open())
    {
        std::cout << "===========File Opened===========" << std::endl;
        while (getline(this->myfile, line)) { //date | value
            std::deque<std::string> _strs;
            if (line == "date | value")
            {
                if (flag == true)
                    std::cout << "Error: bad input => " << line << std::endl;
                flag = true;
                continue;
            }
            if (this->ValidationCheck(line, _strs) == 0) /// _strs에 push_back() ValidationCheck()
                continue;
            // std::cout << "_strs[1] : " << _strs[1] << std::endl;
            ////////////////////////////////////////////////////////////////////////////////
            if (_strs[0] < (this->standard).begin()->first) {
                    std::cout << "Error: No Standard Data. => " << _strs[0] << std::endl;
                    continue;
            }
            it = (this->standard).lower_bound(_strs[0]); // lower??
            _val = atof(_strs[1].c_str());
            if (this->ConvertDouble(_val)!=_strs[1])
            {
                std::cout << "Error: bad input => " << line << std::endl;
                continue;
            }
            if ((this->standard).find(_strs[0]) != (this->standard).end())
            {
                std::cout << _strs[0] << " => " << _strs[1] << " = " <<  (it->second) * _val << std::endl; ///_ret이랑 곱하면 안될 것 같음.
            }
            else
            {
                std::cout << _strs[0] << " => " << _strs[1] << " = " <<  ((--it)->second) * _val << std::endl;
            }
            ////////////////////////////////////////////////////////////////////////////////
        }
        this->myfile.close();
        // stand.close();// stand.close는 소멸자로 옮기는 것이 맞아보임
    }
    else
    {
        std::cout << "file does not opened" << std::endl;
    }
}
