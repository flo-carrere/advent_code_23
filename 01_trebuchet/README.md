## Trebuchet

This is the solution for AoC 2023 - Day1 - trebuchet

## Build

This allows to build for the requirements of part 2 (matching digit and "string digit" in the input)

```
cmake -G Ninja -B build -S .
cmake --build .\build\
```

## Build options

To build for the requirements of part 1 only (matching only digit in the input) you'll
have to build with the <CHECKS_PART_2> option **deactivated**

```
cmake -G Ninja -B build -S . -DCHECKS_PART_2=OFF
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
