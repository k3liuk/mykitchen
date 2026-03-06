#ifndef __GLIB_H__
#define __GLIB_H__

#define     RGB(r,g,b)   (unsigned int)( (r << 16) + (g << 8) + b )

#define   COLOR_BLACK                RGB(0,   0,   0)    
#define   COLOR_NAVY                 RGB(0,   0, 127 )   
#define   COLOR_DGREEN               RGB(0,  127,  0  )  
#define   COLOR_DCYAN                RGB(0,  127, 127 )  
#define   COLOR_MAROON               RGB(127,   0,   0)  
#define   COLOR_PURPLE               RGB(127,   0, 127 ) 
#define   COLOR_OLIVE                RGB(127, 127,   0 ) 
#define   COLOR_LGRAY                RGB(192, 192, 192 ) 
#define   COLOR_DGRAY                RGB(127, 127, 127 ) 
#define   COLOR_BLUE                 RGB(0,   0, 255   ) 
#define   COLOR_GREEN                RGB(0, 255,   0   ) 
#define   COLOR_CYAN                 RGB(0, 255, 255   ) 
#define   COLOR_RED                  RGB(255,   0,   0  )
#define   COLOR_MAGENTA              RGB(255,   0, 255 ) 
#define   COLOR_YELLOW               RGB(255, 255, 0    )
#define   COLOR_WHITE                RGB(255, 255, 255 ) 

void PutPixel(int x,int y,int c);
void DrawLine(int x1,int y1,int x2,int y2,int color  );
void DrawHLine(int x1,int x2,int y,int color);
void DrawVLine(int y1,int y2,int x,int color);
void Rectangle(int x1,int y1,int x2,int y2,int color  );
void FilledRectangle(int x1,int y1,int x2,int y2,int color  );
void Circle(unsigned int x0,unsigned int y0,unsigned int r,int color  );	//»­Ô²
void Fill_Circle(int x0,int y0,int r0,int color  );	//»­Ìî³äÔ²

short changecolor_from_24bit_to_16bit(int color);
void lineto(int x0,int y0,int x1,int y1,int linetype,int pensize,int color  );
void Rectangle_3D(int x,int y,int nx,int ny,int mx,int my,int color  );
void aabks(int x,int y,int nx,int ny,int fir_color,int xy  );
void Glib_Line_Pensize(int x0,int y0,int x1,int y1,int color,int pensize);
void Glib_DASHLine_Pensize(int x0,int y0,int x1,int y1,int color,int pensize);


#endif //__GLIB_H__
//
