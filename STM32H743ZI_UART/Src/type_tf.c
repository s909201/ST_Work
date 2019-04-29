/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
FileName: type_tf.c
ProjectName:
FunctionDesc:
CreateDate:
Version:
Author: Morgan

ModifyHistory:	2019'04'19
Remark:
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/
#include "typedef.h"
#include "type_tf.h"
//---------------------------------------------------------------
const unsigned char CharacterArray[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

//---------------------------------------------------------------
// eg: 35 = 0x23; --> '2' '3'
void U8ToStr(u8 *Str, u8 val)
{
    unsigned char PRINT_VAR;
    PRINT_VAR = val;
    val = (val>>4)&0x0F;
	*Str = CharacterArray[val];
	
    val = (PRINT_VAR)&0x0F;
	*(Str+1) = CharacterArray[val];
}
//---------------------------------------------------------------
// 2015'9'3, add for MODBUS
// eg: 12 -> 'C', 10 -> 'A', 5 -> '5'
u8 U8ToASCII(u8 v)
{
	return CharacterArray[v];
}
// --------------------------------------------------------------
// eg: '0'~'9' -> 0~9 , 'A' -> 10, 'B'-> 11
u8 ASCIIToU8(u8 a)		// ASCII to u8
{
	if( a < 0x3A){
		return (a - '0');	// '0': 0x30
	}else{
		return (a - 55);	// 'A': 0x41, 0x41 -> 10 = 65 - 10 = 55
	}
}
// --------------------------------------------------------------
void StrCopy(u8* dist, u8* from, u16 len)
{
	u16	i;
	for(i=0;i<len;i++){
		*(dist+i)=*(from+i);
	}
}
//---------------------------------------------------------------

//---------------------------------------------------------------
void U8ToDecStr(u8 *Str, u8 val)
{
	*Str = (val/100) + '0';
	*(Str+1) = ((val%100)/10) + '0';
	*(Str+2) = (val%10) + '0';	
}
// --------------------------------------------------------------
void VoltageToDecStr(u8 *Str, float val)
{
	*Str = (u8)(val/100) + '0';
	if(*Str == '0'){
		*Str = ' ';
	}
	
	*(Str+1) = ((u8)val%100)/10 + '0';
	if( (*Str == ' ') && (*(Str+1) == '0') ){
		*(Str+1) = ' ';
	}
	*(Str+2) = ((u8)val%10) + '0';
	*(Str+3) = '.';
	*(Str+4) = ((u8)(val*10)%10) + '0';
}
// --------------------------------------------------------------
// 2017'3'8, 5 bytes
void U16ToDecStr(u8 *Str, u8* val)
{
	u16 sum;
	sum = *(val+1)*256 + *val;
	
	*Str = (u8)(sum/10000) + '0';
	*(Str+1) = (u8)((sum%10000)/1000) + '0';
	*(Str+2) = (u8)((sum%1000)/100) + '0';
	*(Str+3) = (u8)((sum%100)/10) + '0';
	*(Str+4) = (u8)(sum%10) + '0';
	
}
// --------------------------------------------------------------
u32 FourByteToU32(u8* str)
{
	u8 val[4],i;
	for(i=0;i<4;i++){
		
		if( (*(str + i) >= '0') && (*(str + i) <= '9') ){		// Normal
			val[i] = *(str + i) - 0x30;
		}else{
			val[i] = 9;		// for safety
		}
		
	}
	
	return ( (u32)((u32)val[0]*(u32)1000) + ((u32)val[1]*(u32)100) + ((u32)val[2]*(u32)10) + (u32)val[3]);
}
// --------------------------------------------------------------
// ASCII String to Byte, e.g. "172" => 172
u8 ASCIIStringToByte(u8 *str, u8 len)
{
	u8 val;
	switch(len){
				
		case 3:
				val = ASCIIToU8(*(str)) * 100 + ASCIIToU8(*(str + 1)) * 10 + ASCIIToU8(*(str + 2));
				break;
				
		case 2:
				val = ASCIIToU8(*(str)) * 10 + ASCIIToU8(*(str + 1));
				break;
				
		case 1:
				val = ASCIIToU8(*(str));
				break;
				
	}
	return val;
}
// --------------------------------------------------------------

// --------------------------------------------------------------
// Usage Example: 
// StrCopy(&tmpStr[0], (u8*)"172.160.142.129", 15);
// IPtoFourByte(&tmpStr[0], 15, &IPNum[0]);
// Result: IPNum[]
void IPtoFourByte(u8* str, u8 len, u8 *IP)
{
	u8 i,j,dot[5];
	u8 tmp[4];
	u8 NumLen2[4];
	// cc(str,len);
	
	// initial condition
	dot[0] = 0;
	dot[4] = len;
	j=1;
	for(i=0; i< len;i++){
		if( *(str + i) == '.'){
			dot[j++] = i;	// from [1]
		}
	}
	
	// boundary issue
	NumLen2[0] = dot[1];
	
	// StrCopy(&tmp[0], &str[0], NumLen2[0] );
	for(i=0; i< NumLen2[0];i++){
		tmp[i] = str[i];
	}
	
	*IP = ASCIIStringToByte(tmp,(u8)NumLen2[0]);
	
	// ex: IP= 172.17.42.29
	for(i=1;i<4;i++){
		NumLen2[i] = dot[i+1] - dot[i]-1;
		// StrCopy(&tmp[0], &str[ dot[i]+1], NumLen2[i] );
		for(j=0; j< NumLen2[i];j++){
			tmp[j] = str[ dot[i] + 1 ];
		}
		
		*(IP+i) = ASCIIStringToByte(tmp,(u8)NumLen2[i]);
	}
	
}
// --------------------------------------------------------------

// --------------------------------------------------------------
u8 DectoBCD(u8 v)
{
	u8 y;
	y = (v/10)*16 + (v%10);
	return y;
}
// --------------------------------------------------------------
u8 BCDtoDec(u8 v)
{
	u8 y;
	y = (v>>4)*10 + (v&0x0F);
	return y;
}
// --------------------------------------------------------------


