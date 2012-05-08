/*
 * ***********************************************************************
 * Copyright © Erich Pribitzer 2012
 *
 * This file is part of NSBase128
 
 NSBase128 is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 Cmsfromscratch is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with Cmsfromscratch.  If not, see <http://www.gnu.org/licenses/>.
 ***********************************************************************
 */

#import "NSBase128.h"


@implementation NSBase128

	
+(NSString *)encodedLatin1StringFromString:(NSString *)string encoding:(NSStringEncoding)encoding {

	NSString * encoded = nil;
	int strlen=([string length]+1)*4;
	char * enc=(char *)malloc((size_t)strlen);
	if(enc==NULL) return encoded;
	
	base128 * coder = new base128();
	[string getCString:enc maxLength:(strlen) encoding:encoding];
	char * _enc = coder->encode((char *)enc);
	
	if(_enc!=NULL)
		encoded = [[[NSString alloc] initWithCString:_enc encoding:NSISOLatin1StringEncoding] autorelease];

	delete coder;
	free(enc);
	return encoded;	
}

+(NSString *)encodedLatin1StringFromData:(NSData *)data {

	NSString * encoded = nil;
	base128 * coder = new base128();
	char * _enc = coder->encode((void *)[data bytes],[data length]);

	if(_enc!=NULL)
		encoded = [[[NSString alloc] initWithCString:_enc encoding:NSISOLatin1StringEncoding] autorelease];
	delete coder;
	return encoded;
}

+(NSString *)decodedStringFromLatin1String:(NSString *)string encoding:(NSStringEncoding)encoding {
	
	NSString * decoded = nil;
	int strlen=[string length]+1;
	char * dec=(char *)malloc((size_t)(strlen));
	if(dec==NULL) return decoded;
	
	base128 * coder = new base128();
	[string getCString:dec maxLength:(strlen) encoding:NSISOLatin1StringEncoding];
	char * _dec = (char *)coder->decode(dec);
	
	if(_dec!=NULL)
		decoded=[[[NSString alloc] initWithCString:_dec encoding:encoding] autorelease];		

	delete coder;
	free(dec);
	return decoded;	
}

+(NSData *)decodedDataFromLatin1String:(NSString *)string {
	NSData * decoded = nil;
	int strlen=[string length]+1;
	char * dec=(char *)malloc((size_t)(strlen));
	if(dec==NULL) return decoded;	
	
	base128 * coder = new base128();
	[string getCString:dec maxLength:(strlen) encoding:NSISOLatin1StringEncoding];
	void * _dec = coder->decode(dec);

	if(_dec!=NULL)
		decoded=[[[NSData alloc] initWithBytes:_dec length:coder->decoded_size] autorelease];
	delete coder;
	free(dec);
	return decoded;	
	
}

@end
