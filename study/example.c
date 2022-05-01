#include <stdio.h>

int main() {
	int arr[] = { 10, 20, 30 };

	printf("address0 = %u\n", arr);    // ex) 17823472
	printf("address0 = %u\n", &arr[0]);

	printf("address1 = %u\n", arr + 1);
	printf("address1 = %u\n", &arr[1]);

	printf("address2 = %u\n", arr + 2);
	printf("address2 = %u\n", &arr[2]);

	return 0;
}