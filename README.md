# Implementing Data Structures from Scratch

In this project, I will implement various kinds of data structures.

## Table of Content

<!-- * [Preliminaries](#preliminaries) -->
- [Data Structures](#data-structures)
   - [Arena](#arena)
   - [Stack](#stack)

<!-- ## Preliminaries 

This project will follow the guidelines listed below:

* Functions will be, in principle, typeless, possible through `void*`;

* The first parameter will be a pointer to the structure in question;

* Functions will be name <code>\_\_*structure-name*\_*function-name*</code>, following _snake\_case_;

* Structures will be named <code>\_\_*Structure-name*</code>, following _PascalCasing_;

* The templating macro will be named <code>\_\_*structure-name*\_typedef</code>, it will have two arguments:
   * _`decl`_ is the _name_ for the new typed structure,
   * _`type`_ is the _type_ for typed structure;

* Templated functions will be `static inline` and be named <code>*type*\_*structure-name*\_*function-name*</code>

* The default structure, if it make sense for it exist, will be declared with <code>\_\_*structure-name*\_default</code>, the macro will have a _`prefix`_ for allow naming following <code>*prefix*\_default</code>

* Non-templating macros will check if a previous definition exists, so they are overridable, beware that overriding macros my lead to undefined or unwanted behavior

* Use of `size_t` for integer sizes. -->

## Data Structures

### Arena

[Arena Alloc](arena/)

```
  ┌────────────┐
  │ q. b. 23.3 │
  │ Hello () d │                ┌────────────┐  ┌──>Ø
  └────────────┴┐               │ [1,2,3] 44 ├──┘
                ├────────────┐  │ ,34 a      │
                │ World .dsd │ ┌┴────────────┘
                │ 1233 ....d │ │
                └────────────┴─┘
```

<!--
┌┬┐
├┼┤
│┴│
└─┘
-->

### Stack

[Get Pushed](stack/)

```
                                         ┌   ┐        ┌   ┐
                                         │   │        │   │
  ┌   ┐        ┌   ┐        ┌   ┐        │ % │        │   │
  │ D │  pop   │   │ push # │ # │ push % │ # │  pop   │ # │
  │ C │ =====> │ C │ =====> │ C │ =====> │ C │ =====> │ C │
  │ B │        │ B │        │ B │        │ B │        │ B │
  │ A │        │ A │        │ A │        │ A │        │ A │
  └───┘        └───┘        └───┘        └───┘        └───┘
```