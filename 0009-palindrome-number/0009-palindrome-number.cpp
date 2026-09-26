class Solution {
public:
    bool isPalindrome(int x) {
        int og = x;
        long int reverse = 0;
        if(x<0)
        {
            return false;
        }
        while(x!=0)
        {
            int digit= 0;
            digit = x%10;
            x = x/10;
            reverse = reverse*10+digit;
        }
        if(reverse ==og )
        {
            return true;

        }
        else{
            return false;
        }

    }
};