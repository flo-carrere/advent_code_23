## Scratchcards

This is the solution for AoC 2023 - Day6 - Wait for it

## Build

By default the **part 1** of the exercise is built.

```
cmake -G Ninja -B build -S .
cmake --build .\build\
```

## Build options

<BUILD_FOR_PART_1> "Builds for part 1 of the exercise"

```
cmake -G Ninja -B build -S . -DBUILD_FOR_PART_1=1
cmake --build .\build\
```

## Testing

Once built you can invoke the <app.exe> executable on some input files.

```
// The sample input from AoC
.\build\app.exe .\inputs\sample.txt

// The input to PASS the level in AoC
.\build\app.exe .\inputs\real_input.txt
```
