#include <iostream>
#include <vector>

int main() {
    std::vector<int> arr;

//"3 2 1 5 89 9 67 890 67 45 89 56 32 54 46 7 78 87 897 789"
// "3 2 1 5 89 9 67 890 67 45 89"
    arr.push_back(3);
    arr.push_back(2);
    arr.push_back(1);
    arr.push_back(5);
    arr.push_back(89);
    arr.push_back(9);
    arr.push_back(67);
    arr.push_back(890);
    arr.push_back(67);
    arr.push_back(45);
    arr.push_back(89);

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
