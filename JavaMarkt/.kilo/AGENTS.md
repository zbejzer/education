# JavaMarkt

## JDK

The preferred JDK for this project is **Eclipse Temurin 17**. Do not assume or
hardcode its installation path — it varies between machines and can change on
reinstall. Discover it before running any Java or Maven command:

```bash
ls /usr/lib/jvm/          # list installed JVMs; names vary, symlinks are common
grep -E "IMPLEMENTOR|JAVA_VERSION" /usr/lib/jvm/<dir>/release
```

The `release` file in a JDK root directory identifies the vendor and version.
A correct match shows `IMPLEMENTOR="Eclipse Adoptium"` and `JAVA_VERSION="17.…"`.
Example: the directory may be named `temurin-17-jdk` (a symlink), or
`java-17-temurin-jdk`, or carry a platform suffix — verify by the `release`
file contents, never by the name.

## Build commands

Always run Maven with the discovered Temurin 17 as `JAVA_HOME`
(dependencies are cached for it):

```bash
JAVA_HOME=/usr/lib/jvm/<discovered-temurin-17-dir> mvn compile
JAVA_HOME=/usr/lib/jvm/<discovered-temurin-17-dir> mvn test
```

## Sandbox and restricted internet access

Agents run in a sandbox without direct internet access. If a build or test run
fails with symptoms of a missing environment dependency — most commonly Maven
artifacts absent from the local repository cache — notify the user **immediately**
instead of retrying or working around it. The user has to run such commands
manually outside the sandbox; usually a plain `mvn test` run by the user is
enough to pull all required dependencies into the local cache. Retry only after
the user confirms the command has been run.

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
