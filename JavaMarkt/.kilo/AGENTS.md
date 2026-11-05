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

To analyze, parse `jacoco.xml` (bundle counter = root `<counter>` elements,
method coverage = `<class>/<method>` counters, missed lines = `<line mi="...">`).

