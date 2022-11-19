template <typename T>  // or template<class T>  
// parameter T as placeholder for the type of data    
T maximum(T value1, T value2, T value3) 
{
   // T maximumValue{value1}; // C++14, assume value1 is maximum    
    T maximumValue = value1;
   // determine whether value2 is greater than maximumValue
   if (value2 > maximumValue) {
      maximumValue = value2;
   }

   // determine whether value3 is greater than maximumValue
   if (value3 > maximumValue) {
      maximumValue = value3;
   }

   return maximumValue;
}
