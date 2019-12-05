
const unsigned char a = 10;
const unsigned char b = 11;
const unsigned char c = 12;
const unsigned char d = 13;

const unsigned char Room1_1[] =
{
8,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,
9,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,
9,9,10,10,10,10,10,10,10,10,10,10,10,10,10,10,
1,1,7,7,1,7,1,7,1,7,1,7,7,1,7,1,
2,2,7,7,2,7,2,7,2,7,2,7,7,2,7,2,
3,3,7,7,3,7,3,7,3,7,3,7,7,3,7,3,
4,4,7,7,4,7,4,7,4,7,4,7,7,4,7,4,
4,4,7,7,4,7,4,7,4,7,4,7,7,4,7,4,
4,4,7,7,4,7,4,7,4,7,4,7,7,4,7,4,
4,4,7,7,4,7,4,7,4,7,4,7,7,4,7,4,
4,4,7,7,4,7,6,6,6,6,6,6,6,4,7,4,
6,6,6,6,6,6,6,5,5,5,5,5,6,6,6,6,
5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
};

const unsigned char Room1_2[] =
{
13,13,13,13,12,12,0,0,0,0,0,0,0,0,0,0,
13,13,13,13,11,11,0,0,0,0,0,0,0,0,0,0,
10,10,10,11,11,0,0,0,0,0,0,0,0,0,0,0,
7,1,1,7,1,1,1,1,1,1,1,1,1,1,1,1,
7,2,2,7,2,2,2,2,2,2,2,2,2,2,2,2,
7,3,3,7,3,3,3,3,3,3,3,3,3,3,3,3,
7,4,4,7,4,4,4,4,4,4,4,4,4,4,4,4,
7,4,4,7,4,4,4,4,4,6,6,6,6,6,6,4,
7,4,4,7,4,4,4,4,6,6,5,5,5,5,6,6,
7,4,4,7,4,4,4,6,6,5,5,5,5,5,5,5,
7,4,4,7,4,6,6,6,5,5,5,5,5,5,5,5,
6,6,6,6,6,6,6,5,5,5,5,5,5,5,5,5,
5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
};

const unsigned char Room1_3[] =
{
0,0,0,8,8,13,13,13,13,13,13,13,13,13,13,13,
0,0,0,9,9,13,13,13,13,13,13,13,13,13,13,13,
0,0,0,0,9,9,10,10,10,10,10,10,10,10,10,10,
1,1,1,1,1,7,1,7,7,1,7,1,1,7,7,1,
2,2,2,2,2,7,2,7,7,2,7,2,2,7,7,2,
3,3,3,3,3,7,3,7,7,3,7,3,3,7,7,3,
4,4,4,4,4,7,4,7,7,4,7,4,4,7,7,4,
4,4,4,4,4,7,4,7,7,4,7,4,4,7,7,4,
6,6,6,6,4,7,4,7,7,4,7,4,4,7,7,4,
5,5,5,6,6,7,4,7,7,4,7,4,4,7,7,4,
5,5,5,5,6,6,6,7,7,4,7,4,6,6,6,6,
5,5,5,5,5,5,6,6,6,6,7,4,6,5,5,5,
5,5,5,5,5,5,5,5,5,6,6,6,6,5,5,5,
5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
};

const unsigned char Room1_4[] =
{
13,12,12,0,0,0,0,0,0,0,0,0,6,6,6,6,
13,12,11,0,0,0,0,0,0,0,0,0,0,0,0,0,
11,11,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
2,2,2,2,2,2,2,2,2,2,2,2,6,6,6,6,
3,3,3,3,3,3,3,3,3,6,6,3,3,3,3,3,
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,6,6,4,4,4,4,4,4,4,
4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
6,6,6,6,6,4,4,4,4,4,4,4,4,4,4,4,
5,5,5,5,5,4,4,4,4,4,4,4,4,4,4,4,
5,5,5,5,5,4,4,4,4,4,4,4,4,4,4,4,
5,5,5,5,5,4,4,4,4,4,4,4,4,4,4,4,
5,5,5,5,5,4,4,4,4,4,4,4,4,4,4,4,
5,5,5,5,5,4,4,4,4,4,4,4,4,4,4,4,
};