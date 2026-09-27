class Solution {
public:
    int differenceOfSums(int n, int m) {
        int num1 = 0;//3+6+9
        int num2 = 0;//1+2+4+5+7+8+10

        for(int i = 1; i<=n; i++)
        {
            if(i%m==0)
            {
                num1 +=i;
            }
            else{
                num2+=i;
            }
        }
        int num3 = num2-num1;
        return num3;
    }
};