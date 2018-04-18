# Software-Repository-Testbed
Purpose:
When a software system becomes large there may be many hundreds, or even thousands, of packages that make up its source code. Efficient development requires a means for reliably storing, versioning, and viewing each of its parts.

The second project this Spring focuses on building the core capability of a Software Repository. The Repository is intended to manage a, possibly large, collection of source code packages, providing versioning, check-in, check-out, and browsing.

This first stage will consist of a single RepositoryCore process, with an integrated client used for testing. It does not attempt to provide a user the ability to use its features by asynchronous actions. Rather, the client simply provides a programmed set of tests to demonstrate the core capabilities.

We will use the NoSql databased, developed in Project #1, to store metadata about each file in the repository. Version numbers will be appended to file names on check-in. All other information will be contained in metadata, e.g., description, author, check-in status (open or closed), files on which it depends, categories to which the file belongs, and its storage path in the Repository.

In later projects we will build interprocess communication channels and user interfaces to support user interactions from separate client processes.

Features
Your RepositoryCore Project:
- use Visual Studio 2017 and the standard C++ libraries, as provided in the ECS computer labs.
- use the C++ standard library's streams for all I/O and new and delete for all heap-based memory management1.
- provide C++ packages:
  TestExecutive: executes a sequence of tests to demonstrate core Repository functionality.
  RepositoryCore: provides means to check-in, version, browse, and check-out source code packages.
  Check-in: provides the functionality to start a new package version by accepting files, appending version numbers to their filenames, providing dependency and category information, creating metadata, and storing the files in a designated location.
  Check-out: retrieves package files, removing version information from their filenames. Retrieved files will be copied to a specified directory.
  Version: manages version numbering for all files held in the Repository.
  Browse: provides the capability to locate files and view their contents.
  enforce the "Single Responsiblity Principle"2 as illustrated in the package structure described above.
- support check-in by accepting a single package's files3 and append a version number to the end of each file name, e.g., p5.h and p5.cpp become p5.h.3 and p5.cpp.3 if the package name is p5 and the last closed check-in for that package was version 2. A check-in is open, by default. A package with open check-in can be modified without altering its version number. Once a check-in is closed, that version of the package becomes immutable.
The author of a check-in defines all of the packages that the check-in package depends on. However, a check-in can only be closed if its dependent packages are all present in the Repository, with closed check-ins.
- support browsing of one or more packages by displaying package descriptions. The packages to be browsed are identified by a query on the NoSql database that holds metadata for all packages in the repository. The full package text shall be displayed on demand, identified by one of the keys returned from the initial browse query.
- submitted with several packages, all with closed check-ins, and a few packages with open check-ins.
- The TestExecutive shall execute a series of tests that clearly demonstrate your project satisfies each of the Requirements, above.
