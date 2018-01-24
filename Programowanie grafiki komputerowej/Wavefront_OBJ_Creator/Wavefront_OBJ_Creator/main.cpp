#include "Wavefront_OBJ_Creator.h"

int main(void)
{
class WavefrontOBJCreator W;
unsigned long int done;

done = W.CreateWavefrontFile("bitmap.pgm","result.obj");
fprintf(stdout,"Creating Wavefront file...\nReturn code = %lu\n",done);
getchar();

return (0);
};
