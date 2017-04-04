# Fractran-
A compiler for Fractran^.

The goal is to create a compiler for a high-level language based on Fractran.

Fractran is an esoteric language created by John Conway. In Fractran, a program consists of a finite list of positive, rational
numbers. The input to a program is a positive integer n. The list is then searched in order, for a rational number p/q such that
np/q is an integer. Then n is replaced by np/q and the search is restarted from the beginning of the list. The program halts
when no such number p/q can be found, and the final n becomes the output from the program.

The current compiler version can accomplish basic Fractran compilation. After compiling and running the .exe file, the user is
tasked with entering the name of the text file that holds the Fractran program. This name must be without the extension ".txt"
and the file should be in the same directory as the compiler. The file must be formatted such that the first line holds the
Fractran program, which is a list of rationals in the form of p/q, where each rational is separated by a space. p and q must be
in the form of coprime, positive integers. The second line is simply a positive integer that will serve as the input to the
program.

The current release supports the use of parenthesis (), asterisk *, and carrot ^. Note that you can only put the numerator or
denominator in parenthesis, you cannot put the entire fraction. E.g. (n)/(p) is valid, but (n/p) is not. Furthermore, using
asterisk for multiplication and carrot for exponentiation can only happen in parenthesis. An example would be:

(2^2 * 3^3 * 5) / (2^2^2)

An invalid input would be:

(2^2 * 3^3) * 5 / 2^2^2, here the numerator is invalid because of "*5" being outside the parenthesis, and the denominator is
invalid because 2^2^2 is not in parenthesis.

After successfully compiling the program, the program will run and a line will be printed for every time n changes. The
program will stop when it reaches a halting state, or if certain loops are detected. Considering the nature of Fractran, it is
possible for certain loops to be detected. By keeping a record of the changes of n during the duration of the program, if n
repeats it would signal a loop. The program will halt at that point.
