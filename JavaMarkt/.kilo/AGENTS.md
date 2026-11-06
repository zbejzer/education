# JavaMarkt

## Build commands

Always run Maven with Java 17 as JAVA_HOME (dependencies are cached for it):

```bash
JAVA_HOME=/usr/lib/jvm/temurin-17-jdk-amd64 mvn compile
JAVA_HOME=/usr/lib/jvm/temurin-17-jdk-amd64 mvn test
```

Note: the path `/usr/lib/jvm/java-17-temurin-jdk` documented earlier does not exist; use `temurin-17-jdk-amd64`.

## Tests with coverage

A plain `mvn test` (with JAVA_HOME as above) runs tests and generates the JaCoCo
coverage report — no extra flags or manual `-javaagent` needed. Works offline
with `-o`; the local Maven repository contains all required artifacts.

Results after the run:

- `target/site/jacoco/index.html` — human-readable HTML report
- `target/site/jacoco/jacoco.csv` — per-class counters (LINE/BRANCH/COMPLEXITY/...),
  best for automated analysis
- `target/site/jacoco/jacoco.xml` — per-method detail

To analyze the report, run the parser script with uv (stdlib only, no project or
dependencies needed; from the `JavaMarkt/` directory):

```bash
uv run .kilo/jacoco_parser.py
```

On this machine uv's cache (`~/.cache/uv`) is a read-only mount, so prefix the
command with a writable cache directory:

```bash
UV_CACHE_DIR=.kilo/tmp/uv-cache uv run .kilo/jacoco_parser.py
```

It prints the missed-branch count (the coverage bar is 0 missed branches), details
for any missed branch, and uncovered lines per source file. Exits non-zero when
any branch is missed. An alternate report path can be passed as the first argument.

## Scratch files and artifacts

Place any produced artifacts or non-code files (reports, backups, generated
files, scratch output) only in `.kilo/tmp/` — never in the repository tree,
system temp directories, or other locations. `.kilo/tmp/` is git-ignored.
