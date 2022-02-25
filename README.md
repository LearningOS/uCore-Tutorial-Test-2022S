# uCore-Tutorial-Tests

User testcases for [uCore-Tutorial-Code-2022S](https://github.com/learningos/uCore-Tutorial-Code-2022S).

### Usage

```shell
make CHAPTER=5 BASE=1
```

CHAPTER:
* Optional values: 1,2,3,3_2,3t,4,4_3,5,6,7.
* Note that uCore will set the default value of `CHAPTER` according the name of branch. So usually you need not to care about this parameter.

BASE:
* Optional values: 0,1
* Default value: 0
* `BASE=1` will generate basic testcases starting which can be handled by the uCore without any modification. Basic testcases have prefixed names: 'chxb_'.
* `BASE=0` will generate all the testcases.

### Output

* target/bin : all `.bin` file
* target/elf : all `.elf` file (Used for extended lab)
* asm : the assembly of testcases.  

### Dev Log

* v1.0: basic version.
