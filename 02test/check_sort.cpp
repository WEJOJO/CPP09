#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

int main(int argc, char *argv[])
{
	std::vector<int> origin;
	std::vector<int>::iterator iter;

    std::string token;

	if (argc!=2)
	{
		std::cout << "arg err" << std::endl;
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
	std::sort(origin.begin(), origin.end());
	std::cout << "=======in Main========" << std::endl;
    for (int j = 0; j < origin.size(); j++)
        std::cout << origin[j] << " ";
    std::cout << std::endl;
}