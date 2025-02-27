# Implementing Data Structures from Scratch

In this project I will implement various kinds of data structures.

## Table of Content

* [Preliminaries](#preliminaries)
* [Stack](#stack)

## Preliminaries

To begin with, we shall define somethings, working with C, things like generics, quite useful for this kind of application, are missing, to cope with that, we're stick to the following convention:

* Functions will be, in principle, typeless, possible through `void*`;

* The fisrt parameter will be a pointer to the structure in question;

* Functions will be name <code>\_\_*structure-name*\_*function-name*</code>, following _snake\_case_;

* Structures will be named <code>\_\_*Structure-name*</code>, following _PascalCasing_;

* The templating macro will be named <code>\_\_*structure-name*\_typedef</code>, it will have two arguments:
   * _`decl`_ is the _name_ for the new typed structure,
   * _`type`_ is the _type_ for typed structure;

* Templated functions will be `inline` and be named <code>*type*\_*structure-name*\_*function-name*</code>

* The default structure, if it make sense fot it exist, will be declared with <code>\_\_*structure-name*\_default</code>, the macro is _object-like_ (has no need for parentesis).

* Non-templating macros will check if a previous definition exists, so they are overridable, beware that overriding macros my lead to undefined or unwanted behavior

* Use of `size_t` for integer sizes.

## [Stack](stack/README.md)