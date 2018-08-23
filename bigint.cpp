/*
    Name: Chien Cheng-Chuan
	Student ID: 403410011
	Department of computer science and information engineering
	2nd year
*/
#include <iostream>
#include <stack>
#include <cstring>
#include <cstdlib>

using namespace std;

class BigInt
{
public:
    BigInt();
    //Default constructor: The value will be 0.
    BigInt(const long long int number);
    //When using this constructor, user should notice the boundary of long long int.
    //Watch out: If you want to pass 0, please cast it to long long int type.
    BigInt(const char userString[]); 
    //Construct the object with the string input by user.
    BigInt(const BigInt& old);
    //Copy constructor
    ~BigInt();
    //Destructor
    friend ostream& operator << (ostream& output, const BigInt& objWantToShow);
    friend const BigInt operator + (const BigInt& num1, const BigInt& num2);
    friend const BigInt operator - (const BigInt& num1, const BigInt& num2);
    friend const BigInt operator - (const BigInt& num);
    
    BigInt& operator = (const BigInt& rValue);
private:
    int size;
    int capacity;
    char *numString;
    bool isNegative;
    void clearArray(const int capacity);
    //Precondition: Make sure the data in the object doesn't need anymore.
    //Postcondition: It will set all memory of the array to 0.
};

void outsideStrClear(char *str, const int length);
//Precondition: Make sure the string's date doesn't need.
//Postcondition: It will clear all string's char to 0.
void swap(int& a, int& b);
//Precondition: a and b should be interger and call by reference.
//Postcondition: It will swap a and b' value.

int main()
{
    BigInt a("314159265358979323846264338327950288419716939937510"), c(a);
    BigInt *b = new BigInt(1123581321);
    
    c=a+*b;
    cout<<a<<" + "<<*b<<" = "<<c<<endl;
    c=a-*b;
    cout<<a<<" - "<<*b<<" = "<<c<<endl;
    
    return 0;
}

BigInt::BigInt():size(0),capacity(100)
{
    numString=new char[capacity];
    clearArray(capacity);
    
    numString[0]='0';
    size=1;
    isNegative=false;
}

void BigInt::clearArray(const int capacity)
{
    for (int i=0;i<capacity;i++)
        numString[i]=0;
}

BigInt::BigInt(const long long int number)
{
    //What will happen if someone input 000000?
    long long int targetNumber(number);
    bool negative(false);
    if (targetNumber<0) {
        negative=true;
        isNegative=true;
        targetNumber=(-targetNumber);
    }
    else
        isNegative=false;
    
    stack<char> reverseDigit;
    do {
        reverseDigit.push(targetNumber%10);
        targetNumber/=10;
    } while(targetNumber!=0);
    
    if (negative)
        reverseDigit.push('-'-'0');
    
    size=reverseDigit.size();
    capacity=size*2;
    numString=new char[capacity];
    clearArray(capacity);
    
    for (int i=0;!reverseDigit.empty();i++) {
        numString[i]=reverseDigit.top()+'0';
        reverseDigit.pop();
    }
    
}

ostream& operator << (ostream& output, const BigInt& objWantToShow)
{
    output<<objWantToShow.numString;
    return output;
}

BigInt::BigInt(const char userString[])
{
    size=strlen(userString);
    if (userString[0]=='-')
        isNegative=true;
    else 
        isNegative=false;
    for (int i=0;i<size;i++) {
        if (!((userString[i]>='0' && userString[i]<='9')||(i==0 && userString[i]=='-'))) {
            cerr<<"The string is illeagal\n";
            exit(-1);
        }
    }
    capacity=size*2;
    
    numString=new char[capacity];
    clearArray(capacity);
    strcpy(numString,userString);
}

const BigInt operator + (const BigInt& num1, const BigInt& num2)
{
    stack<char> reverseDigit;
    bool carry(false);
    int digitSum(0),i=num1.size-1, j=num2.size-1,newLength(max(num1.size,num2.size)*2);   //Remember to minus 1, because index start from 0
    char *newNumStr = new char[newLength];
    outsideStrClear(newNumStr,newLength);
    
    
    if ((!num1.isNegative)&&(num2.isNegative))  //a+(-b)
        return num1-(-num2);
    else if ((num1.isNegative)&&(!num2.isNegative)) //(-a)+b
        return num2-(-num1);
    else if ((num1.isNegative)&&(num2.isNegative))  //(-a)+(-b)
        return (-((-num1)+(-num2)));
    else {
        //a+b
        for (;i>=0&&j>=0;i--,j--) {
            //digit by digit add
            digitSum=(num1.numString[i]-'0')+(num2.numString[j]-'0');
        
        
            if (carry) 
                ++digitSum;
        
        
            //Decide next digit carry or not.
            if (digitSum>=10) {
                digitSum-=10;
                carry=true;
            }
            else
                carry=false;
                
            //output it to new object.
            reverseDigit.push(digitSum+'0');
            /*cout<<reverseDigit.top()<<endl;
            cin.get();*/
        }
        //Process left digit
        for (;i>=0;i--) {
            if (carry) {
                int finalDigit(num1.numString[i]-'0');
                finalDigit++;
                if (finalDigit>=10) {
                    carry=true;
                    finalDigit-=10;
                }
                else 
                    carry=false;
                reverseDigit.push(finalDigit+'0');
            }
            else
                reverseDigit.push(num1.numString[i]);
        }
    
        for (;j>=0;j--) {
            if (carry) {
                int finalDigit(num2.numString[j]-'0');
                finalDigit++;
                if (finalDigit>=10) {
                    carry=true;
                    finalDigit-=10;
                }
                else 
                    carry=false;
                reverseDigit.push(finalDigit+'0');
            }
            else
                reverseDigit.push(num2.numString[j]);
        }
    
        if (carry)
            reverseDigit.push('1');
    
        //Put it into the new string
        for (i=0;!reverseDigit.empty();i++) {
            newNumStr[i]=reverseDigit.top();
            reverseDigit.pop();
        }
        //cout<<newNumStr;
    
        return BigInt(newNumStr);
    }
}

const BigInt operator - (const BigInt& num1, const BigInt& num2)
{
    //Make sure below is run in the condition: num1 > num2
    stack<char> reverseDigit;
    int i(num1.size-1),j(num2.size-1),digitDiff(0),newLength(max(num1.size,num2.size)*2);
    bool borrow(false);
    char *newNumStr = new char[newLength];
    outsideStrClear(newNumStr,newLength);
    
    if ((!num1.isNegative)&&(num2.isNegative))
        return num1+(-num2);
    else if ((num1.isNegative)&&(!num2.isNegative))
        return -((-num1)+(num2));
    else if ((num1.isNegative)&&(num2.isNegative))
        return (-num2)-(-num1);
    else {
        //Positive minus positive.
        BigInt temp1,temp2;
        bool resultIsPositiveOrNot(false);
        if (num1.size > num2.size) {
            resultIsPositiveOrNot=true; //Result is positive
            temp1=num1, temp2=num2;
        }
        else if (num1.size < num2.size) {
            resultIsPositiveOrNot=false;    //Result is negative
            temp1=num2, temp2=num1;
            swap(i,j);
        }
        else {
            if (strcmp(num1.numString,num2.numString) >= 0) {
                temp1=num1, temp2=num2;
                resultIsPositiveOrNot=true; //Result is positive
            }
            else {
                temp1=num2, temp2=num1;
                resultIsPositiveOrNot=false;    //Result is negative
                swap(i,j);
            }
        }
        
        for (;i>=0&&j>=0;i--,j--) {
            digitDiff=(temp1.numString[i]-'0')-(temp2.numString[j]-'0');
        
            if (borrow) 
                --digitDiff;
        
            if (digitDiff<0) {
                borrow=true;
                digitDiff+=10;
            }
            else
                borrow=false;
                
            reverseDigit.push(digitDiff+'0');
        }
    
        for (;i>=0;i--) {
            digitDiff=temp1.numString[i]-'0';
            if (borrow) {
                --digitDiff;
                if (digitDiff<0) {
                    borrow=true;
                    digitDiff+=10;
                }
                else 
                    borrow=false;
                reverseDigit.push(digitDiff+'0');
                
            }
            else {
                reverseDigit.push(temp1.numString[i]);
            }
        }
        
        if (!resultIsPositiveOrNot)
            reverseDigit.push('-');
    
        for (i=0;!reverseDigit.empty();i++) {
            newNumStr[i]=reverseDigit.top();
            reverseDigit.pop();
        }
    
        return BigInt(newNumStr);
    }
}

void outsideStrClear(char *str, const int length)
{
    for (int i=0;i<length;i++)
        str[i]=0;
}

BigInt& BigInt::operator = (const BigInt& rValue)
{
    if (this == &rValue)
        return *this;   //Because this is pointer and return type is reference.
    else {
        size=rValue.size;
        capacity=rValue.capacity;
        delete [] numString;
        numString = new char[capacity];
        clearArray(capacity);
        
        for (int i=0;i<size;i++)
            numString[i]=rValue.numString[i];
            
        return *this;
    }
}

BigInt::BigInt(const BigInt& old):size(old.size),capacity(old.capacity)
{
    //This is constructor, so *numString doesn't allocate yet.
    numString = new char[capacity];
    clearArray(capacity);
    for (int i=0;i<size;i++)
        numString[i]=old.numString[i];
}

BigInt::~BigInt()
{
    delete [] numString;
}

const BigInt operator - (const BigInt& num)
{
    if (num.numString[0]=='-') 
        return BigInt(num.numString+1);
    else {
        //Positive
        char newNumStr[num.capacity];
        outsideStrClear(newNumStr,num.capacity);
        newNumStr[0]='-';
        strcat(newNumStr,num.numString);
        return BigInt(newNumStr);
    }
}

void swap(int& a, int& b)
{
    int temp(a);
    a=b;
    b=temp;
}