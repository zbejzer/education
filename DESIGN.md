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
(add / update / remove / find-by-code with uniqueness enforcement), and `UserSession`
keeps the command history in a stack-like structure supporting undo.

## Cross-Cutting Decisions

- **Validation at boundaries** — constructors reject invalid state (blank codes, names,
  negative/infinite prices), so domain objects can never exist in an invalid state.
- **Fail-fast errors as exceptions** — user-facing errors are `IllegalArgumentException`
  subtypes (`UnknownCommandException`, `CommandFormatException`); the UI loop catches
  them, prints a message, and keeps running.
- **Single source of state** — all mutable state lives in `UserSession` (catalog, cart,
  history); the UI and commands are stateless apart from command parameters.
- **Extension points** — the `Sellable` interface abstracts anything purchasable, and
  the cart's price recalculation step is a hook intended for future promotion logic,
  keeping the catalog/cart structure open to new product-like and pricing concepts.

## Testing

Each layer has focused unit tests (`src/test/java/...`) mirroring the package
structure: model entities, command execution/undo, session history, and the TUI
parser/command-describing behavior.
