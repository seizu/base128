/*
 * ***********************************************************************
 * Copyright © Erich Pribitzer 2012
 *
 * This file is part of base128

    base128 is free software: you can redistribute it and/or modify
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

#include "base128.h"

char * base128::encode(const char *buffer)
{
	size_t bufferSize = strlen(buffer);
	if(bufferSize<=0) return NULL;
	return encode((void *)buffer, bufferSize);
}

char * base128::encode(void *buffer, size_t bufferSize)
{
	if(bufferSize==0) return NULL;
	size_t re = bufferSize%7;
	size_t size = (size_t)(bufferSize-re)/7*8+re;
	if(re) size++;

	size++;
	if(encoded!=NULL) free(encoded);
	if((encoded=(char *)malloc(size))==NULL) return NULL;

	encoded_size=size-1;

	int ls=0;
	int rs=7;
	int r=0;
	int nc=0;
	
	unsigned char * buff=(unsigned char *)buffer;

	for(size_t inx=0,t=0;inx<bufferSize+1;t++,inx++)
	{
		if(ls>7)
		{
			inx--;
			ls=0;
			rs=7;
		}
		(inx>=bufferSize)?nc=0:nc=(int)buff[inx];

		int r1=nc;           // save nc
		nc=nc<<ls;           // shift left for rs
		nc=(nc & 0x7f)|r;    // OR carry bits
		r=(r1>>rs) & 0x7f;   // shift right and save carry bits
		ls++;
		rs--;

		encoded[t]=ascii[nc];
	}
	encoded[size-1]=0;
	return encoded;
}

void * base128::decode(const char *buffer)
{
	size_t bufferSize = strlen(buffer);
	if(bufferSize<=0) return NULL;
	size_t re = bufferSize%8;
	size_t size = (size_t)(bufferSize-re)/8*7+re;
	if(re) size--;

	if((decoded=malloc(size+1))==NULL) return NULL;
	decoded_size=size;

	unsigned char * dec=(unsigned char *)decoded;
    int rs=8;
    int ls=7;
    int r=0;
	int nc=0;
	int r1=0;
	int t=0;
	const char * loc=NULL;

    for(size_t inx=0;inx<bufferSize;inx++)
    {
        loc=strrchr(ascii,(char)buffer[inx]);
		if(loc!=NULL)
			nc=(int)(loc-ascii);				

        if(rs>7)
        {
            rs=1;
            ls=7;
            r=nc;
            continue;
        }
        r1=nc;
        nc=(nc<<ls) & 0xFF;
        nc=(nc|r);
        r=r1>>rs;
        rs++;
        ls--;
        dec[t++]=(char)nc;
    }
	dec[size]=0;
	decoded_size=size;
	return decoded;
}

base128::base128(void)
{
	decoded_size=0;
	encoded_size=0;
	encoded=NULL;
	decoded=NULL;
	ascii="!#$%()*,.0123456789:;=@ABCDEFGHIJKLMNOPQRSTUVWXYZ[]^_abcdefghijklmnopqrstuvwxyz{|}~¡¢£¤¥¦§¨©ª«¬®¯°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎ";
}

base128::~base128(void)
{
	if(encoded!=NULL)
		free(encoded);
	if(decoded!=NULL)
		free((void*)decoded);
}
