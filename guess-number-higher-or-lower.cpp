/** NOTE: cpp only */
int guess(int num);
class Solution {
  public:
    int guessNumber(int n) {
        int left = 1, right = n;
        while (left <= right) {
            const auto mid = left + (right - left) / 2;
            if (guess(mid) <= 0)
                right = mid - 1;
            else
                left = mid + 1;
        }
        return left;
    }
};
