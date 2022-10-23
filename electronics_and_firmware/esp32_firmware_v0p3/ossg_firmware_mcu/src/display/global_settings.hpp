//#define LGFX_USE_V1

/*
The maximum resolution that can be output depends on the signal type.
720x480 (NTSC,NTSC-J), 864x576 (PAL,PAL-M), 720x576 (PAL-N).

Any resolution less than the maximum resolution can be set.
It is recommended to specify the resolution obtained by dividing the maximum resolution by an integer.
If you specify any other resolution, the ratio of pixels will vary depending on the location, 
and the display will be slightly distorted.

Notes:

(For width)
720/1.125 = 640
480/1.125 = 426.666667

(For height) Works sometimes???
720/1.2 = 600
480/1.2 = 400

(x/1.5) <=== HIGHEST CURRENT WORKING
720/1.5 = 480
480/1.5 = 320

(x/2) = 360
720/2 = 240

Max res 720x480 will usually not display anything... too much memory?
*/

//Change screen res here
#define AV_WIDTH_OG 480 
#define AV_HEIGHT_OG 320
#define AV_SAFEZONE 0

//Reference these for runtime shit
#define AV_WIDTH AV_WIDTH_OG - AV_SAFEZONE
#define AV_HEIGHT AV_HEIGHT_OG - AV_SAFEZONE