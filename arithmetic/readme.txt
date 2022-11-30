Your program takes one line as input. The input line contains three integers separated by spaces. Let
the three integers be I1, I2, and B. I1 and I2 are both nonnegative integers up to 100 digits long (there are
no leading 0s, except when the value itself is 0). B is I1 and I2’s base (B is from 2 to 10).
Your program should output the sum of I1 and I2, using the school method, then the product of I1 and
I2, using the Karatsuba algorithm, and finally the ratio between I1 and I2 (rounded down). You are asked
to come up with a way to perform this division. It’s not covered in lectures. I2 will not be 0.
The results should still use base B. Please separate the results using one space.
Sample input 1: 101 5 10
Sample output 1: 106 505 20
Sample input 2: 10 111 2
Sample output 2: 1001 1110 0
Sample input 3: 111 10 2
Sample output 2: 1001 1110 11
If you are an undergraduate student, simply output 0 as the division result. For sample 3, instead of
1001 1110 11, simply output 1001 1110 0
