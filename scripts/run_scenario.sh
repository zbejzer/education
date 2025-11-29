#!/usr/bin/env bash

mode=$1

cd "$(dirname "$0")"
cd "./../"

work_dir="$(realpath "./")"
build_dir="$work_dir/build"
test_dir="$work_dir/tests"
dist_dir="$work_dir/dist"

exit_code=0

mkdir -p "$dist_dir/" 2>/dev/null

cd "./tests"

"$build_dir/warehouse" $mode < scenario.txt | while
    read -r filename
do
    mv "$test_dir/$filename" "$dist_dir"
    cd "$dist_dir"
    if [ "$mode" == "pdf" ]; then
        out_filename="$(basename "$filename" ".tex").pdf"
    else
        out_filename="$filename"
    fi
    echo "Creating $dist_dir/$out_filename"
    if [ "$mode" == "pdf" ]; then
        pdflatex -interaction=nonstopmode "$dist_dir/$filename" >/dev/null || (echo "Error creating $dist_dir/$filename" && exit_code=73)
    fi
done

mv "$test_dir/store.txt" "$dist_dir"

exit $exit_code