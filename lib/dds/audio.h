#ifndef __AUDIO__
#define __AUDIO__

#include "comlib.h"

#define SOUND_LEN 1024
#define SOUND_COUNT 4
#define SOUND_NAME_MAX_LEN 32


typedef uint16_t audio_sample_t;

typedef struct audio_t
{
	audio_sample_t *data;
	uint32_t len;
	char sound_name[SOUND_NAME_MAX_LEN];
} audio_t;


static audio_sample_t sound_theremin[SOUND_LEN] = {
	0x090F, 0x091E, 0x092C, 0x093B, 0x0948, 0x0957, 0x0964, 0x0973, 0x0981, 0x098F, 0x099E, 0x09AB, 0x09BA, 0x09C7, 0x09D6, 0x09E3, 
	0x09F2, 0x09FF, 0x0A0D, 0x0A1A, 0x0A29, 0x0A36, 0x0A43, 0x0A52, 0x0A5F, 0x0A6D, 0x0A7A, 0x0A88, 0x0A95, 0x0AA2, 0x0AB0, 0x0ABD, 
	0x0ACA, 0x0AD8, 0x0AE5, 0x0AF2, 0x0B00, 0x0B0D, 0x0B1A, 0x0B26, 0x0B33, 0x0B41, 0x0B4E, 0x0B5A, 0x0B67, 0x0B73, 0x0B80, 0x0B8D, 
	0x0B99, 0x0BA6, 0x0BB2, 0x0BBE, 0x0BCB, 0x0BD7, 0x0BE4, 0x0BF0, 0x0BFC, 0x0C07, 0x0C14, 0x0C20, 0x0C2C, 0x0C37, 0x0C43, 0x0C4F, 
	0x0C5A, 0x0C66, 0x0C72, 0x0C7D, 0x0C89, 0x0C94, 0x0C9F, 0x0CAB, 0x0CB5, 0x0CC1, 0x0CCC, 0x0CD7, 0x0CE1, 0x0CED, 0x0CF7, 0x0D02, 
	0x0D0D, 0x0D17, 0x0D22, 0x0D2C, 0x0D36, 0x0D41, 0x0D4B, 0x0D56, 0x0D5F, 0x0D69, 0x0D73, 0x0D7D, 0x0D87, 0x0D91, 0x0D9A, 0x0DA4, 
	0x0DAD, 0x0DB7, 0x0DC0, 0x0DC9, 0x0DD3, 0x0DDC, 0x0DE5, 0x0DEE, 0x0DF6, 0x0DFF, 0x0E08, 0x0E11, 0x0E19, 0x0E22, 0x0E2B, 0x0E33, 
	0x0E3C, 0x0E44, 0x0E4C, 0x0E55, 0x0E5C, 0x0E65, 0x0E6C, 0x0E74, 0x0E7C, 0x0E83, 0x0E8B, 0x0E92, 0x0E99, 0x0EA2, 0x0EA9, 0x0EB0, 
	0x0EB6, 0x0EBD, 0x0EC5, 0x0ECC, 0x0ED3, 0x0ED9, 0x0EE0, 0x0EE6, 0x0EED, 0x0EF3, 0x0EF9, 0x0F00, 0x0F06, 0x0F0C, 0x0F12, 0x0F18, 
	0x0F1D, 0x0F23, 0x0F29, 0x0F2F, 0x0F35, 0x0F39, 0x0F3F, 0x0F45, 0x0F4A, 0x0F4F, 0x0F54, 0x0F59, 0x0F5E, 0x0F63, 0x0F68, 0x0F6C, 
	0x0F71, 0x0F75, 0x0F7A, 0x0F7F, 0x0F82, 0x0F87, 0x0F8B, 0x0F8F, 0x0F93, 0x0F97, 0x0F9B, 0x0F9F, 0x0FA2, 0x0FA5, 0x0FA9, 0x0FAC, 
	0x0FB0, 0x0FB3, 0x0FB7, 0x0FBA, 0x0FBC, 0x0FC0, 0x0FC3, 0x0FC6, 0x0FC8, 0x0FCB, 0x0FCE, 0x0FD0, 0x0FD2, 0x0FD5, 0x0FD7, 0x0FD9, 
	0x0FDC, 0x0FDE, 0x0FE0, 0x0FE2, 0x0FE4, 0x0FE5, 0x0FE8, 0x0FE9, 0x0FEA, 0x0FED, 0x0FEE, 0x0FEF, 0x0FF1, 0x0FF2, 0x0FF2, 0x0FF4, 
	0x0FF5, 0x0FF5, 0x0FF7, 0x0FF7, 0x0FF8, 0x0FF9, 0x0FF9, 0x0FFB, 0x0FFB, 0x0FFB, 0x0FFC, 0x0FFB, 0x0FFC, 0x0FFC, 0x0FFD, 0x0FFC, 
	0x0FFC, 0x0FFC, 0x0FFC, 0x0FFC, 0x0FFB, 0x0FFB, 0x0FFB, 0x0FFA, 0x0FFA, 0x0FF9, 0x0FF8, 0x0FF7, 0x0FF7, 0x0FF6, 0x0FF5, 0x0FF4, 
	0x0FF3, 0x0FF1, 0x0FF0, 0x0FEF, 0x0FED, 0x0FEC, 0x0FEB, 0x0FEA, 0x0FE8, 0x0FE6, 0x0FE5, 0x0FE3, 0x0FE1, 0x0FE0, 0x0FDE, 0x0FDC, 
	0x0FDA, 0x0FD8, 0x0FD6, 0x0FD4, 0x0FD1, 0x0FCF, 0x0FCD, 0x0FCA, 0x0FC8, 0x0FC5, 0x0FC2, 0x0FC0, 0x0FBD, 0x0FBA, 0x0FB7, 0x0FB5, 
	0x0FB2, 0x0FAF, 0x0FAD, 0x0FA9, 0x0FA6, 0x0FA3, 0x0F9F, 0x0F9D, 0x0F99, 0x0F96, 0x0F93, 0x0F8F, 0x0F8C, 0x0F88, 0x0F84, 0x0F81, 
	0x0F7E, 0x0F79, 0x0F76, 0x0F72, 0x0F6E, 0x0F6A, 0x0F67, 0x0F63, 0x0F5F, 0x0F5B, 0x0F56, 0x0F52, 0x0F4E, 0x0F49, 0x0F45, 0x0F41, 
	0x0F3D, 0x0F38, 0x0F33, 0x0F2F, 0x0F2B, 0x0F26, 0x0F22, 0x0F1D, 0x0F18, 0x0F13, 0x0F0F, 0x0F09, 0x0F05, 0x0EFF, 0x0EFB, 0x0EF6, 
	0x0EF1, 0x0EEB, 0x0EE6, 0x0EE1, 0x0EDC, 0x0ED7, 0x0ED1, 0x0ECC, 0x0EC6, 0x0EC1, 0x0EBC, 0x0EB7, 0x0EB1, 0x0EAC, 0x0EA6, 0x0EA0, 
	0x0E9A, 0x0E95, 0x0E8F, 0x0E89, 0x0E84, 0x0E7E, 0x0E78, 0x0E72, 0x0E6C, 0x0E66, 0x0E60, 0x0E5A, 0x0E54, 0x0E4E, 0x0E48, 0x0E42, 
	0x0E3B, 0x0E35, 0x0E2F, 0x0E29, 0x0E23, 0x0E1C, 0x0E15, 0x0E0F, 0x0E08, 0x0E02, 0x0DFB, 0x0DF5, 0x0DEE, 0x0DE8, 0x0DE1, 0x0DDA, 
	0x0DD3, 0x0DCC, 0x0DC6, 0x0DBF, 0x0DB8, 0x0DB2, 0x0DAA, 0x0DA3, 0x0D9D, 0x0D95, 0x0D8F, 0x0D87, 0x0D81, 0x0D79, 0x0D72, 0x0D6B, 
	0x0D63, 0x0D5D, 0x0D55, 0x0D4E, 0x0D46, 0x0D3F, 0x0D37, 0x0D30, 0x0D29, 0x0D21, 0x0D1A, 0x0D13, 0x0D0B, 0x0D03, 0x0CFB, 0x0CF3, 
	0x0CEC, 0x0CE4, 0x0CDC, 0x0CD5, 0x0CCD, 0x0CC5, 0x0CBD, 0x0CB5, 0x0CAD, 0x0CA5, 0x0C9D, 0x0C96, 0x0C8E, 0x0C85, 0x0C7D, 0x0C75, 
	0x0C6D, 0x0C65, 0x0C5C, 0x0C55, 0x0C4C, 0x0C44, 0x0C3C, 0x0C33, 0x0C2B, 0x0C23, 0x0C1A, 0x0C12, 0x0C09, 0x0C01, 0x0BF8, 0x0BF0, 
	0x0BE7, 0x0BDF, 0x0BD6, 0x0BCE, 0x0BC4, 0x0BBC, 0x0BB3, 0x0BAB, 0x0BA1, 0x0B99, 0x0B90, 0x0B87, 0x0B7F, 0x0B75, 0x0B6D, 0x0B63, 
	0x0B5A, 0x0B52, 0x0B48, 0x0B3F, 0x0B36, 0x0B2D, 0x0B24, 0x0B1A, 0x0B12, 0x0B08, 0x0AFF, 0x0AF6, 0x0AEC, 0x0AE3, 0x0ADA, 0x0AD0, 
	0x0AC7, 0x0ABD, 0x0AB4, 0x0AAB, 0x0AA1, 0x0A98, 0x0A8E, 0x0A85, 0x0A7B, 0x0A71, 0x0A68, 0x0A5E, 0x0A55, 0x0A4A, 0x0A41, 0x0A37, 
	0x0A2D, 0x0A23, 0x0A1A, 0x0A0F, 0x0A06, 0x09FC, 0x09F2, 0x09E8, 0x09DE, 0x09D4, 0x09CA, 0x09C0, 0x09B6, 0x09AC, 0x09A2, 0x0998, 
	0x098E, 0x0983, 0x097A, 0x096F, 0x0965, 0x095A, 0x0951, 0x0946, 0x093B, 0x0931, 0x0927, 0x091D, 0x0912, 0x0908, 0x08FD, 0x08F3, 
	0x08E8, 0x08DE, 0x08D3, 0x08C9, 0x08BE, 0x08B4, 0x08A9, 0x089E, 0x0894, 0x0889, 0x087E, 0x0874, 0x0869, 0x085F, 0x0853, 0x0849, 
	0x083E, 0x0834, 0x0828, 0x081E, 0x0813, 0x0808, 0x07FE, 0x07F3, 0x07E8, 0x07DD, 0x07D2, 0x07C7, 0x07BC, 0x07B1, 0x07A6, 0x079B, 
	0x0791, 0x0785, 0x077A, 0x076F, 0x0764, 0x0759, 0x074E, 0x0743, 0x0738, 0x072D, 0x0722, 0x0717, 0x070C, 0x0701, 0x06F6, 0x06EB, 
	0x06DF, 0x06D4, 0x06C9, 0x06BE, 0x06B3, 0x06A7, 0x069C, 0x0691, 0x0686, 0x067B, 0x0670, 0x0664, 0x0659, 0x064E, 0x0643, 0x0637, 
	0x062D, 0x0621, 0x0616, 0x060B, 0x05FF, 0x05F5, 0x05EA, 0x05DE, 0x05D3, 0x05C7, 0x05BC, 0x05B2, 0x05A7, 0x059B, 0x0590, 0x0585, 
	0x057A, 0x056E, 0x0563, 0x0558, 0x054D, 0x0542, 0x0537, 0x052B, 0x0521, 0x0516, 0x050A, 0x04FF, 0x04F4, 0x04E9, 0x04DF, 0x04D3, 
	0x04C8, 0x04BD, 0x04B2, 0x04A8, 0x049C, 0x0491, 0x0487, 0x047C, 0x0471, 0x0466, 0x045B, 0x0451, 0x0446, 0x043B, 0x0430, 0x0425, 
	0x041A, 0x0410, 0x0405, 0x03FA, 0x03F0, 0x03E5, 0x03DA, 0x03D0, 0x03C5, 0x03BB, 0x03B1, 0x03A6, 0x039C, 0x0391, 0x0386, 0x037C, 
	0x0373, 0x0368, 0x035E, 0x0353, 0x0349, 0x033F, 0x0335, 0x032B, 0x0321, 0x0317, 0x030D, 0x0303, 0x02F9, 0x02EF, 0x02E6, 0x02DC, 
	0x02D2, 0x02C8, 0x02BF, 0x02B5, 0x02AB, 0x02A2, 0x0298, 0x028E, 0x0286, 0x027C, 0x0273, 0x026A, 0x0260, 0x0257, 0x024E, 0x0245, 
	0x023C, 0x0233, 0x022A, 0x0221, 0x0219, 0x0210, 0x0206, 0x01FE, 0x01F5, 0x01ED, 0x01E4, 0x01DC, 0x01D4, 0x01CB, 0x01C3, 0x01BB, 
	0x01B3, 0x01AB, 0x01A2, 0x019A, 0x0193, 0x018B, 0x0182, 0x017B, 0x0174, 0x016B, 0x0164, 0x015D, 0x0156, 0x014E, 0x0147, 0x0140, 
	0x0138, 0x0131, 0x012A, 0x0123, 0x011C, 0x0116, 0x010E, 0x0108, 0x0102, 0x00FA, 0x00F4, 0x00EE, 0x00E7, 0x00E1, 0x00DC, 0x00D5, 
	0x00CF, 0x00CA, 0x00C4, 0x00BE, 0x00B8, 0x00B3, 0x00AD, 0x00A7, 0x00A2, 0x009C, 0x0097, 0x0093, 0x008E, 0x0088, 0x0083, 0x007F, 
	0x007A, 0x0075, 0x0071, 0x006C, 0x0068, 0x0064, 0x005F, 0x005B, 0x0057, 0x0053, 0x0050, 0x004C, 0x0047, 0x0044, 0x0040, 0x003D, 
	0x003A, 0x0037, 0x0034, 0x0031, 0x002E, 0x002B, 0x0028, 0x0025, 0x0022, 0x0020, 0x001D, 0x001B, 0x001A, 0x0017, 0x0015, 0x0013, 
	0x0011, 0x0010, 0x000E, 0x000C, 0x000B, 0x000A, 0x0008, 0x0007, 0x0006, 0x0005, 0x0004, 0x0004, 0x0003, 0x0003, 0x0002, 0x0002, 
	0x0001, 0x0001, 0x0000, 0x0001, 0x0001, 0x0001, 0x0002, 0x0002, 0x0002, 0x0003, 0x0004, 0x0005, 0x0005, 0x0006, 0x0008, 0x0009, 
	0x000A, 0x000C, 0x000D, 0x000F, 0x0011, 0x0013, 0x0014, 0x0016, 0x0018, 0x001A, 0x001E, 0x0020, 0x0022, 0x0025, 0x0028, 0x002B, 
	0x002D, 0x0031, 0x0034, 0x0037, 0x003A, 0x003E, 0x0041, 0x0045, 0x0049, 0x004D, 0x0050, 0x0055, 0x0059, 0x005E, 0x0061, 0x0066, 
	0x006B, 0x0070, 0x0075, 0x007A, 0x007F, 0x0084, 0x0089, 0x008E, 0x0094, 0x0099, 0x009E, 0x00A4, 0x00AA, 0x00AF, 0x00B6, 0x00BC, 
	0x00C2, 0x00C8, 0x00CF, 0x00D5, 0x00DC, 0x00E2, 0x00E8, 0x00F0, 0x00F6, 0x00FE, 0x0105, 0x010C, 0x0114, 0x011A, 0x0122, 0x012A, 
	0x0132, 0x0139, 0x0141, 0x0149, 0x0151, 0x015A, 0x0162, 0x016A, 0x0173, 0x017B, 0x0184, 0x018D, 0x0195, 0x019E, 0x01A7, 0x01B0, 
	0x01B9, 0x01C3, 0x01CC, 0x01D5, 0x01DE, 0x01E8, 0x01F2, 0x01FB, 0x0205, 0x020F, 0x0219, 0x0223, 0x022C, 0x0237, 0x0242, 0x024C, 
	0x0257, 0x0260, 0x026B, 0x0275, 0x0281, 0x028C, 0x0297, 0x02A1, 0x02AC, 0x02B8, 0x02C2, 0x02CD, 0x02D9, 0x02E4, 0x02F0, 0x02FC, 
	0x0306, 0x0312, 0x031E, 0x032A, 0x0336, 0x0342, 0x034E, 0x035A, 0x0366, 0x0372, 0x037E, 0x038A, 0x0397, 0x03A4, 0x03B0, 0x03BC, 
	0x03C9, 0x03D5, 0x03E2, 0x03EF, 0x03FC, 0x0408, 0x0415, 0x0422, 0x0430, 0x043C, 0x0449, 0x0456, 0x0464, 0x0471, 0x047E, 0x048C, 
	0x0499, 0x04A6, 0x04B3, 0x04C1, 0x04CF, 0x04DD, 0x04EA, 0x04F7, 0x0506, 0x0513, 0x0521, 0x052F, 0x053C, 0x054A, 0x0558, 0x0566, 
	0x0575, 0x0582, 0x0590, 0x059F, 0x05AC, 0x05BA, 0x05C9, 0x05D7, 0x05E5, 0x05F3, 0x0601, 0x0610, 0x061E, 0x062D, 0x063B, 0x0649, 
	0x0658, 0x0666, 0x0674, 0x0683, 0x0691, 0x069F, 0x06AE, 0x06BC, 0x06CB, 0x06DA, 0x06E8, 0x06F6, 0x0704, 0x0714, 0x0722, 0x0730, 
	0x0740, 0x074E, 0x075C, 0x076B, 0x0779, 0x0788, 0x0797, 0x07A5, 0x07B4, 0x07C2, 0x07D2, 0x07E0, 0x07EE, 0x07FD, 0x080B, 0x081A, 
	0x0828, 0x0837, 0x0845, 0x0854, 0x0862, 0x0871, 0x087F, 0x088E, 0x089D, 0x08AB, 0x08BA, 0x08C7, 0x08D6, 0x08E4, 0x08F3, 0x0901, 

};

static audio_sample_t sound_cello[SOUND_LEN] = {
	0x07FE, 0x0800, 0x0801, 0x0803, 0x0804, 0x0808, 0x0809, 0x080B, 0x080C, 0x080E, 0x0811, 0x0813, 0x0814, 0x0816, 0x0818, 0x081B, 
	0x081C, 0x081E, 0x081F, 0x0822, 0x0824, 0x0826, 0x0827, 0x0829, 0x082C, 0x082E, 0x082F, 0x0831, 0x0833, 0x0836, 0x0838, 0x0839, 
	0x083B, 0x083D, 0x0841, 0x0843, 0x0844, 0x0846, 0x0848, 0x084C, 0x084E, 0x0850, 0x0852, 0x0856, 0x0857, 0x085A, 0x085C, 0x085E, 
	0x0862, 0x0864, 0x0866, 0x0868, 0x086A, 0x086E, 0x0870, 0x0872, 0x0874, 0x0876, 0x087A, 0x087C, 0x087E, 0x0880, 0x0882, 0x0886, 
	0x0888, 0x088A, 0x088C, 0x0890, 0x0892, 0x0894, 0x0896, 0x0898, 0x089C, 0x089F, 0x08A1, 0x08A3, 0x08A5, 0x08A9, 0x08AC, 0x08AE, 
	0x08B0, 0x08B3, 0x08B7, 0x08BA, 0x08BC, 0x08BE, 0x08C3, 0x08C5, 0x08C8, 0x08CA, 0x08CD, 0x08D2, 0x08D4, 0x08D7, 0x08D9, 0x08DC, 
	0x08E1, 0x08E3, 0x08E6, 0x08E9, 0x08EB, 0x08F1, 0x08F4, 0x08F6, 0x08F9, 0x08FC, 0x0902, 0x0905, 0x0909, 0x090C, 0x0912, 0x0915, 
	0x0919, 0x091C, 0x0920, 0x0927, 0x092A, 0x092E, 0x0932, 0x0936, 0x093D, 0x0941, 0x0945, 0x0949, 0x094D, 0x0955, 0x095A, 0x095E, 
	0x0962, 0x0967, 0x096F, 0x0974, 0x0978, 0x097D, 0x0986, 0x098B, 0x098F, 0x0994, 0x0998, 0x09A2, 0x09A6, 0x09AB, 0x09AF, 0x09B4, 
	0x09BD, 0x09C2, 0x09C7, 0x09CC, 0x09D1, 0x09DB, 0x09E0, 0x09E5, 0x09EB, 0x09F6, 0x09FB, 0x0A01, 0x0A06, 0x0A0B, 0x0A18, 0x0A1E, 
	0x0A24, 0x0A2A, 0x0A30, 0x0A3C, 0x0A42, 0x0A49, 0x0A50, 0x0A57, 0x0A64, 0x0A6B, 0x0A71, 0x0A7A, 0x0A82, 0x0A92, 0x0A9B, 0x0AA3, 
	0x0AAB, 0x0ABD, 0x0AC7, 0x0AD1, 0x0ADB, 0x0AE4, 0x0AF8, 0x0B02, 0x0B0D, 0x0B19, 0x0B24, 0x0B3A, 0x0B46, 0x0B51, 0x0B5C, 0x0B69, 
	0x0B83, 0x0B8F, 0x0B9C, 0x0BA9, 0x0BB6, 0x0BD0, 0x0BDE, 0x0BEB, 0x0BF9, 0x0C15, 0x0C22, 0x0C30, 0x0C3E, 0x0C4C, 0x0C68, 0x0C76, 
	0x0C84, 0x0C92, 0x0CA0, 0x0CBB, 0x0CC8, 0x0CD6, 0x0CE3, 0x0CF1, 0x0D0C, 0x0D19, 0x0D25, 0x0D32, 0x0D4C, 0x0D59, 0x0D65, 0x0D72, 
	0x0D7E, 0x0D96, 0x0DA1, 0x0DAD, 0x0DB9, 0x0DC5, 0x0DDB, 0x0DE6, 0x0DF1, 0x0DFB, 0x0E06, 0x0E1B, 0x0E26, 0x0E30, 0x0E39, 0x0E43, 
	0x0E56, 0x0E60, 0x0E69, 0x0E73, 0x0E84, 0x0E8D, 0x0E96, 0x0E9E, 0x0EA7, 0x0EB8, 0x0EC0, 0x0EC8, 0x0ED0, 0x0ED8, 0x0EE8, 0x0EF0, 
	0x0EF8, 0x0EFE, 0x0F05, 0x0F13, 0x0F1A, 0x0F21, 0x0F28, 0x0F2F, 0x0F3B, 0x0F41, 0x0F47, 0x0F4D, 0x0F5A, 0x0F60, 0x0F65, 0x0F6A, 
	0x0F70, 0x0F7A, 0x0F7F, 0x0F85, 0x0F8A, 0x0F8E, 0x0F97, 0x0F9C, 0x0FA0, 0x0FA5, 0x0FAA, 0x0FB2, 0x0FB6, 0x0FB9, 0x0FBD, 0x0FC4, 
	0x0FC8, 0x0FCC, 0x0FCF, 0x0FD2, 0x0FD8, 0x0FDB, 0x0FDE, 0x0FE2, 0x0FE5, 0x0FE9, 0x0FEB, 0x0FED, 0x0FEF, 0x0FF1, 0x0FF5, 0x0FF6, 
	0x0FF7, 0x0FF8, 0x0FF8, 0x0FFA, 0x0FFA, 0x0FFB, 0x0FFB, 0x0FFA, 0x0FF9, 0x0FF9, 0x0FF9, 0x0FF8, 0x0FF7, 0x0FF5, 0x0FF4, 0x0FF3, 
	0x0FF2, 0x0FF0, 0x0FEE, 0x0FEC, 0x0FEA, 0x0FE7, 0x0FE3, 0x0FE1, 0x0FDE, 0x0FDC, 0x0FD8, 0x0FD1, 0x0FCD, 0x0FC9, 0x0FC6, 0x0FBE, 
	0x0FB9, 0x0FB4, 0x0FAF, 0x0FAA, 0x0FA0, 0x0F9B, 0x0F96, 0x0F8F, 0x0F89, 0x0F7C, 0x0F76, 0x0F70, 0x0F69, 0x0F63, 0x0F53, 0x0F4B, 
	0x0F43, 0x0F3B, 0x0F2C, 0x0F24, 0x0F1A, 0x0F11, 0x0F08, 0x0EF5, 0x0EEC, 0x0EE2, 0x0ED9, 0x0ECE, 0x0EB9, 0x0EAE, 0x0EA3, 0x0E99, 
	0x0E8E, 0x0E77, 0x0E6B, 0x0E5F, 0x0E53, 0x0E47, 0x0E2E, 0x0E22, 0x0E15, 0x0E07, 0x0DED, 0x0DDF, 0x0DD2, 0x0DC4, 0x0DB7, 0x0D9B, 
	0x0D8C, 0x0D7E, 0x0D70, 0x0D62, 0x0D46, 0x0D37, 0x0D28, 0x0D19, 0x0D0A, 0x0CEB, 0x0CDC, 0x0CCD, 0x0CBD, 0x0C9E, 0x0C8E, 0x0C7E, 
	0x0C6E, 0x0C5E, 0x0C3E, 0x0C2D, 0x0C1D, 0x0C0C, 0x0BFC, 0x0BDB, 0x0BCA, 0x0BB9, 0x0BA8, 0x0B97, 0x0B75, 0x0B65, 0x0B54, 0x0B43, 
	0x0B31, 0x0B0F, 0x0AFD, 0x0AEC, 0x0ADB, 0x0AB8, 0x0AA6, 0x0A94, 0x0A83, 0x0A71, 0x0A4E, 0x0A3C, 0x0A2A, 0x0A18, 0x0A06, 0x09E2, 
	0x09D0, 0x09BE, 0x09AC, 0x099A, 0x0976, 0x0963, 0x0951, 0x093F, 0x092C, 0x0908, 0x08F6, 0x08E3, 0x08D1, 0x08AD, 0x089A, 0x0888, 
	0x0876, 0x0864, 0x0840, 0x082E, 0x081C, 0x080A, 0x07F8, 0x07D4, 0x07C3, 0x07B1, 0x079F, 0x078D, 0x076A, 0x0758, 0x0746, 0x0734, 
	0x0712, 0x0700, 0x06EE, 0x06DD, 0x06CC, 0x06A9, 0x0698, 0x0686, 0x0675, 0x0664, 0x0642, 0x0631, 0x0620, 0x060F, 0x05FF, 0x05DD, 
	0x05CC, 0x05BC, 0x05AB, 0x059B, 0x0579, 0x0569, 0x0558, 0x0548, 0x0528, 0x0518, 0x0508, 0x04F8, 0x04E8, 0x04C9, 0x04BA, 0x04AA, 
	0x049B, 0x048C, 0x046D, 0x045D, 0x044F, 0x0440, 0x0431, 0x0413, 0x0404, 0x03F6, 0x03E7, 0x03D9, 0x03BD, 0x03AF, 0x03A0, 0x0392, 
	0x0376, 0x0369, 0x035C, 0x034F, 0x0341, 0x0327, 0x031A, 0x030C, 0x0300, 0x02F4, 0x02DB, 0x02CE, 0x02C2, 0x02B6, 0x02A9, 0x0292, 
	0x0287, 0x027B, 0x0270, 0x0259, 0x024E, 0x0243, 0x0239, 0x022F, 0x021A, 0x0210, 0x0205, 0x01FB, 0x01F2, 0x01DF, 0x01D6, 0x01CC, 
	0x01C3, 0x01B9, 0x01A7, 0x019F, 0x0196, 0x018E, 0x0185, 0x0174, 0x016B, 0x0163, 0x015C, 0x014C, 0x0144, 0x013D, 0x0135, 0x012D, 
	0x011F, 0x0117, 0x0110, 0x0109, 0x0102, 0x00F4, 0x00ED, 0x00E7, 0x00E0, 0x00DA, 0x00CD, 0x00C7, 0x00C0, 0x00BB, 0x00B5, 0x00AA, 
	0x00A4, 0x009F, 0x0099, 0x008F, 0x008A, 0x0085, 0x0080, 0x007B, 0x0071, 0x006C, 0x0068, 0x0064, 0x0060, 0x0057, 0x0053, 0x004F, 
	0x004B, 0x0047, 0x0041, 0x003D, 0x003A, 0x0037, 0x0030, 0x002E, 0x002B, 0x0029, 0x0026, 0x0021, 0x001F, 0x001C, 0x001A, 0x0018, 
	0x0014, 0x0012, 0x0010, 0x000F, 0x000D, 0x000A, 0x0009, 0x0008, 0x0007, 0x0006, 0x0003, 0x0003, 0x0003, 0x0002, 0x0001, 0x0001, 
	0x0001, 0x0000, 0x0000, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0002, 0x0002, 0x0002, 0x0003, 0x0004, 0x0004, 0x0005, 
	0x0006, 0x0007, 0x0009, 0x000A, 0x000B, 0x000C, 0x000E, 0x0010, 0x0011, 0x0013, 0x0014, 0x0017, 0x0019, 0x001B, 0x001C, 0x001E, 
	0x0022, 0x0023, 0x0025, 0x0027, 0x0029, 0x002E, 0x0030, 0x0032, 0x0034, 0x0039, 0x003B, 0x003E, 0x0040, 0x0043, 0x0048, 0x004A, 
	0x004D, 0x004F, 0x0051, 0x0056, 0x0059, 0x005B, 0x005D, 0x005F, 0x0064, 0x0066, 0x0068, 0x006A, 0x006C, 0x0070, 0x0072, 0x0074, 
	0x0075, 0x0079, 0x007B, 0x007C, 0x007E, 0x007F, 0x0082, 0x0083, 0x0084, 0x0086, 0x0087, 0x0089, 0x008A, 0x008B, 0x008C, 0x008D, 
	0x008F, 0x0090, 0x0091, 0x0091, 0x0092, 0x0094, 0x0095, 0x0096, 0x0096, 0x0098, 0x0099, 0x009A, 0x009B, 0x009C, 0x009E, 0x009F, 
	0x00A1, 0x00A2, 0x00A4, 0x00A6, 0x00A8, 0x00AA, 0x00AD, 0x00B0, 0x00B5, 0x00B7, 0x00BA, 0x00BD, 0x00C4, 0x00C8, 0x00CB, 0x00CF, 
	0x00D3, 0x00DA, 0x00DF, 0x00E3, 0x00E8, 0x00EC, 0x00F5, 0x00F9, 0x00FE, 0x0103, 0x0108, 0x0111, 0x0116, 0x011B, 0x0120, 0x0125, 
	0x0130, 0x0135, 0x013A, 0x0140, 0x014A, 0x014F, 0x0155, 0x015B, 0x0160, 0x016B, 0x0171, 0x0176, 0x017C, 0x0181, 0x018D, 0x0192, 
	0x0198, 0x019D, 0x01A3, 0x01AE, 0x01B4, 0x01B9, 0x01BF, 0x01C4, 0x01CF, 0x01D5, 0x01DA, 0x01E0, 0x01EC, 0x01F1, 0x01F7, 0x01FD, 
	0x0203, 0x0210, 0x0217, 0x021E, 0x0225, 0x022C, 0x0239, 0x0242, 0x024A, 0x0252, 0x025B, 0x026C, 0x0274, 0x027C, 0x0286, 0x0299, 
	0x02A3, 0x02AD, 0x02B7, 0x02C0, 0x02D5, 0x02DF, 0x02EA, 0x02F4, 0x02FF, 0x0314, 0x031F, 0x0329, 0x0334, 0x033F, 0x0354, 0x035F, 
	0x0369, 0x0374, 0x037F, 0x0394, 0x039E, 0x03A9, 0x03B3, 0x03C8, 0x03D3, 0x03DD, 0x03E7, 0x03F1, 0x0406, 0x0410, 0x041A, 0x0423, 
	0x042D, 0x0440, 0x044A, 0x0453, 0x045D, 0x0467, 0x0478, 0x0481, 0x048A, 0x0492, 0x049B, 0x04AD, 0x04B5, 0x04BD, 0x04C5, 0x04D5, 
	0x04DD, 0x04E5, 0x04EE, 0x04F5, 0x0504, 0x050B, 0x0513, 0x051A, 0x0522, 0x0530, 0x0537, 0x053E, 0x0545, 0x054C, 0x055A, 0x0561, 
	0x0567, 0x056E, 0x057B, 0x0581, 0x0588, 0x058E, 0x0595, 0x05A0, 0x05A6, 0x05AC, 0x05B2, 0x05B8, 0x05C4, 0x05C9, 0x05CF, 0x05D4, 
	0x05D9, 0x05E4, 0x05E9, 0x05EE, 0x05F4, 0x05F9, 0x0603, 0x0608, 0x060D, 0x0612, 0x061C, 0x0621, 0x0626, 0x062B, 0x0630, 0x063A, 
	0x063F, 0x0644, 0x0649, 0x064D, 0x0657, 0x065C, 0x0660, 0x0665, 0x0669, 0x0672, 0x0676, 0x067B, 0x067F, 0x0683, 0x068B, 0x068F, 
	0x0693, 0x0697, 0x069F, 0x06A3, 0x06A6, 0x06AA, 0x06AE, 0x06B5, 0x06B8, 0x06BC, 0x06BF, 0x06C3, 0x06C9, 0x06CD, 0x06D0, 0x06D3, 
	0x06D6, 0x06DD, 0x06E0, 0x06E3, 0x06E6, 0x06ED, 0x06F0, 0x06F3, 0x06F6, 0x06F9, 0x0700, 0x0703, 0x0706, 0x0709, 0x070C, 0x0712, 
	0x0715, 0x0718, 0x071C, 0x071F, 0x0725, 0x0728, 0x072B, 0x072E, 0x0730, 0x0736, 0x0739, 0x073C, 0x073F, 0x0746, 0x0749, 0x074C, 
	0x074F, 0x0752, 0x0758, 0x075B, 0x075E, 0x0761, 0x0764, 0x076A, 0x076D, 0x0770, 0x0773, 0x0775, 0x077B, 0x077D, 0x0780, 0x0782, 
	0x0787, 0x078A, 0x078C, 0x078F, 0x0791, 0x0796, 0x0798, 0x079B, 0x079D, 0x079F, 0x07A4, 0x07A7, 0x07A9, 0x07AB, 0x07AE, 0x07B2, 
	0x07B4, 0x07B7, 0x07B9, 0x07BB, 0x07BF, 0x07C1, 0x07C3, 0x07C5, 0x07CA, 0x07CC, 0x07CE, 0x07D0, 0x07D2, 0x07D6, 0x07D8, 0x07D9, 
	0x07DB, 0x07DD, 0x07E1, 0x07E3, 0x07E5, 0x07E7, 0x07E9, 0x07EC, 0x07EE, 0x07F0, 0x07F1, 0x07F3, 0x07F6, 0x07F8, 0x07F9, 0x07FB, 
};

static audio_sample_t sound_test0[SOUND_LEN] = {
	0x0640, 0x0640, 0x0640, 0x0640, 0x0640, 0x0640, 0x0640, 0x0640, 0x0674, 0x0678, 0x067B, 0x067F, 0x0682, 0x0686, 0x0689, 0x068D, 
	0x0690, 0x069C, 0x06A8, 0x06B4, 0x06C0, 0x06CC, 0x06D8, 0x06E4, 0x06F0, 0x06FC, 0x0708, 0x0714, 0x0720, 0x072C, 0x0738, 0x0744, 
	0x0750, 0x075C, 0x0768, 0x0774, 0x0780, 0x079E, 0x07BD, 0x07DB, 0x07F9, 0x0817, 0x0836, 0x087C, 0x08C5, 0x090F, 0x0958, 0x0962, 
	0x096C, 0x0979, 0x0985, 0x0992, 0x099E, 0x09AB, 0x09B7, 0x09C4, 0x09D0, 0x09DC, 0x09E8, 0x09F4, 0x0A00, 0x0A0C, 0x0A1E, 0x0A2F, 
	0x0A41, 0x0A52, 0x0A64, 0x0A6C, 0x0A74, 0x0A7C, 0x0A84, 0x0A8C, 0x0A94, 0x0A9C, 0x0AA4, 0x0AAC, 0x0AB4, 0x0ABF, 0x0ACB, 0x0AD6, 
	0x0AE2, 0x0AED, 0x0AF9, 0x0B04, 0x0B11, 0x0B1F, 0x0B2C, 0x0B34, 0x0B3B, 0x0B43, 0x0B4B, 0x0B52, 0x0B5A, 0x0B62, 0x0B69, 0x0B71, 
	0x0B79, 0x0B80, 0x0B88, 0x0B8E, 0x0B93, 0x0B99, 0x0B9E, 0x0BA4, 0x0BA9, 0x0BAF, 0x0BB4, 0x0BBA, 0x0BC0, 0x0BC5, 0x0BCB, 0x0BD0, 
	0x0BD6, 0x0BDB, 0x0BE1, 0x0BE6, 0x0BEC, 0x0BF2, 0x0BF7, 0x0BFD, 0x0C02, 0x0C08, 0x0C0A, 0x0C0C, 0x0C0E, 0x0C11, 0x0C13, 0x0C15, 
	0x0C17, 0x0C19, 0x0C1B, 0x0C1D, 0x0C1F, 0x0C22, 0x0C24, 0x0C26, 0x0C28, 0x0C29, 0x0C2B, 0x0C2C, 0x0C2D, 0x0C2F, 0x0C30, 0x0C31, 
	0x0C33, 0x0C34, 0x0C35, 0x0C37, 0x0C38, 0x0C39, 0x0C3B, 0x0C3C, 0x0C3D, 0x0C3F, 0x0C40, 0x0C41, 0x0C43, 0x0C44, 0x0C45, 0x0C47, 
	0x0C48, 0x0C49, 0x0C4B, 0x0C4C, 0x0C4D, 0x0C4F, 0x0C50, 0x0C53, 0x0C56, 0x0C59, 0x0C5B, 0x0C5E, 0x0C61, 0x0C64, 0x0C66, 0x0C67, 
	0x0C69, 0x0C6A, 0x0C6C, 0x0C6C, 0x0C6C, 0x0C6C, 0x0C6C, 0x0C6C, 0x0C6C, 0x0C6C, 0x0C6C, 0x0C6C, 0x0C6C, 0x0C6C, 0x0C6C, 0x0C6C, 
	0x0C6C, 0x0C6C, 0x0C6C, 0x0C6C, 0x0C6C, 0x0C6C, 0x0C6C, 0x0C6B, 0x0C69, 0x0C68, 0x0C67, 0x0C65, 0x0C64, 0x0C63, 0x0C61, 0x0C60, 
	0x0C5F, 0x0C5D, 0x0C5C, 0x0C5B, 0x0C59, 0x0C58, 0x0C57, 0x0C55, 0x0C54, 0x0C53, 0x0C51, 0x0C50, 0x0C4F, 0x0C4D, 0x0C4C, 0x0C4B, 
	0x0C49, 0x0C48, 0x0C47, 0x0C45, 0x0C44, 0x0C3D, 0x0C37, 0x0C30, 0x0C28, 0x0C20, 0x0C18, 0x0C10, 0x0C08, 0x0BFF, 0x0BF7, 0x0BEE, 
	0x0BE6, 0x0BDD, 0x0BD5, 0x0BCC, 0x0BC4, 0x0BBC, 0x0BB4, 0x0BAC, 0x0BA4, 0x0B95, 0x0B86, 0x0B78, 0x0B69, 0x0B5A, 0x0B4B, 0x0B3C, 
	0x0B2E, 0x0B1F, 0x0B10, 0x0AC7, 0x0A7D, 0x08F4, 0x087C, 0x05F0, 0x05BA, 0x0585, 0x054F, 0x051A, 0x04E4, 0x04C9, 0x04AF, 0x0494, 
	0x0488, 0x047C, 0x0470, 0x0464, 0x0458, 0x044C, 0x0440, 0x0434, 0x0428, 0x041C, 0x040F, 0x0403, 0x03F6, 0x03E9, 0x03DC, 0x03D0, 
	0x03C3, 0x03B6, 0x03A9, 0x039D, 0x0390, 0x0383, 0x0377, 0x036A, 0x035D, 0x0350, 0x0344, 0x0337, 0x032A, 0x031D, 0x0311, 0x0304, 
	0x02FB, 0x02F1, 0x02E8, 0x02DF, 0x02D5, 0x02CC, 0x02C3, 0x02B9, 0x02B0, 0x02A7, 0x029D, 0x0294, 0x028B, 0x0281, 0x0278, 0x0273, 
	0x026E, 0x0269, 0x0264, 0x0260, 0x025B, 0x0256, 0x0251, 0x024C, 0x0247, 0x0242, 0x023D, 0x0238, 0x0234, 0x022F, 0x022A, 0x0225, 
	0x0220, 0x021B, 0x0216, 0x0211, 0x020C, 0x0208, 0x0203, 0x01FE, 0x01F9, 0x01F4, 0x01EF, 0x01EA, 0x01E5, 0x01E0, 0x01DC, 0x01D7, 
	0x01D2, 0x01CD, 0x01C8, 0x01C3, 0x01BE, 0x01B9, 0x01B4, 0x01B0, 0x01AB, 0x01A6, 0x01A1, 0x019C, 0x0198, 0x0195, 0x0191, 0x018D, 
	0x0189, 0x0186, 0x0182, 0x017E, 0x017A, 0x0177, 0x0173, 0x016F, 0x016B, 0x0168, 0x0164, 0x0160, 0x015D, 0x0159, 0x0155, 0x0151, 
	0x014E, 0x014A, 0x0146, 0x0142, 0x013F, 0x013B, 0x0137, 0x0133, 0x0130, 0x012C, 0x0128, 0x0125, 0x0121, 0x011E, 0x011A, 0x0117, 
	0x0113, 0x0110, 0x010C, 0x0109, 0x0105, 0x0102, 0x00FE, 0x00FB, 0x00F7, 0x00F4, 0x00F0, 0x00ED, 0x00E9, 0x00E6, 0x00E2, 0x00DF, 
	0x00DB, 0x00D8, 0x00D4, 0x00D1, 0x00CD, 0x00CA, 0x00C6, 0x00C3, 0x00BF, 0x00BC, 0x00B8, 0x00B5, 0x00B1, 0x00AE, 0x00AA, 0x00A7, 
	0x00A3, 0x00A0, 0x009E, 0x009C, 0x009A, 0x0098, 0x0096, 0x0094, 0x0093, 0x0091, 0x008F, 0x008D, 0x008B, 0x0089, 0x0087, 0x0085, 
	0x0083, 0x0081, 0x007F, 0x007D, 0x007C, 0x007A, 0x0078, 0x0076, 0x0074, 0x0072, 0x0070, 0x006F, 0x006E, 0x006D, 0x006B, 0x006A, 
	0x0069, 0x0068, 0x0067, 0x0066, 0x0065, 0x0064, 0x0062, 0x0061, 0x0060, 0x005F, 0x005E, 0x005D, 0x005C, 0x005A, 0x0059, 0x0058, 
	0x0057, 0x0056, 0x0055, 0x0054, 0x0053, 0x0051, 0x0050, 0x004F, 0x004E, 0x004D, 0x004C, 0x004B, 0x004A, 0x0048, 0x0047, 0x0046, 
	0x0045, 0x0044, 0x0043, 0x0042, 0x0040, 0x003F, 0x003E, 0x003D, 0x003C, 0x003B, 0x003A, 0x0039, 0x0037, 0x0036, 0x0035, 0x0034, 
	0x0034, 0x0034, 0x0034, 0x0034, 0x0034, 0x0034, 0x0034, 0x0033, 0x0032, 0x0031, 0x0031, 0x0030, 0x002F, 0x002E, 0x002D, 0x002C, 
	0x002B, 0x002A, 0x002A, 0x0029, 0x0028, 0x0027, 0x0026, 0x0025, 0x0024, 0x0023, 0x0023, 0x0022, 0x0021, 0x0020, 0x001F, 0x001F, 
	0x001E, 0x001D, 0x001C, 0x001C, 0x001B, 0x001A, 0x0019, 0x0019, 0x0018, 0x0017, 0x0016, 0x0016, 0x0015, 0x0014, 0x0013, 0x0013, 
	0x0012, 0x0011, 0x0010, 0x0010, 0x000F, 0x000E, 0x000D, 0x000D, 0x000C, 0x000C, 0x000C, 0x000C, 0x000C, 0x000C, 0x000C, 0x000C, 
	0x000C, 0x000C, 0x000C, 0x000C, 0x000C, 0x000C, 0x000C, 0x000C, 0x000C, 0x000C, 0x000C, 0x000C, 0x000C, 0x000C, 0x000C, 0x000C, 
	0x000C, 0x000B, 0x000B, 0x000A, 0x000A, 0x0009, 0x0009, 0x0008, 0x0008, 0x0008, 0x0007, 0x0007, 0x0006, 0x0006, 0x0005, 0x0005, 
	0x0004, 0x0004, 0x0004, 0x0003, 0x0003, 0x0002, 0x0002, 0x0001, 0x0001, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
	0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0001, 0x0001, 0x0002, 0x0002, 
	0x0003, 0x0003, 0x0004, 0x0005, 0x0005, 0x0006, 0x0006, 0x0007, 0x0007, 0x0008, 0x0009, 0x0009, 0x000A, 0x000A, 0x000B, 0x000B, 
	0x000C, 0x000D, 0x000D, 0x000E, 0x000E, 0x000F, 0x000F, 0x0010, 0x0011, 0x0011, 0x0012, 0x0012, 0x0013, 0x0013, 0x0014, 0x0015, 
	0x0017, 0x0018, 0x0019, 0x001B, 0x001C, 0x001D, 0x001F, 0x0020, 0x0021, 0x0023, 0x0024, 0x0025, 0x0027, 0x0028, 0x0029, 0x002B, 
	0x002C, 0x002D, 0x002F, 0x0030, 0x0031, 0x0033, 0x0034, 0x0035, 0x0037, 0x0038, 0x0039, 0x003B, 0x003C, 0x003E, 0x0041, 0x0043, 
	0x0045, 0x0048, 0x004A, 0x004C, 0x004F, 0x0051, 0x0054, 0x0056, 0x0058, 0x005B, 0x005D, 0x005F, 0x0062, 0x0064, 0x0067, 0x006A, 
	0x006D, 0x0071, 0x0074, 0x0077, 0x007A, 0x007D, 0x0080, 0x0084, 0x0087, 0x008A, 0x008D, 0x0090, 0x0093, 0x0097, 0x009A, 0x009D, 
	0x00A0, 0x00A3, 0x00A6, 0x00A9, 0x00AD, 0x00B0, 0x00B3, 0x00B6, 0x00B9, 0x00BC, 0x00C0, 0x00C3, 0x00C6, 0x00C9, 0x00CC, 0x00CF, 
	0x00D3, 0x00D6, 0x00D9, 0x00DC, 0x00DF, 0x00E3, 0x00E6, 0x00EA, 0x00ED, 0x00F1, 0x00F4, 0x00F8, 0x00FB, 0x00FF, 0x0102, 0x0106, 
	0x0109, 0x010D, 0x0110, 0x0114, 0x0118, 0x011B, 0x011F, 0x0123, 0x0127, 0x012A, 0x012E, 0x0132, 0x0136, 0x0139, 0x013D, 0x0141, 
	0x0145, 0x0148, 0x014C, 0x0150, 0x0154, 0x0157, 0x015B, 0x015F, 0x0163, 0x0166, 0x016A, 0x016E, 0x0172, 0x0175, 0x0179, 0x017D, 
	0x0181, 0x0184, 0x0188, 0x018C, 0x018F, 0x0193, 0x0196, 0x019A, 0x019D, 0x01A1, 0x01A5, 0x01A8, 0x01AC, 0x01AF, 0x01B3, 0x01B6, 
	0x01BA, 0x01BE, 0x01C1, 0x01C5, 0x01C8, 0x01CC, 0x01CF, 0x01D3, 0x01D7, 0x01DA, 0x01DE, 0x01E1, 0x01E5, 0x01E8, 0x01EC, 0x01F6, 
	0x0200, 0x0203, 0x0207, 0x020A, 0x020E, 0x0211, 0x0214, 0x0218, 0x021B, 0x021F, 0x0222, 0x0225, 0x0229, 0x022C, 0x0230, 0x0233, 
	0x0236, 0x023A, 0x023D, 0x0241, 0x0244, 0x0247, 0x024B, 0x024E, 0x0252, 0x0255, 0x0259, 0x025C, 0x0260, 0x0263, 0x0267, 0x026A, 
	0x026E, 0x0271, 0x0275, 0x0278, 0x027C, 0x0281, 0x0285, 0x0289, 0x028D, 0x0292, 0x0296, 0x029A, 0x029F, 0x02A3, 0x02A7, 0x02AB, 
	0x02B0, 0x02B4, 0x02B8, 0x02BD, 0x02C1, 0x02C5, 0x02C9, 0x02CE, 0x02D2, 0x02D6, 0x02DB, 0x02DF, 0x02E3, 0x02E7, 0x02EC, 0x02F0, 
	0x02F4, 0x02F9, 0x02FD, 0x0301, 0x0306, 0x030A, 0x030E, 0x0313, 0x0317, 0x031B, 0x0320, 0x0324, 0x0328, 0x032C, 0x0331, 0x0335, 
	0x0339, 0x033E, 0x0342, 0x0346, 0x034B, 0x034F, 0x0353, 0x0358, 0x035C, 0x0362, 0x0368, 0x036E, 0x0374, 0x0379, 0x037F, 0x0385, 
	0x038B, 0x0391, 0x0397, 0x039D, 0x03A3, 0x03A8, 0x03AE, 0x03B4, 0x03BA, 0x03C0, 0x03C7, 0x03CE, 0x03D6, 0x03DD, 0x03E4, 0x03EB, 
	0x03F2, 0x03FA, 0x0401, 0x0408, 0x040C, 0x040F, 0x0413, 0x0416, 0x041A, 0x041D, 0x0421, 0x0424, 0x042E, 0x0438, 0x043E, 0x0445, 
	0x044B, 0x0452, 0x0458, 0x0466, 0x0473, 0x0481, 0x048E, 0x049C, 0x04A7, 0x04B1, 0x04BC, 0x04C7, 0x04D3, 0x04DE, 0x04EA, 0x04F5, 
	0x0501, 0x0520, 0x0530, 0x0540, 0x0578, 0x0582, 0x058C, 0x0593, 0x0599, 0x05A0, 0x05AA, 0x05B4, 0x05BB, 0x05C1, 0x05D4, 0x05D8, 
	0x05DC, 0x05E3, 0x05E9, 0x05F0, 0x05FA, 0x0605, 0x060F, 0x061A, 0x0624, 0x062E, 0x0638, 0x0638, 0x0638, 0x0640, 0x0646, 0x064C, 
};

static audio_sample_t sound_sine[SOUND_LEN] = {
	0x0800, 0x080C, 0x0819, 0x0825, 0x0832, 0x083E, 0x084B, 0x0858, 0x0864, 0x0871, 0x087D, 0x088A, 0x0896, 0x08A3, 0x08AF, 0x08BC, 
	0x08C8, 0x08D5, 0x08E1, 0x08EE, 0x08FA, 0x0907, 0x0913, 0x0920, 0x092C, 0x0939, 0x0945, 0x0951, 0x095E, 0x096A, 0x0977, 0x0983, 
	0x098F, 0x099C, 0x09A8, 0x09B4, 0x09C1, 0x09CD, 0x09D9, 0x09E5, 0x09F1, 0x09FE, 0x0A0A, 0x0A16, 0x0A22, 0x0A2E, 0x0A3A, 0x0A46, 
	0x0A52, 0x0A5E, 0x0A6A, 0x0A76, 0x0A82, 0x0A8E, 0x0A9A, 0x0AA6, 0x0AB2, 0x0ABE, 0x0ACA, 0x0AD5, 0x0AE1, 0x0AED, 0x0AF8, 0x0B04, 
	0x0B10, 0x0B1B, 0x0B27, 0x0B32, 0x0B3E, 0x0B49, 0x0B55, 0x0B60, 0x0B6C, 0x0B77, 0x0B82, 0x0B8E, 0x0B99, 0x0BA4, 0x0BAF, 0x0BBA, 
	0x0BC6, 0x0BD1, 0x0BDC, 0x0BE7, 0x0BF2, 0x0BFD, 0x0C07, 0x0C12, 0x0C1D, 0x0C28, 0x0C33, 0x0C3D, 0x0C48, 0x0C52, 0x0C5D, 0x0C68, 
	0x0C72, 0x0C7C, 0x0C87, 0x0C91, 0x0C9B, 0x0CA6, 0x0CB0, 0x0CBA, 0x0CC4, 0x0CCE, 0x0CD8, 0x0CE2, 0x0CEC, 0x0CF6, 0x0D00, 0x0D0A, 
	0x0D13, 0x0D1D, 0x0D27, 0x0D30, 0x0D3A, 0x0D43, 0x0D4D, 0x0D56, 0x0D60, 0x0D69, 0x0D72, 0x0D7B, 0x0D84, 0x0D8E, 0x0D97, 0x0D9F, 
	0x0DA8, 0x0DB1, 0x0DBA, 0x0DC3, 0x0DCC, 0x0DD4, 0x0DDD, 0x0DE5, 0x0DEE, 0x0DF6, 0x0DFE, 0x0E07, 0x0E0F, 0x0E17, 0x0E1F, 0x0E27, 
	0x0E2F, 0x0E37, 0x0E3F, 0x0E47, 0x0E4F, 0x0E56, 0x0E5E, 0x0E66, 0x0E6D, 0x0E75, 0x0E7C, 0x0E83, 0x0E8B, 0x0E92, 0x0E99, 0x0EA0, 
	0x0EA7, 0x0EAE, 0x0EB5, 0x0EBC, 0x0EC2, 0x0EC9, 0x0ED0, 0x0ED6, 0x0EDD, 0x0EE3, 0x0EEA, 0x0EF0, 0x0EF6, 0x0EFC, 0x0F02, 0x0F08, 
	0x0F0E, 0x0F14, 0x0F1A, 0x0F20, 0x0F25, 0x0F2B, 0x0F31, 0x0F36, 0x0F3B, 0x0F41, 0x0F46, 0x0F4B, 0x0F50, 0x0F55, 0x0F5A, 0x0F5F, 
	0x0F64, 0x0F69, 0x0F6D, 0x0F72, 0x0F77, 0x0F7B, 0x0F80, 0x0F84, 0x0F88, 0x0F8C, 0x0F90, 0x0F94, 0x0F98, 0x0F9C, 0x0FA0, 0x0FA4, 
	0x0FA8, 0x0FAB, 0x0FAF, 0x0FB2, 0x0FB6, 0x0FB9, 0x0FBC, 0x0FBF, 0x0FC2, 0x0FC5, 0x0FC8, 0x0FCB, 0x0FCE, 0x0FD1, 0x0FD3, 0x0FD6, 
	0x0FD8, 0x0FDB, 0x0FDD, 0x0FDF, 0x0FE1, 0x0FE3, 0x0FE5, 0x0FE7, 0x0FE9, 0x0FEB, 0x0FED, 0x0FEE, 0x0FF0, 0x0FF1, 0x0FF3, 0x0FF4, 
	0x0FF5, 0x0FF7, 0x0FF8, 0x0FF9, 0x0FFA, 0x0FFB, 0x0FFB, 0x0FFC, 0x0FFD, 0x0FFD, 0x0FFE, 0x0FFE, 0x0FFE, 0x0FFF, 0x0FFF, 0x0FFF, 
	0x0FFF, 0x0FFF, 0x0FFF, 0x0FFF, 0x0FFE, 0x0FFE, 0x0FFD, 0x0FFD, 0x0FFC, 0x0FFC, 0x0FFB, 0x0FFA, 0x0FF9, 0x0FF8, 0x0FF7, 0x0FF6, 
	0x0FF5, 0x0FF4, 0x0FF2, 0x0FF1, 0x0FEF, 0x0FEE, 0x0FEC, 0x0FEA, 0x0FE8, 0x0FE6, 0x0FE4, 0x0FE2, 0x0FE0, 0x0FDE, 0x0FDC, 0x0FD9, 
	0x0FD7, 0x0FD4, 0x0FD2, 0x0FCF, 0x0FCC, 0x0FCA, 0x0FC7, 0x0FC4, 0x0FC1, 0x0FBE, 0x0FBA, 0x0FB7, 0x0FB4, 0x0FB0, 0x0FAD, 0x0FA9, 
	0x0FA6, 0x0FA2, 0x0F9E, 0x0F9A, 0x0F96, 0x0F92, 0x0F8E, 0x0F8A, 0x0F86, 0x0F82, 0x0F7D, 0x0F79, 0x0F74, 0x0F70, 0x0F6B, 0x0F66, 
	0x0F62, 0x0F5D, 0x0F58, 0x0F53, 0x0F4E, 0x0F49, 0x0F43, 0x0F3E, 0x0F39, 0x0F33, 0x0F2E, 0x0F28, 0x0F23, 0x0F1D, 0x0F17, 0x0F11, 
	0x0F0B, 0x0F05, 0x0EFF, 0x0EF9, 0x0EF3, 0x0EED, 0x0EE6, 0x0EE0, 0x0EDA, 0x0ED3, 0x0ECC, 0x0EC6, 0x0EBF, 0x0EB8, 0x0EB1, 0x0EAB, 
	0x0EA4, 0x0E9C, 0x0E95, 0x0E8E, 0x0E87, 0x0E80, 0x0E78, 0x0E71, 0x0E69, 0x0E62, 0x0E5A, 0x0E53, 0x0E4B, 0x0E43, 0x0E3B, 0x0E33, 
	0x0E2B, 0x0E23, 0x0E1B, 0x0E13, 0x0E0B, 0x0E03, 0x0DFA, 0x0DF2, 0x0DE9, 0x0DE1, 0x0DD8, 0x0DD0, 0x0DC7, 0x0DBE, 0x0DB6, 0x0DAD, 
	0x0DA4, 0x0D9B, 0x0D92, 0x0D89, 0x0D80, 0x0D77, 0x0D6E, 0x0D64, 0x0D5B, 0x0D52, 0x0D48, 0x0D3F, 0x0D35, 0x0D2C, 0x0D22, 0x0D18, 
	0x0D0F, 0x0D05, 0x0CFB, 0x0CF1, 0x0CE7, 0x0CDD, 0x0CD3, 0x0CC9, 0x0CBF, 0x0CB5, 0x0CAB, 0x0CA1, 0x0C96, 0x0C8C, 0x0C82, 0x0C77, 
	0x0C6D, 0x0C62, 0x0C58, 0x0C4D, 0x0C43, 0x0C38, 0x0C2D, 0x0C22, 0x0C18, 0x0C0D, 0x0C02, 0x0BF7, 0x0BEC, 0x0BE1, 0x0BD6, 0x0BCB, 
	0x0BC0, 0x0BB5, 0x0BAA, 0x0B9F, 0x0B93, 0x0B88, 0x0B7D, 0x0B71, 0x0B66, 0x0B5B, 0x0B4F, 0x0B44, 0x0B38, 0x0B2D, 0x0B21, 0x0B16, 
	0x0B0A, 0x0AFE, 0x0AF3, 0x0AE7, 0x0ADB, 0x0ACF, 0x0AC4, 0x0AB8, 0x0AAC, 0x0AA0, 0x0A94, 0x0A88, 0x0A7C, 0x0A70, 0x0A64, 0x0A58, 
	0x0A4C, 0x0A40, 0x0A34, 0x0A28, 0x0A1C, 0x0A10, 0x0A04, 0x09F8, 0x09EB, 0x09DF, 0x09D3, 0x09C7, 0x09BA, 0x09AE, 0x09A2, 0x0995, 
	0x0989, 0x097D, 0x0970, 0x0964, 0x0958, 0x094B, 0x093F, 0x0932, 0x0926, 0x091A, 0x090D, 0x0901, 0x08F4, 0x08E8, 0x08DB, 0x08CF, 
	0x08C2, 0x08B6, 0x08A9, 0x089D, 0x0890, 0x0883, 0x0877, 0x086A, 0x085E, 0x0851, 0x0845, 0x0838, 0x082C, 0x081F, 0x0812, 0x0806, 
	0x07F9, 0x07ED, 0x07E0, 0x07D3, 0x07C7, 0x07BA, 0x07AE, 0x07A1, 0x0795, 0x0788, 0x077C, 0x076F, 0x0762, 0x0756, 0x0749, 0x073D, 
	0x0730, 0x0724, 0x0717, 0x070B, 0x06FE, 0x06F2, 0x06E5, 0x06D9, 0x06CD, 0x06C0, 0x06B4, 0x06A7, 0x069B, 0x068F, 0x0682, 0x0676, 
	0x066A, 0x065D, 0x0651, 0x0645, 0x0638, 0x062C, 0x0620, 0x0614, 0x0607, 0x05FB, 0x05EF, 0x05E3, 0x05D7, 0x05CB, 0x05BF, 0x05B3, 
	0x05A7, 0x059B, 0x058F, 0x0583, 0x0577, 0x056B, 0x055F, 0x0553, 0x0547, 0x053B, 0x0530, 0x0524, 0x0518, 0x050C, 0x0501, 0x04F5, 
	0x04E9, 0x04DE, 0x04D2, 0x04C7, 0x04BB, 0x04B0, 0x04A4, 0x0499, 0x048E, 0x0482, 0x0477, 0x046C, 0x0460, 0x0455, 0x044A, 0x043F, 
	0x0434, 0x0429, 0x041E, 0x0413, 0x0408, 0x03FD, 0x03F2, 0x03E7, 0x03DD, 0x03D2, 0x03C7, 0x03BC, 0x03B2, 0x03A7, 0x039D, 0x0392, 
	0x0388, 0x037D, 0x0373, 0x0369, 0x035E, 0x0354, 0x034A, 0x0340, 0x0336, 0x032C, 0x0322, 0x0318, 0x030E, 0x0304, 0x02FA, 0x02F0, 
	0x02E7, 0x02DD, 0x02D3, 0x02CA, 0x02C0, 0x02B7, 0x02AD, 0x02A4, 0x029B, 0x0291, 0x0288, 0x027F, 0x0276, 0x026D, 0x0264, 0x025B, 
	0x0252, 0x0249, 0x0241, 0x0238, 0x022F, 0x0227, 0x021E, 0x0216, 0x020D, 0x0205, 0x01FC, 0x01F4, 0x01EC, 0x01E4, 0x01DC, 0x01D4, 
	0x01CC, 0x01C4, 0x01BC, 0x01B4, 0x01AC, 0x01A5, 0x019D, 0x0196, 0x018E, 0x0187, 0x017F, 0x0178, 0x0171, 0x016A, 0x0163, 0x015B, 
	0x0154, 0x014E, 0x0147, 0x0140, 0x0139, 0x0133, 0x012C, 0x0125, 0x011F, 0x0119, 0x0112, 0x010C, 0x0106, 0x0100, 0x00FA, 0x00F4, 
	0x00EE, 0x00E8, 0x00E2, 0x00DC, 0x00D7, 0x00D1, 0x00CC, 0x00C6, 0x00C1, 0x00BC, 0x00B6, 0x00B1, 0x00AC, 0x00A7, 0x00A2, 0x009D, 
	0x0099, 0x0094, 0x008F, 0x008B, 0x0086, 0x0082, 0x007D, 0x0079, 0x0075, 0x0071, 0x006D, 0x0069, 0x0065, 0x0061, 0x005D, 0x0059, 
	0x0056, 0x0052, 0x004F, 0x004B, 0x0048, 0x0045, 0x0041, 0x003E, 0x003B, 0x0038, 0x0035, 0x0033, 0x0030, 0x002D, 0x002B, 0x0028, 
	0x0026, 0x0023, 0x0021, 0x001F, 0x001D, 0x001B, 0x0019, 0x0017, 0x0015, 0x0013, 0x0011, 0x0010, 0x000E, 0x000D, 0x000B, 0x000A, 
	0x0009, 0x0008, 0x0007, 0x0006, 0x0005, 0x0004, 0x0003, 0x0003, 0x0002, 0x0002, 0x0001, 0x0001, 0x0000, 0x0000, 0x0000, 0x0000, 
	0x0000, 0x0000, 0x0000, 0x0001, 0x0001, 0x0001, 0x0002, 0x0002, 0x0003, 0x0004, 0x0004, 0x0005, 0x0006, 0x0007, 0x0008, 0x000A, 
	0x000B, 0x000C, 0x000E, 0x000F, 0x0011, 0x0012, 0x0014, 0x0016, 0x0018, 0x001A, 0x001C, 0x001E, 0x0020, 0x0022, 0x0024, 0x0027, 
	0x0029, 0x002C, 0x002E, 0x0031, 0x0034, 0x0037, 0x003A, 0x003D, 0x0040, 0x0043, 0x0046, 0x0049, 0x004D, 0x0050, 0x0054, 0x0057, 
	0x005B, 0x005F, 0x0063, 0x0067, 0x006B, 0x006F, 0x0073, 0x0077, 0x007B, 0x007F, 0x0084, 0x0088, 0x008D, 0x0092, 0x0096, 0x009B, 
	0x00A0, 0x00A5, 0x00AA, 0x00AF, 0x00B4, 0x00B9, 0x00BE, 0x00C4, 0x00C9, 0x00CE, 0x00D4, 0x00DA, 0x00DF, 0x00E5, 0x00EB, 0x00F1, 
	0x00F7, 0x00FD, 0x0103, 0x0109, 0x010F, 0x0115, 0x011C, 0x0122, 0x0129, 0x012F, 0x0136, 0x013D, 0x0143, 0x014A, 0x0151, 0x0158, 
	0x015F, 0x0166, 0x016D, 0x0174, 0x017C, 0x0183, 0x018A, 0x0192, 0x0199, 0x01A1, 0x01A9, 0x01B0, 0x01B8, 0x01C0, 0x01C8, 0x01D0, 
	0x01D8, 0x01E0, 0x01E8, 0x01F0, 0x01F8, 0x0201, 0x0209, 0x0211, 0x021A, 0x0222, 0x022B, 0x0233, 0x023C, 0x0245, 0x024E, 0x0257, 
	0x0260, 0x0268, 0x0271, 0x027B, 0x0284, 0x028D, 0x0296, 0x029F, 0x02A9, 0x02B2, 0x02BC, 0x02C5, 0x02CF, 0x02D8, 0x02E2, 0x02EC, 
	0x02F5, 0x02FF, 0x0309, 0x0313, 0x031D, 0x0327, 0x0331, 0x033B, 0x0345, 0x034F, 0x0359, 0x0364, 0x036E, 0x0378, 0x0383, 0x038D, 
	0x0397, 0x03A2, 0x03AD, 0x03B7, 0x03C2, 0x03CC, 0x03D7, 0x03E2, 0x03ED, 0x03F8, 0x0402, 0x040D, 0x0418, 0x0423, 0x042E, 0x0439, 
	0x0445, 0x0450, 0x045B, 0x0466, 0x0471, 0x047D, 0x0488, 0x0493, 0x049F, 0x04AA, 0x04B6, 0x04C1, 0x04CD, 0x04D8, 0x04E4, 0x04EF, 
	0x04FB, 0x0507, 0x0512, 0x051E, 0x052A, 0x0535, 0x0541, 0x054D, 0x0559, 0x0565, 0x0571, 0x057D, 0x0589, 0x0595, 0x05A1, 0x05AD, 
	0x05B9, 0x05C5, 0x05D1, 0x05DD, 0x05E9, 0x05F5, 0x0601, 0x060E, 0x061A, 0x0626, 0x0632, 0x063E, 0x064B, 0x0657, 0x0663, 0x0670, 
	0x067C, 0x0688, 0x0695, 0x06A1, 0x06AE, 0x06BA, 0x06C6, 0x06D3, 0x06DF, 0x06EC, 0x06F8, 0x0705, 0x0711, 0x071E, 0x072A, 0x0737, 
	0x0743, 0x0750, 0x075C, 0x0769, 0x0775, 0x0782, 0x078E, 0x079B, 0x07A7, 0x07B4, 0x07C1, 0x07CD, 0x07DA, 0x07E6, 0x07F3, 0x07FF, 

};




static audio_t sound_list[SOUND_COUNT] __unused= {
	{.sound_name = "theremin",	.data = sound_theremin,		.len = SOUND_LEN,},
	{.sound_name = "cello",		.data = sound_cello,		.len = SOUND_LEN,},
	{.sound_name = "test0",		.data = sound_test0,		.len = SOUND_LEN,},
	{.sound_name = "sine",		.data = sound_sine,			.len = SOUND_LEN,},
};




#endif // __AUDIO__
