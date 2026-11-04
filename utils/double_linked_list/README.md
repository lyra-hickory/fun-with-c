# Double Linked List

A small custom double linked list package, meant to act as a completely type agnostic node.

## Usage

## Design

The idea around this project is to have a type agnostic double linked list, taking custom deconstructors.

The design I settled on is this:

- Each node takes a pointer to its data
- Each node has a `dll_type * type`
    - Used for identifying the type with a name
    - types are wholly owned by the implementor
- Each type has its own deconstructor function
    - `NULL` means the implementer owns the data
- The list gets a wrapper instead of handling just raw nodes, which is what the functions rely on
    - tracks `head` and `tail` for easy access
    - `length` included for N(1) length lookup
