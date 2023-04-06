#include <iostream>
#include <vector>

int main() {
    std::vector<int> arr;

    arr.push_back(1);
    arr.push_back(1);
    arr.push_back(3);
    arr.push_back(4);
    arr.push_back(4);
    std::cout << "==========origin==========" << std::endl;
    for (int i = 0; i < arr.size(); i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;

    for (int stand_ind = 1; stand_ind != arr.size(); stand_ind++) {
        int back_ind = stand_ind;
        int stand = arr[stand_ind];
        for (int curr = stand_ind - 1; curr >= 0; curr--)
            if (stand < arr[curr]) {
                arr[back_ind] = arr[curr];
                back_ind--;
            }
        arr[back_ind] = stand;
    }
    std::cout << "==========after==========" << std::endl;
    for (int i = 0; i < arr.size(); i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;
    // 마지막에 stand 넣을 것.
}