#!/usr/bin/env python3
"""Parse the JaCoCo XML report produced by `mvn test`.

Reports the branch-coverage bar (0 missed branches) and lists uncovered
lines per source file. Exits non-zero when any branch is missed, so it can
gate a stage on the coverage rule.

Usage:
    uv run .kilo/jacoco_parser.py [path-to-jacoco.xml]

Stdlib only; no project or dependencies required.
"""

import argparse
import sys
import xml.etree.ElementTree as ET

DEFAULT_REPORT = "target/site/jacoco/jacoco.xml"


def parse_report(path):
    try:
        tree = ET.parse(path)
    except ET.ParseError as e:
        print(f"Error: cannot parse {path}: {e}", file=sys.stderr)
        raise SystemExit(2)
    except OSError as e:
        print(f"Error: cannot read {path}: {e}", file=sys.stderr)
        raise SystemExit(2)
    return tree.getroot()


def missed_branches(root):
    for counter in root.findall("counter"):
        if counter.get("type") == "BRANCH":
            return int(counter.get("missed", 0))
    return 0


def main():
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("report", nargs="?", default=DEFAULT_REPORT,
                        help=f"path to jacoco.xml (default: {DEFAULT_REPORT})")
    args = parser.parse_args()

    root = parse_report(args.report)
    missed = missed_branches(root)

    print(f"Report: {args.report}")
    print(f"Missed branches: {missed}")
    if missed == 0:
        print("Branch coverage bar met (0 missed branches).")
    else:
        print("Branch coverage bar FAILED.")
        for pkg in root.iter("package"):
            for sourcefile in pkg.iter("sourcefile"):
                for line in sourcefile.iter("line"):
                    if int(line.get("mb", 0)) > 0:
                        print(f"  missed branch: "
                              f"{pkg.get('name')}.{sourcefile.get('name')}:"
                              f"{line.get('nr')}")

    uncovered = []
    for pkg in root.iter("package"):
        for sourcefile in pkg.iter("sourcefile"):
            lines = [int(line.get("nr")) for line in sourcefile.iter("line")
                     if int(line.get("mi", 0)) > 0]
            if lines:
                uncovered.append((pkg.get("name"), sourcefile.get("name"), lines))

    if uncovered:
        print("Uncovered lines:")
        for package, sourcefile, lines in uncovered:
            print(f"  {package}.{sourcefile}: {lines}")
    else:
        print("Uncovered lines: none.")

    raise SystemExit(1 if missed > 0 else 0)


if __name__ == "__main__":
    main()
