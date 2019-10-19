# Data-Structures

Note: You will see this multiple times -
_type* ptr = malloc(sizeof ptr)_
and it's worked till now because the size of the address has always been greater than the size of an instance of that type. It should be corrected as so -
_type* ptr = malloc(sizeof *ptr)_
