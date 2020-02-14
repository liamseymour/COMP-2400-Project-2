/*************************************************************************
 *
 *  Project Name: Project 2: One Time, One Time
 *  Description: Encrypt and decrypt using a modified one time pad method.
 *  File names: crypt.c
 *  Date: 2/14/2020
 *  Authors: Bryce Hessler, Lucia-Maria Ristea and Liam Seymour
 *
 ************************************************************************/

#include <stdio.h>

#define MESSAGE_LENGTH 2048
#define DELIMITER 255

unsigned char rotate(unsigned char c, int count);
unsigned char changebit(unsigned char c, int bit, int to);
int bits(unsigned char c);
void shuffleKey(unsigned char *key, int len);

int main(int argc, char *argv[])
{

	/* Read in message until delimiter is found, ignore
	 * chars after message length */
	int message;
	int messageLen = 0;
	unsigned char messageArray[MESSAGE_LENGTH];
	while ((message = getchar()) != DELIMITER ) {
		if (messageLen < MESSAGE_LENGTH) {
			messageArray[messageLen++]= message;
		}
	}

	/* Read in key until EOF */
	int key;
	int keyLen = 0;
	unsigned char keyArray[MESSAGE_LENGTH];
	while ((key = getchar()) != EOF ) {
		if (keyLen < MESSAGE_LENGTH) {
			keyArray[keyLen++] = key;
		}
	}

	/* repeat the key until it is long enough for the message */
	for (int j = 0; j < messageLen - keyLen; j++) {
		keyArray[keyLen+j] = keyArray[j];
	}

	shuffleKey(keyArray, messageLen);

	/* output the encrypted message */
	for (int i = 0; i < messageLen; ++i) {
		putchar(keyArray[i] ^ messageArray[i]);
	}	

	return 0;
}

/*  Description: Rotates the lower-order bits to the right by count.

	Parameters: c - Character to be rotated.
				count - number of rotations to be performed.
	Retuns: The rotated c                                          */
unsigned char rotate(unsigned char c, int count)
{
	int csize = sizeof(c) * 8; /* size of c in bits */
	unsigned char high = c & (1 << (csize -1)); /* capture the highest order bit */
	unsigned char low; /* capture the least significant bit */

	/* perform count rotation operations */
	for (int i = 0; i < count; ++i) {
		low = c & 1;
		c >>= 1;
		c = changebit(c, csize - 2, low);
	}
	/* Set the highest bit back */
	c = changebit(c, csize - 1, high);
	return c;
}

/*  Description: Change the a bit in c.

	Parameters: c   - Character to change.
				bit - The index (from zero) to change in c.
				to  - What to change the bit to (1 or 0)

	Returns: Modified c									  */
unsigned char changebit(unsigned char c, int bit, int to)
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
int bits(unsigned char c)
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

/*  Description: Psuedo Randomizes a key used for
    		 	 encrypting a message.

	Parameters:  key - Key string to shuffle.
				 len - Length of the key.          */
void shuffleKey(unsigned char key[], int len)
{
	int sum = key[len-1] % len;
	unsigned char prev = key[len-1];

	for (int i = 0; i < len; ++i) {
		key[i] = rotate(key[i] ^ key[sum], bits(prev));
		sum = (sum + key[i]) % len;
		prev = key[i];
	}

	return;
}
