#!/usr/bin/env bash

mode=$1
scenario_file=$2
output_dir=$3

warehouse_bin="$(realpath $(dirname "$0"))/warehouse"
scenario_dir="$(realpath $(dirname "$scenario_file"))/"

exit_code=0

if [ -z "$mode" ]; then
    echo "Mode not specified"
    exit_code=1
fi

if [ -z "$scenario_file" ]; then
    echo "Input file not specified"
    exit_code=1
fi

if [ -z "$output_dir" ]; then
    echo "Output directory not specified"
    exit_code=1
fi

if [ ! -f "$scenario_file" ]; then
    echo "Specified scenario file $scenario_file doesn't exist"
    exit_code=1
fi

if [ "$exit_code" -ne "0" ]; then
    echo "Usage: $(basename $0) [mode] [input file] [output directory]"
    exit $exit_code
fi

if [ ! -d "$output_dir" ]; then
    mkdir -p "$output_dir/" || exit 1
fi

scenario_file="$(realpath $scenario_file)"
output_dir="$(realpath $output_dir)"

cd "$scenario_dir"

"$warehouse_bin" "$mode" < "$scenario_file" | while read -r filename; do
    cd "$scenario_dir"
    mv "./$filename" "$output_dir"
    cd "$output_dir"
    if [ "$mode" = "pdf" ]; then
        out_filename="$(basename "$filename" ".tex").pdf"
    else
        out_filename="$filename"
    fi
    echo "Creating $output_dir/$out_filename"
    if [ "$mode" = "pdf" ]; then
        pdflatex -interaction=nonstopmode "$output_dir/$filename" >/dev/null || (echo "Error creating $output_dir/$filename" && exit_code=73)
    fi
done

exit_code=${PIPESTATUS[0]}

mv "$scenario_dir/store.txt" "$output_dir"

exit $exit_code
