#include<vector>
#include <iostream>
using namespace std;
#define log(x) cout << x << endl;


static vector<int> twoSum(vector<int>& nums, int target) {

    for (int i = 0;i < nums.size();i++)
    {
        int n = nums[i];
        for (int j = 0;j < nums.size();j++)
        {
            if (n + nums[j] == target)
            {
                return vector<int>({ i, j });
            }
        }

    }
    return vector<int>({ 0, 0 });
}
ostream& operator<<(ostream& os, const vector<int> vec)
{
    os << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        os << vec[i];
        if (i != vec.size() - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}
