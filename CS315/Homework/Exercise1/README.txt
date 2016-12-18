Name: Tristan Basil
Course: CS315 Section 002
Date: 8/28/16
Assignment: Exercise 1

***How to compile and run program***

In order to compile and run the program, the command "make" should be called,
which creates the executable FizzBuzz. This does not take any command line 
parameters and will print the numbers 1-100 with the Fizz, Buzz, and FizzBuzz
where expected. The regular files can be cleaned by calling "make clean".

*Number of Fizz, Buzz, and FizzBuzz*

27 "Fizz" are printed.
14 "Buzz" are printed.
6 "FizzBuzz" are printed.

*Bonus Question*

The way to figure out the amount of lines that are not Fizz, Buzz, or FizzBuzz
algebraically would use the following equation:

n = N - (floor(N/3) + floor(N/5) - floor(N/15))

Where N represents the integer to count to (100 in the previous example), n
represents the number of lines that are not Fizz, Buzz, or FizzBuzz, and floor()
represents the floor divided value of the contained expression (floor(100/3) would
equal to 33). For N value 100, n would equal 53.
