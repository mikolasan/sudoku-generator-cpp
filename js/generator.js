// Sudoku Generator and Solver for node.js
// Copyright (c) 2011 Blagovest Dachev.  All rights reserved.
//
// This is a port of David Bau's python  implementation:
// http://davidbau.com/archives/2006/09/04/sudoku_generator.html

var map = require('lodash.map');
var range = require('lodash.range');

function makepuzzle(board) {
  var puzzle = [];
  var deduced = makeArray(81, null);
  var order = range(81);

  shuffleArray(order);

  for (var i = 0; i < order.length; i++) {
    var pos = order[i];

    if (deduced[pos] == null) {
      puzzle.push({ pos: pos, num: board[pos] });
      deduced[pos] = board[pos];
      deduce(deduced);
    }
  }

  shuffleArray(puzzle);

  for (var i = puzzle.length - 1; i >= 0; i--) {
    var e = puzzle[i];
    puzzle.splice(i, 1);
    var rating = checkpuzzle(boardforentries(puzzle), board);
    if (rating == -1) {
      puzzle.push(e);
    }
  }

  return boardforentries(puzzle);
}

function checkpuzzle(puzzle, board) {
  if (board == undefined) {
    board = null;
  }

  var tuple1 = solveboard(puzzle);
  if (tuple1.answer == null) {
    return -1;
  }

  if (board != null && boardmatches(board, tuple1.answer) == false) {
    return -1;
  }

  var difficulty = tuple1.state.length;
  var tuple2 = solvenext(tuple1.state);

  if (tuple2.answer != null) {
    return -1;
  }

  return difficulty;
}

function solveboard(original) {
  var board = [].concat(original);
  var guesses = deduce(board);

  if (guesses == null) {
    return { state: [], answer: board };
  }

  var track = [{ guesses: guesses, count: 0, board: board }];
  return solvenext(track);
}

function solvenext(remembered) {
  while (remembered.length > 0) {
    var tuple1 = remembered.pop();

    if (tuple1.count >= tuple1.guesses.length) {
      continue;
    }

    remembered.push({ guesses: tuple1.guesses, count: tuple1.count + 1, board: tuple1.board });
    var workspace = [].concat(tuple1.board);
    var tuple2 = tuple1.guesses[tuple1.count];

    workspace[tuple2.pos] = tuple2.num;

    var guesses = deduce(workspace);

    if (guesses == null) {
      return { state: remembered, answer: workspace };
    }

    remembered.push({ guesses: guesses, count: 0, board: workspace });
  }

  return { state: [], answer: null };
}

function deduce(board) {
  while (true) {
    var stuck = true;
    var guess = null;
    var count = 0;

    // fill in any spots determined by direct conflicts
    var [allowed, needed] = figurebits(board);

    for (var pos = 0; pos < 81; pos++) {
      if (board[pos] == null) {
        var numbers = listbits(allowed[pos]);
        if (numbers.length == 0) {
          return [];
        } else if (numbers.length == 1) {
          board[pos] = numbers[0];
          stuck = false;
        } else if (stuck) {
          var t = map(numbers, function (val, key) {
            return { pos: pos, num: val };
          });

          [guess, count] = pickbetter(guess, count, t);
        }
      }
    }

    if (!stuck) {
      [allowed, needed] = figurebits(board);
    }

    // fill in any spots determined by elimination of other locations
    for (var axis = 0; axis < 3; axis++) {
      for (var x = 0; x < 9; x++) {
        var numbers = listbits(needed[axis * 9 + x]);

        for (var i = 0; i < numbers.length; i++) {
          var n = numbers[i];
          var bit = 1 << n;
          var spots = [];

          for (var y = 0; y < 9; y++) {
            var pos = posfor(x, y, axis);
            if (allowed[pos] & bit) {
              spots.push(pos);
            }
          }

          if (spots.length == 0) {
            return [];
          } else if (spots.length == 1) {
            board[spots[0]] = n;
            stuck = false;
          } else if (stuck) {
            var t = map(spots, function (val, key) {
              return { pos: val, num: n };
            });

            [guess, count] = pickbetter(guess, count, t);
          }
        }
      }
    }

    if (stuck) {
      if (guess != null) shuffleArray(guess);
      return guess;
    }
  }
}

function figurebits(board) {
  var needed = [];
  var allowed = map(board, function (val, key) {
    return val == null ? 511 : 0;
  }, []);

  for (var axis = 0; axis < 3; axis++) {
    for (var x = 0; x < 9; x++) {
      var bits = axismissing(board, x, axis);
      needed.push(bits);

      for (var y = 0; y < 9; y++) {
        var pos = posfor(x, y, axis);
        allowed[pos] = allowed[pos] & bits;
      }
    }
  }

  return [allowed, needed];
}

function posfor(x, y, axis) {
  if (axis == undefined) { axis = 0; }

  if (axis == 0) {
    return x * 9 + y;
  }
  else if (axis == 1) {
    return y * 9 + x;
  }

  return ([0, 3, 6, 27, 30, 33, 54, 57, 60][x] + [0, 1, 2, 9, 10, 11, 18, 19, 20][y])
}

function axismissing(board, x, axis) {
  var bits = 0;

  for (var y = 0; y < 9; y++) {
    var e = board[posfor(x, y, axis)];

    if (e != null) {
      bits |= 1 << e;
    }
  }

  return 511 ^ bits;
}

function listbits(bits) {
  var list = [];
  for (var y = 0; y < 9; y++) {
    if ((bits & (1 << y)) != 0) {
      list.push(y);
    }
  }

  return list;
}

function pickbetter(b, c, t) {
  if (b == null || t.length < b.length) {
    return [t, 1];
  }
  else if (t.length > b.length) {
    return [b, c];
  }
  else if (randomInt(c) == 0) {
    return [t, c + 1];
  }

  return [b, c + 1];
}

function boardforentries(entries) {
  var board = map(range(81), function (val, key) {
    return null;
  });

  for (var i = 0; i < entries.length; i++) {
    var item = entries[i];
    var pos = item.pos;
    var num = item.num;

    board[pos] = num;
  }

  return board;
}

function boardmatches(b1, b2) {
  for (var i = 0; i < 81; i++) {
    if (b1[i] != b2[i]) {
      return false;
    }
  }

  return true;
}

function randomInt(max) {
  return Math.floor(Math.random() * (max + 1));
}

function shuffleArray(original) {
  // Swap each element with another randomly selected one.
  for (var i = 0; i < original.length; i++) {
    var j = i;
    while (j == i) {
      j = Math.floor(Math.random() * original.length);
    }
    var contents = original[i];
    original[i] = original[j];
    original[j] = contents;
  }
}

function makeArray(length, value) {
  return map(range(length), function (val, key) {
    return value;
  })
}


function ratepuzzle(puzzle, samples) {
  var total = 0;

  for (var i = 0; i < samples; i++) {
    var tuple = solveboard(puzzle);

    if (tuple.answer == null) {
      return -1;
    }

    total += tuple.state.length;
  }

  return total / samples;
}


function solvepuzzle(board) {
  return solveboard(board).answer;
}


module.exports = {
  makepuzzle: function () { return makepuzzle(solvepuzzle(makeArray(81, null))); },
  solvepuzzle: solvepuzzle,
  ratepuzzle: ratepuzzle,
  posfor: posfor
};