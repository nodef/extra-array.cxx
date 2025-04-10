Generic array in C.
> Download: [header file](https://raw.githubusercontent.com/cppf/extra-array/master/coll/earray.h).


## structure

```c
at : T*
size : size_t
```


## usage

### declare

```c
// Declare array type.
// This defines structure and declares functions.
EARRAY_DECLARE(name, type)
```

```c
// declare int array
EARRAY_DECLARE(AInt, int)
```


## define

```c
// Define array type.
// This defines functions.
EARRAY_DEFINE(name, type)
```

```c
// define int space
EARRAY_DEFINE(AInt, int)
```


### open

```c
// Open with static memory.
#_open(array, at, size)

```

```c
// define array and char buffer
AInt o;
char buffer[32];

// open with buffer
AInt_open(&o, buffer, 32/sizeof(int));

// print size of array
printf("%zu", o.size);

// write 0x0BADB055 at last index
o.at[o.size-1] = 0x0BADB055;
```


## openHeap

```c
// Open with heap memory.
#_openHeap(array, size)
```

```c
// open of size 64
AInt_openHeap(&o, 64);

// print size of array
printf("%zu", o.size);

// write 0x600DB055 at last index
o.at[o.size-1] = 0x600DB055;
```


### close

```c
// Close, if opened with heap memory.
#_close(array)
```

```c
// close array
AInt_close(&o);
```


### resize

```c
// Resize if opened with heap memory.
#_resize(array, size)
```

```c
// open of size 128
AInt_openHeap(&o, 128);

// resize to size 256
AInt_resize(&o, 256);

// print size of array
printf("%zu", o.size);

// close array
AInt_close(&o);
```
<br><br>


[![cppf](https://i.imgur.com/eKtn1hj.jpg)](https://cppf.github.io)
![](https://ga-beacon.deno.dev/G-RC63DPBH3P:SH3Eq-NoQ9mwgYeHWxu7cw/github.com/nodef/extra-array.cxx)
