#include <stdio.h>
#include <SDL2/SDL.h>


char *mirror_name(char *pathname)
{
    const char *mode = 'r';
    FILE *input_file = fopen(pathname,mode);
    if (input_file == NULL)
    {
        fprintf(stderr, "Could not open the file");
    }
    
}






