#define DIGIT 111
#define RADIX 1000000000

#define DISPRAD "000000000"

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
void dispNumberFloat(struct FLOAT *);
void copyNumberInt(struct NUMBER *, struct NUMBER *);
void copyNumberFloat(struct FLOAT *, struct FLOAT *);
void getAbsInt(struct NUMBER *,struct NUMBER *);
void getAbsFloat(struct FLOAT *,struct FLOAT *);
int isZeroInt(struct NUMBER *);
int isZeroFloat(struct FLOAT *);
int mulByN(struct NUMBER *,struct NUMBER *, int );
int divByN(struct NUMBER *,struct NUMBER *, int, struct NUMBER *);
int setInt(struct NUMBER *, int, int);
int getDigit(struct NUMBER*);
int getDigitDecimal(struct FLOAT*);
int getExp(struct FLOAT *);
void setExp(struct FLOAT *, int);
int setSign(struct NUMBER *,int);
int getSign(struct NUMBER *);
int numCompInt(struct NUMBER *,struct NUMBER *);
int numCompFloat(struct FLOAT *,struct FLOAT *);
int addInt(struct  NUMBER *, struct NUMBER *, struct NUMBER *, int *);
int addFloat(struct  FLOAT *, struct FLOAT *, struct FLOAT *);
int subInt(struct NUMBER * ,struct NUMBER *, struct NUMBER *, int *);
int subFloat(struct FLOAT * ,struct FLOAT *, struct FLOAT *);
int incrementInt(struct NUMBER *, struct NUMBER *);
int multipleInt(struct NUMBER *, struct NUMBER *, struct NUMBER *,struct NUMBER *);
int multipleFloat(struct FLOAT *, struct FLOAT *, struct FLOAT *);
int divideFloat(struct FLOAT *, struct FLOAT *, struct FLOAT *);
int numSqrt(struct FLOAT *,struct FLOAT *);
int power(struct FLOAT *, int ,struct FLOAT *);
int reciprocal(struct FLOAT *, struct FLOAT *);


