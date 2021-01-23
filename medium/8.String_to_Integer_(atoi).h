/*
Implement the myAtoi(string s) function, which converts a string to a 32-bit signed integer
(similar to C/C++'s atoi function).

The algorithm for myAtoi(string s) is as follows:

1. Read in and ignore any leading whitespace.
2. Check if the next character (if not already at the end of the string) is '-' or '+'.
   Read this character in if it is either. This determines if the final result is negative
   or positive respectively. Assume the result is positive if neither is present.
3. Read in next the characters until the next non-digit charcter or the end of the input is reached.
   The rest of the string is ignored.
4. Convert these digits into an integer (i.e. "123" -> 123, "0032" -> 32). If no digits were read,
   then the integer is 0. Change the sign as necessary (from step 2).
5. If the integer is out of the 32-bit signed integer range [-231, 231 - 1], then clamp the integer
   so that it remains in the range. Specifically, integers less than -231 should be clamped to -231,
   and integers greater than 231 - 1 should be clamped to 231 - 1.
6. Return the integer as the final result.

Note:

Only the space character ' ' is considered a whitespace character.
Do not ignore any characters other than the leading whitespace or the rest of the string after the digits.

Example 1:

Input: str = "42"
Output: 42
Explanation: The underlined characters are what is read in, the caret is the current reader position.
Step 1: "42" (no characters read because there is no leading whitespace)
         ^
Step 2: "42" (no characters read because there is neither a '-' nor '+')
         ^
Step 3: "42" ("42" is read in)
           ^
The parsed integer is 42.
Since 42 is in the range [-231, 231 - 1], the final result is 42.

Example 2:

Input: str = "   -42"
Output: -42
Explanation:
Step 1: "   -42" (leading whitespace is read and ignored)
            ^
Step 2: "   -42" ('-' is read, so the result should be negative)
             ^
Step 3: "   -42" ("42" is read in)
               ^
The parsed integer is -42.
Since -42 is in the range [-231, 231 - 1], the final result is -42.

Example 3:

Input: str = "4193 with words"
Output: 4193
Explanation:
Step 1: "4193 with words" (no characters read because there is no leading whitespace)
         ^
Step 2: "4193 with words" (no characters read because there is neither a '-' nor '+')
         ^
Step 3: "4193 with words" ("4193" is read in; reading stops because the next character is a non-digit)
             ^
The parsed integer is 4193.
Since 4193 is in the range [-231, 231 - 1], the final result is 4193.

Example 4:

Input: str = "words and 987"
Output: 0
Explanation:
Step 1: "words and 987" (no characters read because there is no leading whitespace)
         ^
Step 2: "words and 987" (no characters read because there is neither a '-' nor '+')
         ^
Step 3: "words and 987" (reading stops immediately because there is a non-digit 'w')
         ^
The parsed integer is 0 because no digits were read.
Since 0 is in the range [-231, 231 - 1], the final result is 4193.

Example 5:

Input: str = "-91283472332"
Output: -2147483648
Explanation:
Step 1: "-91283472332" (no characters read because there is no leading whitespace)
         ^
Step 2: "-91283472332" ('-' is read, so the result should be negative)
          ^
Step 3: "-91283472332" ("91283472332" is read in)
                     ^
The parsed integer is -91283472332.
Since -91283472332 is less than the lower bound of the range [-231, 231 - 1],
the final result is clamped to -231 = -2147483648.

Constraints:

0 <= s.length <= 200
s consists of English letters (lower-case and upper-case), digits (0-9), ' ', '+', '-', and '.'.

*/

#include <string>

#define INT_MIN -2147483648

#define INT_MAX  2147483647

using namespace std;

class Solution {
public:
    int myAtoi(string m_string) {
        const char *s = m_string.c_str();
        long acc = 0, cutoff;
        bool negative = false;
        int cutlim, basenum = 10;

        // Skip blank character
        while ((*s) == ' ') s++;

        // Negative number?
        if (s[0] == '-')      { negative = true; s++; }
        else if (s[0] == '+') { s++; }

        // Compute output range limits
        cutoff = negative ? INT_MIN : INT_MAX;
        cutlim = cutoff % basenum;
        cutoff /= basenum;

        if (negative) {
            if (cutlim > 0) cutoff += 1;
            cutlim = -cutlim;
        }

        while (1) {
            unsigned char c = (unsigned char) *s++;

            if (c >= '0' && c <= '9') c -= '0';
            else break;

            if (c >= basenum) break;

            if (negative) {
                if (acc < cutoff || (acc == cutoff && c > cutlim)) {
                    acc = INT_MIN;
                } else {
                    acc *= basenum;
                    acc -= c;
                }
            } else {
                if (acc > cutoff || (acc == cutoff && c > cutlim)) {
                    acc = INT_MAX;
                } else {
                    acc *= basenum;
                    acc += c;
                }
            }
        }
        return acc;
    }
};