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

* If we take a look at the 'parameters argc and argv', the first 'argc' represents the number of things we have in our command. argv stores the location of each thing that we store.

* The name of a function is really just the address to the beginning of a function
    * A void pointer is a pointer to anything. It is just an address. 
    
```
    // This would be simply the name of the function
    void* (*start)(void*)
```
* Pass an address that is a void pointer. In our function, take that pointer and cast it to what we need it to be
    * If we have two arguments (or more), we can put them in a struct. Then put the pointer to the struct as the argument. 
    * Then in our function, we cast the pointer to the struct we defined and get the properties we need

#### Tips for final programming project
* The equivalent for a wait with threads is 'join()'
    * With threads, we don't haveo maintain the same parent, child relationship as fork()s
        * We can do a detatch. To tell the parent that we are not going to return
