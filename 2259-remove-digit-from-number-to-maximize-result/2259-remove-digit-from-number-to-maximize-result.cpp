class Solution {
public:
    string removeDigit(string number, char digit) {
        return getMax(number, digit, 0);
    }
    
    string getMax(string number, char target, int p){
        
        while(p < number.size() && number[p] != target) p++;
        
        if(p == number.size()) return "0";
        
        string currMax = number.substr(0, p) + number.substr(p+1);
        if(number[p+1] > number[p]) return currMax;
        
        string nextMax = getMax(number, target, p+1);
        if(cmp(currMax, nextMax)) return nextMax;
        else return currMax;
    }
    
    // if(n1 < n2) return true;
    bool cmp(string& n1, string& n2){
        for(int p = 0; p < n1.size() && p < n2.size(); p++){
            if(n1[p] == n2[p]) continue;
            
            if(n1[p] < n2[p]) return true;
        }
        return false;
    }
};