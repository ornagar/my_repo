#include <stdio.h>
#include <stdlib.h>					/* malloc()			 */

#include "../utils/stack.h"

int HasBrackets(char *str);

int main()
{
	char *str = "{()(fd(())){()}(){sd}{}()}(){()(){()()}()}(fds){()(()()(sdf))}(){()}";

	printf("%d\n", HasBrackets(str));
	
	return (1);
}

int HasBrackets(char *str)
{
	stack_t *open_brac = StackCreate(50, 1);
	
	while ('\0' != *str)
	{
		if ('[' == *str || '{' == *str || '(' == *str)
		{
			StackPush(open_brac, str);
		}
		else if (']' == *str || '}' == *str || ')' == *str)
		{
			if ((*str == ']' && *(char *)StackPeek(open_brac) == '[') ||
				(*str == ')' && *(char *)StackPeek(open_brac) == '(') ||
				(*str == '}' && *(char *)StackPeek(open_brac) == '{'))
			{
				StackPop(open_brac);
			}
			else
			{
				return(0);
			}
		}
		
		++str;
	}
	
	return (1);

}
