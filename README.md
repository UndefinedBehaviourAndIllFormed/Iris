# Iris specification

- [Iris specification](#iris-specification)
  - [Introduction](#introduction)
  - [Character sets](#character-sets)
    - [Separator characters](#separator-characters)
    - [Alpha characters](#alpha-characters)
    - [Numeric characters](#numeric-characters)
    - [Alphanumeric characters](#alphanumeric-characters)
    - [Control characters](#control-characters)
    - [Dot character](#dot-character)
    - [Version characters](#version-characters)
  - [Vocabulary](#vocabulary)
    - [Iris compiler](#iris-compiler)
    - [Command-line](#command-line)
    - [Well-formed](#well-formed)
    - [Ill-formed](#ill-formed)
    - [Iris project](#iris-project)
    - [Numerical sequence](#numerical-sequence)
    - [Alphanumeric sequence](#alphanumeric-sequence)
  - [Project structure](#project-structure)
    - [Project folder](#project-folder)
    - [Documentation folder](#documentation-folder)
    - [Libraries folder](#libraries-folder)
    - [Output folder](#output-folder)
    - [Resource folder](#resource-folder)
    - [Source folder](#source-folder)
    - [Sclera file](#sclera-file)
    - [Cornea file](#cornea-file)
  - [Command-line options](#command-line-options)
    - [Version option](#version-option)
    - [Create option](#create-option)
    - [Compile option](#compile-option)
  - [Compilation pipeline](#compilation-pipeline)
  - [Sclera format](#sclera-format)

## Introduction

Iris is a collection of domain-specific programming languages together with a systems programming language.

Iris is focused at high-performance and reliability, along with a simple and elegant syntax.

Unlike many other programming languages trying to become the "C++ killers", our aim is driven around providing useful & innovative features, and building a language that remains active and used for the years to come.

## Character sets

All the sets of characters defined at this section are conforming the UTF-8 encoding.

### Separator characters

One of the following UCS domains:

``U+0009-U+000A`` or ``U+0020``

or one of the following UCS character descriptions:

```
Horizontal tabulation
Line feed
Space
```

### Alpha characters

One of the following glyph representations of UCS characters:

```
_, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z
```

or one of the following UCS domains:

``U+0041 - U+005A``, ``U+0061 - U+007A`` or ``U+005F``

### Numeric characters

One of the following glyph representations of UCS characters:

```
0, 1, 2, 3, 4, 5, 6, 7, 8, 9
```

or one of the following UCS domains:

``U+0030 - U+0039``

### Alphanumeric characters

One character of the [alpha characters](#alpha-characters) or [numeric characters](#numeric-characters)

### Control characters

One of the following abbreviation representations of UCS characters:

```
NUL, SOH, STX, ETX, EOT, ENQ, ACK, BEL, BS, HT, LF, VT, FF, CR, SO, SI, DLE, DC1-4, NAK, SYN, ETB, CAN, EM, SUB, ESC, FS, GS, RS, US, DEL
```

or one of the following UCS domains:

``U+0000 - U+001F`` or ``U+007F``

### Dot character

The following glyph representation of UCS character:

```
.
```

or the following UCS value:

``U+002E``

### Version characters

An interleaved sequence of a [numerical sequence](#numerical-sequence) and a [dot character](#dot-character).

If any sub-sequence is not interleaved between a [numerical sequence](#numerical-sequence) and a [dot character](#dot-character), the version is [ill-formed](#ill-formed).

Well-formed:

```rust
0.0.1
```

Ill-formed:

```rust
0..1
```
or
```rust
0 0.1
```

;TODO; Add more character sets

## Vocabulary

### Iris compiler

A binary program that functions exactly as stated in this specification.

### Command-line

A terminal-like program, normally part of the Operating System, that provides an STDIN & STDOUT which the user can interact with.

### Well-formed

The program is well-formed according to this specification and will continue forward.

### Ill-formed

The program is not well-formed according to this specification and will print an error message.

### Iris project

A project is an individual, non-relational, set of certain folders & files that make it possible for the [Iris compiler](#iris-compiler) to take these contents as an input and output the result(depending on the configuration options) as another set of files and/or folders.

### Numerical sequence

A sequence of [numeric characters](#numeric-characters).

### Alphanumeric sequence

A sequence of [alphanumeric characters](#alphanumeric-characters). The first character must be an [alpha character](#alpha-characters), otherwise the program is [ill-formed](#ill-formed).

## Project structure

The minimal project structure, where the project name is the [alphanumeric sequence](#alphanumeric-sequence) ``project``, would be the following:

```
project   
│
└───docs
│   
└───libs
│   
└───out
│   
└───res
│   
└───src
│   
│   project.cornea
│ 
│   project.sclera
```

### Project folder

This folder with the name of the project is the project folder and it contains all the elements that a project must have.

### Documentation folder

This project sub-folder should contain all the documentation of your project. The file extension for the documentation must be ``.lens``, and it follows the [Lens](#lens-format) format specification.

### Libraries folder

This project sub-folder should contain all the libraries, native or Retina, of your project. The extensions accepted for the native libraries are:

 1. ``.dll``
 2. ``.dylib``
 3. ``.framework``
 4. ``.so``
   
For the Retina libraries, the file extension must be ``.retina``, and it follows the [Retina](#retina-format) format specification. These might contain an additional file with the extension ``.key``, which provides to the compiler the hashes that it must use to decrypt the library encoded content.

### Output folder

This project sub-folder should contain all the output of your project generated by the compiler.

Depending at the configuration options provided at the [Cornea](#cornea-format) format, it will produce a [Retina](#retina-format) library, with an additional, depending on whether or not the ``encrypt`` option was set to true at the configuration options, ``.keys`` file indicating the hashes used to encrypt such library, or a binary, both with or without their respective documentation, if any.

### Resource folder

This project sub-folder should contain all the resources of your project. Any extension is allowed, these files will be copied onto the output resource folder.

### Source folder

This project sub-folder should contain all the source code of your project. The file extension for the source files must be ``.iris``, and it follows the [Iris](#iris-format) format specification.

### Sclera file

This file with extension ``.sclera``, indicates some pre-configuration options of the project that will affect the parsing of all the project files, including the [Cornea file](#cornea-file).

It follows the [Sclera](#sclera-format) format specification.

### Cornea file

This file with extension ``.cornea``, indicates the configuration options of the project.

It follows the [Cornea](#cornea-format) format specification.

## Command-line options

The [command-line](#command-line) options are given to the Iris compiler to control the following execution. There are 3 options:

 1. ``version``
 2. ``create``
 3. ``compile``

If no options are given, the program is ill-formed.

If none of these options are provided, the program is ill-formed.

### Version option

The ``version`` option provides to the output of the [command-line](#command-line) the version of the actual [Iris compiler](#iris-compiler), in a [version-like format](#version-characters), e.g, the expected output of an [Iris compiler](#iris-compiler) with the version 0.0.1, would be the following:

``0.0.1``

### Create option

The ``create`` option will create at the current directory the [project structure](#project-structure) neccessary by any [Iris project](#iris-project).

It requires an additional [alphanumeric sequence](#alphanumeric-sequence) determining the project name:

Well-formed:

```rust
create project
```

Ill-formed:

```rust
create pr@ject
```

If no project name is provided, the program is ill-formed.

If the project name isn't an [alphanumeric sequence](#alphanumeric-sequence), the program is ill-formed.

If the current directory already contains a [project folder](#project-folder) with the same name as the one being created, the program is ill-formed.

If any of the items of the [project structure](#project-structure), including the [project folder](#project-folder), couldn't be created, the program is ill-formed.

### Compile option

The ``compile`` option will compile with the indicated [Iris compiler](#iris-compiler), at the current directory, the project specified by an additional [alphanumeric sequence](#alphanumeric-sequence), indicating the project name:

Well-formed:

```rust
compile project
```

Ill-formed:

```rust
compile pr@ject
```

If no project name is provided, the program is ill-formed.

If the project name isn't an [alphanumeric sequence](#alphanumeric-sequence), the program is ill-formed.

If any of the items of the [project structure](#project-structure), including the [project folder](#project-folder), couldn't be found, the program is ill-formed.

## Compilation pipeline

## Sclera format

About to come soon....