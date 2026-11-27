---
description: Audit test names and semantic scenario coverage, then add missing tests for behavior that exists
---

# Test audit: names, semantic gaps, missing tests

Scope: `$ARGUMENTS`. If empty, audit all of `JavaMarkt/src/test/java`; otherwise
restrict the audit to the named packages, classes, or files. Do not change production
code. Tests may be added or renamed; production defects are reported, not fixed.

## Phase 0 — Baseline

From the repository root, discover Temurin 17 as described in `.kilo/AGENTS.md`, then:

```bash
cd JavaMarkt
JAVA_HOME=<discovered-temurin-17> mvn test
cd ..
UV_CACHE_DIR=.kilo/tmp/uv-cache uv run .kilo/jacoco_parser.py JavaMarkt/target/site/jacoco/jacoco.xml
```

Record the test count, failures, and missed branches. A 100% branch result is the
starting point, not evidence that scenarios are covered.

## Phase 1 — Name audit

For every test in scope, compare the name with the assertion body.

- Flag names that overclaim (`...ForAllProducts` but only one product is used).
- Flag names that underclaim or describe the method instead of behavior.
- Flag names that claim a path the body never exercises (success only, no failure).
- Rename clear mismatches. When a name promises more than the body checks, add the
  missing assertion rather than weakening the name.
- Do not rename tests for style alone.

## Phase 2 — Semantic group analysis

Treat each test class as a specification. Using only the names and grouped setup,
list scenarios the group implies but does not contain. Check at least:

- empty vs non-empty collection;
- state before vs after a mutation;
- first, middle, and last element;
- duplicate codes/keys vs unique ones;
- success, boundary, and failure paths;
- execute followed by undo, and repeated undo (LIFO);
- defensive-copy and immutability contracts;
- parser/UI behavior for invalid and boundary input;
- global invariants (unique keywords, every enum value resolvable, every command
  reachable through the parser).

Prefer gaps that a user or the domain contract would notice.

## Phase 3 — Existence check

For each candidate scenario, locate the production path in `JavaMarkt/src/main/java`.

- If the behavior exists but is untested, it is a test gap.
- If the behavior does not exist, it is an unimplemented feature or known gap. Report
  it and do not add a test for it.
- Never add a failing/aspirational test, and never assert a bug or private
  implementation detail to raise coverage.

## Phase 4 — Add the missing tests

Follow the project style:

- JUnit 5 `@Test`, `assertAll` for related checks, `assertSame` when identity matters.
- One observable behavior per test; arrange state explicitly; no order dependence.
- Domain language; assert observable state rather than interaction counts.
- Match the existing package/layout and naming conventions.
- Reuse existing helpers; do not add parameterized tests or new libraries.

Group new tests next to related tests in the same class. Keep the diff focused on
verified gaps.

## Phase 5 — Verify

Run the full suite and the JaCoCo parser again. Completion requires:

- no regressions;
- 0 missed branches;
- every added test fails if the corresponding production behavior is removed or
  inverted (sanity-check the assertion).

## Phase 6 — Parallel review

For changes over roughly 100 changed lines or 3 files, launch independent read-only
subagents in parallel with the Task tool:

1. **Business logic** — false assumptions, vacuous assertions, wrong expected values,
   tests that would pass with broken production code.
2. **Duplication** — new tests that duplicate existing coverage or copy setup/asserts
   in a way that will drift.
3. **Dead code** — unused imports, locals, unreachable assertions, obsolete helpers.

Instruct each subagent to edit nothing, review only the current diff, and return only
high-confidence findings in a compact `path`, `line`, `why`, `finding`, `suggestion`
shape, or exactly `NO_FINDINGS`. Re-check every finding against the diff; discard
style, naming, and pre-existing issues. For very large or cross-layer changes, add
the remaining review tracks (security, performance, deploy safety) as separate
subagents.

Do not run `mvn test` concurrently in the same checkout; Surefire and JaCoCo share
`target/`.

## Report

Return a concise report with:

- baseline vs final test/branch counts;
- renamed tests and why;
- semantic gaps found and which were testable;
- tests added, grouped by class;
- behavior that is absent and therefore not tested;
- production defects or design risks discovered but not fixed;
- parallel review result (findings accepted/rejected);
- verification command and outcome.
