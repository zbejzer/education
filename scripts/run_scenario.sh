#!/usr/bin/env bash

cd "$(dirname "$0")"
cd "./../tests"
./../build/warehouse pdf < scenario.txt
pdflatex -interaction=nonstopmode report1411.tex
pdflatex -interaction=nonstopmode report1211.tex
