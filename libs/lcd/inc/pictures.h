#ifndef _INC_PICTURES_H_
#define _INC_PICTURES_H_

#include <string.h> // for size_t type
#include <stdint.h>

//
// Func return size of one picture line in pixels
//
// 'picture_data' - pointer to array with rgb565 value
// 1 pixel == 1 elemant of 'picture_data' array
//
// 'pixels_cnt' - real pixels count of imagine are saved in this pointer
//
size_t GetVideoIconArray(uint16_t ** picture_data, size_t * pixels_cnt);
size_t GetMusicIconArray(uint16_t ** picture_data, size_t * pixels_cnt);
size_t GetMicrophoneIconArray(uint16_t ** picture_data, size_t * pixels_cnt);
 
#endif  // _INC_PICTURES_H_
