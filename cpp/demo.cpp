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

#include <stdio.h>
#include "base128.h"

int main(int argc, char* argv[])
{
	char * str = "Test String\xC3\xB6\xC4\xA6";

	base128 * coder=new base128();	
	char * encoded=coder->encode(str);
	char * decoded=(char *)coder->decode(encoded);
	printf("string:  %s\n",str);
	printf("encoded: %s length: %d\n",encoded,coder->encoded_size);
	printf("decoded: %s    length: %d\n",decoded,coder->decoded_size);

	//free memory	
	delete coder;
	return 0;
}

