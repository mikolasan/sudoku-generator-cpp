class Cell {
public:
    Cell(unsigned x, unsigned y) :
        _x(x),
        _y(y)
    {}
    bool unsolved;
    bool placeDigit(int digit) {
        if (unsolved) {
            _digit = digit;
        }
    }
private:
    unsigned _x, _y;
    int _digit;
}
