/* 
 * Author: J. Bajic
 */
//------------------------------------------------------------------------------------------
// INCLUDE
//------------------------------------------------------------------------------------------
#include "displayDriver.h"
//------------------------------------------------------------------------------------------
// GLOBAL VARIABLES
//------------------------------------------------------------------------------------------
color_t FRAME_BUFF[NUM_OF_PANELS*NUM_PIXELS_PER_PANEL/PPB]={0};
uint8_t BITS_PER_CHANNEL=BPC;
uint16_t BRIGHTNESS=20;
font_t SELECTED_FONT={0};
uint8_t positionX=0;
uint8_t positionY=0;

#if (USE_SD_CARD)
FATFS myFAT={0};
#endif

//------------------------------------------------------------------------------------------
// DISPLAY CONTROL FUNCTIONS
// clock, latch, selectRow, setTopColor, setBottomColor
//------------------------------------------------------------------------------------------
static void clock(void)
{
   CLK_HIGH;
   CLK_LOW;
}

static void latch(void)
{
    LAT_HIGH;
    LAT_LOW;
}

static void selectRow(uint8_t x)
{
#if NUM_OF_SELECTION_BITS>=1
    A(x&0x01);
#endif
#if NUM_OF_SELECTION_BITS>=2
    B((x&0x02)>>1);
#endif
#if NUM_OF_SELECTION_BITS>=3
    C((x&0x04)>>2);
#endif
#if NUM_OF_SELECTION_BITS>=4
    D((x&0x08)>>3);
#endif
}

static void setColor(uint32_t px, uint8_t i) 
{

#if NUM_OF_SUBPANELS>=1
    R1(rCh(getFRAMEpx(px))>>i);
    G1(gCh(getFRAMEpx(px))>>i);
    B1(bCh(getFRAMEpx(px))>>i);
#endif
#if NUM_OF_SUBPANELS>=2
    px+=SUBPANEL_OFFSET;
    R2(rCh(getFRAMEpx(px))>>i);
    G2(gCh(getFRAMEpx(px))>>i);
    B2(bCh(getFRAMEpx(px))>>i);
#endif
#if NUM_OF_SUBPANELS>=3
    px+=SUBPANEL_OFFSET;
    R3(rCh(getFRAMEpx(px))>>i);
    G3(gCh(getFRAMEpx(px))>>i);
    B3(bCh(getFRAMEpx(px))>>i);
#endif
#if NUM_OF_SUBPANELS>=4
    px+=SUBPANEL_OFFSET;
    R4(rCh(getFRAMEpx(px))>>i);
    G4(gCh(getFRAMEpx(px))>>i);
    B4(bCh(getFRAMEpx(px))>>i);
#endif   
}

//------------------------------------------------------------------------------------------
// DISPLAY REFRESH FUNCTIONS
// refreshDisplay, displaySetBrightness
//------------------------------------------------------------------------------------------
void refreshDisplay(void) 
{

    uint32_t pixel, x_offset,y_offset;
    uint8_t row, column, segment, cBit, panel_x, panel_y;
    
    for(cBit=0; cBit<(BITS_PER_CHANNEL); cBit++)
    {    
       for(row=0; row<NUM_OF_ROWS; row++)
       {
    	   selectRow(row);
            y_offset=(row*DISPLAY_WIDTH);   
            for(panel_y=0;panel_y<NUM_OF_PANELS_Y;panel_y++)
            {
                x_offset=0;
                for(panel_x=0;panel_x<NUM_OF_PANELS_X;panel_x++)
                {       
                    for(segment=1; segment<=NUM_OF_SEGMENTS;segment++)
                    {
                        pixel=y_offset+x_offset+((NUM_OF_SEGMENTS-segment)*SEGMENT_OFFSET);

                        for(column=0;column<PANEL_WIDTH; column++)
                        {

                            setColor(pixel+column, cBit);

                            clock();                        
                        }
                    }
                    x_offset+=PANEL_WIDTH;
                }
                y_offset+=VERTICAL_PANEL_OFFSET;
            }

            latch();

            OE_LOW;
                delay_nops(BRIGHTNESS<<cBit); // BCM Modulation
            OE_HIGH;
                delay_nops(1);

        }                
    }
}

void displaySetBrightness(uint8_t level)
{
    BRIGHTNESS=level;
}

//------------------------------------------------------------------------------------------
// DISPLAY INIT FUNCTIONS
// displayInit
//------------------------------------------------------------------------------------------
void displayInit(void)
{
#ifdef enablePORTclocks
	enablePORTclocks();
#endif
#if NUM_OF_SUBPANELS>=1
	R1_IO; G1_IO; B1_IO;
#endif
#if NUM_OF_SUBPANELS>=2
	R2_IO; G2_IO; B2_IO;
#endif
#if NUM_OF_SUBPANELS>=3
	R3_IO; G3_IO; B3_IO;
#endif
#if NUM_OF_SUBPANELS>=4
	R4_IO; G4_IO; B4_IO;
#endif

#if NUM_OF_SELECTION_BITS>=1
	A_IO;
#endif
#if NUM_OF_SELECTION_BITS>=2
	B_IO;
#endif
#if NUM_OF_SELECTION_BITS>=3
	C_IO;
#endif
#if NUM_OF_SELECTION_BITS>=4
	D_IO;
#endif

	CLK_IO; LAT_IO; OE_IO;

#ifdef STAT_LED_IO
	STAT_LED_IO;
#endif
#ifdef DATA_LED_IO
	DATA_LED_IO;
#endif

    displayClear();  
    displaySetFont(DEFAULT_SMALL);
}
//------------------------------------------------------------------------------------------
// DISPLAY FILL FUNCTIONS
// displayFillArea, displayInvertArea, displayFill, displayFillNoise, displayInvert, displayClear 
//------------------------------------------------------------------------------------------
void displayFillArea(uint16_t x1,uint16_t y1, uint16_t x2, uint16_t y2, color_t color)
{
    uint16_t x, y;
    uint32_t line=0;

    x1=x1%DISPLAY_WIDTH;
    if(x2>=DISPLAY_WIDTH)x2=0;
    
    y1=y1%DISPLAY_HEIGHT;
    if(y2>=DISPLAY_HEIGHT)y2=0;
    
    line=y1*DISPLAY_WIDTH;
    for(y=y1;y<y2;y++)
    {
        for(x=x1;x<x2;x++) setFRAMEpx(x+line,color); 
        line+=DISPLAY_WIDTH;
    }
}

void displayInvertArea(uint16_t x1,uint16_t y1, uint16_t x2, uint16_t y2)
{
    uint16_t x, y;
    uint32_t line=0;
    color_t color;
    x1=x1%DISPLAY_WIDTH;
    if(x2>=DISPLAY_WIDTH)x2=0;
    
    y1=y1%DISPLAY_HEIGHT;
    if(y2>=DISPLAY_HEIGHT)y2=0;

    line=y1*DISPLAY_WIDTH;
    for(y=y1;y<y2;y++)
    {
        for(x=x1;x<x2;x++)
        {
            color=getFRAMEpx(x+line);
            color.bits.r=0xFF-color.bits.r;
            color.bits.g=0xFF-color.bits.g;
            color.bits.b=0xFF-color.bits.b;
            setFRAMEpx(x+line,color);
        }
        line+=DISPLAY_WIDTH;
    }
}

void displayFill(color_t color)
{
    uint32_t i;
    
    for(i=0;i<NUM_OF_PANELS*NUM_PIXELS_PER_PANEL;i++)setFRAMEpx(i,color); 
}

void displayFillNoise(void)
{
    uint32_t i;

    for(i=0; i<NUM_OF_PANELS*NUM_PIXELS_PER_PANEL;i++)setFRAMEpx(i,COLOR(rand()*WHITE));
}

void displayInvert(void)
{
    uint32_t i;
    color_t color;
    for(i=0;i<NUM_OF_PANELS*NUM_PIXELS_PER_PANEL;i++) 
    {
        color=getFRAMEpx(i);
        color.bits.r=0xFF-color.bits.r;
        color.bits.g=0xFF-color.bits.g;
        color.bits.b=0xFF-color.bits.b;
        setFRAMEpx(i,color);
    }
}

void displayClear(void)
{
    displayFill(COLOR(0));
}
//------------------------------------------------------------------------------------------
// DISPLAY GAMMA FUNCTIONS
// gammaCorrected, displayGammaCorrectArea, displayGammaCorrect
//------------------------------------------------------------------------------------------
void displayGammaCorrectArea(uint16_t x1,uint16_t y1, uint16_t x2, uint16_t y2)
{
    uint16_t x, y;
    uint32_t line=0;
    
    x1=x1%DISPLAY_WIDTH;
    if(x2>=DISPLAY_WIDTH)x2=0;
    
    y1=y1%DISPLAY_HEIGHT;
    if(y2>=DISPLAY_HEIGHT)y2=0;

    line=y1*DISPLAY_WIDTH;
    for(y=y1;y<y2;y++)
    {
        for(x=x1;x<x2;x++) setFRAMEpx(x+line,gammaCorrected(getFRAMEpx(x+line)));
        line+=DISPLAY_WIDTH;
    }
}

void displayGammaCorrect(void)
{
    uint32_t i;
    
    for(i=0;i<NUM_OF_PANELS*NUM_PIXELS_PER_PANEL;i++) setFRAMEpx(i,gammaCorrected(getFRAMEpx(i)));
}
//------------------------------------------------------------------------------------------
// DISPLAY SCROLL&MIRROR FUNCTIONS
// displayScrollLeftRight, displayScrollUpDown, displayScroll, displayMirror
//------------------------------------------------------------------------------------------
static void displayScrollLeftRight(uint8_t dir)
{

   uint16_t x, y, last_column;
   uint32_t line=0;
   color_t temp={{0,0,0}};

   dir=(dir&0x08)>>3;

   last_column=DISPLAY_WIDTH-1;
   line=0;
   
   for(y=0;y<DISPLAY_HEIGHT;y++)
   {
        if(dir)temp=getFRAMEpx(line);
        else temp=getFRAMEpx(last_column+line);
        
        for(x=0;x<(DISPLAY_WIDTH-1);x++)
        {
            if(dir)setFRAMEpx(x+line,getFRAMEpx((x+1)+line));
            else setFRAMEpx(last_column-x+line,getFRAMEpx(last_column-(x+1)+line));
        }
             
        if(dir)setFRAMEpx(last_column+line,temp);
        else setFRAMEpx(line,temp);

        line+=DISPLAY_WIDTH;   
    }
}

static void displayScrollUpDown(uint8_t dir)
{

    uint16_t x, y;
    uint32_t line=0, last_line=0;
    color_t temp={{0,0,0}};
    
    dir=(dir&0x02)>>1;
    
    last_line=(DISPLAY_HEIGHT-1)*(DISPLAY_WIDTH);

    for(x=0;x<DISPLAY_WIDTH;x++)
    {
        if(dir)temp=getFRAMEpx(x);
        else temp=getFRAMEpx(x+last_line);
        
        line=0;

        for(y=0;y<(DISPLAY_HEIGHT-1);y++)
        {
           if(dir)setFRAMEpx(x+line,getFRAMEpx(x+line+DISPLAY_WIDTH));
           else setFRAMEpx(last_line-line+x,getFRAMEpx(last_line-line-(DISPLAY_WIDTH)+x));
            
            line+=DISPLAY_WIDTH; 
        }
             
        if(dir)setFRAMEpx(x+last_line,temp);
        else setFRAMEpx(x,temp);       
    }
 
}

void displayScroll(uint8_t dir, uint16_t num_of_px, uint8_t speed)
{
    uint16_t i;
    
    for(i=0;i<num_of_px;i++)
    {
        if(dir&(LEFT|RIGHT))displayScrollLeftRight(dir);
        if(dir&(UP|DOWN))displayScrollUpDown(dir);
        DELAY(speed);
    }
}

void displayMirror(unsigned char axis)
{
    uint16_t x, y, last_column;
    uint32_t line=0, last_line;
    color_t temp;
    
    last_line=(DISPLAY_HEIGHT-1)*DISPLAY_WIDTH;
    last_column=DISPLAY_WIDTH-1;
    if(axis&0x02) //mirror Y
    {
        for(x=0;x<DISPLAY_WIDTH;x++)
        {
            line=0;
            for(y=0;y<DISPLAY_HEIGHT/2;y++) 
            {
                temp=getFRAMEpx(x+line);
                setFRAMEpx(x+line,getFRAMEpx(x+last_line-line));
                setFRAMEpx(x+last_line-line,temp);
                line+=DISPLAY_WIDTH;
            }
        }
    }
    if(axis&0x01) //mirror X
    {
        line=0;
        for(y=0;y<DISPLAY_HEIGHT;y++) 
        {
            for(x=0;x<DISPLAY_WIDTH/2;x++)
            {
                temp=getFRAMEpx(x+line);
                setFRAMEpx(x+line,getFRAMEpx(last_column-x+line));
                setFRAMEpx(last_column-x+line,temp);
                
            }
            line+=DISPLAY_WIDTH;
        }  
    }
}
//------------------------------------------------------------------------------------------
// DISPLAY PRINT FUNCTIONS
// displayGoTo, displaySetFont, displayNewLine, displayPutChar, displayPrint
//------------------------------------------------------------------------------------------
void displayGoTo(uint16_t x, uint16_t y)
{
    x=x%DISPLAY_WIDTH;
    y=y%DISPLAY_HEIGHT;
    positionX=x;
    positionY=y;
}
void displaySetFont(font_t font)
{
    SELECTED_FONT=font;
}
void displayNewLine(void)
{
    positionX=0;
    if((positionY+SELECTED_FONT.height+1)>=DISPLAY_HEIGHT)
    {
        positionY=0;
        displayClear();
    }
    else positionY+=SELECTED_FONT.height+1;
}

void displayPutChar(char c, color_t color)
{
    uint16_t x, y, char_offset;
    uint8_t i,j;
    unsigned long long data;
    
    if(c<=SELECTED_FONT.last_char)
    {
        j=SELECTED_FONT.height/8;  // bytes per char
        if(SELECTED_FONT.height%8!=0)j++;
        char_offset=(c-SELECTED_FONT.first_char)*(j*SELECTED_FONT.width+1);
        
        if((positionX+SELECTED_FONT.chars[char_offset]-1)>=DISPLAY_WIDTH)displayNewLine();

        for (x=1;x<=SELECTED_FONT.chars[char_offset];x++)
        {
            data=0;
            for(i=0;i<j;i++)data|=(SELECTED_FONT.chars[char_offset+j*(x-1)+i+1]&0xFF)<<(i*8); 

            if(x!=1||data!=0) // skip if starts with blank line
            {
                for(y=0; y<(SELECTED_FONT.height+1); y++)
                {
                    if((data>>y)&0x01) displaySetPixel(positionX, positionY, color);
                    positionY++;
                }
                positionX++;
                positionY=positionY-(SELECTED_FONT.height+1);
            }
        }
        positionX++; // blank line at the end of char
    }
}

void displayPrint(char *text, color_t color)
{
	while(*text != 0)
	{
		displayPutChar(*text, color);
		text++;
	}
}
//------------------------------------------------------------------------------------------
// DISPLAY DRAW FUNCTIONS
// displaySetPixel, displayDrawRectangle, displayDrawCircle
//------------------------------------------------------------------------------------------
void displaySetPixel(uint16_t x, uint16_t y, color_t color)
{

    x=x%DISPLAY_WIDTH;
    y=y%DISPLAY_HEIGHT;
   
    setFRAMEpx(x+y*DISPLAY_WIDTH,color);
}

void displayDrawRectangle(uint16_t width,uint16_t height, color_t line_color, color_t fill_color)
{
  	uint16_t x=0, y=0, x1, y1;
    
    x1=positionX;
    y1=positionY;
 
  	for (x = 0; x<(width+1); x++) 
  	{
		displaySetPixel((x1+x), y1, line_color);
		displaySetPixel((x1+x), y1+height, line_color);
	}
  	
  	for (y = 0; y<(height+1); y++) 
  	{
		displaySetPixel(x1, y1+y, line_color);
		displaySetPixel(x1+width, y1+y, line_color);
	}
    
    for (x = 1; x<(width); x++) 
  	{
        for (y = 1; y<(height); y++) 
        {
            displaySetPixel(x1+x, y1+y, fill_color);
        }
	}
}

void displayDrawCircle(uint16_t radius, color_t line_color, color_t fill_color)
{
	int sw=0, intY=0, intX=0, i;
	uint16_t d, x, y;
  
    x=positionX;
    y=positionY;
	d = y - x;
	intY = radius;
	sw =3-2*radius;
    
	while(intX<=intY) 
	{
        for(i=(y-(uint8_t)intY)+1; i<(y+(uint8_t)intY);i++)
        {
            displaySetPixel(((uint8_t)(x-intX)), i, fill_color);
            displaySetPixel(((uint8_t)(x+intX)), i, fill_color);
        }
            
		displaySetPixel(((uint8_t)(x+intX)), y+(uint8_t)intY, line_color);
		displaySetPixel(((uint8_t)(x+intX)), y-(uint8_t)intY, line_color);
		displaySetPixel(((uint8_t)(x-intX)), y+(uint8_t)intY, line_color);
		displaySetPixel(((uint8_t)(x-intX)), y-(uint8_t)intY, line_color);


        for(i=(y-(uint8_t)intX); i<(y+(uint8_t)intX)+1;i++)
        {   
            displaySetPixel(((uint8_t)(y+intY-d))-1, i, fill_color);    
            displaySetPixel(((uint8_t)(y-intY-d))+1, i, fill_color);
        }
		displaySetPixel(((uint8_t)(y+intY-d)), y+(uint8_t)intX, line_color);
		displaySetPixel(((uint8_t)(y+intY-d)), y-(uint8_t)intX, line_color);
		displaySetPixel(((uint8_t)(y-intY-d)), y+(uint8_t)intX, line_color); 
		displaySetPixel(((uint8_t)(y-intY-d)), y-(uint8_t)intX, line_color);

        
		if(sw<0) sw+=(4*intX+6);
		else 
		{
			sw+=(4*(intX-intY)+10);
			intY--;
		}
		intX++;

	}  
}
//------------------------------------------------------------------------------------------
// DISPLAY IMAGE FUNCTIONS
// displayLoadImage, displayLoadImageSD
//------------------------------------------------------------------------------------------
void displayLoadImage(const image_t img, uint8_t gamma_corrected)
{
    uint16_t x, y, endX, endY;
    uint32_t line, color, y_offset=0, x_offset;
    uint8_t i, bytes, pixels;
    color_t px;

    
    endX=img.width+positionX;
    endY=img.height+positionY;
    if((endX)>DISPLAY_WIDTH)endX=DISPLAY_WIDTH;
    if((endY)>DISPLAY_HEIGHT)endY=DISPLAY_HEIGHT;

    line=positionY*DISPLAY_WIDTH;  
    
    bytes=img.bytes_per_px;
    pixels=img.px_per_bytes-1;
    if(!bytes)bytes=1;

    for(y=positionY;y<endY;y++)
    {
        for(x=positionX;x<endX;x++)
        {
            color=0;
            //get pixel
            x_offset=(x-positionX)*bytes;
            for(i=0;i<bytes;i++)
                color|=img.pixels[(x_offset>>pixels)+y_offset+i]<<(i<<3); 
            if(pixels)color=(color>>((~x_offset&pixels)<<2))&0x0F; //get only nibble 
            //convert to default color format if needed
            if(img.bytes_per_px!=DEFAULT_FORMAT) color=convertRGB(img.bytes_per_px,DEFAULT_FORMAT,color);
            px=color2px(color);
            //gamma correct or not
            if(gamma_corrected)px=gammaCorrected(px);
            //update frame buffer
            setFRAMEpx(x+line,px);
        }
        line+=DISPLAY_WIDTH;
        y_offset+=(img.width)*bytes>>pixels;
    }
}

#if (USE_SD_CARD)
//------------------------------------------------------------------------------------------
uint8_t mountSD(void)
{
   FRESULT res;

   res=f_mount(&myFAT, "", 1);
   if(res==FR_OK) return TRUE;
   else return FALSE;
}

void unmountSD(void)
{
   f_mount(0, 0, 1);
}

void displayLoadImageSD(TCHAR *file_path, uint8_t gamma_corrected)
{
    FIL myFile;
	unsigned int byteCount;

    uint32_t color, line, last_line;
    uint8_t  data[4];
    uint32_t bmp_offset=0, BMP_bpp, n_colors;
    uint32_t y, x, endX, endY,img_width, img_height, x_offset;
    uint8_t i, format, bytes, pixels;
    uint8_t img_line[DISPLAY_WIDTH*4]={0};
    uint8_t color_palette[1024];
    color_t px;
    //open
    f_open(&myFile, file_path, FA_READ);

    //offset
    f_lseek(&myFile, BMP_DIB); 
    f_read(&myFile, &data, 4, &byteCount);
    bmp_offset=((data[3]<<24)|(data[2]<<16) |(data[1]<<8)|(data[0]))+BMP_DIB;

    //get image width
    f_lseek(&myFile, BMP_WIDTH);
    f_read(&myFile, &data, 4, &byteCount);
    img_width=(data[3]<<24)|(data[2]<<16)|(data[1]<<8)|(data[0]);

    //get image height
    f_lseek(&myFile, BMP_HEIGHT);
    f_read(&myFile, &data, 4, &byteCount);
    img_height=(data[3]<<24)|(data[2]<<16)|(data[1]<<8)|(data[0]);

    //get image Bits Per Pixel
    f_lseek(&myFile, BMP_BPP);
    f_read(&myFile, &data, 4, &byteCount);
    BMP_bpp=(data[1]<<8)|(data[0]);
 
    //get num of colors in palette for low bpp
    if(BMP_bpp<=8)
    {
        f_lseek(&myFile, BMP_COLORS);
        f_read(&myFile, &data, 4, &byteCount);
        n_colors=(data[3]<<24)|(data[2]<<16)|(data[1]<<8)|(data[0]);
    }    
    //go to image data
    f_lseek(&myFile, bmp_offset); 
    
    //read color pallete for low bpp
    if(BMP_bpp<=8)
    {
        if(n_colors==0)n_colors=(1<<BMP_bpp);
        f_read(&myFile, &color_palette, 4*n_colors, &byteCount);
        bmp_offset+=4*n_colors;
    }
    
    //Prepare
    format=BMP_bpp>>3;
    bytes=format;
    if(format>3)format=3;
    pixels=0;
    if(!bytes) // 2 pixels per 1 byte 
    { 
      bytes=1;
      pixels=1;  
    }
    
    endX=img_width+positionX;
    endY=img_height+positionY; 
    if((endX)>DISPLAY_WIDTH)endX=DISPLAY_WIDTH;
    if((endY)>DISPLAY_HEIGHT)
    {
        bmp_offset=bmp_offset+(img_width>>pixels)*(endY-DISPLAY_HEIGHT)*bytes;
        f_lseek(&myFile, bmp_offset); 
        endY=DISPLAY_HEIGHT;
    }
  
    line=positionY*DISPLAY_WIDTH;
    last_line=(endY-1)*DISPLAY_WIDTH+line;

    for(y=positionY;y<endY;y++)
    {

        f_read(&myFile, &img_line, (img_width)*bytes>>pixels, &byteCount);

        for(x=positionX;x<endX;x++)
        {
            color=0;
            //get pixel color
            x_offset=(x-positionX)*bytes;
            for(i=0;i<bytes;i++) color|=img_line[(x_offset>>pixels)+i]<<(i<<3);
            if(pixels)color=(color>>((~x_offset&pixels)<<2))&0x0F; //get only nibble 
            //for low bpp get color from color table
            if(BMP_bpp<=8)
            {   
                color=(color_palette[4*color]|(color_palette[4*color+1]<<8)|(color_palette[4*color+2]<<16));
                format=3;
            }
            //convert pixel to default color format if needed
            if(format!=DEFAULT_FORMAT) color=convertRGB(format,DEFAULT_FORMAT,color);
            px=color2px(color);
            //gamma correct if needed 
            if(gamma_corrected)px=gammaCorrected(px);
            //update frame buffer
            setFRAMEpx(x+last_line-line,px);
        }
        line+=DISPLAY_WIDTH;
    }

    //close
    f_close(&myFile);
    
}

void displayPlayImagesSD(TCHAR * file_path, uint16_t time, uint8_t gamma_corrected)
{
	FRESULT res;    
	DIR dir;         
	FILINFO fno;    
    char path[50]={0};

    f_opendir(&dir, file_path);
    for (;;) 
    {
        res = f_readdir(&dir, &fno); 
        if (res != FR_OK || fno.fname[0] == 0) break;

        sprintf((char*)path, "%s/%s",file_path, fno.fname);
        displayLoadImageSD(path, gamma_corrected);
        DELAY(time);
    }
	f_closedir(&dir);  
}
//------------------------------------------------------------------------------------------
#endif

//------------------------------------------------------------------------------------------
// DISPLAY COLOR FUNCTIONS
// RGB, HSV
//------------------------------------------------------------------------------------------
uint32_t RGB(uint8_t r, uint8_t g, uint8_t b)
{	
	return ((r<<16)|(g<<8)|b);
}

uint32_t HSV(uint16_t h, uint8_t s, uint8_t v)
{
    uint8_t r,g,b;

    double hh=h, ss=s, vv=v;
    double rr, gg, bb;
    double  p,q,t;
    double fract;
    
    ss=ss/100;
    vv=vv/100;
    if(hh>=360)hh=0;
    else hh=hh/60;
    fract = hh - floor(hh);


    p = vv*(1. - ss);
    q = vv*(1. - ss*fract);
    t = vv*(1. - ss*(1. - fract));

    if(hh<1)
    {
        rr = vv; 
        gg = t; 
        bb = p;
    }
    else if(hh<2)
    {
        rr = q;
        gg = vv;
        bb = p;
    }
    else if(hh<3)
    {
        rr = p;
        gg = vv;
        bb = t;
    }
    else if(hh<4)
    {
        rr = p;
        gg = q;
        bb = vv;
    }
    else if(hh<5)
    {
        rr = t;
        gg = p;
        bb = vv;
    }
    else if(hh<6)
    {
        rr = vv; 
        gg = p; 
        bb = q;
    }
    else
    {
        rr = 0; 
        gg = 0; 
        bb = 0;
    };

    r=(uint8_t)(rr*255);
    g=(uint8_t)(gg*255);
    b=(uint8_t)(bb*255);
    
    return ((r<<16)|(g<<8)|b); 
    
}
uint32_t convertRGB(const unsigned char src, const unsigned char dst, uint32_t color)
{
    uint8_t r,g,b;
    
    if(src==0)//RGB111
    {
        r=(color>>2)&0x01;
        g=(color>>1)&0x01;
        b=(color&0x01);
        if(dst==1)      return ((r<<7)|(g<<4)|(b<<1));
        else if(dst==2) return ((r<<15)|(g<<10)|(b<<4));
        else if(dst==3) return ((r<<23)|(g<<15)|(b<<7));
        else            return color;
    }
    else if(src==1)//RGB332
    {
        r=(color>>5)&0x07;
        g=(color>>2)&0x07;
        b=(color&0x03);     
        if(dst==0)      return (((r>>2)<<2)|((g>>2)<<1)|(b>>1));
        else if(dst==2) return ((r<<13)|(g<<8)|(b<<3));
        else if(dst==3) return ((r<<21)|(g<<13)|(b<<6));
        else            return color;

    }
    else if(src==2)//RGB565
    {
        r=(color>>11)&0x1F;
        g=(color>>5)&0x3F;
        b=(color&0x1F);   
        if(dst==0)      return (((r>>4)<<2)|((g>>5)<<1)|(b>>4));
        else if(dst==1) return (((r>>2)<<5)|((g>>3)<<2)|(b>>3));
        else if(dst==3) return ((r<<19)|(g<<10)|(b<<3));
        else            return color;  
    }
    else if(src==3)//RGB888
    {
        r=(color>>16)&0xFF;
        g=(color>>8)&0xFF;
        b=(color&0xFF);
        if(dst==0)      return (((r>>7)<<2)|((g>>7)<<1)|(b>>7));
        else if(dst==1) return (((r>>5)<<5)|((g>>5)<<2)|(b>>6));
        else if(dst==2) return (((r>>3)<<11)|((g>>2)<<5)|(b>>3));
        else            return color;
    }
    else return color;         
}
color_t gammaCorrected(color_t color)
{
	uint8_t r,g,b;
 
	r=gamma_curve[rCh(color)&chMask];
	g=gamma_curve[gCh(color)&chMask];
	b=gamma_curve[bCh(color)&chMask];
    
	return color2px(mixCh(r,g,b));
}
//------------------------------------------------------------------------------------------
// DISPLAY DELAY FUNCTIONS
// display_nops, simpleDelay, refreshDelay, displayDelay
//------------------------------------------------------------------------------------------
void delay_nops(uint32_t nops)
{
    while(nops--) NOP();
}
void simpleDelay(uint32_t delay)
{
    while(delay--)
    {
       delay_nops(CLKs);
    }
}
void refreshDelay(uint16_t x_times)
{
    uint16_t i;
    for(i=0;i<x_times;i++)
    {
        refreshDisplay();
    }
}
void displayDelay(uint16_t time)
{
    DELAY(time);
}
//------------------------------------------------------------------------------------------
// END OF DISPLAY FUNCTIONS
//------------------------------------------------------------------------------------------
