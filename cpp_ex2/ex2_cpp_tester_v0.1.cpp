#include <iostream>
#include "gtest/gtest.h"
#include <sstream>
#include "Fractal.h"
int main(int argc , char *argv[])
{
    testing::InitGoogleTest(&argc , argv);
    return RUN_ALL_TESTS();
}

TEST(FractalTest, DefaultConstructor)
{
	Fractal fractal;
	EXPECT_EQ(true, true);
}

/**
 * GField related tests.
 */
//TEST(GFieldTest , DefaultConstructor)
//{
//    GField gField;
//    EXPECT_EQ(gField.getChar() , 2);
//    EXPECT_EQ(gField.getDegree() , 1);
//    EXPECT_EQ(gField.getOrder() , 2);
//}
//
//TEST(GFieldTest , Constructor1)
//{
//    GField gField1(2);
//    EXPECT_EQ(gField1.getChar() , 2);
//    EXPECT_EQ(gField1.getDegree() , 1);
//    EXPECT_EQ(gField1.getOrder() , 2);
//
//    GField gField2(11);
//    EXPECT_EQ(gField2.getChar() , 11);
//    EXPECT_EQ(gField2.getDegree() , 1);
//    EXPECT_EQ(gField2.getOrder() , 11);
//    //Should cause assertion failure because it's not prime
//    ASSERT_DEATH(GField(6) , "p");
////  ASSERT_DEATH(GField(6) , "isPrime\\(p\\)"); // This should be the the actual message
//}
//
//TEST(GFieldTest , Constructor2)
//{
//    GField gField1(2 , 1);
//    EXPECT_EQ(gField1.getChar() , 2);
//    EXPECT_EQ(gField1.getDegree() , 1);
//    EXPECT_EQ(gField1.getOrder() , 2);
//
//    GField gField2(11 , 2);
//    EXPECT_EQ(gField2.getChar() , 11);
//    EXPECT_EQ(gField2.getDegree() , 2);
//    EXPECT_EQ(gField2.getOrder() , 121);
//
////Should cause assertion failure because it's not prime
//    ASSERT_DEATH(GField(6 , 1) , "p");
////  ASSERT_DEATH(GField(6 , 1) , "isPrime\\(p\\)");// This should be the the actual message
//    //Should c assertion failure because l should be >0
//    ASSERT_DEATH(GField(11 , 0) , "p");
////  ASSERT_DEATH(GField(11 , 0) , "l > 0"); // This should be the the actual message
//    ASSERT_DEATH(GField(11 , -1) , "p");
////  ASSERT_DEATH(GField(11 , -1) , "l > 0"); // This should be the the actual message
//
//}
//
//TEST(GFieldTest , CopyConstructor)
//{
//    GField gField1(11 , 2);
//    GField gField2(gField1);
//    EXPECT_EQ(gField2.getChar() , gField1.getChar());
//    EXPECT_EQ(gField2.getDegree() , gField1.getDegree());
//    EXPECT_EQ(gField2.getOrder() , gField1.getOrder());
//
//}
//
//TEST(GFieldTest , GCD)
//{
//    GFNumber a1(2);
//    GFNumber b1(4);
//    GField gf1;
//    EXPECT_EQ(gf1.gcd(a1 , b1).getNumber() , (2 % gf1.getOrder()));
//
//    GField gf2(11 , 3);
//    GFNumber b2(4 , gf2);
//
//    //Same field check
//    ASSERT_DEATH(gf1.gcd(a1 , b2) , "p");
//    // ASSERT_DEATH(gf1.gcd(a1 , b2) , "a\\.getField\\(\\) == b\\.getField\\(\\)");// This should be the the actual message
//}
//
//TEST(GFieldTest , IsPrime)
//{
//    GField gf1;
//    //Not primes
//    EXPECT_EQ(gf1.isPrime(1) , false);
//    EXPECT_EQ(gf1.isPrime(0) , false);
//    EXPECT_EQ(gf1.isPrime(-20) , false);
//
//    //Primes
//    EXPECT_EQ(gf1.isPrime(2) , true);
//    EXPECT_EQ(gf1.isPrime(3) , true);
//    EXPECT_EQ(gf1.isPrime(-3) , true); //v1.1 edit: we should take the absolute value
//    EXPECT_EQ(gf1.isPrime(11) , true);
//    EXPECT_EQ(gf1.isPrime(2147482801) , true);
//
//}
//
//TEST(GFieldTest , CreateNumber)
//{
//    GField gf1(2 , 5);
//    //In field's range (0-31)
//    EXPECT_EQ(gf1.createNumber(10).getNumber() , 10);
//    EXPECT_EQ(gf1.createNumber(25).getNumber() , 25);
//
//    //bigger than field's range
//    EXPECT_EQ(gf1.createNumber(32).getNumber() , 0);
//    EXPECT_EQ(gf1.createNumber(32 * 1234567).getNumber() , 0);
//
//    //negative numbers
//    EXPECT_EQ(gf1.createNumber(-10).getNumber() , 22);
//    EXPECT_EQ(gf1.createNumber(-100).getNumber() , 28);
//
//    //Checking the number's field ,should equal GF(2**5)
//    EXPECT_EQ(gf1.createNumber(10).getField() , gf1);
//
//}
//
//TEST(GFieldTest , EqualsOperator)
//{
//    GField a(5 , 10);
//    GField b(5 , 11);
//    GField c;
//
//    a = b;
//    EXPECT_EQ(a.getOrder() , b.getOrder());
//
//    //To check if you are holding the addresses of b's values (which you shouldn't ;should copy by value)
//    b = c;
//    EXPECT_NE(a.getOrder() , b.getOrder());
//
//
//    EXPECT_EQ(b.getOrder() , c.getOrder());
//
//}
//
//TEST(GFieldTest , EqualsCompOperator)
//{
//    GField a(5 , 10);
//    GField b(5 , 10);
//    GField c;
//
//    EXPECT_EQ(a == b , true);
//    EXPECT_EQ(a == c , false);
//
//}
//
//TEST(GFieldTest , NotEqualOperator)
//{
//    GField a(5 , 10);
//    GField b(5 , 10);
//    GField c;
//
//    EXPECT_EQ(a != b , false);
//    EXPECT_EQ(a != c , true);
//}
//
//
//TEST(GFieldTest , OutputStreamOperator)
//{
//    GField gField1 , gField2(3 , 10);
//
//    std::ostringstream out1 , out2;
//
//    //Note : if you are failing this (says that nothing is printed but you do print) ,its probably
//    //because you are not editing it on the actual object (you are receiving in not &in)
//
//    (out1 << gField1);
//    EXPECT_EQ(out1.str() , "GF(2**1)");
//
//    (out2 << gField2);
//    EXPECT_EQ(out2.str() , "GF(3**10)");
//
//}
//
//TEST(GFieldTest , InputStreamOperator)
//{
//    GField gField;
//
//    using namespace std;
//    istringstream in("3 10");
//    cin.rdbuf(in.rdbuf());
//
//    cin >> gField;
//
//    EXPECT_EQ(gField.getChar() , 3);
//    EXPECT_EQ(gField.getDegree() , 10);
//
//}
//
///**
// * GFNumber related tests.
// */
//
//
//TEST(GFNumberTest , NumberDefaultConstructor)
//{
//    GFNumber gfNumber;
//    EXPECT_EQ(gfNumber.getNumber() , 0);
//    EXPECT_EQ(gfNumber.getField().getChar() , 2);
//    EXPECT_EQ(gfNumber.getField().getDegree() , 1);
//    EXPECT_EQ(gfNumber.getField().getOrder() , 2);
//}
//
//TEST(GFNumberTest , NumberConstructor1)
//{
//
//    //Normal
//    GFNumber gfNumber1(1);
//    EXPECT_EQ(gfNumber1.getNumber() , 1);
//    EXPECT_EQ(gfNumber1.getField().getChar() , 2);
//    EXPECT_EQ(gfNumber1.getField().getDegree() , 1);
//    EXPECT_EQ(gfNumber1.getField().getOrder() , 2);;
//
//    //Bigger than the field's order
//    GFNumber gfNumber2(4);
//    EXPECT_EQ(gfNumber2.getNumber() , 0);
//    EXPECT_EQ(gfNumber2.getField().getChar() , 2);
//    EXPECT_EQ(gfNumber2.getField().getDegree() , 1);
//    EXPECT_EQ(gfNumber2.getField().getOrder() , 2);
//
//    //Negative num
//    GFNumber gfNumber3(-1);
//    EXPECT_EQ(gfNumber3.getNumber() , 1);
//    EXPECT_EQ(gfNumber3.getField().getChar() , 2);
//    EXPECT_EQ(gfNumber3.getField().getDegree() , 1);
//    EXPECT_EQ(gfNumber3.getField().getOrder() , 2);;
//}
//
//TEST(GFNumberTest , NumberConstructor2)
//{
//    GField gField1;
//    //Negative num
//    GFNumber gfNumber1(-1 , gField1);
//    EXPECT_EQ(gfNumber1.getNumber() , 1);
//    EXPECT_EQ(gfNumber1.getField().getChar() , 2);
//    EXPECT_EQ(gfNumber1.getField().getDegree() , 1);
//    EXPECT_EQ(gfNumber1.getField().getOrder() , 2);;
//
//    GField gField2(11 , 2);
//
//    //Normal num in the field 11^2
//    GFNumber gfNumber2(3 , gField2);
//    EXPECT_EQ(gfNumber2.getNumber() , 3);
//    EXPECT_EQ(gfNumber2.getField().getChar() , 11);
//    EXPECT_EQ(gfNumber2.getField().getDegree() , 2);
//    EXPECT_EQ(gfNumber2.getField().getOrder() , 121);
//
//    //Larger than the field's order
//    GFNumber gfNumber3(125 , gField2);
//    EXPECT_EQ(gfNumber3.getNumber() , 4);
//    EXPECT_EQ(gfNumber3.getField().getChar() , 11);
//    EXPECT_EQ(gfNumber3.getField().getDegree() , 2);
//    EXPECT_EQ(gfNumber3.getField().getOrder() , 121);
//
//
//    //These examples are actually related to GField but added them here too
//
//    //Should cause assertion failure because it's not prime
//    ASSERT_DEATH(GFNumber(125 , GField(6 , 1)) , "p");
////    ASSERT_DEATH(GFNumber(125 , GField(6 , 1)) , "isPrime\\(p\\)"); //This should be the actual message
//
//
//    //Should c assertion failure because l should be >0
//    ASSERT_DEATH(GFNumber(125 , GField(11 , 0)) , "p");
////    ASSERT_DEATH(GFNumber(125 , GField(11 , 0)) , "l > 0");//This should be the actual message
//    ASSERT_DEATH(GFNumber(125 , GField(11 , -1)) , "p");
//
////    ASSERT_DEATH(GFNumber(125 , GField(11 , -1)) , "l > 0");//This should be the actual message
//
//
//}
//
//TEST(GFNumberTest , NCopyConstructor)
//{
//    GField gField(11 , 2);
//
//    GFNumber gfNumber1(3 , gField);
//    GFNumber gfNumber2(gfNumber1);
//
//    EXPECT_EQ(gfNumber2.getNumber() , gfNumber1.getNumber());
//    EXPECT_EQ(gfNumber2.getField() , gfNumber1.getField());
//
//    GFNumber gfNumber3(130 , gField);
//    GFNumber gfNumber4(gfNumber3);
//
//    EXPECT_EQ(gfNumber4.getNumber() , gfNumber3.getNumber());
//    EXPECT_EQ(gfNumber4.getField() , gfNumber3.getField());
//}
//
//TEST(GFNumberTest , GetNumber)
//{
//    GFNumber number(4 , GField(2 , 3));
//
//    EXPECT_EQ(GFNumber().getNumber() , 0);
//    EXPECT_EQ(GFNumber(4).getNumber() , 0);
//    EXPECT_EQ(number.getNumber() , 4);
//    EXPECT_EQ(GFNumber(number).getNumber() , 4);
//
//}
//
//TEST(GFNumberTest , GetField)
//{
//    GFNumber number(4 , GField(2 , 3));
//
//    EXPECT_EQ(GFNumber().getField().getOrder() , 2);
//    EXPECT_EQ(GFNumber(4).getField().getOrder() , 2);
//    EXPECT_EQ(number.getField().getOrder() , 8);
//    EXPECT_EQ(GFNumber(number).getField().getOrder() , 8);
//}
//
//
///**
// * This tests both
// */
//TEST(GFNumberTest , GetPrimeFactors)
//{
//    GField gField(11 , 2);
//    GFNumber number0(0 , gField);
//    GFNumber number1(1 , gField);
//    GFNumber numberEven(16 , gField);
//    GFNumber numberOdd(25 , gField);
//    GFNumber numberPrime17(17 , gField);
//    GFNumber numberPrimeBig(2979367769891 , GField(2 , 42));
//
//    int numOfFactors = 0;
//
//    GFNumber *factors = number0.getPrimeFactors(&numOfFactors);
//    EXPECT_EQ(numOfFactors , 0);
//    delete[]factors;
//
//    numOfFactors = 0;
//    factors = number1.getPrimeFactors(&numOfFactors);
//    EXPECT_EQ(numOfFactors , 0);
//    delete[]factors;
//
//    numOfFactors = 0;
//    factors = numberEven.getPrimeFactors(&numOfFactors);
//    EXPECT_EQ(numOfFactors , 4);
//
//    for (int i = 0; i < numOfFactors; i++)
//    {
//        EXPECT_EQ(factors[i].getNumber() , 2);
//    }
//    delete[]factors;
//
//    numOfFactors = 0;
//    factors = numberOdd.getPrimeFactors(&numOfFactors);
//    EXPECT_EQ(numOfFactors , 2);
//    EXPECT_EQ(factors[0].getNumber() , 5);
//    EXPECT_EQ(factors[1].getNumber() , 5);
//
//    delete[]factors;
//
//    numOfFactors = 0;
//    factors = numberPrime17.getPrimeFactors(&numOfFactors);
//    EXPECT_EQ(numOfFactors , 0);
//    delete[]factors;
//
//    numOfFactors = 0;
//    factors = numberPrimeBig.getPrimeFactors(&numOfFactors);
//    EXPECT_EQ(numOfFactors , 2);
//
//    //Order is not imporant
//    long n1 = factors[0].getNumber() , n2 = factors[1].getNumber() , temp = 0;
//    delete[]factors;
//
//    if (n1 > n2)
//    {
//        temp = n2;
//        n2 = n1;
//        n1 = temp;
//    }
//
//    EXPECT_EQ(n1 , 101);
//    EXPECT_EQ(n2 , 29498690791);
//
//}
//
//TEST(GFNumberTest , GetIsPrime)
//{
//    GField gField(11 , 2);
//    EXPECT_EQ(GFNumber(5 , gField).getIsPrime() , true);//prime
//    EXPECT_EQ(GFNumber(5 , GField(2 , 2)).getIsPrime() , false); // not prime in the field
//    EXPECT_EQ(GFNumber(6 , gField).getIsPrime() , false);//not prime
//}
//
//TEST(GFNumberTest , OpEqualsGFNum) // =
//{
//    GField gf1(2 , 3) , gf2(2 , 11);
//    GFNumber gfNumber1(9 , gf2);
//    GFNumber temp(gfNumber1);
//
//    GFNumber gfNumber2(2 , gf1);
//
//    gfNumber1 = gfNumber2;
//    EXPECT_EQ(gfNumber1.getNumber() , 2);
//
//    gfNumber2 = temp; //v1.2 edit It should take both the field and the number? TODO check default = or just the number v1.2 edit
//    EXPECT_EQ(gfNumber2.getNumber() , 9);
//}
//
//TEST(GFNumberTest , Op_P_GFNum) // + GFNumber
//{
//    GField gf2(11 , 2);
//    GFNumber gfNumber1(9 , gf2);
//    GFNumber gfNumber2(gfNumber1);
//    GFNumber gfNumber3(120 , gf2);
//    GFNumber gfNumber4;
//
//    EXPECT_EQ((gfNumber1 + gfNumber2).getNumber() , 18); // 9+9
//    EXPECT_EQ(gfNumber1.getNumber() , 9); // shouldn't change
//    EXPECT_EQ(gfNumber2.getNumber() , 9); // shouldn't change
//
//
//    EXPECT_EQ((gfNumber2 + gfNumber3).getNumber() , 8); // 128 %121
//
//    //Should cause assertion failure because they are not from the same field
//    ASSERT_DEATH(gfNumber1 + gfNumber4 , "p");
////  ASSERT_DEATH(gfNumber1+gfNumber4,"this->_gf == other\\._gf"); // This should be the the actual message
//
//}
//
//TEST(GFNumberTest , Op_P_Long) // + long
//{
//    GFNumber gfNumber1(9 , GField(11 , 2));
//
//    EXPECT_EQ((gfNumber1 + 12).getNumber() , 21);
//    EXPECT_EQ((gfNumber1).getNumber() , 9);//shouldn't get affected
//    EXPECT_EQ((gfNumber1 + 120).getNumber() , 8);
//
//}
//
//TEST(GFNumberTest , Op_PE_GFNum) // += GFNumber
//{
//    GField gf2(11 , 2);
//    GFNumber gfNumber1(9 , gf2);
//    GFNumber gfNumber2(gfNumber1);
//    GFNumber gfNumber3(120 , gf2);
//    GFNumber gfNumber4;
//
//    gfNumber1 += gfNumber2;
//    EXPECT_EQ(gfNumber1.getNumber() , 18); // 9+9
//    EXPECT_EQ(gfNumber2.getNumber() , 9); // shouldn't change
//
//    gfNumber2 += gfNumber3;
//    EXPECT_EQ(gfNumber2.getNumber() , 8); // 128 %121
//
//    //Should cause assertion failure because they are not from the same field
//    ASSERT_DEATH(gfNumber1 += gfNumber4 , "p");
////  ASSERT_DEATH(gfNumber1+=gfNumber4,"this->_gf == newN\\._gf");// This should be the the actual message
//
//}
//
//TEST(GFNumberTest , Op_PE_Long) // += long
//{
//    GField gf2(11 , 2);
//    GFNumber gfNumber1(9 , gf2);
//
//    EXPECT_EQ((gfNumber1 += 12).getNumber() , 21);
//    EXPECT_EQ((gfNumber1).getNumber() , 21);//should get affected
//    EXPECT_EQ((gfNumber1 += 120).getNumber() , 20); //120+21 %121
//
//    EXPECT_EQ((gfNumber1 += (-30)).getNumber() , 111); //-10 %121
//
//}
//
//TEST(GFNumberTest , Op_M_GFNum) // - GFNumber
//{
//    GField gf2(11 , 2);
//    GFNumber gfNumber1(9 , gf2);
//    GFNumber gfNumber2(gfNumber1);
//    GFNumber gfNumber3(120 , gf2);
//    GFNumber gfNumber4;
//
//    EXPECT_EQ((gfNumber1 - gfNumber2).getNumber() , 0);
//    EXPECT_EQ(gfNumber1.getNumber() , 9); // shouldn't change
//    EXPECT_EQ(gfNumber2.getNumber() , 9); // shouldn't change
//
//
//    EXPECT_EQ((gfNumber2 - gfNumber3).getNumber() , 10); //(9-120) %121
//
//    //Should cause assertion failure because they are not from the same field
//    ASSERT_DEATH(gfNumber1 - gfNumber4 , "p");
////  ASSERT_DEATH(gfNumber1-gfNumber4,"this->_gf == other\\._gf"); // This should be the the actual message
//}
//
//TEST(GFNumberTest , Op_M_Long) // - long
//{
//    GFNumber gfNumber1(9 , GField(11 , 2));
//
//    EXPECT_EQ((gfNumber1 - 12).getNumber() , 118);
//    EXPECT_EQ((gfNumber1).getNumber() , 9);//shouldn't get affected
//    EXPECT_EQ((gfNumber1 - 2).getNumber() , 7);
//}
//
//TEST(GFNumberTest , Op_ME_GFNum) // -= GFNumber
//{
//    GField gf2(11 , 2);
//    GFNumber gfNumber1(9 , gf2);
//    GFNumber gfNumber2(gfNumber1);
//    GFNumber gfNumber3(120 , gf2);
//    GFNumber gfNumber4;
//
//    gfNumber1 -= gfNumber2;
//    EXPECT_EQ(gfNumber1.getNumber() , 0); // 9-9
//    EXPECT_EQ(gfNumber2.getNumber() , 9); // shouldn't change
//
//    gfNumber2 -= gfNumber3;
//    EXPECT_EQ(gfNumber2.getNumber() , 10); // -111% 121
//
//    //Should cause assertion failure because they are not from the same field
//    ASSERT_DEATH(gfNumber1 -= gfNumber4 , "p");
////  ASSERT_DEATH(gfNumber1-=gfNumber4,"this->_gf == newN\\._gf");// This should be the the actual message
//}
//
//TEST(GFNumberTest , Op_ME_Long) // -= long
//{
//    GFNumber gfNumber1(9 , GField(11 , 2));
//
//    EXPECT_EQ((gfNumber1 -= 12).getNumber() , 118);
//    EXPECT_EQ((gfNumber1).getNumber() , 118);//should get affected
//    EXPECT_EQ((gfNumber1 -= (-9)).getNumber() , 6);
//    EXPECT_EQ((gfNumber1 -= (-9)).getNumber() , 15);
//
//}
//
//TEST(GFNumberTest , Op_Mult_GFNum)// * GFNumber
//{
//    GField gf2(11 , 2);
//    GFNumber gfNumber1(9 , gf2);
//    GFNumber gfNumber2(gfNumber1);
//    GFNumber gfNumber3(120 , gf2);
//    GFNumber gfNumber4;
//
//    EXPECT_EQ((gfNumber1 * gfNumber2).getNumber() , 81);
//    EXPECT_EQ(gfNumber1.getNumber() , 9); // shouldn't change
//    EXPECT_EQ(gfNumber2.getNumber() , 9); // shouldn't change
//
//
//    EXPECT_EQ((gfNumber2 * gfNumber3).getNumber() , 112); //(9*120) %121
//
//    //Should cause assertion failure because they are not from the same field
//    ASSERT_DEATH(gfNumber1 * gfNumber4 , "p");
////  ASSERT_DEATH(gfNumber1*gfNumber4,"this->_gf == other\\._gf"); // This should be the the actual message
//}
//
//TEST(GFNumberTest , Op_Mult_Long)// * long
//{
//    GFNumber gfNumber1(9 , GField(11 , 2));
//
//    EXPECT_EQ((gfNumber1 * 12).getNumber() , 108);
//    EXPECT_EQ((gfNumber1).getNumber() , 9);//shouldn't get affected
//    EXPECT_EQ((gfNumber1 * -1).getNumber() , 112);
//}
//
//TEST(GFNumberTest , Op_EMult_GFNum)// *= GFNumber
//{
//    GField gf2(11 , 2);
//    GFNumber gfNumber1(9 , gf2);
//    GFNumber gfNumber2(gfNumber1);
//    GFNumber gfNumber3(120 , gf2);
//    GFNumber gfNumber4;
//
//    gfNumber1 *= gfNumber2;
//    EXPECT_EQ(gfNumber1.getNumber() , 81); // 9*9
//    EXPECT_EQ(gfNumber2.getNumber() , 9); // shouldn't change
//
//    gfNumber2 *= gfNumber3;
//    EXPECT_EQ(gfNumber2.getNumber() , 112); // 1080% 121
//
//    //Should cause assertion failure because they are not from the same field
//    ASSERT_DEATH(gfNumber1 *= gfNumber4 , "p");
////  ASSERT_DEATH(gfNumber1*=gfNumber4,"this->_gf == newN\\._gf");// This should be the the actual message
//}
//
//TEST(GFNumberTest , Op_EMult_Long)// *= long
//{
//    GFNumber gfNumber1(9 , GField(11 , 2));
//
//    EXPECT_EQ((gfNumber1 *= 12).getNumber() , 108);
//    EXPECT_EQ((gfNumber1).getNumber() , 108);//should get affected
//    EXPECT_EQ((gfNumber1 *= (-9)).getNumber() , 117);
//}
//
//TEST(GFNumberTest , Op_Modulu_GFNum)// % GFNumber
//{
//    GField gf2(11 , 2);
//    GFNumber gfNumber1(9 , gf2);
//    GFNumber gfNumber2(gfNumber1);
//    GFNumber gfNumber3(120 , gf2);
//    GFNumber gfNumber4;
//
//    EXPECT_EQ((gfNumber1 % gfNumber2).getNumber() , 0);
//    EXPECT_EQ(gfNumber1.getNumber() , 9); // shouldn't change
//    EXPECT_EQ(gfNumber2.getNumber() , 9); // shouldn't change
//
//
//    EXPECT_EQ((gfNumber2 % gfNumber3).getNumber() , 9); //(9%120) %121
//
//    //Should cause assertion failure because they are not from the same field
//    ASSERT_DEATH(gfNumber1 % gfNumber4 , "p");
////  ASSERT_DEATH(gfNumber1%gfNumber4,"this->_gf == other\\._gf"); // This should be the the actual message
//}
//
//TEST(GFNumberTest , Op_Modulu_Long)// % long
//{
//    GFNumber gfNumber1(9 , GField(11 , 2));
//
//    EXPECT_EQ((gfNumber1 % 4).getNumber() , 1);
//    EXPECT_EQ((gfNumber1).getNumber() , 9);//shouldn't get affected
//    EXPECT_EQ((gfNumber1 % -115).getNumber() , 3);
//}
//
//TEST(GFNumberTest , Op_EModulu_GFNum)// %= GFNumber
//{
//    GField gf2(11 , 2);
//    GFNumber gfNumber1(9 , gf2);
//    GFNumber gfNumber2(gfNumber1);
//    GFNumber gfNumber3(120 , gf2);
//    GFNumber gfNumber4;
//
//    gfNumber1 %= gfNumber2;
//    EXPECT_EQ(gfNumber1.getNumber() , 0); // 9%9
//    EXPECT_EQ(gfNumber2.getNumber() , 9); // shouldn't change
//
//    gfNumber2 %= gfNumber3;
//    EXPECT_EQ(gfNumber2.getNumber() , 9); //9% 120
//
//
//    gfNumber3 %= gfNumber2;
//    EXPECT_EQ(gfNumber3.getNumber() , 3); // 120%9
//
//    //Should cause assertion failure because they are not from the same field
//    ASSERT_DEATH(gfNumber1 %= gfNumber4 , "p");
////  ASSERT_DEATH(gfNumber1%=gfNumber4,"this->_gf == newN\\._gf");// This should be the the actual message
//}
//
//TEST(GFNumberTest , Op_EModulu_Long)// %= long
//{
//    GFNumber gfNumber1(9 , GField(11 , 2));
//
//    EXPECT_EQ((gfNumber1 %= 12).getNumber() , 9);
//    EXPECT_EQ((gfNumber1).getNumber() , 9);//should get affected
//    EXPECT_EQ((gfNumber1 %= (-116)).getNumber() , 4);
//    EXPECT_EQ((gfNumber1 %= (1)).getNumber() , 0);
//}
//
//TEST(GFNumberTest , OP_Comp_EQ)
//{
//    GFNumber a(8 , GField(11 , 2));
//    GFNumber b(8 , GField(11 , 3));
//    GFNumber c(a);
//    GFNumber d;
//
//    // Edit v1.3 : It should compare based on n and order (not p)
//    // Reference :https://moodle2.cs.huji.ac.il/nu18/mod/forum/discuss.php?d=74687
//    EXPECT_EQ(a == b , false);
//
//    EXPECT_EQ(a == c , true);
//    EXPECT_EQ(a == d , false);
//
//}
//
//TEST(GFNumberTest , OP_Comp_NE)
//{
//    GFNumber a(8 , GField(11 , 2));
//    GFNumber b(8 , GField(11 , 3));
//    GFNumber c(a);
//    GFNumber d;
//
//
//    // Edit v1.3 : It should compare based on n and order (not p)
//    // Reference :https://moodle2.cs.huji.ac.il/nu18/mod/forum/discuss.php?d=74687
//    EXPECT_EQ(a != b , true);
//
//    EXPECT_EQ(a != c , false);
//    EXPECT_EQ(a != d , true);
//}
//
//TEST(GFNumberTest , OP_Comp_GT)
//{
//    GField gField(11 , 2);
//    GFNumber a(8 , gField);
//    GFNumber b(8 , gField);
//    GFNumber c(9 , gField);
//    GFNumber d(7 , GField());
//
//    EXPECT_EQ(c > a , true);
//    EXPECT_EQ(a > b , false);
//    EXPECT_EQ(a > c , false);
//
//    ASSERT_DEATH(a > d , "p");
////  ASSERT_DEATH(a > d ,"this->_gf == gfNumber._gf");// This should be the the actual message
//}
//
//TEST(GFNumberTest , OP_Comp_EGT)
//{
//    GField gField(11 , 2);
//    GFNumber a(8 , gField);
//    GFNumber b(8 , gField);
//    GFNumber c(9 , gField);
//    GFNumber d(7 , GField());
//
//    EXPECT_EQ(a >= b , true);
//    EXPECT_EQ(c >= a , true);
//    EXPECT_EQ(a >= c , false);
//
//    ASSERT_DEATH(a >= d , "p");
////  ASSERT_DEATH(a >= d ,"this->_gf == gfNumber._gf");// This should be the the actual message
//}
//
//TEST(GFNumberTest , OP_Comp_ST)
//{
//    GField gField(11 , 2);
//    GFNumber a(8 , gField);
//    GFNumber b(8 , gField);
//    GFNumber c(9 , gField);
//    GFNumber d(7 , GField());
//
//    EXPECT_EQ(c < a , false);
//    EXPECT_EQ(a < b , false);
//    EXPECT_EQ(a < c , true);
//
//    ASSERT_DEATH(a < d , "p");
////  ASSERT_DEATH(a < d ,"this->_gf == gfNumber._gf");// This should be the the actual message
//}
//
//TEST(GFNumberTest , OP_Comp_EST)
//{
//    GField gField(11 , 2);
//    GFNumber a(8 , gField);
//    GFNumber b(8 , gField);
//    GFNumber c(9 , gField);
//    GFNumber d(7 , GField());
//
//    EXPECT_EQ(c <= a , false);
//    EXPECT_EQ(a <= b , true);
//    EXPECT_EQ(a <= c , true);
//
//    ASSERT_DEATH(a <= d , "p");
////  ASSERT_DEATH(a <= d ,"this->_gf == gfNumber._gf");// This should be the the actual message
//}
//
//TEST(GFieldTest , OutputStreamOperatorGFNum)
//{
//    GFNumber gfNumber1 , gfNumber2(10 , GField(11 , 2));
//    std::ostringstream out1 , out2;
//
//    //Note : if you are failing this (says that nothing is printed but you do print) ,its probably
//    //because you are not editing it on the actual object (you are receiving in not &in)
//
//    (out1 << gfNumber1);
//    EXPECT_EQ(out1.str() , "0 GF(2**1)");
//
//    (out2 << gfNumber2);
//    EXPECT_EQ(out2.str() , "10 GF(11**2)");
//}
//
//TEST(GFieldTest , InputStreamOperatorGFNum)
//{
//    GFNumber gfNumber;
//    using namespace std;
//    istringstream in("8 11 2");
//    cin.rdbuf(in.rdbuf());
//
//    cin >> gfNumber;
//    EXPECT_EQ(gfNumber.getNumber() , 8);
//    EXPECT_EQ(gfNumber.getField().getChar() , 11);
//    EXPECT_EQ(gfNumber.getField().getDegree() , 2);
//
//}