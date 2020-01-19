#define DIGIT 10

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
void dispNumberZeroSuppressInt(struct NUMBER *);
void setRandomInt(struct NUMBER *,int);
void copyNumberInt(struct NUMBER *, struct NUMBER *);
void copyNumberFloat(struct FLOAT *, struct FLOAT *);
void getAbsInt(struct NUMBER *,struct NUMBER *);
void getAbsFloat(struct FLOAT *,struct FLOAT *);
int isZeroInt(struct NUMBER *);
int isZeroFloat(struct FLOAT *);
int mulBy10Int(struct NUMBER *,struct NUMBER *);
int mulByNInt(struct NUMBER *,struct NUMBER *, int );
int divBy10Int(struct NUMBER *,struct NUMBER *);
int divByNInt(struct NUMBER *,struct NUMBER *, int, struct NUMBER *);
int setInt(struct NUMBER *,int);
int setFloat(struct FLOAT *, int, int);
int getInt(struct NUMBER *,int *);
int getIntToString(struct NUMBER*,char *);
int getDigitInt(struct NUMBER*);
int getDigitDecimal(struct FLOAT*);
int clearByZeroDecimal(struct FLOAT*, struct FLOAT *);
void swapInt(struct NUMBER *, struct NUMBER *);
int setSignInt(struct NUMBER *,int);
int getSignInt(struct NUMBER *);
int numCompInt(struct NUMBER *,struct NUMBER *);
int numCompFloat(struct FLOAT *,struct FLOAT *);
int addInt(struct  NUMBER *, struct NUMBER *, struct NUMBER *,int *);
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
int numSqrt(struct NUMBER *,struct NUMBER *);
int power(struct NUMBER *, int ,struct NUMBER *);
int reciprocal(struct FLOAT *, struct FLOAT *);