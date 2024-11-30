/**
 * author: Brando
 * date: 6/2/23
 *
 * Using these apis as reference: https://www.openssl.org/docs/man1.1.1/man3/MD5.html
 */

#ifndef BFCHECKSUM_H
#define BFCHECKSUM_H

#include <stddef.h>

typedef enum {
	kBFChecksumTypeUnknown = -1,

	// MD
	kBFChecksumTypeMD5 = 1,

	// SHA
	kBFChecksumTypeSHA1 = 10,
	kBFChecksumTypeSHA256 = 11,
	kBFChecksumTypeSHA512 = 12,
} BFChecksumType;

typedef struct {
	void * context;
	unsigned char * digest;
	int digestLength;
	BFChecksumType type;
} BFChecksumTools;

/**
 * Cleans up memory for tools
 *
 * Caller doesn't own members but still owns tools struct
 */
void BFChecksumDestroy(BFChecksumTools * tools);

/**
 * Inits checksum context
 */
int BFChecksumCreate(BFChecksumTools * tools, BFChecksumType type);

/**
 * updates context
 */
int BFChecksumUpdate(BFChecksumTools * tools, const void * data, size_t size);

/**
 * finalizes context
 */
int BFChecksumFinal(BFChecksumTools * tools);

/**
 * dig: must have length BFChecksumTools.digestLength + 1
 */
int BFChecksumGetDigestString(BFChecksumTools * tools, char * dig);

/** 
 * Returns the suggested string length not including null term character
 */
size_t BFChecksumGetDigestStringLength(BFChecksumTools * tools);

#endif // BFCHECKSUM_H

