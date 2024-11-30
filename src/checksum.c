/**
 * author: Brando
 * date: 6/2/23
 */

#include "checksum.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <openssl/md5.h>
#include <openssl/sha.h>

#include <bflibc/bflibc.h>

size_t BFChecksumGetDigestStringLength(BFChecksumTools * tools) {
	if (tools) return tools->digestLength * 2;
	return -5;
}

void BFChecksumDestroy(BFChecksumTools * tools) {
	if (tools) {
		free(tools->context);
		free(tools->digest);
	}
}

int BFChecksumGetDigestString(BFChecksumTools * tools, char * dig) {
	if (tools && dig) {
		for (int i = 0; i < tools->digestLength; i++) {
			sprintf(dig + (i * 2), "%02x", tools->digest[i]);
		}
		return 0;
	}

	return -4;
}

int BFChecksumCreate(BFChecksumTools * tools, BFChecksumType type) {
	int result = 0;

	if (tools == NULL) {
		result = -1;
	} else {
		tools->type = type;
		tools->digest = 0;
		tools->context = 0;
		tools->digestLength = 0;
	}

	if (result == 0) {
		switch (tools->type) {
			case kBFChecksumTypeMD5:
				tools->digestLength = MD5_DIGEST_LENGTH;
				if ((tools->context = malloc(sizeof(MD5_CTX))) == NULL) {
					result = -1;
				} else if ((tools->digest = malloc(sizeof(unsigned char) * tools->digestLength)) == NULL) {
					result = -1;
				} else if (MD5_Init(tools->context) == 0) {
					result = -1;
				}

				break;

			case kBFChecksumTypeSHA1:
				tools->digestLength = SHA_DIGEST_LENGTH;
				if ((tools->context = malloc(sizeof(SHA_CTX))) == NULL) {
					result = -1;
				} else if ((tools->digest = malloc(sizeof(unsigned char) * tools->digestLength)) == NULL) {
					result = -1;
				} else if (SHA1_Init(tools->context) == 0) {
					result = -1;
				}

				break;

			case kBFChecksumTypeSHA256:
				tools->digestLength = SHA256_DIGEST_LENGTH;
				if ((tools->context = malloc(sizeof(SHA256_CTX))) == NULL) {
					result = -1;
				} else if ((tools->digest = malloc(sizeof(unsigned char) * tools->digestLength)) == NULL) {
					result = -1;
				} else if (SHA256_Init(tools->context) == 0) {
					result = -1;
				}

				break;

			case kBFChecksumTypeSHA512:
				tools->digestLength = SHA512_DIGEST_LENGTH;
				if ((tools->context = malloc(sizeof(SHA512_CTX))) == NULL) {
					result = -1;
				} else if ((tools->digest = malloc(sizeof(unsigned char) * tools->digestLength)) == NULL) {
					result = -1;
				} else if (SHA512_Init(tools->context) == 0) {
					result = -1;
				}

				break;

			default:
				result = -1;
				printf("Unknown type: %d", tools->type);
				break;
		}
	}

	return result;
}

int BFChecksumUpdate(BFChecksumTools * tools, const void * data, size_t size) {
	int result = 0;

	if (tools == NULL) {
		result = -2;
	}

	if (result == 0) {
		switch (tools->type) {
			case kBFChecksumTypeMD5:
				if (MD5_Update(tools->context, data, size) == 0) {
					result = -2;
				}

				break;

			case kBFChecksumTypeSHA1:
				if (SHA1_Update(tools->context, data, size) == 0) {
					result = -2;
				}

				break;

			case kBFChecksumTypeSHA256:
				if (SHA256_Update(tools->context, data, size) == 0) {
					result = -2;
				}

				break;

			case kBFChecksumTypeSHA512:
				if (SHA512_Update(tools->context, data, size) == 0) {
					result = -2;
				}

				break;

			default:
				result = -2;
				printf("Unknown type: %d", tools->type);
				break;
		}
	}

	return result;
}

int BFChecksumFinal(BFChecksumTools * tools) {
	int result = 0;

	if (tools == NULL) {
		result = -3;
	}

	if (result == 0) {
		switch (tools->type) {
			case kBFChecksumTypeMD5:
				if (MD5_Final(tools->digest, tools->context) == 0) {
					result = -3;
				}

				break;

			case kBFChecksumTypeSHA1:
				if (SHA1_Final(tools->digest, tools->context) == 0) {
					result = -3;
				}

				break;

			case kBFChecksumTypeSHA256:
				if (SHA256_Final(tools->digest, tools->context) == 0) {
					result = -3;
				}

				break;

			case kBFChecksumTypeSHA512:
				if (SHA512_Final(tools->digest, tools->context) == 0) {
					result = -3;
				}

				break;

			default:
				result = -3;
				printf("Unknown type: %d", tools->type);
				break;
		}
	}

	return result;
}

