#include <cstdlib>
#include <iostream>
#include <sstream>
#include <list>

//////
#include <chrono>

void MakeSort(int st, int mid, int end, std::list<int> &_origin) {
    std::list<int> t1;
    std::list<int> t2;
    std::list<int>::iterator iter;
    std::list<int>::iterator st_iter;
    std::list<int>::iterator t1_iter;
    std::list<int>::iterator t2_iter;


	int  i = 0;
	iter = _origin.begin();
	while(i < st)
	{
		iter++;
		i++;
	}
	st_iter = iter;
	while(i <= end)
	{
		if (i < mid+1)
			t1.push_back(*iter);
		else
			t2.push_back(*iter);
		iter++;
		i++;
	}
	t1_iter = t1.begin();
	t2_iter = t2.begin();
    while (st_iter != iter) {
        if ((t1_iter != t1.end() && *t1_iter <= *t2_iter) || t2_iter == t2.end()) {
            *st_iter = *t1_iter;
            t1_iter++;
        } else if ((t2_iter != t2.end() && *t1_iter > *t2_iter) || t1_iter == t1.end()) {
            *st_iter = *t2_iter;
            t2_iter++;
        }
        st_iter++;
    }
}

void InsertSort(std::list<int> &arr, int st, int end)
{
    int stand;
    std::list<int>::iterator iter;
    std::list<int>::iterator back_iter;
    std::list<int>::iterator start_iter;
    std::list<int>::iterator curr_iter;

    int i = 0;
    iter = arr.begin();
    while(i<st)
    {
        iter++;
        i++;
    }
    start_iter = iter;//변화없음
    iter++;
    i++;
    while(i<=end)
    {
        back_iter = iter;
        stand = *iter; //주석처리X 담고있어야 함
        iter--;
        curr_iter = iter; //한 칸 전 담기
        iter++; //iter 원상 복구
        while(curr_iter!=arr.begin() && curr_iter!=start_iter)//start_iter인 부분 와일 후에 처리 필요
        {
            if (stand < *curr_iter)//*iter
            {
                *back_iter = *curr_iter;
                back_iter--;
            }
            curr_iter--;
        }
        if (stand < *curr_iter)
        {
                *back_iter = *curr_iter;
                back_iter--;
        }
        *back_iter = stand;
        iter++;
        i++;
    }
}

void MergeSort(std::list<int> &_origin, int st, int end) { //함수명 바꿔줄 것.
    int mid;
    if (end-st+1 <= 100)///길이가 10이하인 배열에 관하여... // deque로 처리할 것이라면 ex00서 빼기 //(st == end) k==10인 상황
    {
        InsertSort(_origin,st,end);
        return;
    }

    // if (end == st)
    //     return ;
    int _size = end - st + 1;
    mid = ((st + end) / 2);
    MergeSort(_origin, st, mid);
    MergeSort(_origin, mid + 1, end);
    MakeSort(st, mid, end, _origin);
    return;
}

int main(int argc, char *argv[]) {
    std::list<int> origin;
    std::string token;

    if (argc != 2) {
        std::cout << "arg ERR" << std::endl;
        exit(1);
    }
    int i = 1;
    while (argv[i]) {
        std::stringstream ss(argv[i]);
        ////일단 파싱 생략
        while (ss >> token)
            origin.push_back(atoi(token.c_str()));
        i++;
    }

    // std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();
    MergeSort(origin, 0, origin.size() - 1);
    // std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now();
    // std::chrono::nanoseconds duration = std::chrono::duration_cast<std::chrono::nanoseconds>((end - start));
    // std::cout << "수행 시간: " << duration.count()*0.001 << " us" << std::endl;



    std::cout << "=======in Main========" << std::endl;
    // for (int j = 0; j < origin.size(); j++)
    //     std::cout << origin[j] << " ";
    // std::cout << std::endl;
	std::list<int>::iterator o_iter;
	o_iter = origin.begin();
	for (;o_iter!=origin.end();o_iter++)
		std::cout << *o_iter << " ";
	std::cout << std::endl;
}

//./a.out "3 2 1 5 89 9 67 890 67 45 89 56 32 54 46 7 78 87 897 789"
//결과값 >>> 1 2 3 5 7 9 32 45 46 54 56 67 67 78 87 89 890 789 890 897
//ㄴ>789이슈 있음

//1 2 3 5 7 9 32 45 46 54 56 67 67 78 87 89 890 789 890 897
//1 2 3 5 7 9 32 45 46 54 56 67 67 78 87 89 89 789 890 897 >>> 병합시에는 문제 없었음. 삽입정렬 구현부 확인 필요.
//1 2 3 5 7 9 32 45 46 54 56 67 67 78 87 89 89 789 890 897



/////./a.out "3 2 1 5 89 9 67 890 67 45 89"
////ㄴ> 결과값 : 1 2 3 5 9 45 89 67 89 89 890
