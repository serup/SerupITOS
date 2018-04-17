#include "types.h"

static uint16_t* VideoMemory = (uint16_t*)0xb8000;

void printf(char* str)
{
    static uint8_t x=0,y=0;      
    
    for(int i=0; str[i] != '\0'; ++i)
    {
        switch(str[i])
        {
            case '\n':
                x=0;
                y++;
                break;
            default:
                VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | str[i];
                x++;
                break;
        }
        
        if(x>=80)
        {
            x=0;
            y++;
        }
        
        if(y>=25)
        {
            for(y=0;y<25;y++)
                for(x=0;x<80;x++)
                    VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | ' ';
                 
            x=0;
            y=0;
        }
    }
}

void clr()
{
    for(int y=0;y<25;y++)
        for(int x=0;x<80;x++)
            VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | ' ';
}

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors()
{
    for(constructor* i = &start_ctors; i != &end_ctors; i++)
        (*i)();
}



extern "C" void kernelMain(void * multiboot_structure, uint32_t magicnumber)
{
        clr();
        
        char *logo =    " ___                        ___  _____\n"
                        "/ __| ___  _ _  _  _  _ __ |_ _||_   _|\n"
                        "\\__ \\/ -_)| '_|| || || '_ \\ | |   | |\n"
                        "|___/\\___||_|   \\_,_|| .__/|___|  |_|\n"
                        "                     |_|\n"
                        "\n"
                        "  Copyright (c) 2018, SerupIT\n";
    
        printf(logo);
        
        while(1); // no sense in stopping the kernel, hence infinite loop
}
