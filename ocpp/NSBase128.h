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

#import "base128.h"

@interface NSBase128 : NSObject {
	
}

+(NSString *)encodedLatin1StringFromData:(NSData *)data;
+(NSString *)encodedLatin1StringFromString:(NSString *)string encoding:(NSStringEncoding)encoding;

+(NSString *)decodedStringFromLatin1String:(NSString *)string encoding:(NSStringEncoding)encoding;
+(NSData *)decodedDataFromLatin1String:(NSString *)string;

@end
