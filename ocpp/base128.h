

#include <stdlib.h>
#include <math.h>
#include <string.h>

class base128
{
public:
	base128(void);
	~base128(void);
	char * encode(void *buffer, size_t size);
	char * encode(const char *buffer);
	void * decode(const char *c_string);
	size_t decoded_size;
	size_t encoded_size;
private:
	const char * ascii;	
	char * encoded;
	void * decoded;
};
