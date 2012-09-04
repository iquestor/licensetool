all: license_tool

license_tool: base32.o hmac.o sha2.o license.o
	$(CC) base32.o sha2.o hmac.o license.o -o license_tool

base32.o: base32.c base32.h
	$(CC) -c base32.c -o base32.o

hmac.o: hmac_sha2.c hmac_sha2.h
	$(CC) -Wall -c hmac_sha2.c -o hmac.o

sha2.o: sha2.c sha2.h
	$(CC) -c sha2.c -o sha2.o

license.o: license.c license.h
	$(CC) -Wall -c license.c -o license.o

clean:
	- rm -rf *.o license_tool
