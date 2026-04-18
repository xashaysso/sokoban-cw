#pragma once

enum class Tile {
    Empty = '.',
    Wall = '#',
    Player = '@',
    Box = 'B',
    Target = 'X',
    BoxOnTarget = '*',
    Void = ' ',
};

enum class Direction {
    Left,
    Up,
    Down,
    Right,
};

enum class MoveResult {
    None,
    Walk,
    Push,
};