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

Holders
-------
The mighty blowfish is a horder. He has a few different ways of holding his favorite posessions:

Lists are the blowfish's favorite way to hold things. The blowfish likes lists because he can hold all sorts of things in a single list and also because it's easy for him to look through a list to find what he needs.

The empty list:
`l{ }`

A list containing a few numbers:
`l{ 1 2 3.4 -7 (sqrt 7) }`

Aside from lists, the blowfish really likes sets. Sets are holders of a unique collection of objects.

The empty set:
`s{ }`

A set containing a few numbers:
`s{ 1 2 3.4 -9 5^7 }`

The last holder that the blowfish likes are dictionaries. Dictionaries associate some value with another.

The empty dictionary:
`d{ }`

A dictionary containing a few things:
`{ "Food" -> "Sushi" "The answer" -> 42 }`