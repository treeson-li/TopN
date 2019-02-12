
/*	--------------------------------------------------------------------	*/
/*	this program uses binary sort algorithm to get the top-M values			*/
/*	in the N values. This is quite useful and efficient in the case			*/
/*	that you only need to know the top-M values and do not need to know		*/
/*	the exact sort ranks of them.											*/
/*	All values store in "values" array. "rank" array should be initialized  */
/*	by their original rank number i.e 1,2,3,4,...,N.						*/
/*	the first M values in "rank" array is the index of the top-M values		*/
/*	bAscend indicates which order you need, descending or ascending.		*/
/*	you can just replace all V_TYPE to the value type you want at ease.		*/
/*																			*/
/*	writen by Li Ming				*/
/*	--------------------------------------------------------------------	*/

#include	"stdio.h"
#define		N	17
#define		M	5

#define	V_TYPE	float

V_TYPE	TopOnes(V_TYPE*	values, int* rank, int totalNum, int topNum, bool bAscend);

void	main()
{
	static int	temp[N] = {12,15,10,0,11,1,7,5,14,13,8,3,6,2,4,9,16};
	int		rank[N];
	V_TYPE	values[N], top_Mth_value;
	int		i;

	for (i = 0; i < N; i++)
	{
		rank[i] = i;
		values[i] = (V_TYPE)temp[i];
		printf("%1.0f ",values[i]);
	}
	printf("\n");

	top_Mth_value = TopOnes(values, rank, N, M, true);//false//true means getting minimum values
	printf("Top values : ");
	for (i = 0; i < M; i++)
	{
		printf("%1.0f ",values[rank[i]]);
	}
	printf("\n");
	printf("Top index  : ");
	for (i = 0; i < M; i++)
	{
		printf("%d ",rank[i]);
	}
	printf("\n");
	printf("the %dth topest value is %2.0f\n", M, top_Mth_value);
	printf("\n");
}


V_TYPE	TopOnes(V_TYPE*	values, int* rank, int totalNum, int topNum, bool bAscend)
{
	int		*no, *resultNo;
	int		i,j,k;
	int		begin,end,p;
	V_TYPE	mid;

	no = new int[totalNum];
	resultNo = new int[totalNum];

	for (k = 0; k < totalNum; k++)
	{
		no[k] = rank[k];
	}

	begin = 0;
	end   = totalNum - 1;

	while ( end != topNum - 1)
	{
		i = begin;
		j = end;
		p = begin;

		mid = values[no[p]];
		p++;

		while (p <= end)
		{
			if (bAscend == true)
			{
				if (values[no[p]] > mid)
				{
					resultNo[j] = no[p];
					j--;
				}
				else
				{
					resultNo[i] = no[p];
					i++;
				}
				p++;
			}
			else
			{
				if (values[no[p]] < mid)
				{
					resultNo[j] = no[p];
					j--;
				}
				else
				{
					resultNo[i] = no[p];
					i++;
				}
				p++;
			}
		}
		resultNo[i] = no[begin];

		for (k = begin; k <= end; k++)
			no[k] = resultNo[k];

		if (i < topNum - 1)
			begin = i + 1;
		else if (i > topNum - 1)
			end = i - 1;
		else
			end = i;
		/*
		for (k = 0; k < totalNum; k++)
		{
			if (k != i)
				printf("%2.0f ",values[no[k]]);
			else
				printf("%2.0f[] ",values[no[k]]);
		}
		printf("\n");
		*/
	}

	if (mid != values[no[topNum-1]])
	{
		mid = values[no[0]];
		for (k = 1; k < topNum; k++)
			if (bAscend == true)
			{
				if (mid < values[no[k]])
					mid = values[no[k]];
			}
			else
			{
				if (mid > values[no[k]])
					mid = values[no[k]];
			}
	}

	for (k = 0; k < topNum; k++)
		rank[k] = no[k];
//	printf("mid = %3.0f\n", mid);

	delete[]  no;
	delete[]  resultNo;

	return	mid;
}
