# STL Containers

C++ containers and data structures implemented in a library-style layout.

## Structure

```text
adapters/
  priority_queue/
containers/
  vector/
  list/
  deque/
  unordered_map/
```

Each container uses a library-style structure:

- `include/` for headers and template implementation
- `src/` for example entry points
- `Makefile` for local build

## Implemented

- `adapters/priority_queue` — priority queue
- `containers/vector` — vector
- `containers/list` — doubly linked list

## In Progress

- `containers/deque`
- `containers/unordered_map`

## Build

Build each module separately:

```bash
cd adapters/priority_queue && make
cd containers/vector && make
cd containers/list && make
cd containers/deque && make
```
