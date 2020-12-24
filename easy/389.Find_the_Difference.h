/*
You are given two strings s and t.

String t is generated by random shuffling string s and then add one more letter tSum a random position.

Return the letter that was added to t.

Example 1:

Input: s = "abcd", t = "abcde"
Output: "e"
Explanation: 'e' is the letter that was added.

Example 2:

Input: s = "", t = "y"
Output: "y"

Example 3:

Input: s = "a", t = "aa"
Output: "a"

Example 4:

Input: s = "ae", t = "aea"
Output: "a"

Constraints:

0 <= s.length <= 1000
t.length == s.length + 1
s and t consist of lower-case English letters.

*/

#include <string>
#include <vector>

using std::string;
using std::vector;

class Solution1 {
public:
    char findTheDifference(string s, string t) {
        int sSum = 0, tSum = 0;
        for (int i = 0; i < s.size(); ++i) {
            sSum += s[i];
        }
        for (int i = 0; i < t.size(); ++i) {
            tSum += t[i];
        }
        return tSum - sSum;
    }
};

class Solution2 {
public:
    char findTheDifference(string s, string t) {
        int ret = 0;
        for (int i = 0; i < s.size(); ++i) {
            ret ^= s[i];
        }
        for (int i = 0; i < t.size(); ++i) {
            ret ^= t[i];
        }
        return ret;
    }
};