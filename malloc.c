


custom malloc
- test if size > 0 and < MAX, if not, return NULL
- test if malloc return NULL, if so, exit with errno


custom free:
- takes double pointer
- free the pointer
- set the pointer to NULL