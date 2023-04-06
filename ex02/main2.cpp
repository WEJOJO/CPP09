#include <cstdlib>
#include <iostream>
#include <sstream>
#include <vector>
#include <deque>

/////////
#include <sys/time.h>
#include <chrono>
void myMethod() {
  auto start = std::chrono::high_resolution_clock::now();

  // 메소드 실행 코드

  auto end = std::chrono::high_resolution_clock::now();
  auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

  std::cout << "Elapsed time: " << elapsed.count() << " milliseconds" << std::endl;
}
////////////
void MakeSort(int st, int mid, int end, std::deque<int> &_origin) {
    std::deque<int> t1;
    std::deque<int> t2;
    int t1_ind = 0;
    int t2_ind = 0;
    int t_st = st;

    for (int t = st; t != mid + 1; t++)
        t1.push_back(_origin[t]);
    for (int t = mid + 1; t <= end; t++)
        t2.push_back(_origin[t]);

    while (st <= end) {
        if ((t1_ind < t1.size() && t1[t1_ind] <= t2[t2_ind]) ||
            t2_ind >= t2.size()) {
            _origin[st] = t1[t1_ind];
            t1_ind++;
        } else if ((t2_ind < t2.size() && t1[t1_ind] > t2[t2_ind]) ||
                   t1_ind >= t1.size()) {
            _origin[st] = t2[t2_ind];
            t2_ind++;
        }
        st++;
    }
}

void InsertSort(std::deque<int> &arr, int st, int end)
{
    int stand;
    int back_ind;

    // std::cout << "=====before InsertSort=====" << std::endl;
    // for (int i = st; i <= end; i++)
    //     std::cout << arr[i] << " ";
    // std::cout << std::endl;

    for (int stand_ind = st + 1; stand_ind <= end; stand_ind++) {
        back_ind = stand_ind;
        stand = arr[stand_ind];
        for (int curr = stand_ind - 1; curr >= st; curr--) //st!
            if (stand < arr[curr]) {
                arr[back_ind] = arr[curr];
                back_ind--;
            }
        arr[back_ind] = stand;
    }
    ////check Insert////
    // std::cout << "=====after InsertSort=====" << std::endl;
    // std::cout << "st :" << st << std::endl;
    // std::cout << "end :" << end << std::endl;
    // for (int i = st; i <= end; i++)
    //     std::cout << arr[i] << " ";
    // std::cout << std::endl;
    ////////////////////
}
// std::vector<int> MergeSort()
void MergeSort(std::deque<int> &_origin, int st, int end) { //함수명 바꿔줄 것.
    int mid;
    if (end-st+1 <= 100)///길이가 10이하인 배열에 관하여... // deque로 처리할 것이라면 ex00서 빼기 //(st == end) k==10인 상황
    {
        InsertSort(_origin,st,end);
        return;
    }

    ////////////////MergeSort Only////////////////
    // if (end==st)
    //     return;
    ////////////////MergeSort Only////////////////

    int _size = end - st + 1;
    mid = ((st + end) / 2);
    MergeSort(_origin, st, mid);
    MergeSort(_origin, mid + 1, end);
    MakeSort(st, mid, end, _origin);
    return;
}

int main(int argc, char *argv[]) {
    std::deque<int> origin;
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
    //_origin print
    // for (int j = 0; j < origin.size(); j++)
    //     std::cout << origin[j] << std::endl;


    auto start = std::chrono::high_resolution_clock::now();
    MergeSort(origin, 0, origin.size() - 1);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "수행 시간: " << duration.count() << " 마이크로초" << std::endl;
    std::cout << "=======in Main========" << std::endl;
    for (int j = 0; j < origin.size(); j++)
        std::cout << origin[j] << " ";
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
