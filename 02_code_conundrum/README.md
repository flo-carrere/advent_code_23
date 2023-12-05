## Code conundrum

This is the solution for AoC 2023 - Day2 - code conundrum

## Build

By default the **part 2** of the exercise is built.

```
cmake -G Ninja -B build -S . -DBUILD_FOR_PART_1=OFF
cmake --build .\build\
```

## Build options

To build for part 1 only (checking if games are (im)possible) you'll
have to build with the <BUILD_FOR_PART_1> option **activated**

```
cmake -G Ninja -B build -S . -BUILD_FOR_PART_1=ON
...
```

## Testing

Once built you can invoke the <app.exe> executable on some input files.

```
// The sample input from AoC
.\build\app.exe .\inputs\sample.txt

// The input to PASS the level in AoC
.\build\app.exe .\inputs\real_input.txt

// Some non-automated "unit-tests" to split the problem into small chunks ;-)
.\build\app.exe .\inputs\unit_test.txt
```

```
// For part 1
1 g
3 r
6 b
3 g
6 r
3 g
15 b -> Impossible   <<<--- This game is impossible with the set {12r, 13g, 14b}
Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, **15** blue, 14 red
 -> 0  <<<--- Output is 0 for that game

6 r
1 b
3 g
2 b
1 r
2 g    <<<--- This game is "possible" with the set {12r, 13g, 14b}
Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green
 -> 5  <<<--- Output is the "game ID" for a "possible" game
 ```

 ```
 // For part 2
14 3 15 <<<--- This shows the minimal set of cube to make a game "possible"
Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red
 -> 630 <<<--- Power of the set

6 3 2
Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green
 -> 36
```
