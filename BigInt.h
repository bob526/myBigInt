/** Team #14,   Name: Chien Cheng-Chuan Student ID: 403410011   Computer Science and Information Engineering,   2nd year.**/
#ifndef BIGINT_NARIKAN
#define BIGINT_NARIKAN

using namespace std;

namespace BigIntNariKan
{
    class BigInt
    {
    public:
        BigInt();
        //Default constructor: The value will be 0.
        BigInt(const long long int number);
        //When using this constructor, user should notice the boundary of long long int.
        //Watch out: If you want to pass 0, please cast it to long long int type.
        BigInt(const int number);
        //Notice the limit of int.
        BigInt(const char userString[]);
        //Construct the object with the string input by user.
        BigInt(const string userString);
        BigInt(const BigInt& old);
        //Copy constructor
        ~BigInt();
        //Destructor
        friend ostream& operator << (ostream& output, const BigInt& objWantToShow);
        friend istream& operator >> (istream& input, BigInt& container);
        friend const BigInt operator + (const BigInt& num1, const BigInt& num2);
        friend const BigInt operator - (const BigInt& num1, const BigInt& num2);
        friend const BigInt operator - (const BigInt& num);
        friend const BigInt operator * (const BigInt& num1, const BigInt& num2);
        friend const BigInt operator / (const BigInt& num1, const BigInt& num2);
        friend const BigInt operator % (const BigInt& num1, const BigInt& num2);

        friend bool operator >(const BigInt& num1, const BigInt& num2);
        friend bool operator ==(const BigInt& num1, const BigInt& num2);
        friend bool operator >=(const BigInt& num1, const BigInt& num2);
        friend bool operator <(const BigInt& num1, const BigInt& num2);
        friend bool operator <=(const BigInt& num1, const BigInt& num2);
        friend bool operator !=(const BigInt& num1, const BigInt& num2);

        BigInt& operator = (const BigInt& rValue);
        friend const BigInt& operator += (BigInt& num1, const BigInt& num2);
        friend const BigInt& operator -= (BigInt& num1, const BigInt& num2);
        friend const BigInt& operator *= (BigInt& num1, const BigInt& num2);
        friend const BigInt& operator /= (BigInt& num1, const BigInt& num2);
        friend const BigInt& operator %= (BigInt& num1, const BigInt& num2);

        BigInt& operator ++();   //Prefix version = ++(variableName);
        BigInt operator ++(int);    //Postfix version = (variableName++);
        BigInt& operator --();  //Prefix version = --(variableName);
        BigInt operator --(int);    //Postfix version = (variableName)--;

        const char* getNumString() const;
        //Precondition: Don't need to pass argument
        //Postcondition: It will return the private memeber numString as C-string.
        const BigInt factorial() const;
        //Precondition: Make sure the value of calling object is positive. (The numString's first char isn't '-')
        //Postcondition: It will return the factorial value of the calling object..
        void set_negative(const bool negativeOrNot);
        //Precondition: It should pass a boolean variable.
        //Postcondition: It will let you change the calling object's sign.

        //--------Please use "="-----------
        void set_store(const int newNum);
        //Precondition: Make sure that the int newNum isn't overflow.
        //Postcondition: It will change the calling object's value to the newNum.
        //This function is the same as assign. If you want program faster, you should use assign("=").
        void set_store(const string str);
        //Precondition: Make sure your string contain legal value.
        //Postcondition: It will modify the calling object's value to the new str.
        //This function is the same as assign. If you want to be faster, please use assign"="
        //---------------------------------

        const bool get_negative() const;
        //Precondition: It doesn't need to pass argument.
        //Postcondition: It will return a bool value indicating the BigInt is negative or not. The return value is protected by const.
        const int get_size() const;
        //Precondition: It doesn't need to pass argument.
        //Postcondition: It will return the size use in the calling object. Notice: sign(-) is also include.

        char& operator [] (const int index);
        //Precondition: Please pass an integer to it. And the calling object should be initialize.
        //Postcondition: It will return the calling object's numString[index]. Notice: It can be Lvalue(e.g: BigIntVariable[10]='5')
        //Very dangerous!!!!


    private:
        int size;
        int capacity;
        char *numString;
        bool isNegative;
        void clearArray(const int capacity);
        //Precondition: Make sure the data in the object doesn't need anymore.
        //Postcondition: It will set all memory of the array to 0.
    };

    //Here is mynamespace, not in the class memeber.

    void swap(int& a, int& b);
    //Precondition: a and b should be interger and call by reference.
    //Postcondition: It will swap a and b' value.

}

#endif
