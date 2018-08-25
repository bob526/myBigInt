/** Team #14,   Name: Chien Cheng-Chuan Student ID: 403410011   Computer Science and Information Engineering,   2nd year.**/
#include <iostream>
#include <stack>
#include <cstring>
#include <cstdlib>
#include <queue>
#include <string>
#include "BigInt.h"

using namespace std;

namespace
{
    //Unname namespace
    int parseDigit(int& yourNum);
    //Precondition: The parameter should be a changeable integer.
    //Postcondition: It will return the rightest digit and divide parameter by 10.
    int removeFrontZero(const char *numString, int capacity);
    //Precondition: It should pass a pointer to char (c string) and its memory size.
    //Postcondition: It will return the offset(how many should I right shift) to avoid the 00005 situation.
    void outsideStrClear(char *str, const int length);
    //Precondition: Make sure the string's date doesn't need.
    //Postcondition: It will clear all string's char to 0.

    const int ADDITIONAL_SPACE(100);

    int parseDigit(int& yourNum)
    {
        int temp(yourNum%10);
        yourNum/=10;
        return temp;
    }

    int removeFrontZero(const char *numString, int capacity)
    {
        int i;
        for (i=0;i<capacity;i++) {
            if (numString[i]!='0' && numString[i]!=0)
                return i;
            else if (numString[i]=='0' && numString[i+1]==0 && i+1<capacity)
                return i;
            else if (numString[i]=='0' && i==capacity-1)
                return i;
            else if (numString[i]==0)
                return 0;
        }
        return 0;
    }

    void outsideStrClear(char *str, const int length)
    {
        for (int i=0;i<length;i++)
            str[i]=0;
    }
}



namespace BigIntNariKan
{
//Here need lots of tab each line.
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

BigInt::BigInt(const int number)
{

    int targetNumber(number);
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
{   //string constructor
    int shiftPreventZero(0);
    size=strlen(userString);
    if (userString[size-1]=='!') {
        numString = new char[ADDITIONAL_SPACE];
        isNegative=false;
        capacity=ADDITIONAL_SPACE;
        //Avoid free(delete) error
        char *prepareFactorial= new char[size+ADDITIONAL_SPACE];
        outsideStrClear(prepareFactorial,size+ADDITIONAL_SPACE);
        strncpy(prepareFactorial,userString,size-1);    //The last one is !, size-1 will ignore it.
        BigInt facValue(prepareFactorial);
        (*this)=facValue.factorial();
        delete [] prepareFactorial;
        prepareFactorial = NULL;
    }
    else {
        if (userString[0]=='-')
            isNegative=true;
        else
            isNegative=false;

        for (int i=0;i<size;i++) {
            if (!((userString[i]>='0' && userString[i]<='9')||(i==0 && userString[i]=='-'))) {
                cerr<<"BigInt: The string is illeagal\n";
                exit(-1);
            }
        }
        capacity=size*2+ADDITIONAL_SPACE;

        shiftPreventZero=removeFrontZero(userString,size);

        numString=new char[capacity];
        clearArray(capacity);

        strcpy(numString,userString+shiftPreventZero);
        size-=shiftPreventZero;
    }

}

const BigInt operator + (const BigInt& num1, const BigInt& num2)
{
    stack<char> reverseDigit;
    bool carry(false);
    int digitSum(0),i=num1.size-1, j=num2.size-1,newLength(max(num1.size,num2.size)*2+ADDITIONAL_SPACE);   //Remember to minus 1, because index start from 0
    char *newNumStr = new char[newLength];
    int frontZeroShift(0);
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
        frontZeroShift=removeFrontZero(newNumStr,newLength);
        if (frontZeroShift>newLength)
            frontZeroShift=0;
        BigInt returnValue(newNumStr+frontZeroShift);
        delete [] newNumStr;
        newNumStr=NULL;
        return returnValue;
    }
}

const BigInt operator - (const BigInt& num1, const BigInt& num2)
{
    //Make sure below is run in the condition: num1 > num2
    stack<char> reverseDigit;
    int i(num1.size-1),j(num2.size-1),digitDiff(0),newLength(max(num1.size,num2.size)*2+ADDITIONAL_SPACE);
    bool borrow(false);
    char *newNumStr = new char[newLength];
    int frontZeroShift(0);
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

        frontZeroShift=removeFrontZero(newNumStr,newLength);
        if (frontZeroShift>newLength)
            frontZeroShift=0;
        BigInt returnValue(newNumStr+frontZeroShift);
        delete [] newNumStr;
        newNumStr=NULL;
        return returnValue;
    }
}

BigInt& BigInt::operator = (const BigInt& rValue)
{
    if (this == &rValue)
        return *this;   //Because this is pointer and return type is reference.
    else {
        size=rValue.size;
        capacity=rValue.capacity;
        isNegative=rValue.isNegative;
        delete [] numString;
        numString = new char[capacity];
        clearArray(capacity);

        for (int i=0;i<size;i++)
            numString[i]=rValue.numString[i];

        return *this;
    }
}

BigInt::BigInt(const BigInt& old):size(old.size),capacity(old.capacity),isNegative(old.isNegative)
{
    //copy constructor
    //This is constructor, so *numString doesn't allocate yet.
    int shiftPreventZero(0);
    numString = new char[capacity];
    clearArray(capacity);
    shiftPreventZero=removeFrontZero(old.numString,capacity);
    for (int i=0;i<size;i++)
        numString[i]=old.numString[i+shiftPreventZero];

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

bool operator >(const BigInt& num1, const BigInt& num2)
{
    if ((num1.isNegative)&&(!num2.isNegative))  //num1<0 && num2>0
        return false;
    else if ((!num1.isNegative)&&(num2.isNegative)) //num1>0 && num2<0
        return true;
    else if ((num1.isNegative)&&(num2.isNegative))  //num1<0 && num2<0
        return (!((-num1)>(-num2)));
    else {  //All positive.
        if (num1.size>num2.size)
            return true;
        else if (num1.size==num2.size) {
            if (strcmp(num1.numString,num2.numString) > 0)
                return true;
            else
                return false;
        }
        else
            return false;
    }
}

bool operator ==(const BigInt& num1, const BigInt& num2)
{
    if (strcmp(num1.numString,num2.numString)==0)
        return true;
    else
        return false;
}

bool operator >=(const BigInt& num1, const BigInt& num2)
{
    if ((num1>num2)||(num1==num2))
        return true;
    else
        return false;
}

bool operator <(const BigInt& num1, const BigInt& num2)
{
    if ((num1.isNegative)&&(!num2.isNegative))  //num1<0 && num2>0
        return true;
    else if ((!num1.isNegative)&&(num2.isNegative)) //num1>0 && num2<0
        return false;
    else if ((num1.isNegative)&&(num2.isNegative))  //num1<0 && num2<0
        return (!((-num1)<(-num2)));
    else {  //All positive.
        if (num1.size<num2.size)
            return true;
        else if (num1.size==num2.size) {
            if (strcmp(num1.numString,num2.numString) < 0)
                return true;
            else
                return false;
        }
        else
            return false;
    }
}

bool operator <=(const BigInt& num1, const BigInt& num2)
{
    if ((num1<num2)||(num1==num2))
        return true;
    else
        return false;
}

const BigInt operator * (const BigInt& num1, const BigInt& num2)
{
    if ((num1.isNegative)&&(num2.isNegative))   //num1<0 && num2<0
        return ((-num1)*(-num2));
    else if ((num1.isNegative)&&(!num2.isNegative)) //num1<0 && num2>0
        return (-((-num1)*(num2)));
    else if ((!num1.isNegative)&&(num2.isNegative)) //num1>0 && num2<0
        return (-((num1)*(-num2)));
    else {      //num1>0 && num2>0
        int carry(0),newLength(0),digitProduct(0),putZeroNum(0);
        stack<char> reverseDigit[num2.size];
        char *newNumStr;    //I will allocate the size according to the size of stack.
        BigInt finalSum("0");
        for (int lowerIdx=num2.size-1;lowerIdx>=0;lowerIdx--,putZeroNum++) {
            //Put zero
            for (int i=0;i<putZeroNum;i++)
                reverseDigit[putZeroNum].push('0');


            //Human multiple.
            for (int upperIdx=num1.size-1; upperIdx>=0; upperIdx--) {
                digitProduct=((num1.numString[upperIdx]-'0') * (num2.numString[lowerIdx]-'0'));
                digitProduct+=carry;
                carry=0;
                if (digitProduct>=10) {
                    for (int i=0;i<2;i++) {
                        int temp(parseDigit(digitProduct)); //digitProduct will be modified.
                        if (i==0)
                            reverseDigit[putZeroNum].push(temp+'0');
                        else
                            carry=temp;
                    }
                }
                else
                    reverseDigit[putZeroNum].push(digitProduct+'0');    //digitProduct=0~9
            }
            if (carry!=0) {
                reverseDigit[putZeroNum].push(carry+'0');
                carry=0;
            }
        }


        /*
            I need to do:
            a stl stack array [num2.size]
            putZeroNum can be index for stl stack array
            In the first loop(old), before enter the second loop(old), put a for loop to put zero
            put an outside loop , putZeroNum can be index.
            Declare another BigInt object as finalSum. It will be returned.
            Put a loop for pop the stl stack array -> a temp BigInt
            fianlSum+=temp BigInt
            return it.
        */
        for (int stackIdx=0;stackIdx<putZeroNum;stackIdx++) {
            newLength=reverseDigit[stackIdx].size()+ADDITIONAL_SPACE;
            newNumStr = new char[newLength];
            outsideStrClear(newNumStr,newLength);
            for (int i=0;!reverseDigit[stackIdx].empty();i++) {
                newNumStr[i]=reverseDigit[stackIdx].top();
                reverseDigit[stackIdx].pop();
            }
            finalSum+=(newNumStr);  //I want to use auto generate it.
            delete [] newNumStr;
            newNumStr=NULL;
        }
        return finalSum;
    }
}

bool operator != (const BigInt& num1, const BigInt& num2)
{
    return !(num1==num2);
}

const char* BigInt::getNumString() const
{
    return numString;
}

const BigInt& operator += (BigInt& num1, const BigInt& num2)
{
    BigInt temp(num1+num2);
    num1=temp;
    return num1;
}

const BigInt& operator -= (BigInt& num1, const BigInt& num2)
{
    BigInt temp(num1-num2);
    num1=temp;
    return num1;
}

const BigInt& operator *= (BigInt& num1, const BigInt& num2)
{
    BigInt temp(num1*num2);
    num1=temp;
    return num1;
}

const BigInt BigInt::factorial() const
{
    //Because it doesn't return reference, so I can return *this and copy constructor will be called auto.
    if (isNegative) {
        cerr<<"BigInt: Factorial error, (-x)! doesn't exist.\n";
        exit(-1);
    }
    else if ((*this)==0) {
        //(*this)=1;
        return BigInt(1);
    }
    else {
        //The value >0
        BigInt answer("1");
        for (BigInt i=2; i<=(*this);i++)
            answer*=i;

        //(*this)=answer;

        return answer;
    }
}

BigInt& BigInt::operator ++()    //Prefix version
{
    (*this)=(*this)+1;
    return *this;
}

BigInt BigInt::operator ++(int)    //Postfix version
{
    BigInt temp(*this);  //Before add one.
    (*this)=(*this)+1;
    return BigInt(temp);
}

BigInt& BigInt::operator --()
{
    (*this)=(*this)-1;
    return *this;
}

BigInt BigInt::operator --(int)
{
    BigInt temp(*this);
    (*this)=(*this)-1;
    return BigInt(temp);
}

const BigInt operator / (const BigInt& num1, const BigInt& num2)
{
    if ((num1.isNegative)&&(num2.isNegative))   //num1<0 && num2<0
        return ((-num1)/(-num2));
    else if ((num1.isNegative)&&(!num2.isNegative)) //num1<0 && num2>0
        return (-((-num1)/(num2)));
    else if ((!num1.isNegative)&&(num2.isNegative)) //num1>0 && num2<0
        return (-((num1)/(-num2)));
    else {  //Both positive.
        if (num1<num2) {
            return BigInt("0");
            //I don't want to process float point and it is also out of range.
        }
        if (num2==0) {
            //cerr<<"BigInt: The denominator can't be 0.\n";
            //exit(-1);
            return BigInt("0");
        }
        char *strForSub,*strForQuotient;
        int strQuotientLen(0);
        queue<char> tempNumStore,quotient;
        BigInt tempBigInt;
        bool first(true);
        for (int pos=0, right=1; right<=num1.size; /**Need control by myself**/) {
            //Cut a good partition..
            //cout<<"pos= "<<pos<<" "<<"right= "<<right<<endl;
            while(right<=num1.size) {
                int lenForSub(0);
                for (int i=pos;i<right;i++)
                    tempNumStore.push(num1.numString[i]);
                lenForSub=tempNumStore.size()+ADDITIONAL_SPACE;
                strForSub = new char[lenForSub];
                outsideStrClear(strForSub,lenForSub);
                for (int i=0;!tempNumStore.empty();i++) {
                    strForSub[i]=tempNumStore.front();
                    tempNumStore.pop();
                }
                tempBigInt = BigInt(strForSub);
                //cout<<"tempBigInt= "<<tempBigInt<<"Right= "<<right<<endl;
                if (tempBigInt < num2 && first) {
                    right++;    //It will continue.
                    delete [] strForSub;
                }
                else {
                    right++;
                    delete [] strForSub;
                    break;
                }

            }
            if (first) {
                first=false;
                pos=right-1;
            }
            else
                pos++;

            //Compute quotient digit by digit.
            for (int i=1;i<=10;i++) {
                BigInt subValue((num2*i));

                if (subValue > tempBigInt) {
                    subValue = BigInt((num2*(i-1)));
                    quotient.push((i-1)+'0');
                    tempBigInt-=subValue;
                    break;
                }
            }

            //tempNumStore*=10;
            for (int i=0;i<tempBigInt.size;i++)
                tempNumStore.push(tempBigInt.numString[i]);

            //tempNumStore+= new digit.


        }
        strQuotientLen=quotient.size()+ADDITIONAL_SPACE;
        strForQuotient=new char[strQuotientLen];
        outsideStrClear(strForQuotient,strQuotientLen);
        for (int i=0;!quotient.empty();i++) {
            strForQuotient[i]=quotient.front();
            quotient.pop();
        }
        BigInt returnValue(strForQuotient);
        delete [] strForQuotient;
        strForQuotient=NULL;
        return returnValue;
    }
}

const BigInt& operator /= (BigInt& num1, const BigInt& num2)
{
    BigInt temp(num1/num2);
    num1=temp;
    return num1;
}

const BigInt operator % (const BigInt& num1, const BigInt& num2)
{
    BigInt quotient(num1/num2),answer;
    answer=num1-(quotient*num2);
    return answer;
}

void BigInt::set_negative(const bool negativeOrNot)
{
    if (negativeOrNot==true) {
        //It will change to negative.
        if (isNegative==false)
            (*this)=-(*this);
        //else -> the sign has already negative, don't need to change.
    }
    else {  //It will change to positive
        if (isNegative==true)
            (*this)=-(*this);
        //else -> the calling object is positive, don't need to change.
    }
}

void BigInt::set_store(const int newNum)
{
    (*this)=newNum;
}

BigInt::BigInt(const string userString)
{   //stl string constructor
    size=userString.size();
    capacity=size*2+ADDITIONAL_SPACE;
    isNegative=false;
    //Above isn't matter

    numString = new char[capacity];
    const char *cStyleUserString=userString.c_str();
    (*this)=cStyleUserString;
}

void BigInt::set_store(const string str)
{
    (*this)=str;
}

const bool BigInt::get_negative() const
{
    return isNegative;
}

const int BigInt::get_size() const
{
    return size;
}

const BigInt& operator %= (BigInt& num1, const BigInt& num2)
{
    BigInt temp(num1%num2);
    num1=temp;
    return num1;
}

istream& operator >> (istream& input, BigInt& container)
{
    string userInput;
    input>>userInput;
    container = userInput;
    return input;
}

char& BigInt::operator [] (const int index)
{
    if (index<size) {
        return numString[index];
    }
    else {
        cerr<<"BigInt: Error, the index is over the size in numString\n";
        exit(-1);
    }
}

//End of namespace BigIntNariKan
}
