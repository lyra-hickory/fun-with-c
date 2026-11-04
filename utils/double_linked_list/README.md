# Double Linked List

A small custom double linked list package, meant to act as a completely type agnostic node.

## Usage

## Design

The idea around this project is to have a type agnostic double linked list, taking custom deconstructors.

The design I settled on is this:

- Each node takes a pointer to its data
- Each node has its own deconstructor function
    - `NULL` means the implementer owns the data
- Each node has a small optional metadata marker meant for identifying different types
    - I am going with `char *`
- The list gets a wrapper instead of handling just raw nodes, which is what the functions rely on
    - tracks `head` and `tail` for easy access
    - `length` included for N(1) length lookup

### Other considerations

I could tie the type and deconstructor fn's to a dll_type which the implementor owns

Pros:

- This means that the deconstructor is only defined once against the type
- Identifying the type is a bit easier than `char *`, and less expensive

Cons:

- All nodes assigned to the type will be opted into the deconstructor
- Less explicit at node definition
- Metadata the implementer needs to define before using the nodes, and has to hold onto it, with the risk of orphaning it, or tying it to the wrapper, where we need to identify it somehow again, where we can use either a simple array with char * identifiers but then we're back at comparing `char *`...
