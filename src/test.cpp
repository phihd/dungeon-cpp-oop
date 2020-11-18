#include <iostream>
using namespace std;
/* A test instance*/
int testInstance1()
{
   if (7 == 9)
      return 1;
   else
      return 0;
}

/* A temporary testing solution built on CTest. 
 * This needs to be changed due to limited documentation. 
 * Also, this method is not practical. 
 */
int main()
{
   /* The return code for this test instance. 0=pass*/
   int s = 0;
   s |= testInstance1(); // Whenever a test failed, the status code got changed to a non-zero value
   s |= 7 == 9;          // This does not work as expected because `false` is evaluated to 0
   return s;
}
