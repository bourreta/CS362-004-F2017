Andrew Bourret
This is my assignment-3 submission!

Changes:
	-implemented 4 unit tests of functions in dominion.c and 4 unit tests of card effects in dominion.c
	-added tests to makefile under title "runtests2." Results are stored in unittestresults.out.
	-changed a bug in smithyEffect() that was creating an infinite loop, making program untestable. Replaced it with other bug, commented in code.
	-initialized z variable in adventurerEffect() to 0. This wasn't an intentional bug in assignment 2, but it was causing a segmentation fault once the infinite loop bug was removed.
