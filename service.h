#ifndef FILES_H
#define FILES_H

void writeProduct(const char *fileName, int productCode, const char *productName, double productPrice);
void readProduct();
void updateProduct(int productCode);
void deleteProduct();

#endif
