class Solution {
public:
    int numberOfEmployeesWhoMetTarget(vector<int>& hours, int target) {
        int s = hours.size();
        int n;
        for (int i = 0; i < s; i++) 
        {
            if(hours[i] >= target)
            {
                n++;
            }
        }
        return n;
        
    }
};