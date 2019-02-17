class Cell {
public:
    bool unsolved;
    bool placeDigit(int digit) {
        if (unsolved) {
            _digit = digit;
        }
    }
private:
    int _digit;
}
