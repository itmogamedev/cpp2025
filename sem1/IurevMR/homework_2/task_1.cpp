typedef unsigned int u32;

const char* conversion_table = "0123456789abcdef";

void convertToSys(u32 input, u32 sys, char* const output) {
    if(input == 0) {
        output[0] = '0';
        output[1] = '\n';
        return;
    }
    u32 len = 0;
    while (input > 0) {
        u32 mod = input % sys;
        output[len] = conversion_table[mod];
        input /= sys;
        len++;
    }
    for(u32 i = 0; i < len / 2; i++) {
        char tmp = output[i];
        output[i] = output[len - 1 - i];
        output[len - 1 - i] = tmp;
    }
    output[len] = '\0';
}

#define convertToHex(input, output) convertToSys(input, 16, output)
#define convertToOct(input, output) convertToSys(input,  8, output)
