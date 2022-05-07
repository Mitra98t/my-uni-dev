.PHONY: clean
.PHONY: test1
.PHONY: test2


direxec: dirmanager.o
	gcc $^ -o $@

dirmanager.o: dirmanager.c
	gcc -c $^ -o $@

clean:
	rm *.o
	rm direxec

test1:
	@echo "Creating files and directory"
	@rm -rf testDirForBash && mkdir testDirForBash && sleep 0.5 && dd if=/dev/zero of=testDirForBash/file2 bs=1M count=3 && sleep 0.5 && dd if=/dev/zero of=testDirForBash/file3 bs=1M count=5 && sleep 0.5 && dd if=/dev/zero of=testDirForBash/file1 bs=1M count=5
	@echo Running Test
	@./dirmanager.sh -d testDirForBash -s 14 -f 0.35 -n 0
	@ls testDirForBash -1q | diff - results/test1Res
	@echo "finished test successfully"

test2: direxec
	@echo "Creating files and directory"
	@rm -rf testDir && mkdir testDir && sleep 0.5 && dd if=/dev/zero of=testDir/file2 bs=1M count=3 && sleep 0.5 && dd if=/dev/zero of=testDir/file3 bs=1M count=5 && sleep 0.5 && dd if=/dev/zero of=testDir/file1 bs=1M count=5
	@echo "Running Test"
	@./direxec -d testDir -s 14 -f 0.35 -n 0
	@ls testDir -1q | diff - results/test2Res
	@echo "finished test successfully"
