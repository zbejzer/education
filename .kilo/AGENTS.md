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
dependencies needed; from the repository root):

```bash
uv run .kilo/jacoco_parser.py JavaMarkt/target/site/jacoco/jacoco.xml
```

The report path is optional and defaults to `target/site/jacoco/jacoco.xml` relative
to the current directory, so pass it explicitly when running from the repository root.

On this machine uv's cache (`~/.cache/uv`) is a read-only mount, so prefix the
command with a writable cache directory:

```bash
UV_CACHE_DIR=.kilo/tmp/uv-cache uv run .kilo/jacoco_parser.py JavaMarkt/target/site/jacoco/jacoco.xml
```

It prints the missed-branch count (the coverage bar is 0 missed branches), details
for any missed branch, and uncovered lines per source file. Exits non-zero when
any branch is missed. An alternate report path can be passed as the first argument.

## Test development workflow (mandatory)

Coverage is not the goal; scenario coverage is. Every test change, and every feature
change that adds tests, follows this sequence:

1. **Baseline** — run `mvn test` and the JaCoCo parser. Record total tests, failures,
   and missed branches.
2. **Name audit** — verify each test name describes its assertion. Rename tests whose
   names overclaim, underclaim, or describe a method instead of behavior; add the
   missing assertion when the name promises more than the body checks.
3. **Semantic group analysis** — read each test class as a specification. From the
   names and grouped setup alone, list scenarios the group implies but never
   exercises: empty/non-empty, before/after, first/middle/last, duplicate/unique,
   success/boundary/failure, execute/undo.
4. **Existence check** — for every candidate scenario, locate the production path. If
   the behavior is absent, report it as an unimplemented feature or known gap. Do not
   add a test for absent behavior and do not weaken the suite to make it green.
5. **Write tests** — add the verified high-value scenarios in the existing JUnit 5
   style. One test per behavior, explicit arrange, observable assertions, `assertAll`
   for related checks, and `assertSame` when identity is contractual.
6. **Verify** — run the full suite, then the JaCoCo parser with the explicit report
   path (see *Tests with coverage*). The task is complete only with 0 missed branches
   and no regressions.
7. **Parallel review** — for changes over roughly 100 changed lines or 3 files, run
   independent read-only reviewers in parallel before reporting completion. See
   *Parallel agent workflows* below.

Never assert a bug or an implementation detail just to raise coverage. If production
behavior is wrong, report it; change production only when the task authorizes it.

The reusable `/test-audit` command encodes this workflow; use it for test-gap work.

## Parallel agent workflows

Use simultaneous subagents for **independent read-only analysis**, not for concurrent
editing. Fan out only when scopes are disjoint and each worker can conclude without
another worker's output. Keep synthesis, edits, and final verification in the main
agent.

| Workflow | Parallel shape | Why it helps |
|---|---|---|
| Test-gap review | 3 reviewers: business logic, duplication, dead code | Independent lenses catch false assumptions, contradictory tests, and unused scaffolding that one pass misses. |
| Diff/code review | 3 reviewers for medium; all six for large (security, performance, business logic, deploy safety, duplication, dead code) | Tracks are independent; `/review deep` already fans out this way. |
| Refactor impact analysis | One reader per package/layer (`model`, `command`, `session`, `ui`) | Call-site and test-impact inventories are independent and parallel. |
| Layer design audit | One reader per layer comparing `DESIGN.md` to code | Each layer can be checked against the design independently. |
| Failure triage | One investigator per failing test class or failure signature | Independent hypotheses shorten root-cause time. |
| Multi-worktree feature split | One Agent Manager worktree per independent feature after shared contracts are fixed | Real parallelism, but only for disjoint code and after stabilizing shared interfaces. |

Do **not** fan out when:

- work is sequential (TDD red → green, `model` → `command` → `parser` → `ui`);
- two workers would edit the same file or need each other's output;
- the change is small (fewer than ~100 changed lines and at most 3 files) — review it
  in one pass;
- the task is one narrow fix with a single obvious verification.

Guardrails:

- Subagents are research-only unless the task explicitly assigns disjoint files to
  each; never let two agents edit the same file.
- Give each subagent the exact scope, its track, and the required output. Require
  high-confidence findings only, or exactly `NO_FINDINGS`.
- Do not run `mvn test` concurrently in the same checkout: Surefire/JaCoCo share
  `target/`. Serialize builds or give each agent a separate Agent Manager worktree.
- The main agent re-checks every finding against the diff and owns the final report.

## Scratch files and artifacts

Place any produced artifacts or non-code files (reports, backups, generated
files, scratch output) only in `.kilo/tmp/` — never in the repository tree,
system temp directories, or other locations. `.kilo/tmp/` is git-ignored.
