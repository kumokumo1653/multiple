#define DIGIT 30

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
int divBy10Int(struct NUMBER *,struct NUMBER *);
int setInt(struct NUMBER *,int);
int setFloat(struct FLOAT *, int, int);
int getInt(struct NUMBER *,int *);
int getIntToString(struct NUMBER*,char *);
int getDigitInt(struct NUMBER*);
void swapInt(struct NUMBER *,struct NUMBER *);
int setSignInt(struct NUMBER *,int);
int getSignInt(struct NUMBER *);
int numCompInt(struct NUMBER *,struct NUMBER *);
int numCompFfloat(struct FLOAT *,struct FLOAT *);
int addInt(struct  NUMBER *, struct NUMBER *, struct NUMBER *);
int subInt(struct NUMBER * ,struct NUMBER *, struct NUMBER *);
int incrementInt(struct NUMBER *, struct NUMBER *);
int decrementInt(struct NUMBER *, struct NUMBER *);
int multipleInt(struct NUMBER *, struct NUMBER *, struct NUMBER *);
int divideInt(struct NUMBER *, struct NUMBER *,struct NUMBER *, struct NUMBER *);
int divIntInt(struct NUMBER *, int, struct NUMBER *,int *);
int numSqrt(struct NUMBER *,struct NUMBER *);
int power(struct NUMBER *, int ,struct NUMBER *);
