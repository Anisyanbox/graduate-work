#include "gui_func.h"
#include "video_buffer.h"
#include <stdint.h>

// -----------------------------------------------------------------------------
void GuiDrawMainWindow(void) {
  uint32_t * video_buf = GetVideoBufferAddr();
  uint32_t buf_size = GetVideoBufferSizeInWords();

  for (uint32_t i = 0; i < buf_size; ++i) {
    *(video_buf + i) = 0xffffffff;
  }
}
