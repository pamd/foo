/* Written by leetcode:
 * http://www.mitbbs.com/article_t/JobHunting/32046063.html
 */
int atoi(const char *str) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int sign = 1;
        while (*str == ' ') {
            str++;
        }
        if (*str == '+') {
            str++;
        } else if (*str == '-') {
            sign = -1;
            str++;
        }
        long long num = 0;
        bool overflow = false;
        while (!overflow && isAlpha(*str)) {
            int dig = *str - '0';
            num = num*10 + dig;
            if (sign == 1 && num > INT_MAX ||
                sign == -1 && -num < INT_MIN)
                overflow = true;
            str++;
        }
        if (sign == -1) {
            num = -num;
        }
        if (overflow) {
            return (sign == 1) ? INT_MAX : INT_MIN;
        } else {
            return (int)num;
        }
    }

    bool isAlpha(char c) {
        return c >= '0' && c <= '9';
    }
