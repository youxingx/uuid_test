//
//  main.c
//  myuuid
//
//  Created by mac on 2017/7/6.
//  Copyright © 2017年 zhengbensuyuan. All rights reserved.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <uuid/uuid.h>



#define UUID128 unsigned __int128

static char DIGITS_64[64] = { '0', '1', '2', '3', '4', '5', '6', '7', '8',
    '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
    'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y',
    'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
    'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y',
    'Z', '_', '-'};

// hex 转 94 进制对应表
static char DIGITS_94[94] = { '0', '1', '2', '3', '4', '5', '6', '7', '8',
    '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
    'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y',
    'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
    'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y',
    'Z', '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',',
    '-', '.', '/', ':', ';', '<', '=', '>', '?', '@', '[', ']', '\\',
    '^', '_', '`', '{', '|', '}', '~'};

static char chars[] = {
    'a','b','c','d','e','f','g','h',
    'i','j','k','l','m','n','o','p',
    'q','r','s','t','u','v','w','x',
    'y','z','0','1','2','3','4','5',
    '6','7','8','9','A','B','C','D',
    'E','F','G','H','I','J','K','L',
    'M','N','O','P','Q','R','S','T',
    'U','V','W','X','Y','Z'
};

//static const unsigned uuid_128_size = 127;
#define uuid_128_size       127
// hex 转 128 进制对应表
static char DIGITS_128[uuid_128_size+1] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e
    , 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e
    , 0x1f, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e
    , 0x2f, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e
    , 0x3f, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e
    , 0x4f, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x5b, 0x5c, 0x5d, 0x5e
    , 0x5f, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e
    , 0x6f, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e
    , 0x7f};

//static const unsigned uuid_256_size = 255;
#define uuid_256_size       255
// hex 转 256 进制对应表
static char DIGITS_256[uuid_256_size+1] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e
    , 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e
    , 0x1f, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e
    , 0x2f, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e
    , 0x3f, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e
    , 0x4f, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x5b, 0x5c, 0x5d, 0x5e
    , 0x5f, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e
    , 0x6f, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e
    , 0x7f, 0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e
    , 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x9e
    , 0x9f, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae
    , 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xbb, 0xbc, 0xbd, 0xbe
    , 0xbf, 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce
    , 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda, 0xdb, 0xdc, 0xdd, 0xde
    , 0xdf, 0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee
    , 0xef, 0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfe
    , 0xff};

void uuid(char *result, int len)
{
    unsigned char uuid[16];
    char output[24];
    const char *p = (const char*)uuid;
    
    uuid_generate(uuid);
    memset(output, 0, sizeof(output));
    
    int i, j;
    for (j = 0; j < 2; j++)
    {
        unsigned long long v = *(unsigned long long*)(p + j*8);
        int begin = j * 10;
        int end =  begin + 10;
        
        for (i = begin; i < end; i++)
        {
            int idx = 0X3D & v;
            output[i] = chars[idx];
            v = v >> 6;
        }
    }
    //printf("%s\n", output);
    len = (len > sizeof(output)) ? sizeof(output) :  len;
    memcpy(result, output, len);
}

void uuid8(char *result)
{
    uuid(result, 8);
    result[8] = '\0';
}

void uuid20(char *result)
{
    uuid(result, 20);
    result[20] = '\0';
}



void uuid64hex(char* uuidRes)
{
    unsigned __int128 uuid_num;
    int strIndex = 0;
    int index = 0;
    
    uuid_t uu;
    uuid_generate( uu );
    memcpy(&uuid_num,&uu,sizeof(uuid_num));
    
    while (uuid_num > 0)
    {
        index = uuid_num % 64 ; uuid_num = uuid_num >> 6;
        uuidRes[strIndex] = DIGITS_64[index];
        ++strIndex;
    }uuidRes[strIndex] = '\0';
}


void uuid94hex(char* uuidRes)
{
    unsigned __int128 uuid_num;
    int strIndex = 0;
    int index = 0;
    
    uuid_t uu;
    uuid_generate( uu );
    memcpy(&uuid_num,&uu,sizeof(uuid_num));
    while (uuid_num > 0)
    {
        index = uuid_num % 94 ; uuid_num /= 94;
        uuidRes[strIndex] = DIGITS_94[index];
        ++strIndex;
    }uuidRes[strIndex] = '\0';
}


void uuid128hex(char* uuidRes)
{
    unsigned __int128 uuid_num;
    int strIndex = 0;
    int index = 0;
    
    uuid_t uu;
    uuid_generate( uu );
    memcpy(&uuid_num,&uu,sizeof(uuid_num));
    while (uuid_num > 0)
    {
        index = uuid_num % uuid_128_size ; uuid_num /= uuid_128_size;
        uuidRes[strIndex] = DIGITS_128[index+1];
        ++strIndex;
    }uuidRes[strIndex] = '\0';
}


void uuid256hex(char* uuidRes)
{
    unsigned __int128 uuid_num;
    int strIndex = 0;
    int index = 0;
    
    uuid_t uu;
    uuid_generate( uu );
    memcpy(&uuid_num,&uu,sizeof(uuid_num));
    while (uuid_num > 0)
    {
        index = uuid_num % uuid_256_size ; uuid_num /= uuid_256_size;
        uuidRes[strIndex] = DIGITS_256[index+1];
        ++strIndex;
    }uuidRes[strIndex] = '\0';
}

void uuid64hexbyuuid(char* uuidRes,char* uuid)
{
    unsigned __int128 uuid_num;
    int strIndex = 0;
    int index = 0;
    uuid_t uu;
    uuid_parse(uuid,uu);
    memcpy(&uuid_num,&uu,sizeof(uuid_num));
    
    while (uuid_num > 0)
    {
        index = uuid_num % 64 ; uuid_num = uuid_num >> 6;
        uuidRes[strIndex] = DIGITS_64[index];
        ++strIndex;
    }uuidRes[strIndex] = '\0';
    
}



void uuid94hexbyuuid(char* uuidRes,char* uuid)
{
    unsigned __int128 uuid_num;
    int strIndex = 0;
    int index = 0;
    uuid_t uu;
    uuid_parse(uuid,uu);
    memcpy(&uuid_num,&uu,sizeof(uuid_num));
    
    while (uuid_num > 0)
    {
        index = uuid_num % 94 ; uuid_num = uuid_num / 94;
        uuidRes[strIndex] = DIGITS_94[index];
        ++strIndex;
    }uuidRes[strIndex] = '\0';
}


void uuid128hexbyuuid(char* uuidRes,char* uuid)
{
    unsigned __int128 uuid_num;
    int strIndex = 0;
    int index = 0;
    uuid_t uu;
    uuid_parse(uuid,uu);
    memcpy(&uuid_num,&uu,sizeof(uuid_num));
    
    while (uuid_num > 0)
    {
        index = uuid_num % uuid_128_size ; uuid_num = uuid_num / uuid_128_size;
        uuidRes[strIndex] = DIGITS_128[index+1];
        ++strIndex;
    }uuidRes[strIndex] = '\0';
}


void uuid256hexbyuuid(char* uuidRes,char* uuid)
{
    unsigned __int128 uuid_num;
    int strIndex = 0;
    int index = 0;
    
    uuid_t uu;
    uuid_generate( uu );
    memcpy(&uuid_num,&uu,sizeof(uuid_num));
    while (uuid_num > 0)
    {
        index = uuid_num % uuid_256_size ; uuid_num /= uuid_256_size;
        uuidRes[strIndex] = DIGITS_256[index+1];
        ++strIndex;
    }uuidRes[strIndex] = '\0';
}


int main(int argc, const char * argv[]) {
    // insert code here...
    char* testuuid = "4384fde6-4e2a-59d4-b935-a9ea9c289b68";

    char bufres[32] = {0};
    uuid64hexbyuuid(bufres,testuuid);
    printf("len:%d, 64 %s len is %d\n",strlen(testuuid),bufres,strlen(bufres));

    uuid94hexbyuuid(bufres,testuuid);
    printf("94 %s len is %d\n",bufres,strlen(bufres));

    uuid128hexbyuuid(bufres,testuuid);
    printf("128 %s len is %d\n",bufres,strlen(bufres));

    uuid256hexbyuuid(bufres,testuuid);
    printf("256 %s len is %d\n",bufres,strlen(bufres));
    return 0;
}
