class Grid {
public:
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
    std::vector<Cell> cells;
}
