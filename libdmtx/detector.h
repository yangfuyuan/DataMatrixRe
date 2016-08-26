
#ifndef __DETECTOR_H__
#define __DETECTOR_H__

#ifdef __cplusplus
extern "C" {
#endif

#define DMTX_RETURN_OK                0
#define DMTX_RETURN_NO_MEMORY         1
#define DMTX_RETURN_INVALID_ARGUMENT  2
#define DMTX_RETURN_DECODE_ERROR      3


#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "dmtx.h"

typedef struct corner_t
{
    int x;
    int y;
}corner_t;

typedef struct corners_t
{
    corner_t corner0;
    corner_t corner1;
    corner_t corner2;
    corner_t corner3;
}corners_t;

typedef struct dmtx_decoded_t
{
	char *data;
    int angle;
    int x;
    int y;
}dmtx_decoded_t;







dmtx_decoded_t *dmtx_decode(unsigned char *im,
                            int width,
                            int height,
                            int pack,
                            int timeoutms);

void
dmtx_decoded_destroy (dmtx_decoded_t *result);


#ifdef __cplusplus
}
#endif

#endif  // #ifndef _DETECTOR_H
