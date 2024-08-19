#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    long long tape[30000] = {0};
    long long stack0 = 0, stack1 = 0;
    char* buf;
    char op;
    int tapeptr = 0;
    int filesize;

    FILE *fptr;

    if (argc < 2)
        return 0;

    if ((fptr = fopen(argv[1], "r")) == NULL) {
        printf("Unable to open %s\n", argv[1]);
        return 1;
    }
    
    fseek(fptr, 0, SEEK_END);
    filesize = ftell(fptr);
    rewind(fptr);
    buf = malloc(filesize + 1);
    fread(buf, 1, filesize, fptr);
    buf[filesize] = 0;
    fclose(fptr);

    for (int i = 0; buf[i]; i++) {
        int loopcnt = 1;
        if (buf[i] >= '0' && buf[i] <= '9') {
            long long n = 0;

            while (buf[i] >= '0' && buf[i] <= '9')
                n = n * 10 + buf[i++] - '0';

            tape[tapeptr] = n;
        }

        switch (buf[i]) {
            case '>': tapeptr++; break;
            case '<': tapeptr--; if (tapeptr < 0) tapeptr = 0; break;
            case '+': tape[tapeptr]++; break;
            case '-': tape[tapeptr]--; break;
            case '^': stack1 = stack0; stack0 = tape[tapeptr]; break;
            case 'v': tape[tapeptr] = stack0; stack0 = stack1; break;
            case 'd': stack0 = stack1 / stack0; stack1 = 0; break;
            case 'r': stack0 = stack1 % stack0; stack1 = 0; break;
            case 'm': stack0 *= stack1; stack1 = 0; break;
            case 's': stack0 = stack1 - stack0; stack1 = 0; break;
            case 'a': stack0 += stack1; stack1 = 0; break;
            case '.': printf("%c", tape[tapeptr]); break;
            case '#': printf("%lld", tape[tapeptr]); break;
            case ',': scanf("%lld", &tape[tapeptr]); break;
            case '[': if (tape[tapeptr] > 0) break;
                      else while (loopcnt) {
                          i++;
                          if (buf[i] == '[')
                              loopcnt++;
                          if (buf[i] == ']')
                              loopcnt--;
                      } break;
            case ']': if (tape[tapeptr] <= 0) break;
                      else while (loopcnt) {
                          i--;
                          if (buf[i] == ']')
                              loopcnt++;
                          if (buf[i] == '[')
                              loopcnt--;
                      } break;
        }
    }


    return 0;
}
