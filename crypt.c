/*******************************
 *
 *  Project Name: Project 2: One Time, One Time
 *  Description: Encrypt and decrypt using a modified one time pad method.
 *  File names: crypt.c
 *  Date: 2/14/2020   
 *  Authors: Bryce Hessler, Lucia-Maria Ristea and Liam Seymour
 *
 *******************************/

#include <stdio.h>

void printbin(char c);
char rotate(char c, int count);
char changebit(char c, char bit, char to);
int bits(char c);

int main(int argc, char *argv[])
{
	/* Start Testing: TEMP */
	char c = '~';
	printf("The binary representation of %c is: ", c);
	printbin(c);
	printf("\nThere are %d one bits in %c\n", bits(c), c);
	int shift = 5;
	printf("Rotating %c by %d yields: ", c, shift);
	printbin(rotate(c, shift));
	printf("\n");
	/* End Testing */


	return 0;
}

/*  Description: Print the binary representation of n.
	
	Parameters:  c - Character to be printed.        */
void printbin(char c)
{
	size_t csize = sizeof(c) * 8; /* size of c in bits */
	char mask = 1 << (csize - 1);

	for (int i =0; i < csize; ++i) {
		if ((c & mask) == 0) {
			putchar('0');
		} else {
			putchar('1');
		}
		c <<= 1;
	}
//	putchar('\n');
}

/*  Description: Rotates the lower-order bits to the right by count.
	
	Parameters: c - Character to be rotated.
				count - number of rotations to be performed.
	Retuns: The rotated c                                          */
char rotate(char c, int count)
{
	int cbits = sizeof(c) * 8; /* size of c in bits */
	char high = c & (1 << (cbits -1)); /* capture the highest order bit */
	char low; /* capture the least significant bit */
	
	/* perform count rotation operations */
	for (int i = 0; i < count; ++i) {
		low = c & 1; 
		c >>= 1;
		c = changebit(c, cbits - 2, low);
	}
	/* Set the highest bit back */
	c = changebit(c, cbits - 1, high);
	return c;
}

/*  Description: Change the a bit in c. 
   
	Parameters: bit - The index (from zero) to change in c. 
				to  - What to change the bit to (1 or 0) 
				c   - Character to change.

	Returns: Modified c									  */
char changebit(char c, char bit, char to)
{
	if (to) {
		/* set the bit */
		c = c | (to << (bit));
	} else {
		/* unset the bit */
		c = c & ~(to << bit);
	}
	return c;
}

/*  Description: Return number of 1 bits in the binary
				 representation of c. 
	
	Parameters: c - Character to count bits in.
	
	Retunrs: Sum of 1 bits in c.					 */
int bits(char c)
{
	int sum;
	/* For each bit in c, add it to sum */
	for (sum = 0; c != 0; c >>= 1) {
		if (c % 2 == 1) {
			sum++;
		}
	}
	return sum;
}









