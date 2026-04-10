#pragma once

enum class Tile {
    Empty = '.',
    Wall = '#',
    Player = '@',
    Box = 'B',
    Target = 'X',
    BoxOnTarget = '*',
    Void = -1,
};

enum class Direction {
    Left,
    Up,
    Down,
    Right,
};