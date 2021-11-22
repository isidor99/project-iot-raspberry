LIBS = -lpigpio -lm -lcurl -lpthread
INCLUDES = lib/source/pca.c lib/source/motor.c lib/source/client.c lib/source/callback.c

main: main.c
	gcc -o $@ $< $(LIBS) $(INCLUDES)

clean:
	rm -f main
