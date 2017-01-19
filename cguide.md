# C Programming Reference List and Guide


This guide will be built out to include important code blocks and tricks used during OS and is intended to help me become a better programmer overall and enhance C skills.


## Compilation and Program Execution

Simple Compilation

```
gcc programName.c -o fileName
```

Execution

```
fileName
```

Further guide on GCC can be found [Here](http://pages.cs.wisc.edu/~beechung/ref/gcc-intro.html)


## C Tips and tricks

### "Parameters in C"
```
int main(int argc, char* argv[]) 
{ 
    if (argc < 2) { 
        fputs("Usage: must supply a command\n", stderr); 
        exit(1); 
    }

    puts("Before the exec"); 
    if (execvp(argv[1], &argv[1]) < 0) { 
        perror("exec failed"); 
        exit(1); 
    } 
    puts("After the exec");

    return 0; 
}
```

If we take a look at the 'parameters argc and argv', the first 'argc' represents the number of things we have in our command. argv stores the location of each thing that we store.
