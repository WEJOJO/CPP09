// 3 5 9 7 4

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <vector>
void MakeSort(int st, int mid, int end, std::vector<int> &_origin) {
    std::vector<int> t1;
    std::vector<int> t2;
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
// std::vector<int> MergeSort()
void MergeSort(std::vector<int> &_origin, int st, int end) {
    int mid;
    if (st == end) // k에 대한 삽입정렬 추가할 것.
        return;

    int _size = end - st + 1;
    mid = ((st + end) / 2);
    MergeSort(_origin, st, mid);
    MergeSort(_origin, mid + 1, end);
    MakeSort(st, mid, end, _origin);
    return;
}

int main(int argc, char *argv[]) {
    std::vector<int> origin;
    std::string token;

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

    MergeSort(origin, 0, origin.size() - 1);
    std::cout << "=======in Main========" << std::endl;
    for (int j = 0; j < origin.size(); j++)
        std::cout << origin[j] << std::endl;
}