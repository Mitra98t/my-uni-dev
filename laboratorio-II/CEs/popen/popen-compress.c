#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <util.h>

#if !defined MAX_FILENAME_LENGTH
#define MAX_FILENAME_LENGTH 255
#endif

#define CHUNKSIZE  16384

int main(int argc, char *argv[]) {
  if (argc == 1) {
    fprintf(stderr, "use: %s file [file]\n", argv[0]);
    return EXIT_FAILURE;
  }
  
  const int len = MAX_FILENAME_LENGTH + 64;

  char *buffer = malloc(CHUNKSIZE);
  if (!buffer) {
    perror("malloc");
    return EXIT_FAILURE;
  }
  
  for(int i=1; i<argc; ++i) {  
    const char *filename = argv[i];    
    int r;
    if ((r=isRegular(filename, NULL)) == 1) {
      FILE *fin;
      if ((fin = fopen(filename, "r")) == NULL) {
	perror("fopen");
	continue;
      }
      
      char str[len];
      snprintf(str, len, "gzip - -c > %s.gz", filename);
      FILE *fpipe;
      if ((fpipe = popen(str, "w")) == NULL) {
	perror("popen");
	continue;
      }

      while(!feof(fin)) {
	size_t sz = fread(buffer, 1, CHUNKSIZE, fin);
	if (sz>0)
	  if (fwrite(buffer, 1, sz, fpipe) != sz) {
	    perror("fwrite");
	    break;
	  }
      }
      if (pclose(fpipe) == -1) {
	perror("pclose");
      }
      continue;
    }
    if (r==0) 
      fprintf(stderr, "%s is not a regular file\n", filename);
    else 
      perror("isRegular");    
  }
  
  free(buffer);
  return 0;
}


  
