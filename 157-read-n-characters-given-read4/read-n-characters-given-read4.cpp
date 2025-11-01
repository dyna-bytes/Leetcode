/**
 * The read4 API is defined in the parent class Reader4.
 *     int read4(char *buf4);
 */
#define debug(x) cout << #x << " is " << x << endl;

class Solution {
public:
    /**
     * @param buf Destination buffer
     * @param n   Number of characters to read
     * @return    The number of actual characters read
     */
    int read(char *buf, int n) {
        int copied_chars = 0;
        int read_chars = 4;
        while (copied_chars < n) {
            read_chars = read4(buf + copied_chars);
            copied_chars += read_chars;
            if (read_chars != 4) break;
        }
        buf[n] = '\0';

        return copied_chars;
    }
};