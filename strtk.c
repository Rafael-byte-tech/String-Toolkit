#include <stdlib.h>
#include <stdio.h>
#define MAXC 475000
#define MAXW 95000
/*------------------------------------------------------------------------------------------------------------------*/
/*Funcao recebe 2 strings como parametro e copia o conteudo da original para a clone.*/
void strcln(char *clone, char *original)
{
	/*operacoes*/
	*clone = *original;
	
	while (*original != '\0')
	{
		
		clone += 1;
		original += 1;
	
		*clone = *original;
		
	}
}/*Fim da funcao*/
/*------------------------------------------------------------------------------------------------------------------*/
/*Funcao recebe string como parametro e retorna seu comprimento.*/
unsigned int strln(char *str)
{
	/*declaracao de variaveis*/
	unsigned int len;
	
	/*instacimento de variaveis*/
	len = 0;
	
	/*operacoes*/
	while(*str != '\0')
	{
		str += 1;
		len += 1;
	}
	
	return len;
}/*Fim da funcao*/
/*------------------------------------------------------------------------------------------------------------------*/
/*Funcao recebe 2 strings como parametro. Retorna 0 para diferentes ou 1 para iguais*/
short unsigned int iseq(char *str1, char *str2)
{
	/*declaracao de variaveis*/
	unsigned int len1, len2;
	
	/*instanciamento de variaveis*/
	len1 = strln(str1);
	len2 = strln(str2);
	
	/*operacoes*/
	if (len1 != len2)
	{
		return 0;
	}
	
	for (int i=0; i<len1; i++)
	{
		if (*str1 != *str2)
		{	
			return 0;
		}
		
		str1 += 1;
		str2 += 1;
	}
	
	return 1;
}/*Fim da funcao*/
/*-------------------------------------------------------------------------------------------------------------------*/
/*Funcao auxiliar da funcao strdiv(). Verifica se um segmento de "str" eh igual a string "divider".
  Parametros: string (str); string que delimita a divisao (divider); comprimento de divider (dividerLen); index (i)*/
short unsigned int isdiv(char *str, char *divider, int dividerLen, int i)
{
	/*declaracao de variaveis*/
	unsigned int j;	/*itera divider*/
	
	/*instanciamento de variaveis*/
	j = 0;			
	
	/*operacoes*/
	while (str[i] == divider[j] && str[i] != '\0')
	{		
		i++;
		j++;	
	}
	
	if (j == dividerLen)	/*todos os caracters do segmento de "str" e "divider" sao iguais*/
	{
		return 1;			/*flag para igual*/	
	}
	
	else
	{
		return 0;			/*flag para diferente*/	
	}
}

/*Funcao auxiliar de strdiv. Guarda os tokens adquiridos em strdiv em um array de tokens.
  Parametros: array de strings (tokenArray); buffer de chars; contador de tokens (tokCounter); 
			  array de comprimentos dos tokens (tokLens)*/
void tokarr(char **tokens, char *buffer, unsigned int *tokCounter, unsigned int *tokLens)
{
	/*declaracao de variaveis*/
	char *token;						/*string que serah armazenada no array de strings "tokenArray"*/
	int k;								/*Itera buffer*/
	
	/*inicializacao de variaveis*/
	k = 0;			
	token = "\0";
	
	/*Itera cada posicao do array de strings*/
	for (int i=0; i<*tokCounter; i++)
	{
		/*Aloca memoria para string"*/
		tokens[i] = (char *)malloc (tokLens[i] * sizeof (char));
		token = (char *)malloc (tokLens[i] * sizeof (char));
		
		/*Itera cada posicao do array "token"*/
		for (int j=0; j<(tokLens[i]); j++)
		{		
			if (buffer[k] != '\n')	/*Impede que token contenha '\n'*/
			{
				token[j] = buffer[k];
			}
			k++;							
		}
		
		strcln(tokens[i], token);		/*copia string de token para tokenArray[i]*/
		tokens[i][tokLens[i]] = '\0';	/*posiciona \0 ao final do array de chars*/
	}
	
	free(token);						/*desaloca memoria*/
}

/*Funcao divide string em tokens usando outra string como delimitadora
  Parametros: string (str); string delimitadora (divider); numero de tokens (tokCounter)*/

char **strdiv(char *str, char *divider, unsigned int *tokCounter)
{
	/*declaracao de variaveis*/
	char **tokens, *buffer;                   				 
	unsigned int strLen, dividerLen, bufLen, *tokLens, i;
	
	/*instanciamento de variaveis*/
	tokLens = (unsigned int *)malloc (MAXW * sizeof(unsigned int));
	buffer = (char *)malloc (MAXC * sizeof(char));
		
	strLen = strln(str);
	dividerLen = strln(divider);
	
	bufLen = 0;
	*tokCounter = 0;
	
	tokLens[*tokCounter] = 0;	/*insere 0 no endereco alocado em "tokLens", caso ele seja usado*/
			
	i = 0;
	
	/*operacoes*/
	while (i < strLen)			/*itera "str" enquanto "i" for menor que o comprimento de "str" (strLen)*/
	{
		/*o buffer armazena todos os chars que estao entre os delimitadores (divider)*/
		if (str[i] != divider[0] || isdiv(str, divider, dividerLen, i) == 0)
		{		
			buffer[bufLen] = str[i];							/*buffer recebe char*/
			bufLen++;											/*incrementa comprimento do buffer*/
			
			tokLens[*tokCounter] += 1;							/*incrementa comprimento do token*/	
		}
		
		/*segmento de chars "[i][i + 1]...[i + dividerLen]" estah em "divider"*/
		else 
		{
			i += (dividerLen - 1);								/*i pula o segmento igual a "divider"*/
			
			/*"divider" nao estah no inicio ou fim de "str"*/
			if ((i + 1) != dividerLen && (i + 1) != strLen)
			{		
				*tokCounter += 1;								/*incrementa o contador de tokens*/
				 tokLens[*tokCounter] = 0;		
			}
		}
		
		i++;													/*incrementa i*/
	}
	
	*tokCounter += 1;											/*(tokCounter + 1) -> numero de tokens*/
	
	tokens = (char **)malloc (*tokCounter * sizeof (char*));	/*aloca memoria para array de strings*/
	
	tokarr(tokens, buffer, tokCounter, tokLens);				/*insere tokens no array de strings*/
	
	free(buffer);												/*libera buffer*/
	free(tokLens);
			
	return tokens;												/*retorna tokens de "str"*/
}/*Fim da funcao*/
/*------------------------------------------------------------------------------------------------------------------*/
/* Teste para funcao strdiv
	printf("\nbuffer: %s\nbuffer size: %d\ntokens: %d\n", buffer, bufLen, *tokCounter);
	
	for (int k=0; k<*tokCounter; k++)
	{
		
		printf("token(%d) size: %d\n", k, tokLens[k]);
		
	}
*/

/*-------------------------------------------------------------------------------------------------------------------*/