Rshell 
======
UCR CS100 Assignment2

Authors and Contributors
------------
David Nguyen

Shashank Sharma

Files
-----
```
Command.cc
Command.hh
Connector.cc
Connector.hh
LICENSE
main.cpp
README.md
RShellBase.cc
RShellBase.hh
RShellContainer.cc
RShellContainer.hh
```

Bugs
-----
Memory leak with RShellContainer.clear(); does not actually clear memory since the vectors contain pointers.

Issues with execution when '#' is the first char.

Test cases loop the last line endlessly.
