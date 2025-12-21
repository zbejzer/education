# Warsztat programisty - Zadanie projektowe - Magazyn

## Prerequisites

- [CMake](https://cmake.org/download/)

In order to use the [run_scenario.sh script](scripts\run_scenario.sh) you'll need the `pdflatex` tool along with support for Polish language.

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
