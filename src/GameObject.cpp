#include "GameObject.h"
//Imprime en hezadecimal el UID md5 del objeto
void GameObject::PrintUID()
{
	printf("%s : ", name.c_str() );
	for (int i = 0; i < 16; i++)
	{
		printf( "%02X", uid[i]);
	}
	printf("\n");
}
