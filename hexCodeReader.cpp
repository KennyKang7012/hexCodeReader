// hexCodeReader.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include <iostream>
#include <stdio.h>

// 將16進制轉換為10進制
int hexToDec(unsigned char hex) {
	if (hex >= '0' && hex <= '9') {
		return hex - '0';
	}
	else if (hex >= 'A' && hex <= 'F') {
		return hex - 'A' + 10;
	}
	else if (hex >= 'a' && hex <= 'f') {
		return hex - 'a' + 10;
	}
	return 0; // 錯誤處理，如果不是有效的16進制數字，返回0
}

int main() 
{
	FILE *file;
	long fileSize;
	unsigned char *data;

	// 開啟檔案
	file = fopen("1.txt", "r");
	if (file == NULL) {
		printf("無法開啟檔案\n");
		return 1;
	}

	// 取得檔案大小
	fseek(file, 0, SEEK_END);
	fileSize = ftell(file);
	fseek(file, 0, SEEK_SET);
	printf("fileSize = %d\r\n", fileSize);

	// 分配記憶體空間
	data = (unsigned char *)malloc(fileSize);
	if (data == NULL) {
		printf("記憶體分配失敗\n");
		fclose(file);
		return 1;
	}

	// 讀取檔案內容
	size_t bytesRead = fread(data, sizeof(unsigned char), fileSize, file);
	printf("bytesRead = %zd\r\n", bytesRead);
	if (bytesRead != fileSize) {
		printf("讀取檔案失敗\n");
		fclose(file);
		free(data);
		return 1;
	}

	// 讀取並解析HEX碼
	//unsigned int hexValue;
	//while (fscanf(file, "0x%02x,", &hexValue) == 1) {
	//	printf("0x%02X ", hexValue);
	//}

	// 關閉檔案
	fclose(file);

	// 組成byte並打印
	for (long i = 0; i < fileSize; i += 5) {
		unsigned char byte = (unsigned char)((hexToDec(data[i + 2]) << 4) | hexToDec(data[i + 3]));
		printf("0x%02X ", byte);
	}
	printf("\n");

	// 釋放記憶體
	free(data);

	system("pause");
	return 0;
}
