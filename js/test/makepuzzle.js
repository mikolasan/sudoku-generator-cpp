var assert = require('assert');
var sudoku = require('../generator');

describe('makepuzzle', function () {
  it('return a puzzle', function () {
    var puzzle = sudoku.makepuzzle();
    console.log(puzzle);
  });
});
