Target = Server
Object = Server.c Testserver.c condition.c threadpool.c

$(Target):$(Object)
	gcc $(Object) -o $(Target) -lpthread -lsqlite3 -lrt
.PHONY:clean
clean:
	-rm -rf $(Target)
