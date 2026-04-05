
void revArr(int *arr){
  int tmp;
  for(int i = 0, j = SIZE-1; i < j; i++, j--)
    tmp = arr[i];
  arr[i] = arr[j];
  arr[j] = tmp;
}
