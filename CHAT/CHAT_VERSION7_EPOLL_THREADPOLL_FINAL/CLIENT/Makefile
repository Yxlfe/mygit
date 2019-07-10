Target = Client
Object = Client.c Testclient.c

$(Target):$(Object)
	gcc $(Object) -o $(Target) -lpthread -lsqlite3
.PHONY:clean
clean:
	-rm -rf $(Target)
