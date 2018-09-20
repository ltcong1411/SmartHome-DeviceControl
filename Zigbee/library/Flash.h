////////////////////////////////////////////////////////////////////
// THU VIEN DINH NGHIA CAC HAM XU LY FLASH MEMORY
// VIET BOI : PHAM VAN THUAN	DTVT07-K55
// Version : 1.0	14/10/2014
// Email:	phthuanbk55@gmail.com
// Blog :	http://thuanbk55.blogspot.com/
// .................................................................
// MSP430x2xx LIBRARY
//******************************************************************/

#ifndef FLASH_H_
#define FLASH_H_

// Luu y: Het suc can than khi ghi du lieu vao
// SegmentA vi no chua gia tri Calib_Clock co the lam
// sai xung dong ho DCO
typedef enum {	SegmentA,
				SegmentB,
				SegmentC,
				SegmentD
				}Segment;

void Init_Flash();	//Khoi tao tan so hoat dong cua Flash
//Ghi bien "var" vao segment o vi tri position
void Flash_Write_Byte(Segment seg,  unsigned char var, unsigned char position);
void Flash_Read_Byte(Segment seg, unsigned char *var, unsigned char position);
//Ghi 1 khoi du lieu vao flash,yeu cau khong duoc ghi qua segment (position+numb<64)
void Flash_Write_Block(Segment seg, unsigned char *var,unsigned char position,unsigned char numb);
void Flash_Read_Block(Segment seg, unsigned char *var,unsigned char position,unsigned char numb);

/******************************************************************************\
*					Function (noi dung ham)	                           *
\******************************************************************************/
void Init_Flash()
{
	FCTL2 = FWKEY + FSSEL0 + FN0;
	// FNx : MCLK/3 for Flash Timing Generator
	// fFTG = 257kHz ->476kHz
}
void Flash_Write_Byte(Segment seg, unsigned char var, unsigned char position)
{
    unsigned char *Flash_ptr;                          // Flash pointer
    unsigned char i=0;
    unsigned char Data_temp[64];		//Ghi 64 byte cua segment ra truoc
    switch(seg)
    {
    	case SegmentA: Flash_ptr = (unsigned char *) 0x10C0;break;    	// Initialize Flash segment A pointer
    	case SegmentB: Flash_ptr = (unsigned char *) 0x1080;break;    	// Initialize Flash segment B pointer
    	case SegmentC: Flash_ptr = (unsigned char *) 0x1040;break;     	// Initialize Flash segment C pointer
    	case SegmentD: Flash_ptr = (unsigned char *) 0x1000;break;     	// Initialize Flash segment D pointer
    }

    for(i=0;i<64;i++)    Data_temp[i]= *Flash_ptr++; // copy value segment C to variable

    switch(seg)
	{
		case SegmentA: Flash_ptr = (unsigned char *) 0x10C0;break;     	// Initialize Flash segment A pointer
		case SegmentB: Flash_ptr = (unsigned char *) 0x1080;break;    	// Initialize Flash segment B pointer
		case SegmentC: Flash_ptr = (unsigned char *) 0x1040;break;   	// Initialize Flash segment C pointer
		case SegmentD: Flash_ptr = (unsigned char *) 0x1000;break;    	// Initialize Flash segment D pointer
	}
    FCTL1 = FWKEY +ERASE;                    // Set Erase bit
    FCTL3 = FWKEY;                           // Clear Lock bit
    *Flash_ptr = 0;                          // Dummy write to erase Flash segment

    while(FCTL3&BUSY);						//Wait for complete erase
    FCTL1 = FWKEY + WRT;                     // Set WRT bit for write operation

    for(i=0;i<64;i++)
    {
    	if(i==position)*Flash_ptr++ =var;
    	else *Flash_ptr++ = Data_temp[i];  // Write value to flash
    	while(!(FCTL3&WAIT));						//Wait for complete erase
	}
    FCTL1 = FWKEY;                            // Clear WRT bit
    while(FCTL3&BUSY);						//Wait for complete erase
    FCTL3 = FWKEY + LOCK +LOCKA;                    // Set LOCK bit
}

//Chu+?c na(ng: ?o?c biê?n var tu+? ô nho+? position trong segment C
void Flash_Read_Byte(Segment seg, unsigned char *var, unsigned char position)
{
      unsigned char *Flash_ptr;                        // Segment C pointer
      switch(seg)
      {
      	case SegmentA: Flash_ptr = (unsigned char *) 0x10C0;break;     	// Initialize Flash segment A pointer
      	case SegmentB: Flash_ptr = (unsigned char *) 0x1080;break;     	// Initialize Flash segment B pointer
      	case SegmentC: Flash_ptr = (unsigned char *) 0x1040;break;     	// Initialize Flash segment C pointer
      	case SegmentD: Flash_ptr = (unsigned char *) 0x1000;break;    	// Initialize Flash segment D pointer
      }
      Flash_ptr +=  position;                    // Jump to desired address
      *var = *Flash_ptr;          // copy value segment C to variable
}
//Ghi 1 khoi du lieu vao flash,yeu cau khong duoc ghi qua segment (position+numb<64)
void Flash_Write_Block(Segment seg, unsigned char *var,unsigned char position,unsigned char numb)
{
    unsigned char *Flash_ptr;                          // Flash pointer
    unsigned char i=0;
    unsigned char Data_temp[64];		//Ghi 64 byte cua segment ra truoc
    switch(seg)
    {
    	case SegmentA: Flash_ptr = (unsigned char *) 0x10C0;break;     	// Initialize Flash segment A pointer
    	case SegmentB: Flash_ptr = (unsigned char *) 0x1080;break;    	// Initialize Flash segment B pointer
    	case SegmentC: Flash_ptr = (unsigned char *) 0x1040;break;    	// Initialize Flash segment C pointer
    	case SegmentD: Flash_ptr = (unsigned char *) 0x1000;break;     	// Initialize Flash segment D pointer
    }

    for(i=0;i<64;i++)    Data_temp[i]= *Flash_ptr++; // copy value segment C to variable

    switch(seg)
	{
		case SegmentA: Flash_ptr = (unsigned char *) 0x10C0;break;    	// Initialize Flash segment A pointer
		case SegmentB: Flash_ptr = (unsigned char *) 0x1080;break;    	// Initialize Flash segment B pointer
		case SegmentC: Flash_ptr = (unsigned char *) 0x1040;break;     	// Initialize Flash segment C pointer
		case SegmentD: Flash_ptr = (unsigned char *) 0x1000;break;  	// Initialize Flash segment D pointer
	}
    FCTL1 = FWKEY +ERASE;                    // Set Erase bit
    FCTL3 = FWKEY;                           // Clear Lock bit
    *Flash_ptr = 0;                          // Dummy write to erase Flash segment

    while(FCTL3&BUSY);						//Wait for complete erase
    FCTL1 = FWKEY + WRT;                     // Set WRT bit for write operation

    for(i=0;i<64;i++)
    {
    	if((i>=position)&&(numb>0))
    		{
    			*Flash_ptr++ =*var;
    			var++;
    			numb--;
    		}
    	else *Flash_ptr++ = Data_temp[i];  // Write value to flash
    	while(!(FCTL3&WAIT));						//Wait for complete erase
	}
    FCTL1 = FWKEY;                            // Clear WRT bit
    while(FCTL3&BUSY);						//Wait for complete erase
    FCTL3 = FWKEY + LOCK +LOCKA;                    // Set LOCK bit
}
void Flash_Read_Block(Segment seg, unsigned char *var,unsigned char position,unsigned char numb)
{
    unsigned char *Flash_ptr;                        // Segment C pointer
    switch(seg)
    {
    	case SegmentA: Flash_ptr = (unsigned char *) 0x10C0;break;     	// Initialize Flash segment A pointer
    	case SegmentB: Flash_ptr = (unsigned char *) 0x1080;break;     	// Initialize Flash segment B pointer
    	case SegmentC: Flash_ptr = (unsigned char *) 0x1040;break;     	// Initialize Flash segment C pointer
    	case SegmentD: Flash_ptr = (unsigned char *) 0x1000;break;     	// Initialize Flash segment D pointer
    }
    Flash_ptr +=  position;                    // Jump to desired address
    while(numb>0)
    {
    	*var = *Flash_ptr;          // copy value segment C to variable
    	var++;
    	Flash_ptr++;
    	numb--;
    }
}
#endif /* FLASH_H_ */
