
#include "detector.h"




dmtx_decoded_t *dmtx_decode(unsigned char *im, int width, int height,int pack, int timeoutms)
{
    DmtxImage *img = NULL;
    DmtxDecode *decode = NULL;
    DmtxRegion *region = NULL;
    DmtxMessage *msg = NULL;
    DmtxTime msec, *timeout = NULL;
    DmtxVector2 p00, p10, p11, p01;
    double rotate;

    dmtx_decoded_t *result = NULL;
    img = dmtxImageCreate(im, width, height, pack);

    if (img == NULL) return NULL;
    int heights = dmtxImageGetProp(img, DmtxPropHeight);

    decode = dmtxDecodeCreate(img, 1);
    if(decode == NULL) return NULL;

    dmtxDecodeSetProp(decode, DmtxPropSymbolSize, 1);
    dmtxDecodeSetProp(decode, DmtxPropScheme, 0);

    timeout = (timeoutms != DmtxUndefined) ? &msec : NULL;
    if (timeout != NULL)
        msec = dmtxTimeAdd(dmtxTimeNow(), timeoutms);

    region = dmtxRegionFindNext(decode, timeout);

    if(region != NULL) {
        result = (dmtx_decoded_t *)calloc(1, sizeof(dmtx_decoded_t));

        p00.X = p00.Y = p10.Y = p01.X = 0.0;
        p10.X = p01.Y = p11.X = p11.Y = 1.0;
        dmtxMatrix3VMultiplyBy(&p00, region->fit2raw);
        dmtxMatrix3VMultiplyBy(&p10, region->fit2raw);
        dmtxMatrix3VMultiplyBy(&p11, region->fit2raw);
        dmtxMatrix3VMultiplyBy(&p01, region->fit2raw);

        int x0 = (int)(p00.X + 0.5);
        int y0 = (int)(heights - 1 - (int)(p00.Y + 0.5));
        int x1 = (int)(p01.X + 0.5);
        int y1 = (int)(heights - 1 - (int)(p01.Y + 0.5));
        int x2 = (int)(p10.X + 0.5);
        int y2 = (int)(heights - 1 - (int)(p10.Y + 0.5));
        int x3 = (int)(p11.X + 0.5);
        int y3 = (int)(heights - 1 - (int)(p11.Y + 0.5));



        int centerx =  (x0 + x1 + x2 + x3) / 4;
        int centery = (y0 + y1 + y2 + y3) / 4;

        int offsetx = centerx - width / 2 ;
        int offsety = centery - height / 2;

        rotate = (2 * M_PI) + (atan2(region->fit2raw[0][1], region->fit2raw[1][1]) -
            atan2(region->fit2raw[1][0], region->fit2raw[0][0])) / 2.0;
        rotate = (rotate * 180/M_PI);  // degrees
        if (rotate >= 360) rotate -= 360;

        result->angle = (int) (rotate + 0.5);

        msg = dmtxDecodeMatrixRegion(decode, region, DmtxUndefined);
        if (msg != NULL) {
            result->data = (char*)calloc(1, msg->outputSize-2);
            if (result->data != NULL) {
                memcpy(result->data, msg->output +2, msg->outputSize-2);



                result->x = (((int)(*(msg->output)) - 48)*2 -9)*10 + (int)(offsetx*3 / 16);
                result->y = (((int)(*(msg->output + 1)) - 48)*2 - 9)*10 + (int)(offsety*3 / 16);
            }

            dmtxMessageDestroy(&msg);
        }
        dmtxRegionDestroy(&region);

    }

    dmtxDecodeDestroy(&decode);
    dmtxImageDestroy(&img);

    return result;

}


void dmtx_decoded_destroy (dmtx_decoded_t *result)
{
    if(!result)
        return;
    if(!result->data)
        free(result->data);
    free(result);
}

