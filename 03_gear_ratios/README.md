## Gear Ratios

This is the solution for AoC 2023 - Day3 - Gear Ratios

## Build

By default the **part 1** of the exercise is built.

```
cmake -G Ninja -B build -S .
cmake --build .\build\
```

## Build options

<BUILD_FOR_PART_1> "Builds for part 1 of the exercise"  
<DISPLAY_SCHEMATIC> "Debug option to display schematic" (default ON)  
<DISPLAY_PARTS> "Debug option to display all extracted parts" (default OFF)  
<DISPLAY_SYMBOLS> "Debug option to display all extracted symbols" (default OFF)  

```
cmake -G Ninja -B build -S . -DDISPLAY_PARTS=ON -DDISPLAY_SYMBOLS=ON
cmake --build .\build\
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
