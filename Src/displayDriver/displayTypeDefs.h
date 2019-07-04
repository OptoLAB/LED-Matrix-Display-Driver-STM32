/* 
 * Author: J. Bajic
 */

#ifndef DISPLAYTYPEDEFS_H
#define	DISPLAYTYPEDEFS_H

//-------------------------------------------------------------------
//DEFINE TYPES
//-------------------------------------------------------------------
//8, 16 & 32 bits data
//-------------------------------------------------------------------
#ifndef uint8_t
    typedef unsigned char type_uint8_t;      //XC32 compiler
    #define uint8_t type_uint8_t
#endif
#ifndef uint16_t
    typedef unsigned short type_uint16_t;
    #define uint16_t type_uint16_t
#endif
#ifndef uint32_t
    typedef unsigned int type_uint32_t;
    #define uint32_t type_uint32_t
#endif

// font structure
//-------------------------------------------------------------------
#ifndef font_t  
    typedef struct{
        unsigned char width;
        unsigned char height;
        unsigned char first_char;
        unsigned char last_char; 
        const unsigned char *chars; 
    }type_font_t;
    #define font_t type_font_t
#endif

// color formats/types
//-------------------------------------------------------------------
#ifndef color111_t 
    typedef union{
        struct {
        uint8_t  b:1;
        uint8_t  g:1;
        uint8_t  r:1;
        uint8_t  x:1;
        uint8_t b1:1;
        uint8_t g1:1;
        uint8_t r1:1;
        uint8_t  x1:1;
        }bits;
        uint8_t color;
    }type_color111_t;
    #define color111_t type_color111_t
#endif

#ifndef color332_t
    typedef union{
        struct{ 
        uint8_t b:2;
        uint8_t g:3;
        uint8_t r:3; 
        }bits;
        uint8_t color;
    }type_color332_t;
    #define color332_t type_color332_t
#endif

#ifndef color565_t     
    typedef union{
        struct{ 
        uint16_t b:5;
        uint16_t g:6;
        uint16_t r:5;
        }bits;
        uint16_t color;
    }type_color565_t;
    #define color565_t type_color565_t
#endif    

#ifndef color888_t     
    typedef union{
        struct{  
        uint8_t b;
        uint8_t g;
        uint8_t r; 
        }bits;  
        uint8_t color[3];
    }type_color888_t;
    #define color888_t type_color888_t
#endif

#ifndef color_t
    #if defined(RGB111)
        #define color_t color111_t
    #elif defined(RGB332)
        #define color_t color332_t
    #elif defined(RGB565)
        #define color_t color565_t
    #elif defined(RGB888)
        #define color_t color888_t
    #else   // default
        #define color_t color565_t 
    #endif
#endif

// image structure
//-------------------------------------------------------------------
#ifndef image_t
    typedef struct{
        unsigned char width;
        unsigned char height;
        unsigned char bytes_per_px;
        unsigned char px_per_bytes;
        const unsigned char *pixels; 
    }type_image_t; 
    #define image_t type_image_t
#endif    
    
#endif	/* DISPLAYTYPEDEFS_H */

