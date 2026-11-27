# JavaMarkt — Design Overview

JavaMarkt is a console-based shopping application. The user interacts with a text shell
(REPL), whose input is translated into **commands** that operate on a shared **user
session** holding the domain state (product catalog and shopping cart). The design is
layered, with dependencies pointing strictly inward: UI → session/commands → model.

## High-Level Architecture

The application consists of three layers:

- **UI layer** (`ui.tui`) — the text front-end. `TextUserInterface` runs the REPL loop
  and renders output; `Parser`, `CommandType`, and `CommandDescriber` translate raw
  input into `ParsedCommand` and then into `Command` objects, and translate commands
  back into readable text.
- **Session layer** (`session`, `command`) — `UserSession` holds all state and the
  command history; `Command` objects are the executable, undoable operations performed
  on that state.
- **Model layer** (`model`) — the domain: `ProductCatalog` for registered products,
  `Cart`/`CartItem` for the current purchase, and the `Product`/`Sellable` entities.

Control flows from the UI downward: the UI executes or undoes commands in the session,
and commands operate on the model. The model never depends on the layers above it.

`Main` acts as the **composition root**: it creates the catalog, session, and UI and
wires them together. Everything downstream depends only on interfaces passed to it.

## Packages

| Package | Responsibility |
|---|---|
| `model` | Domain state: products, catalog, cart. No knowledge of UI or commands. |
| `session` | One shopping session: owns cart and catalog, tracks executed commands. |
| `command` | One class per user operation; knows how to execute and undo itself. |
| `ui.tui` | Text front-end: parsing, command registry, help/history rendering. |

Flow of a single user request: `TextUserInterface` reads a line → `Parser` maps it to a
`ParsedCommand` (a `CommandType` plus raw arguments) → shell-level requests (help, exit,
history, undo) are handled by the UI itself, while domain requests are converted into a
`Command` and handed to `UserSession`, which executes it and records it in history.

## Design Patterns

- **Command** (`command` package) — every user operation is an object implementing
  `execute`/`undo`. Commands are parameterized at construction time and receive the
  `UserSession` only at execution, decoupling the UI from domain actions and enabling
  **undoable history** (each command carries the information needed to reverse itself,
  e.g. the product removed by an unregister operation).
- **Visitor** (`CommandVisitor`) — commands expose an `accept` method with double
  dispatch. `CommandDescriber` is a visitor that converts command objects back into
  human-readable input text for `history`/`undo` output, without type checks or
  coupling the command hierarchy to presentation details.
- **Simple Factory / Translator** (`Parser.toCommand`) — the parser is the only place
  that instantiates concrete command classes, mapping validated `ParsedCommand` input
  to the appropriate `Command`. The rest of the system depends on the `Command`
  interface only.
- **Registry** (`CommandType` enum) — a single, self-describing table of all shell
  commands (keyword, description, syntax, required argument count, routing target).
  Help output, parsing, and validation are all driven from this one registry, so
  adding a command means adding one enum entry.
- **Adapter** (`CartItem`) — wraps a `Product` behind the same `Sellable` interface,
  delegating identity/price queries while adding cart-specific behavior (discount
  price).
- **Iterator** (`ProductCatalog implements Iterable<Product>`) — the catalog exposes
  iteration over its contents without revealing its internal storage.
- **Value Objects / Immutability** — `Product` and `ParsedCommand` are immutable:
  fully validated at construction, no setters, defensive copies of collections. Shared
  instances can therefore be stored in the catalog, cart, and history safely.

The `ProductCatalog` additionally plays the role of an **in-memory repository**
(add / remove / find-by-code with uniqueness enforcement), and `UserSession`
keeps the command history in a stack-like structure supporting undo.

## Cross-Cutting Decisions

- **Validation at boundaries** — constructors reject invalid state (blank codes, names,
  negative/infinite prices), so domain objects can never exist in an invalid state.
- **Fail-fast errors as exceptions** — user-facing errors are `IllegalArgumentException`
  subtypes (`UnknownCommandException`, `CommandFormatException`); the UI loop catches
  them, prints a message, and keeps running.
- **Single source of state** — all mutable state lives in `UserSession` (catalog, cart,
  history); the UI and commands are stateless apart from command parameters.
- **Catalog-anchored cart invariant** — the cart may only contain products currently
  registered in the catalog, and only via the catalog's own instances: `add <code>`
  resolves the product through the catalog and inserts that instance. Consequently
  `unregister` is blocked while the code is in the cart (hard delete of a referenced
  product is impossible; real shops retire products via a soft status flip, which is
  out of scope here). With LIFO undo ordering and same-instance restores, this holds
  at all times without undo-time checks.
- **Total, recoverable undo** — a failed undo keeps its command at the top of the
  history (preserving LIFO safety); `clear_history` discards recorded operations
  without touching state, so a stuck history can never trap the user.
- **Extension points** — the `Sellable` interface abstracts anything purchasable, and
  the cart's price recalculation step is a hook intended for future promotion logic,
  keeping the catalog/cart structure open to new product-like and pricing concepts.

## Testing

Tests are executable specifications of behavior, not a coverage exercise. JaCoCo's
0-missed-branch gate is a floor: it proves the branches that exist are exercised, not
that the scenarios the domain cares about exist. Every test change is checked against
two gates:

1. **Coverage gate** — `.kilo/jacoco_parser.py` reports 0 missed branches.
2. **Semantic gate** — every behavior has a test whose name and assertions state the
   scenario and expected outcome, and the test group has no obvious missing scenario.

### Test design contract

- One test = one observable behavior. The name states condition and expected outcome
  (`recalculateOnEmptyCartDoesNotThrow`), not the method or implementation detail.
- Assert observable state (return values, cart/catalog contents, output), not private
  structure or interaction counts.
- Test only behavior that exists. If a scenario belongs to an unimplemented feature,
  record the gap and implement the feature with its tests; never add a failing or
  aspirational test to the suite.
- Arrange state explicitly in every test; tests must not depend on execution order.
- Cover the semantic matrix, not just branches: success, boundary, failure, and
  state transition (empty/non-empty, before/after, first/middle/last,
  duplicate/unique, execute/undo).
- Follow the existing JUnit 5 style (`@Test`, `assertAll` for related checks,
  `assertSame` where identity is contractual). Do not introduce parameterized tests
  or new libraries the project does not already use.

### Adding or reviewing a test group

1. **Baseline** — run the suite and the JaCoCo parser; record counts and failures.
2. **Name audit** — verify each name describes its assertion. Rename overclaiming or
   method-oriented names and add the missing assertion when a name promises more than
   the body checks.
3. **Semantic gap analysis** — read each test class as a specification. From the
   names and grouped setup alone, list scenarios the group implies but never
   exercises.
4. **Existence check** — locate the production path for each candidate scenario. If
   it is absent, report it as an unimplemented feature or known gap instead of writing
   a test.
5. **Write tests** — add only verified, high-value scenarios; prefer one new test per
   behavior over extending an unrelated test.
6. **Verify** — run the full suite and the JaCoCo parser; 0 missed branches and no
   regressions.
7. **Parallel review** — for medium or large test changes, run independent read-only
   reviewers in parallel (business logic, duplication, dead code) before completion.
   The fan-out policy lives in `.kilo/AGENTS.md`.

### Test layers

| Layer | Specifies |
|---|---|
| `model` | Entity invariants and collection semantics: validation, identity, ordering, duplicates, snapshots, empty/boundary state. |
| `command` | One operation's execute/undo contract, including failure paths and state restoration. |
| `session` | History semantics: recording, LIFO undo, failed-undo retention, snapshots, clearing. |
| `ui.tui` | Parsing and validation, command translation, help/history/undo rendering, REPL survival after rejected input. |
