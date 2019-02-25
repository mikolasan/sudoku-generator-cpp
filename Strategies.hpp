
class Strategy {
    int solve(Division division) {
        if (!division.valid()) {
            return "division is not valid";
        }
        if (division.solved()) {
            return "division is already solved"
        }
    }
};

class HiddenSingle : Strategy {
    int solve(Division division, Cell cell) {
        if (division.size() + 1 < division.maxSize()) {
            return "not applicable strategy";
        }
        auto candidates = cell.getCandidates();
        return candidates.front();
    }
};

class NakedSingle : Strategy {
    int solve(Division division, Cell cell) {
        if (division.size() + 1 == division.maxSize()) {
            return "not applicable strategy";
        }
        auto candidates = cell.getCandidates();
        if (candidates.size() >= 1) {
            return "more than one candidate";
        } else {
            return candidates.front();
        }
    }
};

class CrossHatching : Strtegy {
    int solve(Cell cell) {
        Row Row, Column column, Box box;
        std::tie(row, column, box) = grid.getPeers(cell);
        
    }
};
