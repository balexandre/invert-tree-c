Simple project to get `fork()` tree

to run

```bash
cd ./src
gcc -Wall -o mano mano.c && ./mano 5
```

where `5` is how many interactions one want to run (from 0 to 32, as defined in the source)

## Objective

to create an inverted V process tree like

![](https://i.imgur.com/UKip1WM.png)

where the output, if `n=5` should be

```bash
Inverted V process tree with n=5:
Process AB has PID=12931
Process A1 has PID=12932 and PPID=12931
Process B1 has PID=12933 and PPID=12931
Process B2 has PID=12934 and PPID=12933
Process A2 has PID=12935 and PPID=12932
Process B3 has PID=12936 and PPID=12934
Process B4 has PID=12938 and PPID=12936
Process A3 has PID=12937 and PPID=12935
Process B5 has PID=12939 and PPID=12938
Process A4 has PID=12940 and PPID=12937
Process A5 has PID=12941 and PPID=12940
```

##

Test are written using [Check](https://libcheck.github.io/check/index.html) framework
