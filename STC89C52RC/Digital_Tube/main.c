// 共阳数码管

#include <REGX52.H>

unsigned char NixieTable[] = 
	{	
	0xC0, 
	0xF9, 0xA4, 0xB0, 
	0x99, 0x92, 0x82, 
	0xF8, 0x80, 0x90
	};
	// 共阳极
	// 0
	// 1 2 3
	// 4 5 6
	// 7 8 9

void Delay1ms(unsigned int xms)		//@12.000MHz
{
	unsigned char i, j;
	do
	{
		i = 2;
		j = 239;
		do
		{
			while (--j);
		} while (--i);
	}while (--xms);
}
	
void Nixie1(unsigned char Location, unsigned char Number)   // 点亮数码管
{
	while (1)
	{
		/* 
		// WE使能 1为接通使能，不通电   0通电
		P2_0 = 1;  // WE1 ~ WE4 
		P2_1 = 1;  
		P2_2 = 0;
		P2_3 = 1;
		*/ 
		
		switch (Location)
		{
			case 1:
				P2_0 = 0;
				break;
			case 2:
				P2_1 = 0;
				break;
			case 3:
				P2_2 = 0;
				break;
			case 4:
				P2_3 = 0;
				break;
			default:
				P2_0 = P2_1 = P2_2 = P2_3 = 0;
				break;
				
		}
		
		/* // 共阳：1熄灭 0点亮  例：6 -> 1000 0010 -> 0x82
		P0_0 = 0;   // a   
		P0_1 = 1;   // b
		P0_2 = 0;   // c
		P0_3 = 0;   // d
		P0_4 = 0;   // e
		P0_5 = 0;   // f
		P0_6 = 0;   // g
		P0_7 = 1;   // dp
		*/
		//P0 = 0x82;
		P0 = NixieTable[Number];
	}
}

void Nixie2(unsigned char Location, unsigned char Number)  // 点亮数码管(消影版)
{
	switch (Location)
	{
		case 1:
			P2_0 = 0;
			break;
		case 2:
			P2_1 = 0;
			break;
		case 3:
			P2_2 = 0;
			break;
		case 4:
			P2_3 = 0;
			break;
		default:
			P2_0 = P2_1 = P2_2 = P2_3 = 0;
			break;	
	}
	P0 = NixieTable[Number];
	
	Delay1ms(1);
	P0 = 0xFF;  // 清零， 为了消影
	P2_0 = P2_1 = P2_2 = P2_3 = 1;   // 清零

}

void NixieNum4(unsigned int Number) // 数码管闪烁
{
	unsigned char Num1, Num2, Num3, Num4;
	
	if (Number >= 10000)  // 4位
	{
		Number = Number % 10000;
	}		
	
	Num1 = (Number / 1000) % 10;
	Num2 = (Number / 100) % 10;
	Num3 = (Number / 10) % 10;
	Num4 = Number % 10;
	
	while(1)
	{
		if (Num1)  // 1234
		{
			Nixie2(1, Num1);  // 1
		}
		
		if (Num2)
		{
			Nixie2(2, Num2);  // 2
		}
		
		if (Num3)
		{
			Nixie2(3, Num3);  // 3
		}
		
		if (Num4)
		{
			Nixie2(4, Num4);  // 4
		}
	}

}

void NixieNum()
{
	while (1)
	{

	Nixie2(1, 1);
	
	Nixie2(2, 3);

	Nixie2(3, 5);
	
	Nixie2(4, 7);

	}
}

void main()
{

	//Nixie1(3, 6);  // 点亮数码管
	
	//NixieNum();
	NixieNum4(12345); // 4位数码管闪烁 2345  

		
	
	
}