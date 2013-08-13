Sushi Rolls (all about blowfish syntax)
=======================================
The blowfish is still in development, so this document is for the description of the theoretical blowfish syntax.


Numbers
-------
There are two ways to store numbers in blowfish:

Integers:
`42`

Floats:
`3.14`

When something (a number or an identifier or an expression) is to be negated in blowfish, it must be directly preceded by a minus sign:

Negative integer:
`-42`

Negative float:
`-3.14`

Negative expression:
`-( sqrt 25 )`

So the following is *not* a valid negative number because of the space:

Invalid negative number:
`- 24`

Math
----
The mighty blowfish likes math. It has some pretty standard math operations:

Addition:
`14 + 5`

Subtraction:
`1.2 - 5`

Multiplication:
`3.14 * 9`

Division:
`12 / 3.4`

Modulus:
`15 % 2`

Exponentiation:
`2^9`

The mighty blowfish believes in a sacred order. It does math in the following order (where the things that come first, happen first):

 1. Exponentiation
 2. Multiplication, division and modulus
 3. Addition and subtraction

Pretty standard stuff eh?
