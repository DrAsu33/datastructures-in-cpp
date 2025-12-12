#ifndef STRINGHEADER
#define STRINGHEADER

#include <string>
#include <vector>
using std::vector, std::string;
vector<size_t> lps(const string& s)
{
    size_t size = (size_t)s.size();
    vector<size_t> res(size);
    res[0] = 0;
    size_t j = 0;
    for(size_t i = 1; i < size; i++)
    {
        char c = s[i];
        while(j != 0 && s[j] != c)
            j = res[j-1];
        if(j != 0 || c == s[0])
            res[i] = ++j;
        else    
            res[i] = 0;
    }
    return res;
}

int substring(const string& str, const string& substr)
{
    vector<size_t> next(lps(substr));
    size_t i = 0, j = 0, s1 = (size_t)str.size(), s2 = (size_t)substr.size();
    while(i < s1  && j < s2)
    {
        if(str[i] == substr[j]) 
            {i++; j++;}
        else if(j > 0) 
            j = next[j-1];
        else 
            i++;
    }
    if(j == s2) //matched succesefully
        return (int)(i - s2);
    else
        return -1;
}


#endif