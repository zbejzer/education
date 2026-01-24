# Warsztat programisty - Zadanie projektowe - Magazyn

## Completed non-mandatory elements

| Code | Punctuation | Description                             |
| ---- | ----------- | --------------------------------------- |
| RD   | 1           | Readme file                             |
| L1   | 1           | Using library                           |
| L2   | 1           | Using both static and dynamic libraries |
| EC   | 2           | Handling subcategories                  |

## Prerequisites

- [CMake](https://cmake.org/download/)

In order to use the [run_scenario.sh script](tools\run_scenario.sh) you'll need the `pdflatex` tool along with support for Polish language.

### Ubuntu

Install the following TeX Live packages:

```bash
sudo apt-get install -y texlive-base texlive-latex-recommended texlive-lang-polish
```

## Cloning

### Submodules

This software depends on Google Test library. To clone it as a submodule use:

```bash
git submodule update --init --remote --recursive
```

## Building

### CMake

Cleaning previous configuration

```bash
rm -rf ./build
```

Building

```bash
cmake -S . -B build
cmake --build build
```

## Running

```bash
 ./scripts/run_scenario.sh <pdf|txt>
```

## Running tests

### Unit tests

```bash
ctest --test-dir build -j4 --output-on-failure
```
