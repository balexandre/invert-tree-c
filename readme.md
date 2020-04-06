Simple project to get `fork()` tree

to run

```bash
gcc -Wall -o mano mano.c && ./mano 5
```

## Objective

to create an inverted V process tree like

![](https://i.imgur.com/UKip1WM.png)

where the output, if `n=5` would be 

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
