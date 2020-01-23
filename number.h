#define DIGIT 115
#define RADIX 1000000000
#define DISPRAD "        0"

struct NUMBER{
    int n[DIGIT];
    int sign;
};
struct FLOAT{
    struct NUMBER n;
    int exp;
};

void clearByZeroInt(struct NUMBER *);
void clearByZeroFloat(struct FLOAT *);
void dispNumberInt(struct NUMBER *);
void dispNumberFloat(struct FLOAT *);
void dispNumberFloatforCopy(struct FLOAT *);
void copyNumberInt(struct NUMBER *, struct NUMBER *);
void copyNumberFloat(struct FLOAT *, struct FLOAT *);
void getAbsInt(struct NUMBER *,struct NUMBER *);
void getAbsFloat(struct FLOAT *,struct FLOAT *);
int isZeroInt(struct NUMBER *);
int isZeroFloat(struct FLOAT *);
int mulByRadInt(struct NUMBER *,struct NUMBER *);
int mulByNInt(struct NUMBER *,struct NUMBER *, int );
int divByRadInt(struct NUMBER *,struct NUMBER *);
int divByNInt(struct NUMBER *,struct NUMBER *, int, struct NUMBER *);
int setInt(struct NUMBER *, int, int);
int setRandomInt(struct NUMBER * , int);
int setRandomFloat(struct FLOAT *, int, int);
int getIntToString(struct NUMBER*,char *);
int getDigitInt(struct NUMBER*);
int getDigitDecimal(struct FLOAT*);
int getExp(struct FLOAT *);
void setExp(struct FLOAT *, int);
int clearByZeroDecimal(struct FLOAT*, struct FLOAT *);
void swapInt(struct NUMBER *, struct NUMBER *);
int setSignInt(struct NUMBER *,int);
int getSignInt(struct NUMBER *);
int numCompInt(struct NUMBER *,struct NUMBER *);
int numCompFloat(struct FLOAT *,struct FLOAT *);
int addInt(struct  NUMBER *, struct NUMBER *, struct NUMBER *, int *);
int addFloat(struct  FLOAT *, struct FLOAT *, struct FLOAT *);
int subInt(struct NUMBER * ,struct NUMBER *, struct NUMBER *, int *);
int subFloat(struct FLOAT * ,struct FLOAT *, struct FLOAT *);
int incrementInt(struct NUMBER *, struct NUMBER *);
int decrementInt(struct NUMBER *, struct NUMBER *);
int multipleInt(struct NUMBER *, struct NUMBER *, struct NUMBER *,struct NUMBER *);
int multipleFloat(struct FLOAT *, struct FLOAT *, struct FLOAT *);
int divideInt(struct NUMBER *, struct NUMBER *,struct NUMBER *, struct NUMBER *);
int divideFloat(struct FLOAT *, struct FLOAT *, struct FLOAT *);
int divIntInt(struct NUMBER *, int, struct NUMBER *,int *);
int numSqrt(struct FLOAT *,struct FLOAT *);
int numSqrt2(struct FLOAT *, struct FLOAT *);
int power(struct FLOAT *, int ,struct FLOAT *);
int reciprocal(struct FLOAT *, struct FLOAT *);