#include <vector>

using Cell = int;

class Division {
public:
    Division(unsigned id) :
        _id(id),
        _full(false)
    {}
    bool rule() {
        //return std::all_of(cells.begin(), cells.end(), [] (
    }
    bool constraint() {

    }
private:
    unsigned _id;
    char _altId;
    std::vector<Cell> _cells; // 9
    bool _full;
};

class Rows : Division;
class Column : Division;
class Box : Division;

using House = Row;

class Grid {
public:
    Grid() {}
    void fill() {
        for (auto )
    }
    void generate() {

    }
    std::string toString();
    void fill(std::string values);
    std::tuple<Row, Column, Box> getPeers(Cell cell);
    std::vector<House> getHouses();
    std::vector<Floor> getFloors();
    std::vector<Tower> getTowers();
    std::vector<Cell> getCells();
    std::vector<int> getCandidates();
    std::vector<Row> getRows();
    std::vector<Column> getColumns();
    std::vector<Box> getBoxes();
    std::vector<Diagonal> getDiagonals();
private:
    std::vector<Cell> cells; // 81
};

static Grid startingGrid;
static Grid solutionGrid;
static Grid candidateGrid;
